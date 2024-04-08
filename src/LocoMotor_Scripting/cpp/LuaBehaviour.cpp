#include "LuaBehaviour.h"
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <LuaBridge/LuaBridge.h>

LocoMotor::LuaBehaviour::LuaBehaviour() : _luaState(nullptr), _object(nullptr) {}

void LocoMotor::LuaBehaviour::helloWorld() {
	std::cout << "Hola de buenas a le mundo" << std::endl;
}

LocoMotor::LuaBehaviour::~LuaBehaviour() {
	if (_object != nullptr) {
		delete _object;
	}
	if (_luaState != nullptr) {
		
	}
	
}