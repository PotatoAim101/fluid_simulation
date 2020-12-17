#include "matrix.h"

/*constructors*/
Matrix::Matrix() {
	col = 0;
	row = 0;
	values.clear();
	scale=1;
}

Matrix::Matrix(int c, int r, int s) {
	col = c;
	row = r;
	resize(col, row);
	scale=s;
}

/*gets and sets*/
int Matrix::getRow() const {
	return row;
}

int Matrix::getCol() const {
	return col;
}

float Matrix::getValue(int i, int j) const {
	if(i>0 && i <row && j>0 && j<row)
		return values[i+(j-1)*col];
	else return 0;
}

void Matrix::setValue(int i, int j, float v) {
	if(i>0 && i <row && j>0 && j<row)
		values[i+inferior(j-1,0)*col] = v;
}

void Matrix::resize(int c, int r) {
	col=c;
	row=r;
	values.resize(col*row,0);
}

void Matrix::setScale(int s) {
	scale=s;
}

int Matrix::getScale() const {
	return scale;
}

/* operations */
Matrix operator+(Matrix const& m1, Matrix const& m2) {
	Matrix result(m1);
	for(int i(0); i < m1.getCol(); i++) 
	{
		for(int j(0); j < m1.getCol(); j++) 
		{
			result.setValue(i,j, m1.getValue(i,j)+m2.getValue(i,j));
		}
	}
	return result;
}

Matrix operator*(Matrix const& m, float k) {
	Matrix result(m);
	for(int i(0); i < m.getCol(); i++) 
	{
		for(int j(0); j < m.getCol(); j++) 
		{
			result.setValue(i,j, m.getValue(i,j)*k);
		}
	}
	return result;
}

Matrix operator-(Matrix const& m1, Matrix const& m2) {
	Matrix result(m1);
	for(int i(0); i < m1.getCol(); i++) 
	{
		for(int j(0); j < m1.getCol(); j++) 
		{
			result.setValue(i,j, m1.getValue(i,j)-m2.getValue(i,j));
		}
	}
	return result;
}

Matrix operator/(Matrix const& m, float k) {
	Matrix result(m);
	for(int i(0); i < m.getCol(); i++) 
	{
		for(int j(0); j < m.getCol(); j++) 
		{
			result.setValue(i,j, m.getValue(i,j)/k);
		}
	}
	return result;
}

