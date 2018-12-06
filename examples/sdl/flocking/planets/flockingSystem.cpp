#include "gamedata.h"
#include "flockingSystem.h"
#include "kaceyMultisprite.h"
#include <math.h>
float FlockingSystem::EPSILON=0.001f;
FlockingSystem::FlockingSystem(const std::string &name) :
 
cohesion_roi(Vector2f(Gamedata::getInstance().getXmlFloat(name+"cohesion_roiX"), Gamedata::getInstance().getXmlFloat(name+"cohesion_roiY"))), 
separation_roi(Vector2f(Gamedata::getInstance().getXmlFloat(name+"separation_roiX"),Gamedata::getInstance().getXmlFloat(name+"separation_roiY"))), 
alignment_roi(Vector2f(Gamedata::getInstance().getXmlFloat(name+"alignment_roiX"),Gamedata::getInstance().getXmlFloat(name+"alignment_roiY"))), 
Ka(Gamedata::getInstance().getXmlFloat(name+"avoidance")), 
Kv(Gamedata::getInstance().getXmlFloat(name+"velocityMatch")), 
Kc(Gamedata::getInstance().getXmlFloat(name+"centering")), 
m(Gamedata::getInstance().getXmlFloat(name+"mass")), 
amax(Vector2f( Gamedata::getInstance().getXmlFloat(name+"maxAccelX"), 
	Gamedata::getInstance().getXmlFloat(name+"maxAccelY"))), 
boids(),
timestep(Gamedata::getInstance().getXmlFloat(name+"TimeStep"))
 {
	Vector2f randPosOff(Gamedata::getInstance().getXmlFloat(name+"RandPosOffX"), Gamedata::getInstance().getXmlFloat(name+"RandPosOffY"));
	Vector2f randVelOff(Gamedata::getInstance().getXmlFloat(name+"RandVelOffX"), Gamedata::getInstance().getXmlFloat(name+"RandVelOffY"));
	unsigned int numBoids = Gamedata::getInstance().getXmlInt(name+"numberOfBoids");
	std::string spriteName = Gamedata::getInstance().getXmlStr(name+"Sprite");
	boids.reserve(numBoids);
	for (unsigned int i = 0; i < numBoids; ++i) {
		boids.push_back(new KaceyMultisprite(spriteName, 
      Vector2f(randPosOff.X()+rand()%100, randPosOff.Y()+rand()%100), 
      Vector2f(randVelOff.X(), randVelOff.Y()))
    );
	}
}

FlockingSystem::
FlockingSystem(const std::string &name, const unsigned int &numBoids, 
               const float &mass, const Vector2f &coh_roi, 
               const Vector2f &sep_roi, const Vector2f &align_roi, 
               const float &avoid, const float &velMatch, 
               const float &center, const Vector2f &maxAccel, 
               const Vector2f &randPosOff, const Vector2f &randVelOff, 
               const float &ts) : 
  cohesion_roi(coh_roi), 
  separation_roi(sep_roi), 
  alignment_roi(align_roi), 
  Ka(avoid), Kv(velMatch), Kc(center), 
  m(mass), amax(maxAccel), boids(), timestep(ts) 
{
	boids.reserve(Gamedata::getInstance().getXmlInt(name+"numberOfBoids"));
	for (unsigned int i = 0; i < numBoids; ++i) {
		boids.push_back(
      new KaceyMultisprite(name, 
        Vector2f(randPosOff.X(), randPosOff.Y()), 
        Vector2f(randVelOff.X(), randVelOff.Y()))
      );
	}
}

void FlockingSystem::update(const Uint32 ticks) {
		Vector2f accelS, accelC, accelA;
		std::vector<Vector2f> vel;
		vel.reserve(boids.size());

		unsigned int index = 0;
	for (std::vector<Drawable*>::iterator iter = boids.begin(); 
		iter != boids.end(); ++iter) {
		accelS = separation(*iter);
		accelC = cohesion(*iter);
		accelA = alignment(*iter);
		//apply the acceleration to the current boid using Euler integration
		Vector2f accel = accelS + accelC + accelA;
		accel[0] = fmin(accel.X(), amax.X());
		accel[1] = fmin(accel.Y(), amax.Y());
		vel[index++] = (*iter)->getVelocity() + 0.01f * (accelS + accelC + accelA);
	}
	index = 0;
	for (std::vector<Drawable*>::iterator iter = boids.begin();
		iter != boids.end(); ++iter) {
			(*iter)->setVelocity(vel[index++]);
			(*iter)->update(ticks);
		}

}
std::vector<Drawable*> FlockingSystem::getBoidList() const {
	std::vector<Drawable*> listing;
	for (std::vector<Drawable*>::const_iterator iter = boids.begin();
		iter != boids.end(); ++iter) {
		listing.push_back(*iter);
	}
	return listing;
}
void FlockingSystem::draw() const{
	for (std::vector<Drawable*>::const_iterator iter = boids.begin();
		iter != boids.end(); ++iter) {
		(*iter)->draw();
	}
}
float FlockingSystem::
influence(const float &distance, const float &r1, const float &r2) {
	float result = 0.0f;
	if (distance > r1 && distance <= r2)
		result = 1.0f - (distance - r1)/(r2 - r1);
	else if (distance < r1)
		result = 1.0f;
	return result;

}

// Velocity Matching
Vector2f FlockingSystem::cohesion(const Drawable* boid) {
	Vector2f aij;
	for (size_t i = 0; i < boids.size(); ++i) {
			if (boid != boids[i]) {
				Vector2f Xij = (boids[i]->getPosition() - boid->getPosition());
				if (fabs(Xij.X()) > EPSILON && fabs(Xij.Y()) > EPSILON) {
					float dij = Xij.magnitude();
					aij += influence(dij, cohesion_roi[0], cohesion_roi[1])/m * Kv * (boids[i]->getVelocity() - boid->getVelocity());
				}
			}
	}
	return aij;
}

// Avoidance 
Vector2f FlockingSystem::separation(const Drawable* boid) {
	Vector2f aij;
	for (size_t i = 0; i < boids.size(); ++i) {
			if (boid != boids[i]) {
				Vector2f Xij = (boids[i]->getPosition() - boid->getPosition());
				if (fabs(Xij.X()) > EPSILON && fabs(Xij.Y()) > EPSILON) {
					float dij = Xij.magnitude();
					Vector2f Uij = Xij.normalize();
					aij += -influence(dij, separation_roi[0], separation_roi[1])/m * Ka/dij  * Uij;
				}
			}
	}

	return aij;
}
// Centering 
Vector2f FlockingSystem::alignment(const Drawable *boid) {
	Vector2f aij;
	for (size_t i = 0; i < boids.size(); ++i) {
			if (boid != boids[i]) {
				Vector2f Xij = (boids[i]->getPosition() - boid->getPosition());
				if (Xij.X() > EPSILON && Xij.Y() > EPSILON) {
					float dij = Xij.magnitude();
					Vector2f Uij = Xij.normalize();
					aij += influence(dij, alignment_roi[0], alignment_roi[1])/m * Kc*dij  * Uij;
				}
			}
	}
	return aij;
}
