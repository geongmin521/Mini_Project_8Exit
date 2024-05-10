#pragma once

class Vector3 {
public:
	float _x;
	float _y;
	float _z;
	Vector3();
	Vector3(float x, float y, float z);

	const float Magnitude() const;
	Vector3 Normalized() const;

	const float dot(Vector3& a, Vector3& b) const;
	Vector3 Cross(Vector3& a, Vector3& b) const;

	void operator=	(const Vector3& v);

	Vector3 operator+=	(const Vector3& v);
	Vector3 operator-=	(const Vector3& v);
	Vector3 operator*=	(const float& scalar);
	Vector3 operator/=	(const float& scalar);

	Vector3 operator+	(const Vector3& v) const;
	Vector3 operator-	(const Vector3& v) const;
	Vector3 operator*	(const float& scalar) const;
	Vector3 operator/	(const float& scalar) const;
};