#include "ScriptManager.h"

#include <cassert>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

using namespace LocoMotor;
using namespace LocoMotor::Scripting;

ScriptManager* ScriptManager::_instance = nullptr;

ScriptManager::ScriptManager() : _luaState(nullptr) {}
ScriptManager::~ScriptManager() {
	//Close scripts and Lua Context
}

bool ScriptManager::Init() {
	assert(_instance == nullptr);
	return true;
}