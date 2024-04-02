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

	class MOTOR_API Engine {
	public:
		Engine();

		/// @brief Method to call before calling the InitGame Function in the game dll
		/// @return if false, abort
		bool Init();

		/// @brief Method to call from the InitGame function in the game dll
		/// @param gameName 
		/// @return 
		bool StartGameWindow(const char* gameName);

		/// @brief Dont use it
		/// @return please
		bool MainLoop();
		int showWindow(int type,std::string msg);
	private:

		std::string _gameName;

		LocoMotor::SceneManager* _scnManager;

		std::string _startScene;
		bool _exit;
		static Engine* _instance;
	};
}

#endif // !LOCOMOTOR_ENGINE
