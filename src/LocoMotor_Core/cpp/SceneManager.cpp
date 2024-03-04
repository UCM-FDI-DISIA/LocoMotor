#include "SceneManager.h"
#include "Scene.h"
#include <cassert>
#include <iostream>


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

void LocoMotor::SceneManager::createScene(const std::string& name) {
    if (_scenes.count(name) > 0) return;
    Scene* newScene = new Scene(name);
    if (_activeScene == nullptr) _toStart = newScene;
    _scenes.insert({ name,newScene });
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

void LocoMotor::SceneManager::update() {
    if (_toStart != nullptr) {
        _activeScene->destroy();
        _toStart->start();
        _activeScene = _toStart;
        _toStart = nullptr;
    }
    if (_activeScene == nullptr) return; 
    _activeScene->update(_dt);
    float time =  clock() / (float)CLOCKS_PER_SEC;
    _dt = time - _lastFrameTime;
    _dt *= 1000.0;
    _lastFrameTime = time;
 

}
LocoMotor::SceneManager::SceneManager() : _scenes(), _activeScene(nullptr), _toStart(nullptr), _lastFrameTime(0), _dt(0.001) {}

LocoMotor::SceneManager::~SceneManager() {}
