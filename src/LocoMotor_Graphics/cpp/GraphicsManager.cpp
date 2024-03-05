//Ogre includes
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreGpuProgramManager.h>
#include <OgreShaderGenerator.h>
#include <OgreOverlaySystem.h>
#include <OgreViewport.h>
#include <OgreMaterialManager.h>
//SDL includes
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
//Std include
#include <iostream>
//Graphics includes
#include "GraphicsManager.h"
#include "Camera.h"
#include "SGTechniqueResolverListener.h"
#include "Node.h"
#include "Light.h"

using namespace LocoMotor;
using namespace Graphics;

static GraphicsManager* _instance = nullptr;

GraphicsManager::GraphicsManager() {
	_activeScene = nullptr;
	_mShaderGenerator = nullptr;
	_root = nullptr;
	_ovrSys = nullptr;
	_nodeRoot = nullptr;
	_mLight = nullptr;
}

GraphicsManager::~GraphicsManager() {
	shutdown();
}

std::string GraphicsManager::initialize(std::string name) {
	try {
		_root = new Ogre::Root();
		_ovrSys = new Ogre::OverlaySystem();
	}
	catch (...) {
		return "Error while constructing internal ogre library";
	}
	try {
		_root->showConfigDialog(nullptr);
		_root->restoreConfig();
		_root->initialise(false);
	}
	catch (...) {
		return "Error while initializing internal ogre library";
	}
	try {
		initWindow(name);
	}
	catch (...) {
		return "Error while initializing window";
	}
	try {
		loadResources();
	}
	catch (...) {
		return "Error while loading resources: make sure all .fontdef, .material, .particle, etc have no duplicates/are correctly written";
	}
	return "";
}

void GraphicsManager::init() {
	if (_instance == nullptr) {
		_instance = new GraphicsManager();
	}
}

void GraphicsManager::createScene(std::string name) {
	if (_scenes.count(name) > 0) {
		std::cerr << "ERROR: Ya hay una escena con el nombre \"" << name << "\". Elige otro nombre por favor\n";
		return;
	}
	Ogre::SceneManager* sM = _root->createSceneManager();
	sM->addRenderQueueListener(_ovrSys);
	_scenes.insert({ name, sM });
	if (_activeScene == nullptr) _activeScene = sM;
	_mShaderGenerator->addSceneManager(sM);
	_nodeRoot = new Node(sM->getRootSceneNode(), "root");
}

void GraphicsManager::render() {
	if (_activeScene == nullptr) return;
	_camera->render();
	_root->renderOneFrame();
}

Ogre::RenderWindow* GraphicsManager::getRenderWindow() {
	return _mWindow.render;
}

void GraphicsManager::setActiveScene(std::string name) {
	if (_scenes.count(name) == 0) {
		std::cerr << "ERROR: No existe una escena con el nombre \"" << name << "\".\n";
		return;
	}
	for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
		if (it->first == name) {
			_activeScene = it->second;
			return;
		}
	}
}

Ogre::Entity* GraphicsManager::createRenderer(std::string src) {

	return _activeScene->createEntity(src);

}

Ogre::Light* GraphicsManager::createMainLight() {

	_mLight = _activeScene->createLight();
	return _mLight;

}

Ogre::Light* GraphicsManager::getMainLight() {
	return _mLight;
}

int GraphicsManager::getWindowHeight() {
	return _mWindow.render->getHeight();
}

int GraphicsManager::getWindowWidth() {
	return _mWindow.render->getWidth();
}

GraphicsManager* LocoMotor::Graphics::GraphicsManager::getInstance() {
	if (_instance == nullptr) {
		_instance = new GraphicsManager();
	}
	return _instance;
}

void LocoMotor::Graphics::GraphicsManager::deactivateScene(std::string name) {
	if (_scenes.count(name) == 0) {
		std::cerr << "ERROR: No existe una escena con el nombre \"" << name << "\".\n";
		return;
	}
	for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
		if (it->first == name) {
			it->second->destroyAllCameras();
			it->second->destroyAllParticleSystems();
			return;
		}
	}
}

void GraphicsManager::loadResources() {
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	Ogre::String sec_name , type_name , arch_name;
	Ogre::ConfigFile::SettingsBySection_ seci = cf.getSettingsBySection();

	for (Ogre::ConfigFile::SettingsBySection_::const_iterator it = seci.cbegin(); it != seci.cend(); ++it) {
		sec_name = it->first;
		Ogre::ConfigFile::SettingsMultiMap settings = it->second;
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings.begin(); i != settings.end(); ++i) {
			type_name = i->first;
			arch_name = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				arch_name , type_name , sec_name);
		}
	}

	sec_name = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec_name);

	arch_name = genLocs.front().archive->getName();
	type_name = genLocs.front().archive->getType();

	std::string mRTShaderLibPath = arch_name + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials" , type_name , sec_name);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL" , type_name , sec_name);

	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	if (Ogre::RTShader::ShaderGenerator::initialize()) {
		_mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		if (mRTShaderLibPath.empty())
			return;

		// Create and register the material manager listener if it doesn't exist yet.
		if (!_mMaterialMgrListener) {
			_mMaterialMgrListener = new SGTechniqueResolverListener(_mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener((Ogre::MaterialManager::Listener*) _mMaterialMgrListener);
		}
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

NativeWindowPair GraphicsManager::initWindow(std::string name) {
	uint32_t w , h;
	Ogre::NameValuePairList miscParams;

	Ogre::ConfigOptionMap ropts = _root->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w; // width
	mode >> token; // 'x' as seperator between width and height
	mode >> h; // height

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt"))
			std::cout << "Gamecontroller Mappings Loaded" << "\n";
		else
			std::cout << "Gamecontroller Mappings NOT Loaded" << "\n";

		SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	}

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (ropts["Full Screen"].currentValue == "Yes")  flags = SDL_WINDOW_FULLSCREEN;

	_mWindow.native = SDL_CreateWindow(name.c_str() , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , w , h , flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_mWindow.native , &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	_mWindow.render = _root->createRenderWindow(name , w , h , false , &miscParams);
	return _mWindow;
}


void GraphicsManager::shutdown() {

	// Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (_mMaterialMgrListener != nullptr) {
		Ogre::MaterialManager::getSingleton().removeListener((Ogre::MaterialManager::Listener*) _mMaterialMgrListener);
		delete _mMaterialMgrListener;
		_mMaterialMgrListener = nullptr;
	}

	// Destroy RTShader system.
	if (_mShaderGenerator != nullptr) {
		Ogre::RTShader::ShaderGenerator::destroy();
		_mShaderGenerator = nullptr;
	}

	for (auto it = _scenes.begin(); it != _scenes.end(); it = _scenes.erase(it)) {
		if (it->second == _activeScene) {
			_activeScene = nullptr;
		}
		it->second->removeRenderQueueListener(_ovrSys);
		_root->destroySceneManager(it->second);
		delete it->second;
	}

	if (_mWindow.render != nullptr) {
		_root->destroyRenderTarget(_mWindow.render);
		_mWindow.render = nullptr;
	}

	if (_mWindow.native != nullptr) {
		SDL_DestroyWindow(_mWindow.native);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		_mWindow.native = nullptr;
	}

	if (_mLight != nullptr) {
		_activeScene->destroyLight(_mLight);
		_mLight = nullptr;
	}

	delete Ogre::OverlaySystem::getSingletonPtr();
	delete _root;
	_root = nullptr;

	delete _instance;
	_instance = nullptr;

	delete _nodeRoot;
	_nodeRoot = nullptr;
}


Node* GraphicsManager::createNode(std::string name) {
	if (_sceneNodes.count(name) > 0 || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	Node* node = _nodeRoot->CreateChild(name);
	_sceneNodes.insert({ name,node });
	return node;
}

Node* GraphicsManager::createNode(std::string name, std::string parent) {
	if (_sceneNodes.count(name) > 0 || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	else if (_sceneNodes.count(parent) == 0) {
		std::cerr << "No node with name " << name << " found. Could not create child\n";
		return nullptr;
	}
	else if (parent == "Root") {
		return createNode(name);
	}
	Node* node = getNode(name)->CreateChild(name);
	return node;
}

Node* GraphicsManager::getNode(std::string name) {
	if (_sceneNodes.count(name) == 0) {
		std::cerr << "No node with the name " << name << " found\n";
		return nullptr;
	}
	if (name == "Root") {
		return _nodeRoot;
	}

	return _sceneNodes.at(name);
}

void GraphicsManager::destroyNode(std::string name) {
	if (_sceneNodes.count(name) == 0 || name == "Root") {
		std::cerr << "No node with the name " << name << " found\n";
	}
	else {
		_nodeRoot->DestroyChild(_sceneNodes[name]);
		_sceneNodes.erase(name);
	}
}

Ogre::SceneManager* LocoMotor::Graphics::GraphicsManager::getSceneManager() {
	return _activeScene;
}
