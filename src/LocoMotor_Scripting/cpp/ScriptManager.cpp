#include "ScriptManager.h"

#include <cassert>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>
#include "GameObject.h"
#include "LuaBehaviour.h"
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

