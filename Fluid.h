#pragma once

#include "utils.h"

using namespace std ;
using namespace sf ;

class Fluid
{
public:
	Fluid() ;
	Fluid(float const& _width, float const& _height, float const& _rho, float const& _k, float const& _buoyancyFactor, float const& _L, float const& _scale) ;

	void Update(float const& dt) ;

	Sprite getPressureSprite() ; 
	Sprite getTemperatureSprite() ;
	Sprite getSpeedSprite() ;
	Sprite getDensitySprite() ;
	Sprite getWallSprite() ;
	Sprite get3DSprite() ;
	
	void Reset() ;

	void drawSpeedField(RenderWindow &window, float const& size, Color const& color) const ;

	int getWidth() const ;
	int getHeight() const ;
	float getScale() const ;
	Matrix getP() const ;

	void setWallZone(Vector2f const& pos, float const& size, int const& on) ;
	void addPressureZone(Vector2f const& pos, float const& size, float const& _p) ;
	void addTemperatureZone(Vector2f const& pos, float const& size, float const& _T) ;
	void addSpeedZone(Vector2f pos, Vector2f size, Vector2f speed) ;
	void addDensityZone(Vector2f pos, float size, float _density) ;
	
private:
	int width ;
	int height ;
	float rho ; 
	float k ;
	float buoyancyFactor ;
	float L ;
	float ambientTemperature ;
	Matrix u ;
	Matrix v ;
	Matrix u0 ;
	Matrix v0 ;
	Matrix p ;
	Matrix wall ;
	Matrix T ;
	Matrix T0 ;
	Matrix density ;
	Matrix density0 ;

	Image image ; 
	Texture texture ;
	Sprite sprite ;

	Image posPressureColor ; 
	Image negPressureColor ; 
	Image temperatureColor ; 
	Image speedColor ;
	Image densityColor ;

	float pScale ;
	float vScale ;
	float tScale ;
	
	float scale ;
};

