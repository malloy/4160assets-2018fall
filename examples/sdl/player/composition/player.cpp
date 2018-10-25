#include "player.h"
#include "gamedata.h"


Player::Player( const std::string& name) :
  player(name),
  initialVelocity(player.getVelocity()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

void Player::stop() { 
  //player.setVelocity( Vector2f(0, 0) );
  player.setVelocityX( 0.93*player.getVelocityX() );
  player.setVelocityY(0);
}

void Player::right() { 
  if ( player.getX() < worldWidth-getScaledWidth()) {
    player.setVelocityX(initialVelocity[0]);
  }
} 
void Player::left()  { 
  if ( player.getX() > 0) {
    player.setVelocityX(-initialVelocity[0]);
  }
} 
void Player::up()    { 
  if ( player.getY() > 0) {
    player.setVelocityY( -initialVelocity[1] );
  }
} 
void Player::down()  { 
  if ( player.getY() < worldHeight-getScaledHeight()) {
    player.setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) { 
  player.update(ticks);
  stop();
}
