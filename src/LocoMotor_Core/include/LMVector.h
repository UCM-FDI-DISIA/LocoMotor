#pragma once
#ifndef LM_VECTOR
#define LM_VECTOR

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

//namespace Ogre {
//	typedef Vector<3, Real> Vector3;
//}

namespace LocoMotor {
	class MOTOR_API LMQuaternion;
	//Vector class to be used with LocoMotor
	class MOTOR_API LMVector3 {

	public:
		// Default constructor initializes vector to (0, 0, 0)
		/// @brief Create a new Vector3 with everything Set to 0
		LMVector3();

		// Constructor initializes vector to specified values
		/// @brief Create a new Vector3
		LMVector3(float x, float y, float z);

		// Getter functions
		/// @brief Get the X value of the Vector
		float getX() const;
		/// @brief Get the Y value of the Vector
		float getY() const;
		/// @brief Get the Z value of the Vector
		float getZ() const;

		// Setter functions
		/// @brief Set the X value of the Vector
		void setX(float x);
		/// @brief Set the Y value of the Vector
		void setY(float y);
		/// @brief Set the Z value of the Vector
		void setZ(float z);

		// Equal operators of vectors

		// Sum operators of vectors
		LMVector3 operator+(const LMVector3& other) const;
		LMVector3 operator+(const float& other) const;
		// Sub operators of vectors
		LMVector3 operator-(const LMVector3& other) const;
		LMVector3 operator-(const float& other) const;

		// Mul operators of vectors
		LMVector3 operator*(const LMVector3& other) const;
		LMVector3 operator*(const float& other) const;

		// Div operators of vectors
		LMVector3 operator/(const LMVector3& other) const;
		LMVector3 operator/(const float& other) const;

		// Dot product
		///	@brief Get the Dot Product of two Vectors
		/// @param other The other Vector
		float dot(const LMVector3& other) const;

		// Cross product
		///	@brief Get the Cross Product of two Vectors
		/// @param other The other Vector
		LMVector3 cross(const LMVector3& other) const;

		// Cross product
		///	@brief Get the Cross Product of two Vectors
		/// @param normal The normal Vector
		/// @param other The other Vector
		LMVector3 cross(const LMVector3& other, const LMVector3& normal) const;

		// Magnitude
		///	@brief Get the Magnitude of a Vector
		float magnitude() const;

		// Normalize
		///	@brief Normalize a Vector
		void normalize();

		// Angle
		///	@brief Get the Angle between two Vectors
		/// @param other The other Vector to measure from
		float angle(const LMVector3& other) const;

		// Angle
		///	@brief Get the Angle between two Vectors
		/// @param other The other Vector to measure from
		/// @param normal The normal Vector
		float angle(const LMVector3& other, const LMVector3& normal) const;

		// Angle
		///	@brief Get the Angle between two Vectors in degrees
		/// @param other The other Vector to measure from
		/// @param normal The normal Vector
		/// @param axis The axis to measure by
		float angle(const LMVector3& other, const LMVector3& normal, const LMVector3& axis) const;

		// rotate
		///	@brief Rotate a Vector
		/// @param axis The axis to rotate around
		/// @param angle The angle to rotate (degrees)
		LMVector3 rotate(const LMVector3& axis, float angle);

		// perpendicular
		///	@brief Get the perpendicular vector from two Vectors
		/// @param other The other Vector
		LMVector3 perpendicular(const LMVector3& other) const;


		/// @brief Convert a rotation vector to Quaternion
		LMQuaternion asRotToQuaternion() const;

		/// @brief Converts a String to a vector
		/// @param s String to convert
		/// @return Vector3 converted
		static LMVector3 stringToVector(const std::string& s);

		static LMVector3 lerp(const LMVector3& start, const LMVector3& end, float t);

		static float distance(const LMVector3& v1, const LMVector3& v2);

		bool operator==(const LMVector3& other) const;

	private:
		float _x = 0, _y = 0, _z = 0;
	};

	//Quaternion class to be used with LocoMotor
	class LMQuaternion {

	public:
		// Default constructor initializes quaternion to (1, 0, 0, 0)
		/// @brief Create a new Quaternion with everything Set to default
		LMQuaternion();

		// Constructor initializes quaternion to specified values
		/// @brief Create a new Quaternion
		LMQuaternion(float w, float x, float y, float z);

		// Getter functions
		/// @brief Get the W value of the Quaternion
		float getW() const;
		/// @brief Get the X value of the Quaternion
		float getX() const;
		/// @brief Get the Y value of the Quaternion
		float getY() const;
		/// @brief Get the Z value of the Quaternion
		float getZ() const;

	//Setter functions
		/// @brief Set the W value of the Quaternion
		void setW(float w);
		/// @brief Set the X value of the Quaternion
		void setX(float x);
		/// @brief Set the Y value of the Quaternion
		void setY(float y);
		/// @brief Set the Z value of the Quaternion
		void setZ(float z);

		//Equal operators of quaternions
		LMQuaternion operator=(const LMQuaternion& other);

		// Add operators of quaternions
		LMQuaternion operator+(const LMQuaternion& other) const;

		// Sub operators of quaternions
		LMQuaternion operator-(const LMQuaternion& other) const;

		// Mul operators of quaternions
		LMQuaternion operator*(const LMQuaternion& other) const;
		LMQuaternion operator*(float scalar) const;
		LMVector3 operator*(const LocoMotor::LMVector3& other) const;

		// Div operators of quaternions
		LMQuaternion operator/(float scalar) const;

		// Conjugate
		/// @brief Get the Conjugate of a Quaternion
		LMQuaternion conjugate() const;

		// Magnitude
		/// @brief Get the Magnitude of a Quaternion
		float magnitude() const;

		// Normalize
		/// @brief Normalize a Quaternion
		void normalize();

		// Rotate
		/// @brief Rotate a Quaternion
		/// @param axis The Axis to rotate around
		/// @param angle The Angle to rotate by (degrees)
		LMQuaternion rotate(const LMVector3& axis, float angle) const;

		// Rotate a vector by this quaternion
		/// @brief Rotate a Vector by this Quaternion
		/// @param vector The Vector to be rotated
		LMVector3 rotate(const LMVector3& vector) const;

		// Up vector from Quaternion
		/// @brief Get the Up Vector from a Quaternion
		LMVector3 up() const;

		// Right vector from Quaternion
		/// @brief Get the Right Vector from a Quaternion
		LMVector3 right() const;

		// Forward vector from Quaternion
		/// @brief Get the Forward Vector from a Quaternion
		LMVector3 forward() const;

		/// @brief Returns the Quaternion to Euler vector3
		LMVector3 toEuler() const;
	private:
		float _w = 0, _x = 0, _y = 0, _z = 0;
	};
}

#endif 