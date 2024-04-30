#include "ScriptManager.h"

#include <cassert>
#include <functional>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>
#include "GameObject.h"
#include "LuaBehaviour.h"
#include "Transform.h"
#include "LMVector.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Engine.h"

using namespace LocoMotor;
using namespace LocoMotor::Scripting;

ScriptManager* ScriptManager::_instance = nullptr;

ScriptManager::ScriptManager() : _luaState(nullptr) {}
ScriptManager::~ScriptManager() {
	lua_close(_luaState);
}

bool LocoMotor::Scripting::ScriptManager::initLua() {
	std::cout << "init Lua" << std::endl;
	_luaState = luaL_newstate();
	if (_luaState == nullptr) {
		std::cerr << "[Script error] Could not create lua state" << std::endl;
		return false;
	}
	luaL_openlibs(_luaState);
	registerToLua();
	return true;
}

void LocoMotor::Scripting::ScriptManager::registerToLua() {
	std::cout << "Registrando clases señores" << std::endl;
	luabridge::getGlobalNamespace(_luaState)
		.beginClass<LuaBehaviour>("LuaBehaviour")
		.addFunction("gameObject", &LuaBehaviour::getGameObject)
		.endClass()

		.beginClass<GameObject>("GameObject")
		.addFunction("transform", &GameObject::getTransform)
		.addFunction("addComponent", &GameObject::addComponent)
		.addFunction("getComponent", &GameObject::getComponentByName)
		.addFunction("isActive", &GameObject::isActive)
		.addFunction("setActive", &GameObject::setActive)
		.addFunction("removeComponent", &GameObject::removeComponents)
		.addFunction("getName", &GameObject::getName)
		.endClass()

		.beginClass<LMVector3>("Vector3")
		.addStaticFunction("new", &LMVector3::createVector)
		.addProperty("x", &LMVector3::getX, &LMVector3::setX)
		.addProperty("y", &LMVector3::getY, &LMVector3::setY)
		.addProperty("z", &LMVector3::getZ, &LMVector3::setZ)
		.addFunction("magnitude", &LMVector3::magnitude)
		.addFunction("normalize", &LMVector3::normalize)
		.endClass()

		.beginClass<LMQuaternion>("Quaternion")
		.addStaticFunction("new", &LMQuaternion::createQuat)
		.addProperty("x", &LMQuaternion::getX, &LMQuaternion::setX)
		.addProperty("y", &LMQuaternion::getY, &LMQuaternion::setY)
		.addProperty("z", &LMQuaternion::getZ, &LMQuaternion::setZ)
		.addFunction("magnitude", &LMQuaternion::magnitude)
		.addFunction("normalize", &LMQuaternion::normalize)
		.endClass()

		.beginClass<Transform>("Transform")
		.addProperty("position", &Transform::getPosition, &Transform::setPosition)
		.addProperty("rotation", &Transform::getRotation, &Transform::setRotation)
		.addProperty("size", &Transform::getSize, &Transform::setSize)
		.addFunction("getEulerRotation", &Transform::getEulerRotation)
		.endClass()

		.beginClass<Scene>("Scene")
		.addFunction("addGameObject", &Scene::addGameobject)
		.addFunction("removeGameObject", &Scene::removeGameobject)
		.addFunction("getObjectByName", &Scene::getObjectByName)
		.addFunction("name", &Scene::getSceneName)
		.endClass()

		.beginClass<SceneManager>("SceneManager")
		.addStaticFunction("Instance", &SceneManager::GetInstance)
		.addFunction("loadScene", &SceneManager::loadScene)
		.addFunction("changeScene", &SceneManager::changeScene)
		.addFunction("getActiveScene", &SceneManager::getActiveScene)
		.endClass();
}

bool ScriptManager::Init() {
	assert(_instance == nullptr);
	_instance = new ScriptManager();
	if (!_instance->initLua()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}
	return true;
}

void ScriptManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

ScriptManager* LocoMotor::Scripting::ScriptManager::GetInstance() {
	return _instance;
}

bool LocoMotor::Scripting::ScriptManager::loadScript(const std::string& name, LuaBehaviour* behaviour) {
	static const std::string basePath = "Assets/Scripts/";
	static const std::string luaExtension = ".lua";
	std::string fullPath = basePath + name + luaExtension;

	
	
	
	luabridge::setGlobal(_luaState, behaviour, "behaviour");
	if (luaL_dofile(_luaState, fullPath.c_str())) {
		std::string error = "Interpretation error at component " + name
			+ "\n" + std::string(lua_tostring(_luaState, -1));
		std::cerr << error << std::endl;
		Engine::GetInstance()->showWindow(2, error);
		return false;
	}
	behaviour->setLuaContext(_luaState);
	return true;
}

