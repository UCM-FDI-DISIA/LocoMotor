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

		void createScene(const std::string& name);
		void changeScene(const std::string& name);
		void update();
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