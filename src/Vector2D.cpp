#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}
Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::add(const Vector2D& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}
Vector2D& Vector2D::subtract(const Vector2D& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}
Vector2D& Vector2D::multiply(const Vector2D& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}
Vector2D& Vector2D::divide(const Vector2D& other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

Vector2D& operator+ (Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}
Vector2D& operator- (Vector2D& v1, const Vector2D& v2)
{
	return v1.subtract(v2);
}
Vector2D& operator* (Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}
Vector2D& operator/ (Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}

Vector2D& Vector2D::operator+= (const Vector2D& v)
{
	return this->add(v);
}
Vector2D& Vector2D::operator-= (const Vector2D& v)
{
	return this->subtract(v);
}
Vector2D& Vector2D::operator*= (const Vector2D& v)
{
	return this->multiply(v);
}
Vector2D& Vector2D::operator/= (const Vector2D& v)
{
	return this->divide(v);
}

Vector2D& Vector2D::operator+ (const double& n)
{
	this->x += n;
	this->y += n;

	return *this;
}
Vector2D& Vector2D::operator- (const double& n)
{
	this->x -= n;
	this->y -= n;

	return *this;
}
Vector2D& Vector2D::operator* (const double& n)
{
	this->x *= n;
	this->y *= n;

	return *this;
}
Vector2D& Vector2D::operator/ (const double& n)
{
	this->x /= n;
	this->y /= n;

	return *this;
}

std::ostream& operator<< (std::ostream& stream, const Vector2D& v)
{
	stream << "(" << v.x << ", " << v.y << ")" << std::endl;

	return stream;
}