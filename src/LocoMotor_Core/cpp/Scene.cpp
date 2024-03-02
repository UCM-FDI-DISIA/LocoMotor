#include "Scene.h"
#include "Camera.h"
#include "GraphicsManager.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "GameObject.h"


using namespace LocoMotor;
Scene::Scene(std::string name) {
	_name = name;
	Graphics::GraphicsManager::getInstance()->createScene(_name);
}

Scene::~Scene() {
	std::unordered_map<std::string, GameObject*>::const_iterator it;
	for (it = _gameObjList.cbegin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		delete it->second;
	}
	for (it = _gameObjBufferList.cbegin(); it != _gameObjBufferList.end(); it = _gameObjBufferList.erase(it)) {
		delete it->second;
	}
	_cam = nullptr;

}


void Scene::start() {
	_toDestroy = false;
	for (auto& obj : _gameObjList) {
		//obj.second->StartComp();
	}
	_isActiveScene = true;
}


void Scene::update(float dt) {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;
	}
	for (auto& obj : _gameObjList) {
		obj.second->update(dt);
	}
	//End of loop, once all objects are Updated, add buffered objects
	for (auto& obj : _gameObjBufferList) {
		_gameObjList.insert(obj);
		//obj.second->StartComp();
	}
	_gameObjBufferList.clear();
}

void Scene::render() {
	Graphics::GraphicsManager::getInstance()->render();
}


void Scene::deactivate() {
	_toDestroy = true;
}


bool LocoMotor::Scene::toDestroy() {
	return _toDestroy;
}

void Scene::destroy() {
	_isActiveScene = false;
	std::unordered_map<std::string, GameObject*>::iterator it;
	for (it = _gameObjList.begin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		Graphics::GraphicsManager::getInstance()->destroyNode(it->second->getName());
		delete it->second;
	}
	Graphics::GraphicsManager::getInstance()->deactivateScene(_name);
}


bool Scene::getActiveStatus() {
	return _isActiveScene;
}


std::string Scene::getSceneName() {
	return _name;
}


void Scene::setSceneCam(Graphics::Camera* camera) {
	_cam = camera;
	Graphics::GraphicsManager::getInstance()->setActiveCamera(_cam);
}


GameObject* LocoMotor::Scene::addGameobject(std::string name) {
	if (_gameObjList.count(name) > 0) {
	#ifdef DEBUG
		std::cerr << "Ya existe un objeto con el nombre " << name << " se retornara" << std::endl;
	#endif // DEBUG
		return _gameObjList[name];
	}
	GameObject* newObj = new GameObject(name);
	newObj->init(this, true);
	_gameObjList.insert({ name, newObj });
	return newObj;
}
GameObject* LocoMotor::Scene::addGameobjectRuntime(std::string name) {
	//Return already existing gameObject
	if (_gameObjList.count(name) > 0) return _gameObjList[name];
	if (_gameObjBufferList.count(name) > 0) return _gameObjBufferList[name];

	//Create new Object, add to bufferList first
	GameObject* newObj = new GameObject(name);
	newObj->init(this, true);
	//newObj->addComponent("Transform");
	_gameObjBufferList.insert({ name, newObj });

	return newObj;
}

void LocoMotor::Scene::removeGameobject(std::string name) {
	if (_gameObjList.count(name) == 0) {
	#ifdef DEBUG
		std::cerr << "No existe un objeto con el nombre " << name << std::endl;
	#endif // DEBUG
		return;
	}
	delete _gameObjList[name];
	_gameObjList.erase(name);
	Graphics::GraphicsManager::getInstance()->destroyNode(name);
}


GameObject* LocoMotor::Scene::getObjectByName(std::string name) {
	if (_gameObjList.count(name) == 0)
		return nullptr;
	return _gameObjList[name];
}


GameObject* LocoMotor::Scene::getCamera() {
	return _camera_gObj;
}

void LocoMotor::Scene::setCamObj(GameObject* cam) {
	_camera_gObj = cam;
}

