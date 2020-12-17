#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
#include "Fluid.h"

using namespace std;
using namespace sf;

int main()
{
	const int width = 500;
	const int height = 500;
	const int scale = 2;

	RenderWindow window(sf::VideoMode(width, height, 32), "Euler fluid");

	Fluid fluid(width/scale,height/scale,1.239,101e3,800,1,scale);
	
	Clock deltaTime;
	Clock Time;
	float dt=0.000003;

	Vector2f mousePos, mousePrevPos, mouseSpeed;
	
	Event event;
	
	while(window.isOpen())
	{
		while(window.pollEvent(event)){}

		mousePrevPos = mousePos;
		mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		mouseSpeed = (mousePos - mousePrevPos)/(float)dt;
		
		/* keys */
		bool left = Mouse::isButtonPressed(Mouse::Right);
		bool right = Mouse::isButtonPressed(Mouse::Left);

		bool Lctrl = Keyboard::isKeyPressed(Keyboard::LControl);
		bool P = Keyboard::isKeyPressed(Keyboard::P); //Positive pressure
		bool N = Keyboard::isKeyPressed(Keyboard::N); //Negative pressure
		bool D = Keyboard::isKeyPressed(Keyboard::D); //visualize speed
		bool S = Keyboard::isKeyPressed(Keyboard::S); //Speed
		bool C = Keyboard::isKeyPressed(Keyboard::C); //pressure
		bool R = Keyboard::isKeyPressed(Keyboard::R); //Remove
		bool T = Keyboard::isKeyPressed(Keyboard::T); //Tempreture 
		
		if(left && Lctrl) fluid.set_wall(mousePos,8,0);
		else if(left) fluid.set_wall(mousePos,8,1);

		if(right && S) { fluid.add_speed(Vector2f(0,55), Vector2f(width,30), Vector2f(0,5)); }
		if(right && P)fluid.add_pressure(mousePos, 30, 100000); 
		if(right && N)fluid.add_pressure(mousePos, 30, -100000); 
		else if(right && T) fluid.add_temperature(mousePos, 10, 1000);
		else if(right && C) fluid.add_pressure(mousePos,30,300000);
		else if(right) fluid.add_density(mousePos, 20, 1);
		if(R) fluid.reset();

		fluid.update(dt);
		
		window.clear(Color::White);

		if(S) window.draw(fluid.get_speed_sprite());
		else if(P) window.draw(fluid.get_pressure_sprite());
		else if(N) window.draw(fluid.get_pressure_sprite());
		else if(C) window.draw(fluid.get3DSprite());

		else if(T) window.draw(fluid.get_temperature_sprite());

		else window.draw(fluid.get_density_sprite());
		
		window.draw(fluid.get_wall_sprite());

		if(D) fluid.draw_speed_field(window, 10, Color::White);

		window.display();
	}
}
