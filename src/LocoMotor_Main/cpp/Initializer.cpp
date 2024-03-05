#include "Initializer.h"
//#include "GraphicsManager.h"
#include "ComponentsFactory.h"
#include "PhysicsManager.h"
#include "AudioManager.h"

#include "AudioSource.h"
#include "AudioListener.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "Rigidbody.h"

using namespace LocoMotor;

Initializer::Initializer() {
	_gameName = "No window title";
	_scnManager = nullptr;
	_startScene = "";
	_exit = false;
}

bool Initializer::StartGameWindow(const char* gameName) {
	/*
	_gameName = gameName;
	std::string err = OgreWrapper::OgreManager::GetInstance()->Initialize(gameName);
	if (err != "") {
		LogSystem::GetInstance()->Save(0, err);
		_exit = true;
	}
	*/
	return true;
}

bool Initializer::Init() {
	//Graphics::GraphicsManager::Init();

	if (!Audio::AudioManager::Init()) {
		//Graphics::GraphicsManager::Release();
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
		//Graphics::GraphicsManager::Release();
		Audio::AudioManager::Release();
		//Physics::PhysicsManager::Release();
		//InputManager::Release();
		//SceneManager::Release();
		//ScriptManager::Release();
		return false;
	}
	ComponentsFactory* cmpFac = ComponentsFactory::GetInstance();

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
	while (!_exit) {
		if (_scnManager->GetCurrentScene() == nullptr) {
			LogSystem::GetInstance()->Save(0, "No scene has been loaded. Exiting now");
			break;
		}

		FmodWrapper::AudioManager::GetInstance()->Update(_scnManager->GetDelta());
		OgreWrapper::OgreManager::GetInstance()->Render();

		PhysicsManager::GetInstance()->Update(_scnManager->GetDelta());

		if (LocoMotor::InputManager::GetInstance()->RegisterEvents())
			break;
		_scnManager->Update();
	}
	SceneManager::Clear();
	PhysicsManager::Clear();
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();
	ScriptManager::Clear();
	InputManager::Clear();
	ComponentsFactory::Clear();
	LogSystem::Clear();
	return;
	*/
	Audio::AudioManager::Release();
	ComponentsFactory::Release();
	return true;
}