#ifndef GAMEDATA__H
#define GAMEDATA__H
#include <string>
#include <map>
#include <vector>
#include "vector2f.h"
#include "parseXML.h"

class CollisionStrategy;
class Gamedata {
public:
  static Gamedata& getInstance();
  ~Gamedata();
  void displayData() const;

  bool getXmlBool(const std::string&) const;
  const std::string& getXmlStr(const std::string&) const;
  float getXmlFloat(const std::string&) const;
  int getXmlInt(const std::string&) const;
  float getRandInRange(int min, int max) const;
  float getRandFloat(float min, float max) const;
  Vector2f getNewVelocity() const;

  CollisionStrategy* getStrategy() const { return strategy; }
  const std::string& getStrategyString() const { return strategyString; }
  void setStrategy(int n);
private:
  ParseXML parser;
  CollisionStrategy* strategy;
  std::string strategyString;
  std::vector<CollisionStrategy*> strategies;
  const map<std::string, std::string> gameData;


  Gamedata(const std::string& fn = "xmlSpec/game.xml");
  Gamedata(const Gamedata&);
  Gamedata& operator=(const Gamedata&);
};
#endif
