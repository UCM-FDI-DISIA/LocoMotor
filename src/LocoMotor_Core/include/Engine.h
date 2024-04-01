#pragma once
#ifndef LOCOMOTOR_ENGINE
#define LOCOMOTOR_ENGINE

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace LocoMotor {
	class SceneManager;
	class GameObject;

	class Engine {
	public:
		MOTOR_API Engine();

		/// @brief Method to call before calling the InitGame Function in the game dll
		/// @return if false, abort
		MOTOR_API bool Init();

		/// @brief Method to call from the InitGame function in the game dll
		/// @param gameName 
		/// @return 
		MOTOR_API bool StartGameWindow(const char* gameName);

		/// @brief Dont use it
		/// @return please
		MOTOR_API bool MainLoop();
		MOTOR_API int showWindow(int type,std::string msg);
	private:

		std::string _gameName;

		LocoMotor::SceneManager* _scnManager;

		std::string _startScene;
		bool _exit;
		static Engine* _instance;
	};
}

#endif // !LOCOMOTOR_ENGINE
