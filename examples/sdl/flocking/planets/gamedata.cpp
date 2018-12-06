#include <sstream>
#include <limits>
#include <cmath>
#include "gamedata.h"
#include "collisionStrategy.h"

Gamedata& Gamedata::getInstance() {
  static Gamedata gamedata;
  return gamedata;
}

Gamedata::~Gamedata( ) {
  for (unsigned int i = 0; i < strategies.size(); ++i) {
    delete strategies[i];
  }
}

Gamedata::Gamedata(const string& fn ) :
  parser(fn),
  strategy( NULL ),
  strategyString(),
  strategies(),
  gameData(parser.getXmlData())
{ 
  strategies.push_back( new MidPointCollisionStrategy );
  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  setStrategy( getXmlInt("collisionStrategy") );
}

void Gamedata::setStrategy(int n) {
  strategy = strategies[n];
  if ( n == 0 ) strategyString = "Midpoint";
  if ( n == 1 ) strategyString = "Rectangular";
  if ( n == 2 ) strategyString = "Per Pixel";
}

// The next method was contributed by Matt Dabney
const int DIRECTION_MOD = 100;
const int MAX_EXPLOSION_SPD = 200;
const int MIN_EXPLOSION_SPD = 40;
Vector2f Gamedata::getNewVelocity() const {
  float x_dir = (rand() % DIRECTION_MOD) * (rand()%2?-1:1);
  float y_dir = (rand() % DIRECTION_MOD) * (rand()%2?-1:1);
  if (fabs(x_dir) < 0.001 && fabs(y_dir) < 0.001) {
    x_dir += rand()%2?-1:1;
    y_dir += rand()%2?-1:1;
  }
  Vector2f velocity(x_dir, y_dir);   
  velocity = velocity.normalize();   
  int speed = (rand() % (MAX_EXPLOSION_SPD - MIN_EXPLOSION_SPD)) 
              + MIN_EXPLOSION_SPD;

  velocity *= speed;
  return velocity;
}

float Gamedata::getRandInRange(int min, int max) const {
  return min + (rand()/(std::numeric_limits<int>::max()+1.0f))*(max-min);
}

float Gamedata::getRandFloat(float min, float max) const {
  return min + (rand() / (RAND_MAX + 1.0f)) * (max - min);
}

bool Gamedata::getXmlBool(const string& tag) const {
  std::map<string, string>::const_iterator ptr = gameData.find(tag);
  if ( ptr == gameData.end() )
    throw string("Game: Didn't find boolean tag ")+tag+string(" in xml");
  else {
    if ( ptr->second == "true" ) return true;
    else return false;
  }
}

int Gamedata::getXmlInt(const string& tag) const {
  std::map<string, string>::const_iterator ptr = gameData.find(tag);
  if ( ptr == gameData.end() )
    throw string("Game: Didn't find integer tag ")+tag+string(" in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    int data;
    strm >> data;
    return data;
  }
}

float Gamedata::getXmlFloat(const string& tag) const {
  std::map<string, string>::const_iterator ptr = gameData.find(tag);
  if ( ptr == gameData.end() )
    throw string("Game: Didn't find float tag ")+tag+string(" in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    float data;
    strm >> data;
    return data;
  }
}

const string& Gamedata::getXmlStr(const string& tag) const {
  std::map<string, string>::const_iterator ptr = gameData.find(tag);
  if ( ptr == gameData.end() )
    throw string("Game: Didn't find string tag ")+tag+string(" in xml");
  else return ptr->second;
}

void Gamedata::displayData() const {
  std::map<string, string>::const_iterator ptr = gameData.begin();
  while ( ptr != gameData.end() ) {
    cout << ptr->first << ", " << ptr->second << endl;
    ++ptr;
  }
}


