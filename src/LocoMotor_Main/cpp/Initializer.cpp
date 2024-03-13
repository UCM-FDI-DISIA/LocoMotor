#include "Initializer.h"
#include "GraphicsManager.h"
#include "ComponentsFactory.h"
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "LMInputs.h"

#include "AudioSource.h"
#include "AudioListener.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Rigidbody.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"

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

	// Inicializar inputManager
	if (!Input::InputManager::Init()) {
		SceneManager::Release();
		ComponentsFactory::Release();
		cmpFac = nullptr;
		Audio::AudioManager::Release();
		Graphics::GraphicsManager::Release();
	}




	cmpFac->registerComponent<AudioSource>("AudioSource");
	cmpFac->registerComponent<AudioListener>("AudioListener");
	cmpFac->registerComponent<Camera>("Camera");
	cmpFac->registerComponent<MeshRenderer>("MeshRenderer");
	cmpFac->registerComponent<ParticleSystem>("ParticleSystem");
	cmpFac->registerComponent<RigidBody>("RigidBodyComponent");
	cmpFac->registerComponent<Light>("Light");

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

	Scene* scn = _scnManager->createScene("prueba");
	ComponentsFactory* cmpFac = ComponentsFactory::GetInstance();
	//cmpFac->createComponent("Camera");
	GameObject* camGO = scn->addGameobject("camera");
	Camera* cam = (Camera*) camGO->addComponent("Camera");
	cam->init();
	GameObject* cubeGO = scn->addGameobject("cube");
	MeshRenderer* mesh = (MeshRenderer*) cubeGO->addComponent("MeshRenderer");
	mesh->init("cubeMesh", "", false);
	mesh->setMesh("Cubeman.mesh");
	mesh->setMaterial("CustomMaterial");
	mesh->setVisible(true);

	GameObject* lightGO = scn->addGameobject("light");
	Light* light = (Light*) lightGO->addComponent("Light");

	light->init("FLight", 1);

	// Prueba input
	Input::InputManager::ControllerId mainControllerId = Input::InputManager::invalidControllerId();

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



		// PRUEBA INPUT
		Input::InputManager::GetInstance()->RegisterEvents();

		// Teclado
		if (Input::InputManager::GetInstance()->GetKeyDown(Input::LMKS_A))
			std::cout << "A" << std::endl;


		// Conexion y desconexion de mandos
		std::list<Input::InputManager::ControllerId> controllersAdded = Input::InputManager::GetInstance()->getOnConnectControllers();
		std::list<Input::InputManager::ControllerId> controllersRemoved = Input::InputManager::GetInstance()->getOnDisconnectControllers();

		if (controllersAdded.size() > 0)
				mainControllerId = controllersAdded.front();

		// Prueba Mando
		if (mainControllerId != Input::InputManager::invalidControllerId()) {
			if (Input::InputManager::GetInstance()->GetButtonDown(mainControllerId, Input::LMControllerButtons::LMC_A))
				std::cout << "Controller A" << std::endl;
			if (Input::InputManager::GetInstance()->GetButtonDown(mainControllerId, Input::LMControllerButtons::LMC_B))
				std::cout << "Controller B" << std::endl;
		}

		//if (Input::InputManager::GetInstance()->GetJoystickValue(0, Input::InputManager::Axis::Horizontal))
		//	std::cout << "Axis X" << std::endl;
		//if (Input::InputManager::GetInstance()->GetJoystickValue(0, Input::InputManager::Axis::Vertical))
		//	std::cout << "Axis Y" << std::endl;


		/*if (time > 1.f)
			_exit = true;*/
	}

	SceneManager::Release();
	ComponentsFactory::Release();
	Audio::AudioManager::Release();
	Graphics::GraphicsManager::Release();
	return true;
}