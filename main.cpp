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
		
		bool right = Mouse::isButtonPressed(Mouse::Right);
		bool left = Mouse::isButtonPressed(Mouse::Left);
		bool mid = Mouse::isButtonPressed(Mouse::Middle);
		bool Lctrl = Keyboard::isKeyPressed(Keyboard::LControl);
		bool F = Keyboard::isKeyPressed(Keyboard::F); //Forces
		bool T = Keyboard::isKeyPressed(Keyboard::T); //Tempreture 
		bool D = Keyboard::isKeyPressed(Keyboard::D); 
		bool S = Keyboard::isKeyPressed(Keyboard::S); //Speed
		bool C = Keyboard::isKeyPressed(Keyboard::C); //circular force
		bool R = Keyboard::isKeyPressed(Keyboard::R); //Remove
		
		if(mid && Lctrl) fluid.setWallZone(mousePos,8,0);
		else if(mid) fluid.setWallZone(mousePos,8,1);

		if(left) { fluid.addSpeedZone(Vector2f(0,55), Vector2f(width,30), Vector2f(0,5)); }
		if(right && F)fluid.addPressureZone(mousePos, 30, 100000); 
		else if(right && T) fluid.addTemperatureZone(mousePos, 10, 1000);
		else if(right && C) fluid.addPressureZone(mousePos,30,300000);
		else if(right) fluid.addDensityZone(mousePos, 20, 1);
		if(R) fluid.Reset();

		fluid.Update(dt);
		
		window.clear(Color::White);

		if(T) window.draw(fluid.getTemperatureSprite());
		else if(D) window.draw(fluid.getSpeedSprite());
		else if(F) window.draw(fluid.getPressureSprite());
		else if(C) window.draw(fluid.get3DSprite());
		else window.draw(fluid.getDensitySprite());
		
		window.draw(fluid.getWallSprite());

		if(T) fluid.drawSpeedField(window, 10, Color::White);

		window.display();
	}
}
