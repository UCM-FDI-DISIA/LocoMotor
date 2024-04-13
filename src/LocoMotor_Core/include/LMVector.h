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
		float GetX() const;
		/// @brief Get the Y value of the Vector
		float GetY() const;
		/// @brief Get the Z value of the Vector
		float GetZ() const;

		// Setter functions
		/// @brief Set the X value of the Vector
		void SetX(float x);
		/// @brief Set the Y value of the Vector
		void SetY(float y);
		/// @brief Set the Z value of the Vector
		void SetZ(float z);

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
		float Dot(const LMVector3& other) const;

		// Cross product
		///	@brief Get the Cross Product of two Vectors
		/// @param other The other Vector
		LMVector3 Cross(const LMVector3& other) const;

		// Cross product
		///	@brief Get the Cross Product of two Vectors
		/// @param normal The normal Vector
		/// @param other The other Vector
		LMVector3 Cross(const LMVector3& other, const LMVector3& normal) const;

		// Magnitude
		///	@brief Get the Magnitude of a Vector
		float Magnitude() const;

		// Normalize
		///	@brief Normalize a Vector
		void Normalize();

		// Angle
		///	@brief Get the Angle between two Vectors
		/// @param other The other Vector to measure from
		float Angle(const LMVector3& other) const;

		// Angle
		///	@brief Get the Angle between two Vectors
		/// @param other The other Vector to measure from
		/// @param normal The normal Vector
		float Angle(const LMVector3& other, const LMVector3& normal) const;

		// Angle
		///	@brief Get the Angle between two Vectors in degrees
		/// @param other The other Vector to measure from
		/// @param normal The normal Vector
		/// @param axis The axis to measure by
		float Angle(const LMVector3& other, const LMVector3& normal, const LMVector3& axis) const;

		// rotate
		///	@brief Rotate a Vector
		/// @param axis The axis to rotate around
		/// @param angle The angle to rotate (degrees)
		LMVector3 Rotate(const LMVector3& axis, float angle);

		// perpendicular
		///	@brief Get the perpendicular vector from two Vectors
		/// @param other The other Vector
		LMVector3 Perpendicular(const LMVector3& other) const;


		/// @brief Convert a rotation vector to Quaternion
		LMQuaternion AsRotToQuaternion() const;

		/// @brief Converts a String to a vector
		/// @param s String to convert
		/// @return Vector3 converted
		static LMVector3 StringToVector(const std::string& s);

		static LMVector3 Lerp(const LMVector3& start, const LMVector3& end, float t);

		static float Distance(const LMVector3& v1, const LMVector3& v2);

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
		float GetW() const;
		/// @brief Get the X value of the Quaternion
		float GetX() const;
		/// @brief Get the Y value of the Quaternion
		float GetY() const;
		/// @brief Get the Z value of the Quaternion
		float GetZ() const;

	//Setter functions
		/// @brief Set the W value of the Quaternion
		void SetW(float w);
		/// @brief Set the X value of the Quaternion
		void SetX(float x);
		/// @brief Set the Y value of the Quaternion
		void SetY(float y);
		/// @brief Set the Z value of the Quaternion
		void SetZ(float z);

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
		LMQuaternion Conjugate() const;

		// Magnitude
		/// @brief Get the Magnitude of a Quaternion
		float Magnitude() const;

		// Normalize
		/// @brief Normalize a Quaternion
		void Normalize();

		// Rotate
		/// @brief Rotate a Quaternion
		/// @param axis The Axis to rotate around
		/// @param angle The Angle to rotate by (degrees)
		LMQuaternion Rotate(const LMVector3& axis, float angle) const;

		// Rotate a vector by this quaternion
		/// @brief Rotate a Vector by this Quaternion
		/// @param vector The Vector to be rotated
		LMVector3 Rotate(const LMVector3& vector) const;

		// Up vector from Quaternion
		/// @brief Get the Up Vector from a Quaternion
		LMVector3 Up() const;

		// Right vector from Quaternion
		/// @brief Get the Right Vector from a Quaternion
		LMVector3 Right() const;

		// Forward vector from Quaternion
		/// @brief Get the Forward Vector from a Quaternion
		LMVector3 Forward() const;

		/// @brief Returns the Quaternion to Euler vector3
		LMVector3 ToEuler() const;
	private:
		float _w = 0, _x = 0, _y = 0, _z = 0;
	};
}

#endif 