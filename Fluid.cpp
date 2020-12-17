#include "Fluid.h"

/* Default constructor */
Fluid::Fluid() {
	/* initializing the numerical values */
	width = 300;
	height = 300;
	scale = 1;
	buoyancy_fctr = 0.001;
	ambient_tpr = 0;
	rho = 10; 
	k = rho*25;
	L=1;
	
	/* picking the right size for the different matrices representing the fluid properties */
	u.resize(width, height);
	v.resize(width, height);
	u_pred.resize(width, height);
	v_pred.resize(width, height);
	pressure.resize(width, height);
	walls.resize(width, height);
	density.resize(width, height); 
	density_pred.resize(width, height);

	
	temperature.resize(width, height);
	temperature_pred.resize(width, height);

	/* Setting the scale in the matrices (scale set in main.cpp to dcode the number of particles) */
	u.setScale(scale);
	v.setScale(scale);
	u_pred.setScale(scale);
	v_pred.setScale(scale);
	pressure.setScale(scale);
	walls.setScale(scale);
	density.setScale(scale);
	density_pred.setScale(scale);
	
	
	temperature.setScale(scale);
	temperature_pred.setScale(scale);


	/* for loops to set all values of density and velocity to 0 and temperature to ambient temperature */
	for(int i(0); i < width; i++)
	{
		for(int j(0); j < height; j++)
		{
			u.setValue(i,j,0);
			v.setValue(i,j,0);
			u_pred.setValue(i,j,0);
			v_pred.setValue(i,j,0);
			pressure.setValue(i,j,0);
			walls.setValue(i,j,0);
			density.setValue(i,j,0);
			density_pred.setValue(i,j,0);

			
			temperature.setValue(i,j,ambient_tpr);
			temperature_pred.setValue(i,j,ambient_tpr);
		}
	}

	/* initialize the simulation space and load the colors for pressur, speed and temperature */
	image.create(width, height,Color::Black);
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	posPressureColor.loadFromFile("pressure+.jpg");
	negPressureColor.loadFromFile("pressure-.jpg");
	speedColor.loadFromFile("speed.jpg");
	densityColor.loadFromFile("density.jpg");

	
	temperatureColor.loadFromFile("color.jpg");
}

/* constructor */
Fluid::Fluid(float _width, float _height, float _rho, float _k, float _buoyancy_fctr, float _L, float _scale) {
	/* initializing the numerical values */
	width = _width;
	height = _height;
	scale = _scale;
	buoyancy_fctr = _buoyancy_fctr;
	ambient_tpr = 0;
	rho = _rho; 
	k = _k;
	L = 2*_L/(width+height);

	/* picking the right size for the different matrices representing the fluid properties */
	u.resize(width, height);
	v.resize(width, height);
	u_pred.resize(width, height); 
	v_pred.resize(width, height);
	pressure.resize(width, height); 
	walls.resize(width, height);
	density.resize(width, height);
	density_pred.resize(width, height);

	
	temperature.resize(width, height); 
	temperature_pred.resize(width, height);
	
	/* Setting the scale in the matrices (scale set in main.cpp to dcode the number of particles) */
	u.setScale(scale);
	v.setScale(scale);
	u_pred.setScale(scale);
	v_pred.setScale(scale);
	pressure.setScale(scale);
	walls.setScale(scale);
	density.setScale(scale);
	density_pred.setScale(scale);


	temperature.setScale(scale);
	temperature_pred.setScale(scale);

	/* for loops to set all values of density and velocity to 0 and temperature to ambient temperature */
	for(int i(0); i <= width; i++)
	{
		for(int j(0); j <= height; j++)
		{
			u.setValue(i,j,0);
			v.setValue(i,j,0);
			u_pred.setValue(i,j,0);
			v_pred.setValue(i,j,0);
			pressure.setValue(i,j,0);
			walls.setValue(i,j,0); if(i<5) walls.setValue(i,j,2); if(i>width-5) walls.setValue(i,j,3); if(j<5) walls.setValue(i,j,4); if(j>height-5) walls.setValue(i,j,5);
			density.setValue(i,j,0);
			density_pred.setValue(i,j,0);

			temperature.setValue(i,j,ambient_tpr);
			temperature_pred.setValue(i,j,ambient_tpr);
		}
	}
	
	/* initialize the simulation space and load the colors for pressur, speed and temperature */
	image.create(width, height,Color::Black);
	texture.loadFromImage(image);
	sprite.setTexture(texture,true);
	sprite.setScale(scale,scale);
	posPressureColor.loadFromFile("pressure+.jpg");
	negPressureColor.loadFromFile("pressure-.jpg");
	speedColor.loadFromFile("speed.jpg");
	densityColor.loadFromFile("density.jpg");

	
	temperatureColor.loadFromFile("color.jpg");

	pressure_scale = 3*60000;
	viscosity_scale = 3*200;
	temperature_scale = 3*350;
	
	scale = _scale;
}

/* Updater function for the simulation */
void Fluid::update(float dt) {
	for(int i(2); i < width-2; i++) {
		for(int j(2); j < height-2; j++) {
			/* most important lines */
			/* They represent how we deal with navier stokes equation and compute fluid properties */
			u.setValue(i,j, u.getValue(i,j) - ( (1/rho)*(pressure.getValue(i+1,j)-pressure.getValue(i-1,j))/(2.f*L))*dt);
			v.setValue(i,j, v.getValue(i,j) - ( (1/rho)*(pressure.getValue(i,j+1)-pressure.getValue(i,j-1))/(2.f*L))*dt);
			
			v.setValue(i,j, v.getValue(i,j) - buoyancy_fctr*(temperature.getValue(i,j)-ambient_tpr)*dt);

			/* This is how we deal with boundaries
			 * 0 --> nothing
			 * 1 --> user walls
			 * 2 --> upper bound
			 * 3 --> lower bound
			 * 4 --> left bound
			 * 5 --> right bound */
			if(walls.getValue(i,j)==1)
			{
				u.setValue(i,j,0);
				v.setValue(i,j,0);
				u_pred.setValue(i,j,0);
				v_pred.setValue(i,j,0);
				density.setValue(i,j,0);
				density_pred.setValue(i,j,0);

				temperature.setValue(i,j,ambient_tpr);
				temperature_pred.setValue(i,j,ambient_tpr);
			}
			if(walls.getValue(i,j)==2)
			{
				u.setValue(i,j,u.getValue(i+1,j));
				v.setValue(i,j,v.getValue(i+1,j));
				u_pred.setValue(i,j,u_pred.getValue(i+1,j));
				v_pred.setValue(i,j,v_pred.getValue(i+1,j));
			}
			if(walls.getValue(i,j)==3)
			{
				u.setValue(i,j,u.getValue(i-1,j));
				v.setValue(i,j,v.getValue(i-1,j));
				u_pred.setValue(i,j,u_pred.getValue(i-1,j));
				v_pred.setValue(i,j,v_pred.getValue(i-1,j));
			}
			if(walls.getValue(i,j)==4)
			{
				u.setValue(i,j,u.getValue(i,j+1));
				v.setValue(i,j,v.getValue(i,j+1));
				u_pred.setValue(i,j,u_pred.getValue(i,j+1));
				v_pred.setValue(i,j,v_pred.getValue(i,j+1));
			}
			if(walls.getValue(i,j)==5)
			{
				u.setValue(i,j,u.getValue(i,j-1));
				v.setValue(i,j,v.getValue(i,j-1));
				u_pred.setValue(i,j,u_pred.getValue(i,j-1));
				v_pred.setValue(i,j,v_pred.getValue(i,j-1));
			}
		}
	}

	/* for loops to update speed, viscosity, density and teperature */
	for(int i(1); i < width-1; i++)
	{
		for(int j(1); j < height-1; j++)
		{
			pressure.setValue(i,j, pressure.getValue(i,j) - k*( (u.getValue(i+1,j)-u.getValue(i-1,j))/(2.f*L)  + (v.getValue(i,j+1)-v.getValue(i,j-1))/(2.f*L) )*dt );

			if(walls.getValue(i,j)!=1)
			{
				float x = i-dt*u.getValue(i,j)/L; 
				float y = j-dt*v.getValue(i,j)/L; 

				if (x<1) x=1; if (x>width-1) x=width-1; int i0=(int)x; int i1=i0+1;
				if (y<1) y=1; if (y>height-1) y=height-1; int j0=(int)y; int j1=j0+1; 
				float s1 = x-i0; float s0 = 1-s1; float t1 = y-j0; float t0 = 1-t1;
				u_pred.setValue(i,j, s0*(t0*u.getValue(i0,j0)+t1*u.getValue(i0,j1)) + s1*(t0*u.getValue(i1,j0)+t1*u.getValue(i1,j1)));
				v_pred.setValue(i,j, s0*(t0*v.getValue(i0,j0)+t1*v.getValue(i0,j1)) + s1*(t0*v.getValue(i1,j0)+t1*v.getValue(i1,j1)));
				density_pred.setValue(i,j, s0*(t0*density.getValue(i0,j0)+t1*density.getValue(i0,j1))+s1*(t0*density.getValue(i1,j0)+t1*density.getValue(i1,j1))); 

				temperature_pred.setValue(i,j, s0*(t0*temperature.getValue(i0,j0)+t1*temperature.getValue(i0,j1))+s1*(t0*temperature.getValue(i1,j0)+t1*temperature.getValue(i1,j1)));
			}
		}
	}
	u=u_pred;
	v=v_pred; 
	density = density_pred;

	temperature=temperature_pred;
}

/* Allows to delete everything from the simulation */
void Fluid::reset() {
	for(int i(1); i < width-1; i++)
	{
		for(int j(1); j < height-1; j++)
		{
			u.setValue(i,j,0);
			v.setValue(i,j,0);
			u_pred.setValue(i,j,0);
			v_pred.setValue(i,j,0);
			pressure.setValue(i,j,0);
			density.setValue(i, j, 0);
			density_pred.setValue(i, j, 0);
			if(walls.getValue(i,j)==1) walls.setValue(i,j,0);

			temperature.setValue(i,j,ambient_tpr);
		}
	}
}

/* Allows to draw the pressure, using the pressure+ and pressure- images, with red for positive pressure and
blue for negative pressure */
Sprite Fluid::get_pressure_sprite() {
	for(int i(1); i < width-1; i++)
		for(int j(1); j < height-1; j++)
			if(pressure.getValue(i,j) > 0 ) image.setPixel(i,j,color_gradient(posPressureColor, pressure.getValue(i,j)/pressure_scale));
			else image.setPixel(i,j,color_gradient(negPressureColor, -pressure.getValue(i,j)/pressure_scale));
	
	texture.loadFromImage(image);
	return sprite;
}

/* Allows to draw speed with the speed colors image */
Sprite Fluid::get_speed_sprite() {
	for(int i(1); i < width-1; i++)
		for(int j(1); j < height-1; j++)
			image.setPixel(i,j,color_gradient(speedColor,sqrt(pow(u.getValue(i,j),2)+pow(v.getValue(i,j),2))/viscosity_scale));
		
	texture.loadFromImage(image);
	return sprite;
}

/* Allows to draw density with the density color images (from white to black) */
Sprite Fluid::get_density_sprite() {
	for(int i(1); i < width-1; i++)
		for(int j(1); j < height-1; j++)
			image.setPixel(i,j,color_gradient(densityColor,density.getValue(i,j)*1.f));
		
	texture.loadFromImage(image);
	return sprite;
}

/* Allows to draw walls drawn by the user */
Sprite Fluid::get_wall_sprite() {
	for(int i(1); i < width-1; i++)
		for(int j(1); j < height-1; j++)
			if(walls.getValue(i,j)==1)
				image.setPixel(i,j,Color(200, 200, 170));
			else if(walls.getValue(i,j)>=2)
				image.setPixel(i,j,Color(100, 100, 120));
			else
				image.setPixel(i,j,Color::Transparent);
	texture.update(image);
	return sprite;
}

/* Allows to draw pressure feilds in a 3D way to show the "waves"*/
Sprite Fluid::get3DSprite() {
	for(int i(1); i < width-1; i++)
		for(int j(1); j < height-1; j++)
			image.setPixel(i,j,Color(u.getValue(i,j)/viscosity_scale*1.4*127.5+127.5,v.getValue(i,j)/viscosity_scale*1.4*127.5+127.5,255.f));

	texture.loadFromImage(image);
	return sprite;
}

/* Allows to add a density to a simulation */
void Fluid::add_density(Vector2f pos, float const& size, float const& d) {
	for(int i((pos.x-size)/scale); i < (pos.x+size)/scale; i++)
		for(int j((pos.y-size)/scale); j < (pos.y+size)/scale; j++)
			if(distance(Vector2f(i,j),pos/scale)<size/scale)
				density.setValue(i,j,d);
}

/* Allows to add walls to a simulation */
void Fluid::set_wall(Vector2f const& pos, float const& size, int w) {
	for(int i((pos.x-size)/scale); i < (pos.x+size)/scale; i++)
		for(int j((pos.y-size)/scale); j < (pos.y+size)/scale; j++)
			if(distance(Vector2f(i,j),pos/scale)<size/scale)
				walls.setValue(i,j,w);
}

/* Allows to add pressure to a simulation */
void Fluid::add_pressure(Vector2f const& pos, float const& size, float const& p) {
	for(int i((pos.x-size)/scale); i < (pos.x+size)/scale; i++)
		for(int j((pos.y-size)/scale); j < (pos.y+size)/scale; j++)
			if(distance(Vector2f(i,j),pos/scale)<size/scale)
				pressure.setValue(i,j, p);
}

/* Allows to add speed to a simulation */
void Fluid::add_speed(Vector2f pos, Vector2f size, Vector2f speed) {
	for(int i(pos.x/scale); i < (pos.x+size.x)/scale; i++)
	{
		for(int j(pos.y/scale); j < (pos.y+size.y)/scale; j++)
		{
			u.setValue(i,j,u.getValue(i,j)+speed.x);
			v.setValue(i,j,v.getValue(i,j)+speed.y);
		}
	}
}

/* Allows to draws the speed in the form of vectors to a simulation */
void Fluid::draw_speed_field(RenderWindow &window, float const& size, Color const& color) const {
	for(int i(1); i < width-1; i+=5)
	{
		for(int j(2); j < height-2; j+=5)
		{
			draw_line( Vector2f(scale*i, scale*j), size*Vector2f(u.getValue(i,j),v.getValue(i,j))/50.f, window, color);
		}
	}
}


/* Allows have the colors on temperature from the image (blue to red) */
Sprite Fluid::get_temperature_sprite() {
	for(int i(1); i < width-1; i++)
		for(int j(1); j < height-1; j++)
			image.setPixel(i,j,color_gradient(temperatureColor,temperature.getValue(i,j)/temperature_scale));
		
	texture.loadFromImage(image);
	return sprite;
}

/* Allows to add a temperature to a simulation */
void Fluid::add_temperature(Vector2f pos, float const& size, float const& t) {
	for(int i((pos.x-size)/scale); i < (pos.x+size)/scale; i++)
		for(int j((pos.y-size)/scale); j < (pos.y+size)/scale; j++)
			if(distance(Vector2f(i,j),pos/scale)<size/scale)
				temperature.setValue(i,j,t);
}
