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
	luabridge::LuaRef luaAwake = (*obj)["awake"];
	if (!luaAwake.isFunction()) {
		
		return;
	}
	try {
		luaAwake(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;
	}
}

void LocoMotor::LuaBehaviour::onEnable() {
	luabridge::LuaRef luaEnable = (*obj)["onEnable"];
	if (!luaEnable.isFunction()) {
		
		return;
	}
	try {
		luaEnable(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::start() {
	luabridge::LuaRef luaStart = (*obj)["start"];
	if (!luaStart.isFunction()) {
		return;
	}
	try {
		luaStart(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;
		
	}
}

void LocoMotor::LuaBehaviour::update(float dt) {
	luabridge::LuaRef luaUpdate = (*obj)["update"];
	if (!luaUpdate.isFunction()) {
		
		return;
	}
	try {
		luaUpdate(*obj, dt);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::fixedUpdate() {
	luabridge::LuaRef luaFixed = (*obj)["fixedUpdate"];
	if (!luaFixed.isFunction()) {
		
		return;
	}
	try {
		luaFixed(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::onDisable() {
	luabridge::LuaRef luaDisable = (*obj)["onDisable"];
	if (!luaDisable.isFunction()) {
		
		return;
	}
	try {
		luaDisable(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::onDestroy() {
	luabridge::LuaRef luaDestroy = (*obj)["onDestroy"];
	if (!luaDestroy.isFunction()) {
		
		return;
	}
	try {
		luaDestroy(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionEnter(GameObject* other) {
	luabridge::LuaRef luaCollEnter = (*obj)["onCollisionEnter"];
	if (!luaCollEnter.isFunction()) {
		return;
	}
	try {
		luaCollEnter(*obj, other);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionStay(GameObject* other) {
	luabridge::LuaRef luaCollStay = (*obj)["onCollisionStay"];
	if (!luaCollStay.isFunction()) {
		return;
	}
	try {
		luaCollStay(*obj, other);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionExit(GameObject* other) {
	luabridge::LuaRef luaCollExit = (*obj)["onCollisionExit"];
	if (!luaCollExit.isFunction()) {
		return;
	}
	try {
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
	luabridge::LuaRef luaSetParams = (*obj)["setParameters"];
	if (!luaSetParams.isFunction()) {
		std::cout << "Lua Warning: " << "You must define a function called " << _name << ":setParameters(params) in " << _name << ".lua" << 
			"if you want to set the parameters from this component from the scene files" << std::endl;
		return;
	}
	try {		
		luaSetParams(*obj, paramsTable);
	}
	catch (luabridge::LuaException e) {
		std::cout << e.what() << std::endl;;
	}
	
}

bool LocoMotor::LuaBehaviour::initBehaviour() {
	obj = new luabridge::LuaRef(luabridge::getGlobal(_luaState, "this"));
	if ((*obj).isNil()) {
		std::cout << "Lua Interpreter Warning: No variable called " << _name << "Var on the lua script " << _name << ".lua" << std::endl;
		std::cout << "Please define a variable called " << _name << "Var and set it to " << _name << ":new()" << std::endl;
		//return false;
	}
	return true;
}
