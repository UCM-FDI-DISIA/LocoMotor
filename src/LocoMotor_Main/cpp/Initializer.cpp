#include "Initializer.h"
#include "GraphicsManager.h"
#include "ComponentsFactory.h"
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "SceneManager.h"

#include "AudioSource.h"
#include "AudioListener.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "Rigidbody.h"

#include <iostream>

using namespace LocoMotor;

Initializer::Initializer() {
	_gameName = "No window title";
	_scnManager = nullptr;
	_startScene = "";
	_exit = false;
}

bool Initializer::StartGameWindow(const char* gameName) {
	
	return Graphics::GraphicsManager::GetInstance()->initWindow(gameName);
}

bool Initializer::Init() {

	if (!Graphics::GraphicsManager::Init()) {
		return false;
	}

	if (!Audio::AudioManager::Init()) {
		Graphics::GraphicsManager::Release();
		return false;
	}

	//Physics::PhysicsManager::Init();
	//PhysicsManager::GetInstance()->SetContactStartCallback(LMcontactStart);
	//PhysicsManager::GetInstance()->SetContactProcessCallback(LMcontactProcessed);
	//PhysicsManager::GetInstance()->SetContactEndedCallback(LMcontactExit);
	//InputManager::Init();
	//SceneManager::Init();
	//ScriptManager::Init();

	if (!ComponentsFactory::Init()) {
		Audio::AudioManager::Release();
		Graphics::GraphicsManager::Release();
		//Physics::PhysicsManager::Release();
		//InputManager::Release();
		//SceneManager::Release();
		//ScriptManager::Release();
		return false;
	}
	ComponentsFactory* cmpFac = ComponentsFactory::GetInstance();

	if (!SceneManager::Init()) {
		ComponentsFactory::Release();
		cmpFac = nullptr;
		Audio::AudioManager::Release();
		Graphics::GraphicsManager::Release();
	}
	_scnManager = SceneManager::GetInstance();

	cmpFac->registerComponent<AudioSource>("AudioSource");
	cmpFac->registerComponent<AudioListener>("AudioListener");
	cmpFac->registerComponent<Camera>("Camera");
	cmpFac->registerComponent<MeshRenderer>("MeshRenderer");
	cmpFac->registerComponent<ParticleSystem>("ParticleSystem");
	cmpFac->registerComponent<RigidBody>("RigidBodyComponent");
	//cmpFac->registerComponent<Transform>("Transform");
	//cmpFac->registerComponent<UITextLM>("UITextLM", false);
	//cmpFac->registerComponent<UIImageLM>("UIImageLM", false);

	return true;
}

bool Initializer::MainLoop() {
	/*
	//If Ogre Manager was not initialize by a Registergame() call, it will be initialized with the name GAME DLL FAIL
	if (OgreWrapper::OgreManager::GetInstance() == nullptr) {
		OgreWrapper::OgreManager::Init();
		std::string err = OgreWrapper::OgreManager::GetInstance()->Initialize("GAME DLL FAIL");
		if (err != "") {
			LogSystem::GetInstance()->Save(0, err);
			_exit = true;
		}
	}
	//OgreWrapper::OgreManager::GetInstance()->FadeMaterial("m_Test00");
	SceneManager::Clear();
	PhysicsManager::Clear();
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();
	ScriptManager::Clear();
	InputManager::Clear();
	ComponentsFactory::Clear();
	LogSystem::Clear();
	*/

	float _dt;
	float _lastFrameTime = 0.f;

	while (!_exit) {
		if (false /*_scnManager->getCurrentScene() == nullptr*/) {
			std::cerr << "\033[1;31m" << "No scene has been loaded. Exiting now" << "\033[0m" << std::endl;
			_exit = true;
		}

		float time = clock() / (float) CLOCKS_PER_SEC;
		_dt = time - _lastFrameTime;
		_dt *= 1000.0;
		_lastFrameTime = time;

		_scnManager->update(_dt);

		Audio::AudioManager::GetInstance()->update();

		//Physics::PhysicsManager::GetInstance()->update(_dt);

		Graphics::GraphicsManager::GetInstance()->render();

		//if (LocoMotor::InputManager::GetInstance()->RegisterEvents())
		//	break;

		if (time > 1.f)
			_exit = true;
	}

	SceneManager::Release();
	ComponentsFactory::Release();
	Audio::AudioManager::Release();
	Graphics::GraphicsManager::Release();
	return true;
}