#include "LuaBehaviour.h"
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <LuaBridge/LuaBridge.h>

LocoMotor::LuaBehaviour::LuaBehaviour() : _luaState(nullptr), _luaUpdate(nullptr), _luaEnable(nullptr), _luaStart(nullptr), _luaAwake(nullptr), _luaFixed(nullptr),
_luaDisable(nullptr), _luaDestroy(nullptr), _methods(), _properties() {}

LocoMotor::LuaBehaviour::~LuaBehaviour() {


}