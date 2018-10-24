// This example is shamelessly taken from:
// http://sourcemaking.com/design_patterns/observer/cpp/1
#include <vector>
#include <iostream>

class Observer {
public:
  virtual ~Observer(){}
  virtual void notify(int value) = 0;
};

class Subject {
public:
  Subject() : value(0), observers() {}
  void attach(Observer *obs) {
    observers.push_back(obs);
  }
  void setVal(int v) {
    value = v;
    notifyObservers();
  }
  void notifyObservers() {
    for (unsigned i = 0; i < observers.size(); ++i) {
      observers[i]->notify(value);
    }
  }
private:
  int value;
  std::vector<Observer*> observers;
};

class DivObserver: public Observer {
public:
  DivObserver(Subject *subject, int d) : div(d) {
    subject->attach(this);
    div = d;
  }
  void notify(int v) {
    std::cout << v << " div " << div << " is " << v / div << std::endl;
  }
private:
  int div;
};

class ModObserver: public Observer {
public:
  ModObserver(Subject *model, int m) : mod(m) {
    model->attach(this);
  }
  void notify(int v) {
    std::cout << v << " mod " << mod << " is " << v % mod << std::endl;
  }
private:
  int mod;
};

int main() {
  Subject subj;
  DivObserver divObs1(&subj, 4);
  DivObserver divObs2(&subj, 3);
  ModObserver modObs3(&subj, 3);
  subj.setVal(14);
}

