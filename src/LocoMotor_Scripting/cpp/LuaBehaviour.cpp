#include "LuaBehaviour.h"
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>
#include "ScriptManager.h"
#include "Engine.h"


LocoMotor::LuaBehaviour::LuaBehaviour() : _luaState(nullptr), _luaUpdate(nullptr), _luaEnable(nullptr), _luaStart(nullptr), _luaAwake(nullptr), _luaFixed(nullptr),
_luaDisable(nullptr), _luaDestroy(nullptr), _luaSetParameters(nullptr) {
}

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
	if (_luaUpdate == nullptr) return;
	try {
		(*_luaUpdate)(obj, dt);
	}
	catch (luabridge::LuaException& except) {
		std::cout << except.what() << std::endl;
	}
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
	if (params.size() == 0) return;
	//Si se esta inicializando con parametros (desde la carga de mapas) creo una tabla de lua con los parametros, porque LuaBridge no tiene un
	//wrapper para poder pasar std::pairs a Lua
	luabridge::LuaRef table = luabridge::newTable(_luaState);
	for (auto& param : params) {
		table[param.first] = param.second;
	}
	try {		
		(*_luaSetParameters)(obj, table);
	}
	catch (luabridge::LuaException e) {
		std::cout << e.what();
	}
	
}

bool LocoMotor::LuaBehaviour::initBehaviour() {
	luabridge::setGlobal(_luaState, this, "obj");

	obj = new luabridge::LuaRef(luabridge::getGlobal(_luaState, (_name + "Var").c_str()));

	if ((*obj).isNil()) {
		std::cout << "Lua Interpreter Error: No variable called " << _name << "Var on the lua script " << _name << ".lua" << std::endl;
		std::cout << "Please define a variable called " << _name << "Var and set it to " << _name << ":new()" << std::endl;
		return false;
	}

	_luaUpdate = new luabridge::LuaRef((*obj)["update"]);
	if (!_luaUpdate->isFunction()) {
		std::string warning = "Warning:" + _name + ":update(dt) is not defined in the script";
		std::cout << warning << std::endl;
		Engine::GetInstance()->showWindow(1, warning);
		delete _luaUpdate;
		_luaUpdate = nullptr;
	}
	_luaStart = new luabridge::LuaRef((*obj)["start"]);
	if (!_luaStart->isFunction()) {
		std::string warning = "Warning:" + _name + ":start() is not defined in the script";
		std::cout << warning << std::endl;
		Engine::GetInstance()->showWindow(1, warning);
		delete _luaStart;
		_luaStart = nullptr;
	}
	_luaFixed = new luabridge::LuaRef((*obj)["fixedUpdate"]);
	if (!_luaFixed->isFunction()) {
		std::string warning = "Warning:" + _name + ":fixedUpdate() is not defined in the script";
		std::cout << warning << std::endl;
		Engine::GetInstance()->showWindow(1, warning);
		delete _luaFixed;
		_luaFixed = nullptr;
	}
	_luaEnable = new luabridge::LuaRef((*obj)["onEnable"]);
	if (!_luaEnable->isFunction()) {
		std::string warning = "Warning:" + _name + ":onEnable() is not defined in the script";
		std::cout << warning << std::endl;
		Engine::GetInstance()->showWindow(1, warning);
		delete _luaEnable;
		_luaEnable = nullptr;
	}
	_luaDisable = new luabridge::LuaRef((*obj)["onDisable"]);
	if (!_luaDisable->isFunction()) {
		std::string warning = "Warning:" + _name + ":onDisable() is not defined in the script";
		std::cout << warning << std::endl;
		Engine::GetInstance()->showWindow(1, warning);
		delete _luaDisable;
		_luaDisable = nullptr;
	}
	_luaAwake = new luabridge::LuaRef((*obj)["awake"]);
	if (!_luaAwake->isFunction()) {
		std::string warning = "Warning:" + _name + ":awake() is not defined in the script";
		std::cout << warning << std::endl;
		Engine::GetInstance()->showWindow(1, warning);
		delete _luaAwake;
		_luaAwake = nullptr;
	}
	_luaSetParameters = new luabridge::LuaRef((*obj)["setParameters"]);
	if (!_luaSetParameters->isFunction()) {
		std::string warning = "Warning:" + _name + ":setParameters(params) is not defined in the script";
		std::cout << warning << std::endl;
		Engine::GetInstance()->showWindow(1, warning);
		delete _luaSetParameters;
		_luaSetParameters = nullptr;
	}
	return true;
}
