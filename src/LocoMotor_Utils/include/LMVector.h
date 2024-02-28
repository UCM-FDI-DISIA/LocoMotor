



namespace LocoMotor {
	class LMQuaternion;
	//Vector class to be used with LocoMotor
	class LMVector3 {

	public:
		// Default constructor initializes vector to (0, 0, 0)
		/// @brief Create a new Vector3 with everything Set to 0
		LMVector3();

		// Constructor initializes vector to specified values
		/// @brief Create a new Vector3
		LMVector3(double x, double y, double z);

		// Getter functions
		/// @brief Get the X value of the Vector
		double GetX() const { return _x; }
		/// @brief Get the Y value of the Vector
		double GetY() const { return _y; }
		/// @brief Get the Z value of the Vector
		double GetZ() const { return _z; }

	private:
		double _x = 0, _y = 0, _z = 0;
	};
}
