#include "SceneManager.h"
#include "Scene.h"
#include <cassert>
#include <iostream>
#include "LuaParser.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
LocoMotor::SceneManager* LocoMotor::SceneManager::_instance = nullptr;

bool LocoMotor::SceneManager::Init() {
    assert(_instance == nullptr);
    _instance = new SceneManager();
    return true;
}

void LocoMotor::SceneManager::Release() {
    assert(_instance != nullptr);

    delete _instance;
    _instance = nullptr;
}

LocoMotor::SceneManager* LocoMotor::SceneManager::GetInstance() {
    assert(_instance != nullptr);
    return _instance;
}

LocoMotor::Scene* LocoMotor::SceneManager::createScene(const std::string& name) {
    if (_scenes.count(name) > 0) return _scenes[name];
    Scene* newScene = new Scene(name);
    if (_activeScene == nullptr) _toStart = newScene;
    _scenes.insert({ name,newScene });
    return newScene;
}

void LocoMotor::SceneManager::changeScene(const std::string& name) {
    if (_scenes.count(name) == 0) {
        std::cerr << "Scene \"" << name << "\", doesn't exist, call createScene(name) before trying to access a scene.\n";
        return;
    }
    else {
        _toStart = _scenes[name];
    }
}

void LocoMotor::SceneManager::loadScene(const std::string& path, const std::string& name)
{
    LuaParser parser= LuaParser();
    auto sceneMap = parser.loadSceneFromFile(path, name);
    if (!sceneMap.has_value()) {
        //TODO: Error fatal;
        return;
    }
    Scene* mScene = createScene(name);
     
    for (auto& objPair : sceneMap.value()) {
        GameObject* gObj = mScene->addGameobject(objPair.first);
        for (auto& cmpPair : objPair.second) {
            Component* cmp = gObj->addComponent(cmpPair.first);
            cmp->setParameters(cmpPair.second);
            
        }
        if (gObj->getComponent<Transform>() == nullptr) {
            Transform* tr = dynamic_cast<Transform*>(gObj->addComponent("Transform"));
            tr->InitRuntime();
        }
    }
}

void LocoMotor::SceneManager::update(float dT) {
    if (_toStart != nullptr) {
        if (_activeScene != nullptr)_activeScene->destroy();
        _toStart->start();
        _activeScene = _toStart;
        _toStart = nullptr;
    }
    if (_activeScene == nullptr) return; 
    _activeScene->update(dT);
 


}
LocoMotor::SceneManager::SceneManager() : _scenes(), _activeScene(nullptr), _toStart(nullptr), _lastFrameTime(0), _dt(0.001) {}

LocoMotor::SceneManager::~SceneManager() {

    for (auto scene : _scenes)
        delete scene.second;
}
