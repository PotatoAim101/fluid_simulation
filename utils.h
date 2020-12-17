#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "Matrix.h"

#define E(i,j) ((i)+(N)*(j))
#define PI 3.14159265359

using namespace sf;
using namespace std;

float distance(Vector2f const& u, Vector2f const& v);
void draw_line(Vector2f const& pos, Vector2f const& dir, RenderWindow &window, Color const& color);
float inferior(float value, float min);
Color color_gradient(Image &colors, float x);