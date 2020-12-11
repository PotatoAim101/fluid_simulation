#include "utils.h"

using namespace sf;
using namespace std;

void interpolation(float &x, float const& y, float const& time, float const& deltaTime) {
	x += (2.f*(y-x)*deltaTime)/time;
}

void angleInterpolation(float &x, float y, float const& time, float const& dt) {
	if(abs(y-x) > 180)
	{
		if(x>y)
			y+=360;
		else
			x+=360;
	}
	x += (2*(y-x)*dt)/time;
	
	if(x>360)
		x = (int)x%360;
}

float determinant(Vector2f const& u, Vector2f const& v)  {
	float result = u.x*v.y - u.y*v.x;
	return result;
}

float dotProduct(Vector2f const& u, Vector2f const& v) {
	return u.x*v.x + u.y*v.y;
}

float Angle(Vector2f const& v1, Vector2f const& v2) {
	float angle = atan2(determinant(v1,v2), dotProduct(v1,v2))*180/PI;
	if(angle<0)
		angle = 360 + angle;
	return angle;
}

void drawPoint(Vector2f const& p, float const& radius, RenderWindow &window, Color const& color){
	CircleShape c(radius);
	c.setFillColor(color);
	c.setPosition(p);
	c.setOrigin(radius,radius);
	window.draw(c);
}

void drawLine(Vector2f const& pos, Vector2f const& dir, RenderWindow &window, Color const& color) {
	VertexArray lines(Lines, 2);
	lines[0].position = pos;
	lines[0].color = color;
	lines[1].position = dir+pos;
	lines[1].color = color;
	window.draw(lines);
}

float Distance(Vector2f const& u, Vector2f const& v) {
	return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2));
}

Vector2f rotatePoint(Vector2f const& point, Vector2f const& center, float const& angle)  {
	float x = center.x + (point.x - center.x)*cos(angle*(PI/180)) - (point.y - center.y)*sin(angle*(PI/180));
	float y = center.y + (point.x - center.x)*sin(angle*(PI/180)) + (point.y - center.y)*cos(angle*(PI/180));
	return Vector2f(x,y);
}

float Norm (Vector2f const& v)  {
	float result = sqrt(pow(v.x,2)+pow(v.y,2));
	return result;
}
Vector2f Normalize (Vector2f const& v) {
	return v/Norm(v);
}


bool mouseClickedOnce(Mouse::Button const& button, bool &clickedFlag)  {
	bool result = false;
	if(Mouse::isButtonPressed(button) && clickedFlag == false)
	{
		result = true;
		clickedFlag = true;
	}
	else if (Mouse::isButtonPressed(button) && clickedFlag == true) 
	{
		result = false;
		clickedFlag = true;
	}
	else
	{
		result = false;
		clickedFlag = false;
	}
	return result;
}
bool keyPushedOnce(Keyboard::Key const& key, bool &pushFlag)
{
	bool result = false;
	if(Keyboard::isKeyPressed(key) && pushFlag == false)
	{
		result = true;
		pushFlag = true;
	}
	else if (Keyboard::isKeyPressed(key) && pushFlag == true) 
	{
		result = false;
		pushFlag = true;
	}
	else
	{
		result = false;
		pushFlag = false;
	}
	return result;
}

float infBound(float value, float min)  {
	float result;
	if(value < min)
		result = min;
	else
		result = value;
	return result;
}

Color colorGradient(Image &color, float x) {
	if(x>0.999) x=0.999;
	if(x<0.001) x=0.001;
	return color.getPixel((int)(x*color.getSize().x),0);
}
int quo(int a, int b) {
	int q = 0;
	if(b==0) return 0;
	else
	while(a-b>=0)
	{
		a = a-b;
		q++;
	}
	return q;
}
