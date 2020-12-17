#include "utils.h"

using namespace sf;
using namespace std;

/* we use this function to draw the speed vectors */
void draw_line(Vector2f const& pos, Vector2f const& dir, RenderWindow &window, Color const& color) {
	VertexArray lines(Lines, 2);
	lines[0].position = pos;
	lines[0].color = color;
	lines[1].position = dir+pos;
	lines[1].color = color;
	window.draw(lines);
}

float distance(Vector2f const& u, Vector2f const& v) {
	return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2));
}

float inferior(float value, float min)  {
	float result;
	if(value < min)
		result = min;
	else
		result = value;
	return result;
}

Color color_gradient(Image &color, float x) {
	if(x>0.999) x=0.999;
	if(x<0.001) x=0.001;
	return color.getPixel((int)(x*color.getSize().x),0);
}
