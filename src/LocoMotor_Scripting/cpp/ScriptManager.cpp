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
	luabridge::getGlobalNamespace(_luaState)
		.beginNamespace("LocoMotor")
		.beginClass<LuaBehaviour>("LuaBehaviour")
		.addFunction("update", &LuaBehaviour::update)
		.addFunction("start", &LuaBehaviour::start)
		.addFunction("onEnable", &LuaBehaviour::onEnable)
		.addFunction("onDisable", &LuaBehaviour::onDisable)
		.addFunction("fixedUpdate", &LuaBehaviour::fixedUpdate)
		.addFunction("awake", &LuaBehaviour::awake)
		.endClass()
		.endNamespace();
}

bool ScriptManager::Init() {
	assert(_instance == nullptr);
	//Lua context initialization
	//Preload Scripts??
	return true;
}

void ScriptManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}