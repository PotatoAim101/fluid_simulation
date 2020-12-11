#pragma once

#include "utils.h"

using namespace std;
using namespace sf;

class Particle {
/*attributes*/	
private:
	float mass;

	vector<Vector2f> applied_forces; // all forces applied to particle
	Vector2f position; // 2D position
	Vector2f speed; // speed v= ( x(t+dt) - x(t) ) / dt
	Vector2f acc; // acceleration a= ( v(t+dt) - v(t) ) / dt
	
public:
	/*public attribut*/
	bool sleeping;

	/*methods*/
	Particle();
	Particle(float m, Vector2f p, Vector2f s);

	float getMass() const;
	void setMass(float m);
	vector<Vector2f> getForces() const;
	Vector2f getTotalForce() const;
	void addForce(Vector2f f);
	void clearForce();
	Vector2f getPosition() const;
	void setPosition(Vector2f p);
	Vector2f getSpeed() const;
	void setSpeed(Vector2f s);
	Vector2f getAcceleration() const;
	void setAcceleration(Vector2f a);
	void sleep();
	void wake();
	bool isSleeping() const;

	void update(float dt);
};
