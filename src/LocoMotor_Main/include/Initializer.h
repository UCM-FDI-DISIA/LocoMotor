#pragma once
#ifndef LOCOMOTOR_INITIALIZER
#define LOCOMOTOR_INITIALIZER

/*
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
*/

#include <string>

namespace LocoMotor {
	class SceneManager;
	class GameObject;

	class Initializer {
	public:
		Initializer();

		/// @brief Method to call before calling the InitGame Function in the game dll
		/// @return if false, abort
		bool Init();

		/// @brief Method to call from the InitGame function in the game dll
		/// @param gameName 
		/// @return 
		/*MOTOR_API*/ bool StartGameWindow(const char* gameName);

		/// @brief Dont use it
		/// @return please
		bool MainLoop();
	private:

		std::string _gameName;

		LocoMotor::SceneManager* _scnManager;

		std::string _startScene;
		bool _exit;
	};
}

#endif // !LOCOMOTOR_INITIALIZER
