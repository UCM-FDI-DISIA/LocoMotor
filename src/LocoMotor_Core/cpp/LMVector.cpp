#define _USE_MATH_DEFINES

#include "LMVector.h"
#include <cmath>

using namespace LocoMotor;

// Default constructor initializes vector to (0, 0, 0)
LMVector3::LMVector3() : _x(0), _y(0), _z(0) {}

// Constructor initializes vector to specified values
LMVector3::LMVector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}

// Getter functions
// Get the X value of the Vector
float LMVector3::getX() const {
	return _x;
}
// Get the Y value of the Vector
float LMVector3::getY() const {
	return _y;
}
// Get the Z value of the Vector
float LMVector3::getZ() const {
	return _z;
}

// Setter functions
// Set the X value of the Vector
void LMVector3::setX(float x) {
	this->_x = x;
}
// Set the Y value of the Vector
void LMVector3::setY(float y) {
	this->_y = y;
}
// Set the Z value of the Vector
void LMVector3::setZ(float z) {
	this->_z = z;
}
// Sum
LMVector3 LMVector3::operator+(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x + other._x,
		this->_y + other._y,
		this->_z + other._z);

	return aux;
}

LMVector3 LMVector3::operator+(const float& other) const {
	LMVector3 aux = LMVector3(
		this->_x + other,
		this->_y + other,
		this->_z + other);

	return aux;
}

// Sub
LMVector3 LMVector3::operator-(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x - other._x,
		this->_y - other._y,
		this->_z - other._z);

	return aux;
}
LMVector3 LMVector3::operator-(const float& other) const {
	LMVector3 aux = LMVector3(
		this->_x - other,
		this->_y - other,
		this->_z - other);

	return aux;
}

// Mul
LMVector3 LMVector3::operator*(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x * other._x,
		this->_y * other._y,
		this->_z * other._z);
	return aux;
}

LMVector3 LMVector3::operator*(const float& other) const {
	LMVector3 aux = LMVector3(
		this->_x * other,
		this->_y * other,
		this->_z * other);

	return aux;
}

// Div
LMVector3 LMVector3::operator/(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x / other._x,
		this->_y / other._y,
		this->_z / other._z);

	return aux;
}
LMVector3 LMVector3::operator/(const float& other) const {
	LMVector3 aux = LMVector3(
		this->_x / other,
		this->_y / other,
		this->_z / other);

	return aux;
}


// Dot product
float LMVector3::dot(const LMVector3& other) const {
	return _x * other._x + _y * other._y + _z * other._z;
}

// Cross product
LMVector3 LMVector3::cross(const LMVector3& other) const {
	return LMVector3(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
}
// Cross product
LMVector3 LMVector3::cross(const LMVector3& other, const LMVector3& axis) const {
	LMVector3 currentCross = cross(other);
	if (currentCross.dot(axis) < 0) {
		currentCross = currentCross * -1;
	}
	return currentCross;
}

// Magnitude
float LMVector3::magnitude() const {
	return sqrt(_x * _x + _y * _y + _z * _z);
}

// Normalize
void LMVector3::normalize() {
	float mag = magnitude();
	if (mag > 0) {
		_x /= mag;
		_y /= mag;
		_z /= mag;
	}
}

// Angle between two vectors
float LMVector3::angle(const LMVector3& other) const {
	float currentDot = dot(other);
	float mag = magnitude() * other.magnitude();
	if (mag > 0) {
		return acos(currentDot / mag);
	}
	return 0;
}

//Angle between two vectors
float LMVector3::angle(const LMVector3& other, const LMVector3& axis) const {
	float currentAngle = angle(other);
	LMVector3 currentCross = cross(other);
	if (currentCross.dot(axis) < 0) {
		currentAngle = -currentAngle;
	}

	currentAngle = currentAngle * (float) (180 / M_PI);

	return currentAngle;
}


//Angle between two vectors in degrees
float LMVector3::angle(const LMVector3& other, const LMVector3& normal, const LMVector3& axis) const {
	float currentAngle = angle(other, normal);
	LMVector3 currentCross = cross(other, normal);
	if (currentCross.dot(axis) < 0) {
		currentAngle = -currentAngle;
	}

	currentAngle = currentAngle * (float) (180.f / M_PI);

	return currentAngle;
}

// Rotate a vector around an axis in degrees
LMVector3 LMVector3::rotate(const LMVector3& axis, float angle) {
	LMVector3 cross = axis.cross(*this);
	LMVector3 dot = axis * axis.dot(*this);
	LMVector3 cross2 = axis.cross(cross);
	LMVector3 a = dot + cross * ((float) sin(angle * M_PI / 180.)) + cross2 * ((float) (1 - cos(angle * M_PI / 180.)));

	this->_x = a.getX();
	this->_y = a.getY();
	this->_z = a.getZ();

	return a;
}

//Get the perpendicular vector from two vectors
LMVector3 LMVector3::perpendicular(const LMVector3& other) const {
	return cross(other).cross(*this);
}


LMQuaternion LMVector3::asRotToQuaternion() const {
	// Abbreviations for the various angular functions

	// Degree to Radian
	LMVector3 aux = *this;
	aux = aux * (float) (M_PI / 180);

	double cr = cos(aux.getX() * 0.5);
	double sr = sin(aux.getX() * 0.5);
	double cp = cos(aux.getY() * 0.5);
	double sp = sin(aux.getY() * 0.5);
	double cy = cos(aux.getZ() * 0.5);
	double sy = sin(aux.getZ() * 0.5);



	LMQuaternion q;
	q.setW((float) (cr * cp * cy + sr * sp * sy));
	q.setX((float) (sr * cp * cy - cr * sp * sy));
	q.setY((float) (cr * sp * cy + sr * cp * sy));
	q.setZ((float) (cr * cp * sy - sr * sp * cy));

	return q;
}

LMVector3 LMVector3::stringToVector(const std::string& s) {

	std::string vectorString = s;
	unsigned char currAxis = 0;
	std::string num = "";
	LMVector3 result = LMVector3();
	for (const char c : vectorString) {
		if (c != ' ') {
			num += c;
		}
		else {
			float value = 0.f;
			try {
				value = std::stof(num);
			}
			catch (const char*) {
				value = 0.f;
			}
			if (currAxis == 0) {
				result.setX(value);
			}
			else if (currAxis == 1) {
				result.setY(value);
			}
			else if (currAxis == 2) {
				result.setZ(value);
			}
			currAxis++;
			num = "";
			if (currAxis == 3) {
				break;
			}
		}
	}
	float value = 0.0f;
	try {
		value = std::stof(num);
	}
	catch (...) {
		value = 0.0f;
	}
	if (currAxis == 2)
		result.setZ(value);

	return result;
}

LMVector3 LocoMotor::LMVector3::lerp(const LMVector3& start, const LMVector3& end, float t) {
	return LMVector3(start.getX() + t * (end.getX() - start.getX()),
				   start.getY() + t * (end.getY() - start.getY()),
				   start.getZ() + t * (end.getZ() - start.getZ()));
}

float LocoMotor::LMVector3::distance(const LMVector3& v1, const LMVector3& v2) {
	float dx = v2.getX() - v1.getX();
	float dy = v2.getY() - v1.getY();
	float dz = v2.getZ() - v1.getZ();
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

bool LocoMotor::LMVector3::operator==(const LMVector3& other) const
{
	return _x == other._x && _y == other._y && _z == other._z;
}



//Quaternion class to be used with LocoMotor

// Default constructor initializes quaternion to (1, 0, 0, 0)
LMQuaternion::LMQuaternion() : _w(1), _x(0), _y(0), _z(0) {}

// Constructor initializes quaternion to specified values
LMQuaternion::LMQuaternion(float w, float x, float y, float z) : _w(w), _x(x), _y(y), _z(z) {}

// Getter functions
float LMQuaternion::getW() const {
	return _w;
}
float LMQuaternion::getX() const {
	return _x;
}
float LMQuaternion::getY() const {
	return _y;
}
float LMQuaternion::getZ() const {
	return _z;
}

//Setter functions
void LMQuaternion::setW(float w) {
	this->_w = w;
}
void LMQuaternion::setX(float x) {
	this->_x = x;
}
void LMQuaternion::setY(float y) {
	this->_y = y;
}
void LMQuaternion::setZ(float z) {
	this->_z = z;
}

// Quaternion equal
LMQuaternion LMQuaternion::operator=(const LMQuaternion& other) {
	_w = other._w;
	_x = other._x;
	_y = other._y;
	_z = other._z;
	return *this;
}



// Quaternion addition
LMQuaternion LMQuaternion::operator+(const LMQuaternion& other) const {
	return LMQuaternion(_w + other._w, _x + other._x, _y + other._y, _z + other._z);
}


// Quaternion subtraction
LMQuaternion LMQuaternion::operator-(const LMQuaternion& other) const {
	return LMQuaternion(_w - other._w, _x - other._x, _y - other._y, _z - other._z);
}


// Quaternion multiplication
LMQuaternion LMQuaternion::operator*(const LMQuaternion& other) const {
	float newW = _w * other._w - _x * other._x - _y * other._y - _z * other._z;
	float newX = _w * other._x + _x * other._w + _y * other._z - _z * other._y;
	float newY = _w * other._y - _x * other._z + _y * other._w + _z * other._x;
	float newZ = _w * other._z + _x * other._y - _y * other._x + _z * other._w;
	return LMQuaternion(newW, newX, newY, newZ);
}
// Scalar multiplication
LMQuaternion LMQuaternion::operator*(float scalar) const {
	return LMQuaternion(_w * scalar, _x * scalar, _y * scalar, _z * scalar);
}

// Scalar division
LMQuaternion LMQuaternion::operator/(float scalar) const {
	return LMQuaternion(_w / scalar, _x / scalar, _y / scalar, _z / scalar);
}



LMVector3 LMQuaternion::operator*(const LMVector3& other) const {
	float num = this->_x * 2.f;
	float num2 = this->_y * 2.f;
	float num3 = this->_z * 2.f;
	float num4 = this->_x * num;
	float num5 = this->_y * num2;
	float num6 = this->_z * num3;
	float num7 = this->_x * num2;
	float num8 = this->_x * num3;
	float num9 = this->_y * num3;
	float num10 = this->_w * num;
	float num11 = this->_w * num2;
	float num12 = this->_w * num3;
	LMVector3 result = LMVector3();
	result.setX((1.f - (num5 + num6)) * other.getX() + (num7 - num12) * other.getY() + (num8 + num11) * other.getZ());
	result.setY((num7 + num12) * other.getX() + (1.f - (num4 + num6)) * other.getY() + (num9 - num10) * other.getZ());
	result.setZ((num8 - num11) * other.getX() + (num9 + num10) * other.getY() + (1.f - (num4 + num5)) * other.getZ());
	return result;
}

// Conjugate
LMQuaternion LMQuaternion::conjugate() const {
	return LMQuaternion(_w, -_x, -_y, -_z);
}

// Magnitude
float LMQuaternion::magnitude() const {
	return sqrt(_w * _w + _x * _x + _y * _y + _z * _z);
}

// Normalize
void LMQuaternion::normalize() {
	float mag = magnitude();
	if (mag > 0) {
		_w /= mag;
		_x /= mag;
		_y /= mag;
		_z /= mag;
	}
}

//Rotate a quaternion
LMQuaternion LMQuaternion::rotate(const LMVector3& axis, float angle) const {
	LMQuaternion q;
	float halfAngle = (float) (angle * (M_PI / 180.0f)) / 2.0f;
	float sinHalfAngle = sin(halfAngle);
	q.setW(cos(halfAngle));
	q.setX(axis.getX() * sinHalfAngle);
	q.setY(axis.getY() * sinHalfAngle);
	q.setZ(axis.getZ() * sinHalfAngle);
	return q * (*this);
}

// Rotate a vector by this quaternion
LMVector3 LMQuaternion::rotate(const LMVector3& vector) const {
	LMQuaternion vectorQuat(0, vector.getX(), vector.getY(), vector.getZ());
	LMQuaternion result = (*this) * vectorQuat * conjugate();
	return LMVector3(result.getX(), result.getY(), result.getZ());
}

// Up vector of this quaternion
LMVector3 LMQuaternion::up() const {
	return rotate(LMVector3(0, 1, 0));
}

// Right vector of this quaternion
LMVector3 LMQuaternion::right() const {
	return rotate(LMVector3(1, 0, 0));
}

// Forward vector of this quaternion
LMVector3 LMQuaternion::forward() const {
	return rotate(LMVector3(0, 0, -1));
}

LMVector3 LMQuaternion::toEuler() const {
	LMVector3 angles;

// roll (x-axis rotation)
	float sinr_cosp = 2 * (this->_w * this->_x + this->_y * this->_z);
	float cosr_cosp = 1 - 2 * (this->_x * this->_x + this->_y * this->_y);
	angles.setX(std::atan2(sinr_cosp, cosr_cosp));

	// pitch (y-axis rotation)
	float sinp = std::sqrt(1 + 2 * (this->_w * this->_y - this->_x * this->_z));
	float cosp = std::sqrt(1 - 2 * (this->_w * this->_y - this->_x * this->_z));
	angles.setY(2 * std::atan2(sinp, cosp) - (float) M_PI / 2.f);

	// yaw (z-axis rotation)
	float siny_cosp = 2 * (this->_w * this->_z + this->_x * this->_y);
	float cosy_cosp = 1 - 2 * (this->_y * this->_y + this->_z * this->_z);
	angles.setZ(std::atan2(siny_cosp, cosy_cosp));

	return angles;
}


