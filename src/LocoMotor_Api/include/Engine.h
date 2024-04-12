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
		

		/// @brief Method to call before calling the InitGame Function in the game dll
		/// @return if false, abort
		static bool Init();

		bool init();
		/// @brief Returns the instance of the Engine singleton
		static Engine* GetInstance();
		/// @brief Deletes the instance of the Engine singleton
		static void Release();

		void setWindowName(const std::string& name);
		void setStartingScene(const std::string& file, const std::string& name);

		/// @brief Dont use it
		/// @return please
		bool mainLoop();
		int showWindow(int type,std::string msg);
		void quit();
	private:

		/// @brief Method to call from the InitGame function in the game dll
		/// @param gameName 
		/// @return 
		bool startGameWindow();

		std::string _gameName;

		std::string _startingSceneFile;
		std::string _startingSceneName;

		LocoMotor::SceneManager* _scnManager;

		std::string _startScene;
		bool _exit;
		static Engine* _instance;

		Engine();
		~Engine();
	};
}

#endif // !LOCOMOTOR_ENGINE
