// This class was contributed by Kacey Coley, Dec 2012

#include <vector>
#include "drawable.h"
class FlockingSystem {
public:
	FlockingSystem(const std::string &name);	
	FlockingSystem(const std::string &name, const unsigned int &numBoids,
           const float &mass, const Vector2f &coh_roi, const Vector2f &sep_roi, 
           const Vector2f &align_roi, const float &avoid, const float &velMatch,                 const float &center, const Vector2f &maxAccel, const Vector2f &randPosOff, const Vector2f &randVelOff, const float &ts);
	void update(const Uint32 ticks);
	void draw() const;
	std::vector<Drawable*> getBoidList() const;
  Drawable* getFirstBoid() const { return boids[0]; }
	float getCohesionValue() const { return Kv; }
	float getSeparationValue() const { return Ka; }
	float getAlignmentValue() const { return Kc; }
private:
	float influence(const float &distance, const float &r1, const float &r2);
	Vector2f cohesion(const Drawable*); // used for velocity matching
	Vector2f separation(const Drawable*); // used for avoidance
	Vector2f alignment(const Drawable*); //  used for centering
	Vector2f cohesion_roi;
	Vector2f separation_roi;
	Vector2f alignment_roi;
	float Ka, Kv, Kc;
	float m;
	Vector2f amax;
	std::vector<Drawable*> boids;
	float timestep;
	static float EPSILON;
};
