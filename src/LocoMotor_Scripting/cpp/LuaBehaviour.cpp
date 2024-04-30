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


LocoMotor::LuaBehaviour::LuaBehaviour() : _luaState(nullptr) {
}

LocoMotor::LuaBehaviour::~LuaBehaviour() {
	
	/*if (_luaUpdate != nullptr) delete _luaUpdate;
	if (_luaStart != nullptr) delete _luaStart;
	if (_luaDestroy != nullptr) delete _luaDestroy;
	if (_luaEnable != nullptr) delete _luaEnable;
	if (_luaEnable != nullptr) delete _luaDisable;
	if (_luaAwake != nullptr) delete _luaAwake;
	if (_luaFixed != nullptr) delete _luaFixed;*/
	if (obj != nullptr) delete obj;
}

void LocoMotor::LuaBehaviour::awake() {
	try {
		luabridge::LuaRef luaAwake = (*obj)["awake"];
		if (!luaAwake.isFunction()) {

			return;
		}
		luaAwake(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;
	}
}

void LocoMotor::LuaBehaviour::onEnable() {
	
	try {
		luabridge::LuaRef luaEnable = (*obj)["onEnable"];
		if (!luaEnable.isFunction()) {

			return;
		}
		luaEnable(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::start() {
	
	
	try {
		luabridge::LuaRef luaStart = (*obj)["start"];
		if (!luaStart.isFunction()) {
			return;
		}
		luaStart(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;
		
	}
}

void LocoMotor::LuaBehaviour::update(float dt) {
	
	try {
		luabridge::LuaRef luaUpdate = (*obj)["update"];
		if (!luaUpdate.isFunction()) {

			return;
		}
		luaUpdate(*obj, dt);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::fixedUpdate() {
	
	try {
		luabridge::LuaRef luaFixed = (*obj)["fixedUpdate"];
		if (!luaFixed.isFunction()) {

			return;
		}
		luaFixed(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::onDisable() {
	
	try {
		luabridge::LuaRef luaDisable = (*obj)["onDisable"];
		if (!luaDisable.isFunction()) {

			return;
		}
		luaDisable(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::onDestroy() {
	try {
		luabridge::LuaRef luaDestroy = (*obj)["onDestroy"];
		if (!luaDestroy.isFunction()) {

			return;
		}
		luaDestroy(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionEnter(GameObject* other) {
	
	try {
		luabridge::LuaRef luaCollEnter = (*obj)["onCollisionEnter"];
		if (!luaCollEnter.isFunction()) {
			return;
		}
		luaCollEnter(*obj, other);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionStay(GameObject* other) {
	
	try {
		luabridge::LuaRef luaCollStay = (*obj)["onCollisionStay"];
		if (!luaCollStay.isFunction()) {
			return;
		}
		luaCollStay(*obj, other);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionExit(GameObject* other) {
	
	try {
		luabridge::LuaRef luaCollExit = (*obj)["onCollisionExit"];
		if (!luaCollExit.isFunction()) {
			return;
		}
		luaCollExit(*obj, other);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::setParameters(ComponentMap& params) {
	for (auto it = params.begin(); it != params.end(); ) {
		if ((*it).first == "scriptName") {
			_name = (*it).second;
			if (!Scripting::ScriptManager::GetInstance()->loadScript(_name, this)) {
				return;
			}
			if (!initBehaviour()) {
				std::cout << _name << "Was not a table" << std::endl;
				return;
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
	luabridge::LuaRef paramsTable = luabridge::newTable(_luaState);
	for (auto& param : params) {
		paramsTable[param.first] = param.second;
	}
	try {	
		luabridge::LuaRef luaSetParams = (*obj)["setParameters"];
		if (!luaSetParams.isFunction()) {
			std::cout << "Lua Warning: " << "You must define a function called " << _name << ":setParameters(params) in " << _name << ".lua" <<
				"if you want to set the parameters from this component from the scene files" << std::endl;
			return;
		}
		luaSetParams(*obj, paramsTable);
	}
	catch (luabridge::LuaException e) {
		std::cout << e.what() << std::endl;;
	}
	
}

luabridge::LuaRef LocoMotor::LuaBehaviour::getScript() const {
	std::cout << "test "<<_name<<": nil " << obj->isNil() << "test user" << obj->isUserdata() << "test table" << obj->isTable() << std::endl;
	return *obj;
}

bool LocoMotor::LuaBehaviour::initBehaviour() {
	std::cout << _name << std::endl;
	obj = new luabridge::LuaRef(luabridge::getGlobal(_luaState, _name.c_str()));
	if (!obj->isTable()) {
		std::cout << "Lua Interpreter Warning: No table called " << _name << " on the lua script " << _name << ".lua" << std::endl;
		return false;
	}
	if(obj->isUserdata()) {
		std::cout << "userdata" << _name << std::endl;
	}
	luabridge::setGlobal(_luaState, *obj, _name.c_str());
	return true;
}
