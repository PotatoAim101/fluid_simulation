#include "Particle.h"

Particle::Particle() {
	mass = 50;
	position = Vector2f(50,50);
	speed = Vector2f(0,0);
	acc = Vector2f(0,0);
	sleeping = false;
}

Particle::Particle(float m, Vector2f p, Vector2f s) {
	mass = m;
	position = p;
	speed = s;
	acc = Vector2f(0,0);
	sleeping = false;
}

float Particle::getMass() const {
	return mass;
}

void Particle::setMass(float m) {
	mass=m;
}

vector<Vector2f> Particle::getForces() const {
	return applied_forces;
}

Vector2f Particle::getTotalForce() const {
	Vector2f res(0,0);
	for(int i(0); i < applied_forces.size(); i++)
	{
		res += applied_forces[i];
	}
	return res;
}

void Particle::addForce(Vector2f f) {
	applied_forces.push_back(f);
}

void Particle::clearForce() {
	applied_forces.clear();
}

Vector2f Particle::getPosition() const {
	return position;
}

void Particle::setPosition(Vector2f p) {
	position = position;
}

Vector2f Particle::getSpeed() const {
	return speed;
}

void Particle::setSpeed(Vector2f s) {
	speed = s;
}

Vector2f Particle::getAcceleration() const {
	return acc;
}

void Particle::setAcceleration(Vector2f a) {
	acc = a;
}

void Particle::sleep() {
	sleeping = true;
}

void Particle::wake() {
	sleeping = false;
}

bool Particle::isSleeping() const {
	return sleeping;
}

void Particle::update(float dt) {
	if(sleeping == false) {
		Vector2f previousPosition = position;
		position = position + speed*dt + 0.5f*getTotalForce()/mass*(float)pow(dt,2);
		speed = (position-previousPosition)/dt;
		clearForce();
	}
}
