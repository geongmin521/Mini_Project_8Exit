#include "Vector3.h"
#include "globalheader.h"

Vector3::Vector3() : _x(0), _y(0), _z(0) {}

Vector3::Vector3(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

const float Vector3::Magnitude() const
{
	return sqrt(_x * _x + _y * _y + _z * _z);
}

Vector3 Vector3::Normalized() const
{
	if (Magnitude() == 0) return Vector3();
	return *this / Magnitude();
}

const float Vector3::dot(Vector3& a, Vector3& b) const {
	return a._x * b._x + a._y * b._y + a._z * b._z;
}

Vector3 Vector3::Cross(Vector3& a, Vector3& b) const
{
	return Vector3(
		a._y * b._z - a._z * b._y,
		a._z * b._x - a._x * b._z,
		a._x * b._y - a._y * b._x
		);
}

void Vector3::operator=		(const Vector3& v) {
	_x = v._x;
	_y = v._y;
	_z = v._z;
}

Vector3 Vector3::operator+=	(const Vector3& v) {
	_x += v._x;
	_y += v._y;
	_z += v._z;
	return *this;
}

Vector3 Vector3::operator-=	(const Vector3& v) {
	_x -= v._x;
	_y -= v._y;
	_z -= v._z;
	return *this;
}

Vector3 Vector3::operator*=	(const float& scalar) {
	_x *= scalar;
	_y *= scalar;
	_z *= scalar;
	return *this;
}

Vector3 Vector3::operator/=	(const float& scalar) {
	_x /= scalar;
	_y /= scalar;
	_z /= scalar;
	return *this;
}

Vector3 Vector3::operator+	(const Vector3& v) const {
	return Vector3(*this) += v;
}

Vector3 Vector3::operator-	(const Vector3& v) const {
	return Vector3(*this) -= v;
}

Vector3 Vector3::operator*	(const float& scalar) const {
	return Vector3(*this) *= scalar;
}

Vector3 Vector3::operator/	(const float& scalar) const {
	return Vector3(*this) /= scalar;
}