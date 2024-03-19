#include "Engine.h"
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
	_scnManager = nullptr;
	_startScene = "";
	_exit = false;
}

bool Engine::StartGameWindow(const char* gameName) {

	return Graphics::GraphicsManager::GetInstance()->initWindow(gameName);
}

bool Engine::Init() {

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
	cmpFac->registerComponent<RigidBody>("RigidBody");
	cmpFac->registerComponent<Light>("Light");
	cmpFac->registerComponent<Transform>("Transform");
	cmpFac->registerComponent<UIText>("UIText");
	cmpFac->registerComponent<UIImage>("UIImage");


	return true;
}

bool Engine::MainLoop() {
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
	_scnManager->loadScene("Assets/Scenes/Scene.lua", "Scene");
	//ComponentsFactory* cmpFac = ComponentsFactory::GetInstance();
	////cmpFac->createComponent("Camera");
	/*GameObject* camGO = scn->addGameobject("camera");
	camGO->addComponent("Transform");
	Camera* cam = (Camera*) camGO->addComponent("Camera");
	cam->init();
	GameObject* cubeGO = scn->addGameobject("cube");
	Transform* cubeTrnsf = (Transform*) cubeGO->addComponent("Transform");
	cubeTrnsf->SetPosition(LMVector3(0, 0, -150));
	cubeTrnsf->SetSize(LMVector3(20, 20, 20));
	cubeTrnsf->SetRotation(LMVector3(300, -15, 0));
	MeshRenderer* mesh = (MeshRenderer*) cubeGO->addComponent("MeshRenderer");
	mesh->init("cubeMesh", "", false);
	mesh->setMesh("Cubeman.mesh");
	mesh->setMaterial("CustomMaterial");
	mesh->setVisible(true);
	
	GameObject* lightGO = scn->addGameobject("light");
	lightGO->addComponent("Transform");
	Light* light = (Light*) lightGO->addComponent("Light");
	
	light->init("FLight", 1);

	GameObject* UI = scn->addGameobject("ui");
	UIImage* img = (UIImage*) UI->addComponent("UIImage");
	img->initializeABorrar();
	img->setImage("UIMaterial");
	img->setAnchorPoint(1.f, 0.f);
	img->setPosition(-5, 5);
	img->setPivot(1.f, 0.f);
	img->setDimensions(200, 200);

	GameObject* UIte = scn->addGameobject("uite");
	UIText* txt = (UIText*) UIte->addComponent("UIText");
	txt->initializeABorrar();
	txt->setFont("Heavitas");
	txt->setDimensions(0, 100);
	txt->setAlignment(TextAlignment::RIGHT);*/

	// Prueba input
	Input::InputManager::ControllerId firstController = Input::InputManager::invalidControllerId();
	Input::InputManager::ControllerId secondController = Input::InputManager::invalidControllerId();
	Input::InputManager::ControllerId thirdController = Input::InputManager::invalidControllerId();

	bool shown = false;

	while (!_exit) {
		if (false /*_scnManager->getCurrentScene() == nullptr*/) {
			std::cerr << "\033[1;31m" << "No scene has been loaded. Exiting now" << "\033[0m" << std::endl;
			_exit = true;
		}

		float time = clock() / (float) CLOCKS_PER_SEC;
		_dt = time - _lastFrameTime;
		_dt *= 1000.0;
		_lastFrameTime = time;

		if (Input::InputManager::GetInstance()->RegisterEvents()) {
			_exit = true;
		}

		_scnManager->update(_dt);

		Audio::AudioManager::GetInstance()->update();

		//Physics::PhysicsManager::GetInstance()->update(_dt);

		Graphics::GraphicsManager::GetInstance()->render();

		// PRUEBA INPUT
		// Teclado
		if (Input::InputManager::GetInstance()->GetKeyDown(Input::LMKS_A))
			std::cout << "KEYBOARD A" << std::endl;


		// Conexion y desconexion de mandos
		std::list<Input::InputManager::ControllerId> controllersAdded = Input::InputManager::GetInstance()->getOnConnectControllers();
		std::list<Input::InputManager::ControllerId> controllersRemoved = Input::InputManager::GetInstance()->getOnDisconnectControllers();

		// Conexion de usuarios
		for (int i = 0; i < controllersAdded.size(); i++) {
			if (firstController == Input::InputManager::invalidControllerId()) {
				firstController = controllersAdded.front();
				controllersAdded.pop_front();
			}

			else if (secondController == Input::InputManager::invalidControllerId()) {
				secondController = controllersAdded.front();
				controllersAdded.pop_front();
			}
			else
				controllersAdded.pop_front();
		}

		// Desconexion de usuarios
		for (int i = 0; i < controllersRemoved.size(); i++) {
			// Si se ha desconectado el primer usuario
			if (firstController == controllersRemoved.front()) {
				firstController = Input::InputManager::invalidControllerId();
				controllersRemoved.pop_front();
			}

			else if (secondController == controllersRemoved.front()) {
				secondController = Input::InputManager::invalidControllerId();
				controllersRemoved.pop_front();
			}
			else
				controllersRemoved.pop_front();
		}


		// Input de usuarios con mando
		if (firstController != Input::InputManager::invalidControllerId()) {
			if (Input::InputManager::GetInstance()->GetButtonDown(firstController, Input::LMControllerButtons::LMC_A))
				std::cout << "FIRST USER / Controller A" << std::endl;
			if (Input::InputManager::GetInstance()->GetButtonDown(firstController, Input::LMControllerButtons::LMC_B))
				std::cout << "FIRST USER / Controller B" << std::endl;

			float joystickValue = Input::InputManager::GetInstance()->GetJoystickValue(firstController, 0, Input::InputManager::Axis::Horizontal);
			if (joystickValue != 0)
				std::cout << "FIRST USER / Axis X = " << joystickValue << std::endl;
		}

		if (secondController != Input::InputManager::invalidControllerId()) {
			if (Input::InputManager::GetInstance()->GetButtonDown(secondController, Input::LMControllerButtons::LMC_A))
				std::cout << "SECOND USER / Controller A" << std::endl;
			if (Input::InputManager::GetInstance()->GetButtonDown(secondController, Input::LMControllerButtons::LMC_B))
				std::cout << "SECOND USER / Controller B" << std::endl;

			float joystickValue = Input::InputManager::GetInstance()->GetJoystickValue(secondController, 0, Input::InputManager::Axis::Horizontal);
			if (joystickValue != 0)
				std::cout << "SECOND USER / Axis X = " << joystickValue << std::endl;
		}

		if (thirdController != Input::InputManager::invalidControllerId()) {
			if (Input::InputManager::GetInstance()->GetButtonDown(thirdController, Input::LMControllerButtons::LMC_A))
				std::cout << "THIRD USER / Controller A" << std::endl;
			if (Input::InputManager::GetInstance()->GetButtonDown(thirdController, Input::LMControllerButtons::LMC_B))
				std::cout << "THIRD USER / Controller B" << std::endl;

			float joystickValue = Input::InputManager::GetInstance()->GetJoystickValue(thirdController, 0, Input::InputManager::Axis::Horizontal);
			if (joystickValue != 0)
				std::cout << "THIRD USER / Axis X = " << joystickValue << std::endl;
		}


		int butId = -1;

		if (time > 5.f && !shown) {
			shown = true;
			int type=2;
			std::string msg= "No funca, arreglalo";
			butId=showWindow(type,msg);
		}
		if (butId == 1) {
			_exit = true;
		}
		else if (butId == 2) {
			shown = false;
		}

	}

	

	Input::InputManager::Release();
	SceneManager::Release();
	ComponentsFactory::Release();
	Audio::AudioManager::Release();
	Graphics::GraphicsManager::Release();
	return true;
}

int Engine::showWindow(int type,std::string msg) {
	const SDL_MessageBoxButtonData buttons[] = {
		{0, 1, "Close Game" },
		{0, 0, "Ok" },
		//{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "oka" },
	};
	const SDL_MessageBoxButtonData buttons2[] = {
		{0, 1, "Close Game" },
		
	};
	const SDL_MessageBoxColorScheme colorScheme = { {0, 29, 112} };//, { 0, 29, 112 }, { 0, 29, 112 }, { 0, 29, 112 }, { 0, 29, 112 }

	
	SDL_MessageBoxData messageBoxData; 
	if(type==0){
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