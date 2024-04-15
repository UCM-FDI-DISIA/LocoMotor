#include "Engine.h"
#include "GraphicsManager.h"
#include "ComponentsFactory.h"
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "LMInputs.h"

#include "AudioSource.h"
#include "EventEmitter.h"
#include "AudioListener.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Rigidbody.h"
#include "UIImage.h"
#include "UIText.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMVector.h"
#include "LuaParser.h"

#include <iostream>
#include <SDL_messagebox.h>

using namespace LocoMotor;

Engine* Engine::_instance = nullptr;

Engine::Engine() {
	_gameName = "No window title";
	_startingSceneFile = "";
	_startingSceneName = "";
	_scnManager = nullptr;
	_startScene = "";
	_exit = false;
}

Engine::~Engine() {

}

bool Engine::Init() {

	assert(_instance == nullptr);
	_instance = new Engine();
	if (!_instance->init()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}
	return true;
}
bool Engine::init(){
	if (!Graphics::GraphicsManager::Init()) {
		return false;
	}

	if (!Audio::AudioManager::Init(true)) {
		Graphics::GraphicsManager::Release();
		return false;
	}

	if (!Physics::PhysicsManager::Init()) {
		Physics::PhysicsManager::Release();
		return false;
	}
	//PhysicsManager::GetInstance()->SetContactStartCallback(LMcontactStart);
	//PhysicsManager::GetInstance()->SetContactProcessCallback(LMcontactProcessed);
	//PhysicsManager::GetInstance()->SetContactEndedCallback(LMcontactExit);
	//InputManager::Init();
	//SceneManager::Init();
	//ScriptManager::Init();

	if (!ComponentsFactory::Init()) {
		Audio::AudioManager::Release();
		Graphics::GraphicsManager::Release();
		Physics::PhysicsManager::Release();
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
		return false;
	}
	
	_scnManager = SceneManager::GetInstance();

	// Inicializar inputManager
	if (!Input::InputManager::Init()) {
		SceneManager::Release();
		ComponentsFactory::Release();
		cmpFac = nullptr;
		Audio::AudioManager::Release();
		Graphics::GraphicsManager::Release();
		return false;
	}


	cmpFac->registerComponent<EventEmitter>("EventEmitter");
	cmpFac->registerComponent<AudioSource>("AudioSource");
	cmpFac->registerComponent<AudioListener>("AudioListener");
	cmpFac->registerComponent<Camera>("Camera");
	cmpFac->registerComponent<MeshRenderer>("MeshRenderer");
	cmpFac->registerComponent<ParticleSystem>("ParticleSystem");
	cmpFac->registerComponent<RigidBody>("RigidBody");
	cmpFac->registerComponent<Light>("Light");
	cmpFac->registerComponent<Transform>("Transform");
	cmpFac->registerComponent<UIText>("UIText");
	cmpFac->registerComponent<UIImage>("UIImage");


	return true;
}

Engine* LocoMotor::Engine::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}

void LocoMotor::Engine::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

void LocoMotor::Engine::setWindowName(const std::string& name) {
	_gameName = name;
}

void LocoMotor::Engine::setStartingScene(const std::string& file, const std::string& name) {
	_startingSceneFile = file;
	_startingSceneName = name;
}

bool Engine::mainLoop() {

	

	if (!Graphics::GraphicsManager::GetInstance()->initWindow(_gameName)) {
		std::cerr << "Error creating game window" << std::endl;
		_exit = true;
	}
	else if (_startingSceneFile != "" && _startingSceneName != "") {
		_scnManager->loadScene(_startingSceneFile, _startingSceneName);
		_scnManager->changeScene(_startingSceneName);
	}


	float _dt;
	float _lastFrameTime = 0.f;

	// Prueba input
	Input::InputManager::ControllerId firstController = Input::InputManager::invalidControllerId();
	Input::InputManager::ControllerId secondController = Input::InputManager::invalidControllerId();
	Input::InputManager::ControllerId thirdController = Input::InputManager::invalidControllerId();

	//// Prueba animaciones
	//GameObject* cubeGO = nullptr;
	//MeshRenderer* mainMesh = nullptr;
	//Transform* cubeTrnsf = nullptr;



	bool shown = false;
	float fixedTimeStep = 16;
	float fixedTime = 0.f;

	while (!_exit) {
		if (_scnManager->getActiveScene() == nullptr) {
			std::cerr << "\033[1;31m" << "No scene has been loaded. Exiting now" << "\033[0m" << std::endl;
			_exit = true;
			break;
		}

		float time = clock() / (float) CLOCKS_PER_SEC;
		_dt = time - _lastFrameTime;
		_dt *= 1000.0;
		fixedTime += _dt;
		_lastFrameTime = time;
		while (fixedTime >= fixedTimeStep) {
			_scnManager->fixedUpdate();
			Physics::PhysicsManager::GetInstance()->update(fixedTimeStep);
			fixedTime -= fixedTimeStep;
		}

		if (Input::InputManager::GetInstance()->RegisterEvents()) {
			_exit = true;
		}

		_scnManager->update(_dt);

		//if (cubeTrnsf != nullptr) {
		//	cubeGO = SceneManager::GetInstance()->getActiveScene()->getObjectByName("cube");
		//	cubeTrnsf = cubeGO->getComponent<Transform>();
		//	mainMesh = cubeGO->getComponent<MeshRenderer>();
		//}

		Audio::AudioManager::GetInstance()->update();

		

		Graphics::GraphicsManager::GetInstance()->render();
//
//		// PRUEBA INPUT
//		// Teclado
///*		if (Input::InputManager::GetInstance()->GetKeyDown(Input::LMKS_A)) {
//			std::cout << "KEYBOARD A" << std::endl;
//
//			if (SceneManager::GetInstance()->getActiveScene()->getObjectByName("cube") != nullptr) {
//
//				mainMesh->setEnabled(!mainMesh->isEnabled());
//			}
//		}
//		else */if (Input::InputManager::GetInstance()->GetKeyDown(Input::LMKS_S)) {
//			if (mainMesh != nullptr)
//				mainMesh->playAnimation("Idle", true);
//		}
//		else if (Input::InputManager::GetInstance()->GetKeyDown(Input::LMKS_D)) {
//			if (mainMesh != nullptr)
//				mainMesh->playAnimation("Run", true);
//		}
//		else if (Input::InputManager::GetInstance()->GetKey(Input::LMKS_E)) {
//			if (cubeTrnsf != nullptr)
//				cubeTrnsf->SetRotation(LMVector3(cubeTrnsf->GetRotation().GetX(),
//					cubeTrnsf->GetRotation().GetY() + 60 * _dt/1000, cubeTrnsf->GetRotation().GetZ()));
//		}
//
//		if (mainMesh != nullptr)
//			mainMesh->updateAnimation(_dt / 1000);
//		else
//
//			std::cout << "mainMesh null" << std::endl;


		//// Conexion y desconexion de mandos
		//std::list<Input::InputManager::ControllerId> controllersAdded = Input::InputManager::GetInstance()->getOnConnectControllers();
		//std::list<Input::InputManager::ControllerId> controllersRemoved = Input::InputManager::GetInstance()->getOnDisconnectControllers();

		//// Conexion de usuarios
		//for (const Input::InputManager::ControllerId& controllerId : controllersAdded) {

		//	if (firstController == Input::InputManager::invalidControllerId())
		//		firstController = controllerId;

		//	else if (secondController == Input::InputManager::invalidControllerId())
		//		secondController = controllerId;

		//	else if (thirdController == Input::InputManager::invalidControllerId())
		//		thirdController = controllerId;
		//}

		//// Desconexion de usuarios
		//for (const Input::InputManager::ControllerId& controllerId : controllersRemoved) {

		//	// Si se ha desconectado el primer usuario
		//	if (firstController == controllerId)
		//		firstController = Input::InputManager::invalidControllerId();

		//	else if (secondController == controllerId)
		//		secondController = Input::InputManager::invalidControllerId();

		//	else if (thirdController == controllerId)
		//		thirdController = Input::InputManager::invalidControllerId();
		//}


		//// Input de usuarios con mando
		//if (firstController != Input::InputManager::invalidControllerId()) {
		//	if (Input::InputManager::GetInstance()->GetButtonDown(firstController, Input::LMControllerButtons::LMC_A))
		//		std::cout << "FIRST USER / Controller A" << std::endl;
		//	if (Input::InputManager::GetInstance()->GetButtonDown(firstController, Input::LMControllerButtons::LMC_B)) {
		//		std::cout << "FIRST USER / Controller B" << std::endl;
		//		Input::InputManager::GetInstance()->RumbleController(secondController, 1, 0.3f);
		//	}

		//	float joystickValue = Input::InputManager::GetInstance()->GetJoystickValue(firstController, 0, Input::InputManager::Axis::Horizontal);
		//	if (joystickValue != 0)
		//		std::cout << "FIRST USER / Axis X = " << joystickValue << std::endl;

		//	float triggerValue = Input::InputManager::GetInstance()->GetTriggerValue(firstController, 0);
		//	if (triggerValue != 0)
		//		std::cout << "FIRST USER / Trigger Left = " << triggerValue << std::endl;
		//}

		//if (secondController != Input::InputManager::invalidControllerId()) {
		//	if (Input::InputManager::GetInstance()->GetButtonDown(secondController, Input::LMControllerButtons::LMC_A))
		//		std::cout << "SECOND USER / Controller A" << std::endl;
		//	if (Input::InputManager::GetInstance()->GetButtonDown(secondController, Input::LMControllerButtons::LMC_B)) {
		//		std::cout << "SECOND USER / Controller B" << std::endl;
		//		Input::InputManager::GetInstance()->SetControllerLedColor(firstController, 0, 255, 255);
		//	}

		//	float joystickValue = Input::InputManager::GetInstance()->GetJoystickValue(secondController, 0, Input::InputManager::Axis::Horizontal);
		//	if (joystickValue != 0)
		//		std::cout << "SECOND USER / Axis X = " << joystickValue << std::endl;
		//}

		//if (thirdController != Input::InputManager::invalidControllerId()) {
		//	if (Input::InputManager::GetInstance()->GetButtonDown(thirdController, Input::LMControllerButtons::LMC_A))
		//		std::cout << "THIRD USER / Controller A" << std::endl;
		//	if (Input::InputManager::GetInstance()->GetButtonDown(thirdController, Input::LMControllerButtons::LMC_B))
		//		std::cout << "THIRD USER / Controller B" << std::endl;

		//	float joystickValue = Input::InputManager::GetInstance()->GetJoystickValue(thirdController, 0, Input::InputManager::Axis::Horizontal);
		//	if (joystickValue != 0)
		//		std::cout << "THIRD USER / Axis X = " << joystickValue << std::endl;
		//}



	}



	Input::InputManager::Release();
	SceneManager::Release();
	ComponentsFactory::Release();
	Audio::AudioManager::Release();
	Physics::PhysicsManager::Release();
	Graphics::GraphicsManager::Release();
	return true;
}

int Engine::showWindow(int type, std::string msg) {
	const SDL_MessageBoxButtonData buttons[] = {
		{0, 1, "Close Game" },
		{0, 0, "Ok" },

	};
	const SDL_MessageBoxButtonData buttons2[] = {
		{0, 1, "Close Game" },

	};
	const SDL_MessageBoxColorScheme colorScheme = { {0, 29, 112} };


	SDL_MessageBoxData messageBoxData;
	if (type == 0) {
		messageBoxData = {
			SDL_MESSAGEBOX_INFORMATION,
			NULL,
			"Info",
			msg.c_str(),
			SDL_arraysize(buttons),
			buttons,
			&colorScheme
		};
	}
	else if (type == 1) {
		messageBoxData = {
			SDL_MESSAGEBOX_WARNING,
			NULL,
			"Warning",
			msg.c_str(),
			SDL_arraysize(buttons),
			buttons,
			&colorScheme
		};
	}
	else {
		messageBoxData = {
			SDL_MESSAGEBOX_ERROR,
			NULL,
			"Error",
			msg.c_str(),
			SDL_arraysize(buttons2),
			buttons2,
			&colorScheme
		};
	}
	int butId = -1;
	SDL_ShowMessageBox(&messageBoxData, &butId);

	return butId;
}

void Engine::quit() {
	_exit = true;
}