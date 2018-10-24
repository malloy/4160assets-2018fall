#!/usr/bin/python
'''
  This observer pattern example was originally obtained at:
  http://beej.us/blog/data/observer-pattern/
  This example was modified by Brian Malloy
'''
import sys

# ----------------------------------------------------------------
class Subject(object):
  """
    A class of thing that can be observed.  When its notifyObservers()
    method is called with an event, it passes that event on to its
    observers.
  """
  def __init__(self):
    self.observerList = []
  def attach(self, observer):
    self.observerList.append(observer)
  def detach(self, observer): pass
  def notifyObservers(self, event):
    for observer in self.observerList:
      observer.observeEvent(event)
    
# ----------------------------------------------------------------
class Observer(object):
  """
    A class of thing that observes a Subject. The Subject calls
    the Observer's observeEvent() method if it observes an event.
  """
  def __init__(self, name):
    self.name = name
  def observeEvent(self, event):
    sys.stdout.write('=== %s: "%s"\n' % (self.name, event))


# ----------------------------------------------------------------
class GoatDetector(Subject):
  """
    This class notifies its observers if a string contains the word 'goat'.
  """
  def detect(self, line):
    if line.find('goat') >= 0:
      self.notifyObservers('goats detected')

# ----------------------------------------------------------------
class DuckDetector(Subject):
  """
    This class notifies its observers if a string contains the word 'duck'.
  """
  def detect(self, line):
    if line.find('duck') >= 0:
      self.notifyObservers('ducks detected')
        
if __name__ == "__main__":
  goatD = GoatDetector()
  duckD = DuckDetector()
  
  alice = Observer('Alice')
  bert = Observer('Bert')
  chris = Observer('Chris')

  goatD.attach(alice)
  goatD.attach(bert)
  duckD.attach(chris)

  line = raw_input("Type a line: ")
  while line:
    goatD.detect(line)
    duckD.detect(line)    
    line = raw_input("Type a line: ")
