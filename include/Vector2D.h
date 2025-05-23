#pragma once

#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& add(const Vector2D& other);
	Vector2D& subtract(const Vector2D& other);
	Vector2D& multiply(const Vector2D& other);
	Vector2D& divide(const Vector2D& other);

	friend Vector2D& operator+ (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator- (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator* (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/ (Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+= (const Vector2D& v);
	Vector2D& operator-= (const Vector2D& v);
	Vector2D& operator*= (const Vector2D& v);
	Vector2D& operator/= (const Vector2D& v);

	Vector2D& operator+ (const double& n);
	Vector2D& operator- (const double& n);
	Vector2D& operator* (const double& n);
	Vector2D& operator/ (const double& n);

	friend std::ostream& operator<< (std::ostream& stream, const Vector2D& v);
};