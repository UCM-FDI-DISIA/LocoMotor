#include "LuaParser.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <LuaBridge/LuaBridge.h>
#include <iostream>
using namespace LocoMotor;

luabridge::LuaRef LuaParser::getFromLua(std::string name) {
	return luabridge::getGlobal(_luaState, name.c_str());
}

void LuaParser::reportErrors(int status) {
	if (status == 0) {
		return;
	}
	// remove error message from Lua state
	lua_pop(_luaState, 1);
}

int LuaParser::readLua(const std::string path) {

	// load some code from Lua file
	int scriptLoadStatus = luaL_dofile(_luaState, path.c_str());

	// define error reporter for any Lua error
	reportErrors(scriptLoadStatus);
	return scriptLoadStatus;
}

std::optional<LocoMotor::LuaParser::LuaScene> LuaParser::loadSceneFromFile(const std::string& path,const std::string& sceneName) {
	if (readLua(path) != 0) {
		return std::nullopt;
	}

	LuaScene sc = LuaScene();
	luabridge::LuaRef luaScene = getFromLua(sceneName);
	lua_pushnil(luaScene);
	if (luaScene.isNil()) {
		std::cout << "Escena fue null xdxd\n";
		return std::nullopt;
	}
	while (lua_next(luaScene, 0) != 0) {
		std::string gObjName = lua_tostring(luaScene, -2);
		luabridge::LuaRef entity = luaScene[gObjName];
		LuaObject obj = getObject(entity);
		sc.insert({ gObjName,obj });
		if (obj.empty()) {
			//TODO: ERROR NO BLOQUANTE
			continue;
		}
		lua_pop(luaScene, 1);
	}
	

	return sc;
}


LocoMotor::LuaParser::LuaParser() {
	_luaState = luaL_newstate();
	luaL_openlibs(_luaState);
}

LocoMotor::LuaParser::~LuaParser() {
	lua_close(_luaState);
}

LocoMotor::LuaParser::LuaObject LuaParser::getObject(luabridge::LuaRef entity) {

	lua_pushnil(entity);
	if (entity.isNil()) {
		return LuaObject();
	}
	LuaObject obj{};
	
	while (lua_next(entity, 0) != 0) {
		std::string compName = lua_tostring(entity, -2);

		luabridge::LuaRef component = entity[compName];
		
		lua_pushnil(component);
		LuaComponent cmp{};
		
		while (lua_next(component, 0) != 0) {
			std::string key = lua_tostring(entity, -2);
			std::string val = lua_tostring(entity, -1);
			cmp.insert({ key,val });
			lua_pop(component, 1);
		}
		obj.insert({ compName,cmp });
		lua_pop(entity, 1);
	}
	
	return obj;
}
