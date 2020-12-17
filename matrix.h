#pragma once

#include "utils.h"

using namespace std;
using namespace sf;

class Matrix{
/*attributes*/
private:
	int col;
	int row;
	vector<float> values;
	int scale;
	
/*methods*/
public:
	Matrix();
	Matrix(int c, int r, int s);
	float getValue(int i, int j) const;
	void setValue(int i, int j, float value);
	void resize(int c, int r);
	int getRow() const;
	int getCol() const;
	void setScale(int s);
	int getScale() const;
};

Matrix operator+(Matrix const& m1, Matrix const& m2);
Matrix operator-(Matrix const& m1, Matrix const& m2);
Matrix operator*(Matrix const& m, float const& k);
Matrix operator/(Matrix const& m, float const& k);
