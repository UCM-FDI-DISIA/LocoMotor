#include "LuaBehaviour.h"
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <LuaBridge/LuaBridge.h>
#include "ScriptManager.h"

LocoMotor::LuaBehaviour::LuaBehaviour() : _luaState(nullptr), _luaUpdate(nullptr), _luaEnable(nullptr), _luaStart(nullptr), _luaAwake(nullptr), _luaFixed(nullptr),
_luaDisable(nullptr), _luaDestroy(nullptr) {}

LocoMotor::LuaBehaviour::~LuaBehaviour() {
	
	if (_luaUpdate != nullptr) delete _luaUpdate;
	if (_luaStart != nullptr) delete _luaStart;
	if (_luaDestroy != nullptr) delete _luaDestroy;
	if (_luaEnable != nullptr) delete _luaEnable;
	if (_luaEnable != nullptr) delete _luaDisable;
	if (_luaAwake != nullptr) delete _luaAwake;
	if (_luaFixed != nullptr) delete _luaFixed;
	if (obj != nullptr) delete obj;
}

void LocoMotor::LuaBehaviour::start() {
	(*_luaStart)();
}

void LocoMotor::LuaBehaviour::update(float dt) {
	(*_luaUpdate)(dt);
}

void LocoMotor::LuaBehaviour::setParameters(ComponentMap& params) {
	for (auto it = params.begin(); it != params.end(); ) {
		if ((*it).first == "scriptName") {
			_name = (*it).second;
			Scripting::ScriptManager::GetInstance()->loadScript(_name, this);
			if (!initBehaviour()) {
				
			}
			params.erase(it);
			break;
		
		}
		else {
			++it;
		}
	}
	//luaSetParameters(params);
}

bool LocoMotor::LuaBehaviour::initBehaviour() {
	luabridge::setGlobal(_luaState, this, "obj");

	obj = new luabridge::LuaRef(luabridge::getGlobal(_luaState, (_name + "Var").c_str()));

	if ((*obj).isNil()) {
		std::cout << "ESNIL" << std::endl;
		return false;
	}

	_luaUpdate = new luabridge::LuaRef((*obj)["update"]);
	_luaStart = new luabridge::LuaRef((*obj)["start"]);
	_luaFixed = new luabridge::LuaRef((*obj)["fixedUpdate"]);
	_luaEnable = new luabridge::LuaRef((*obj)["onEnable"]);
	_luaDisable = new luabridge::LuaRef((*obj)["onDisable"]);
	_luaAwake = new luabridge::LuaRef((*obj)["awake"]);
	return true;
}
