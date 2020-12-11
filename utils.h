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

float determinant(Vector2f const& u, Vector2f const& v);
float dotProduct(Vector2f const& u, Vector2f const& v);
float Angle(Vector2f const& v1, Vector2f const& v2);
float Distance(Vector2f const& u, Vector2f const& v);
float Norm (Vector2f const& v);
Vector2f Normalize (Vector2f const& v);

void interpolation(float &x, float const& y, float const& time, float const& deltaTime);
void angleInterpolation(float &x, float y, float const& time, float const& dt);

void drawPoint(Vector2f const& p, float const& radius, RenderWindow &window, Color const& color);
void drawLine(Vector2f const& pos, Vector2f const& dir, RenderWindow &window, Color const& color);

Vector2f rotatePoint(Vector2f const& point, Vector2f const& center, float const& angle);

bool mouseClickedOnce(Mouse::Button const& button, bool &clickFlag);
bool keyPushedOnce(Keyboard::Key const& key, bool &pushFlag);

float infBound(float value, float min);

Color colorGradient(Image &colors, float x);

int quo(int a, int b);
