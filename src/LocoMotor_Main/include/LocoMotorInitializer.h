#pragma once
#ifndef LOCOMOTOR_INITIALIZER
#define LOCOMOTOR_INITIALIZER

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace LocoMotor {
	class SceneManager;
	class GameObject;

	class LocoMotorInitializer {
	public:
		MOTOR_API LocoMotorInitializer();
		MOTOR_API void Init();

		MOTOR_API void RegisterGame(const char* gameName);

		/// @brief Dont use it
		/// @return please
		MOTOR_API void MainLoop();
	private:

		std::string _gameName;

		LocoMotor::SceneManager* _scnManager;

		std::string _startScene;
		bool _exit;
	};
}

#endif // !LOCOMOTOR_INITIALIZER
