#include "ScriptManager.h"

#include <cassert>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

#include "LuaBehaviour.h"

using namespace LocoMotor;
using namespace LocoMotor::Scripting;

ScriptManager* ScriptManager::_instance = nullptr;

ScriptManager::ScriptManager() : _luaState(nullptr) {}
ScriptManager::~ScriptManager() {
	//Close scripts and Lua Context
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
		.beginClass<LuaBehaviour>("Polla")
		.addFunction("update", &LuaBehaviour::update)
		.addFunction("start", &LuaBehaviour::start)
		.addFunction("onEnable", &LuaBehaviour::onEnable)
		.addFunction("onDisable", &LuaBehaviour::onDisable)
		.addFunction("fixedUpdate", &LuaBehaviour::fixedUpdate)
		.addFunction("awake", &LuaBehaviour::awake)
		.addFunction("setParameters", &LuaBehaviour::setParameters)
		.addFunction("helloWorld", &LuaBehaviour::helloWorld)
		.endClass();
		
}

bool ScriptManager::Init() {
	assert(_instance == nullptr);
	std::cout << "Init estatico" << std::endl;
	_instance = new ScriptManager();
	_instance->initLua();
	//Lua context initialization
	//Preload Scripts??
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

void ScriptManager::test() {
	if (luaL_dofile(_luaState, "Assets/Scripts/Prueba.lua")) {
		std::cerr << "Error leyendo script " << lua_tostring(_luaState, -1);
		return;
	}


}
