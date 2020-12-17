#pragma once

#include "utils.h"

using namespace std;
using namespace sf;

class Fluid
{
public:
	Fluid();
	Fluid(float const&, float const&, float const&, float const&, float const&, float const&, float const&);

	void update(float const&);
	
	void reset();

	Sprite get_speed_sprite();
	Sprite get_density_sprite();
	Sprite get_pressure_sprite();
	Sprite get_wall_sprite();
	Sprite get3DSprite();

	void add_density(Vector2f, float, float);
	void set_wall(Vector2f const&, float const&, int const&);
	void add_pressure(Vector2f const&, float const&, float const&);
	void add_speed(Vector2f, Vector2f, Vector2f);
	void draw_speed_field(RenderWindow &, float const&, Color const&) const;

	Sprite get_temperature_sprite();
	void add_temperature(Vector2f const&, float const&, float const&);
	
private:
	int width;
	int height;
	float scale;

	float rho; 
	float k;
	float buoyancy_fctr;
	float L;
	float ambient_tpr;

	Matrix u;
	Matrix u_pred;
	Matrix v;
	Matrix v_pred;
	Matrix p;
	Matrix walls;
	Matrix density;
	Matrix density_pred;

	Matrix temperature;
	Matrix temperature_pred;

	Image image; 
	Texture texture;
	Sprite sprite;

	Image posPressureColor; 
	Image negPressureColor; 
	Image temperatureColor; 
	Image speedColor;
	Image densityColor;

	float pressure_scale;
	float viscosity_scale;
	float temperature_scale;
};

