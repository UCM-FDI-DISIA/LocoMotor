#pragma once
#ifndef LOCOMOTOR_SCENEMANAGER
#define LOCOMOTOR_SCENEMANAGER
#include <string>
#include <unordered_map>

namespace LocoMotor {
	class Scene;
	class SceneManager {
	public:
		static bool Init();
		static void Release();
		static SceneManager* GetInstance();

		/// @brief Creates a new scene with the name provided. Method created for testing pursposes
		/// @param name Name for the scene
		Scene* createScene(const std::string& name);
		/// @brief Changes to the scene with the given name, if it is not found, nothing will happen.
		/// @param name Name of the scene
		void changeScene(const std::string& name);

		/// @brief Loads a scene form the given file
		/// @param path Path to a .lua file defining the scene
		/// @param name Name of the scene inside the Lua file
		void loadScene(const std::string& path, const std::string& name);
		/// @brief updates the state of the scenes
		void update(float dT);
	private:
		static SceneManager* _instance;
		SceneManager();
		~SceneManager();
		std::unordered_map<std::string, Scene*> _scenes;
		Scene* _activeScene;
		Scene* _toStart;
		float _lastFrameTime;
		float _dt;
	};
}
#endif