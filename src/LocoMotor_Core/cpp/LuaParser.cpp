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
	if (status) {
		// remove error message from Lua state
		std::cout << std::string(lua_tostring(_luaState, -1)) << std::endl;
		lua_pop(_luaState, -1);
		return;
	}
}

int LuaParser::readLua(const std::string path) {

	// load some code from Lua file
	int scriptLoadStatus = luaL_dofile(_luaState, path.c_str());

	// define error reporter for any Lua error
	std::cerr << "\033[1;31m";
	reportErrors(scriptLoadStatus);
	std::cerr << "\033[0m" << std::endl;
	return scriptLoadStatus;
}

std::optional<LocoMotor::SceneMap> LuaParser::loadSceneFromFile(const std::string& path,const std::string& sceneName) {
	if (readLua(path) != 0) {
		std::cerr << "\033[1;31m" << "Error loading file '" << path << "'\033[0m" << std::endl;
		return std::nullopt;
	}

	SceneMap sc = SceneMap();
	luabridge::LuaRef luaScene = getFromLua(sceneName);
	lua_pushnil(luaScene);
	if (luaScene.isNil()) {
		std::cout << "\033[1;31m" << "Escena '" << sceneName <<"' fue null" << "\033[0m" << std::endl;
		return std::nullopt;
	}
	while (lua_next(luaScene, 0) != 0) {
		std::string gObjName = lua_tostring(luaScene, -2);
		luabridge::LuaRef entity = luaScene[gObjName];
		
		ObjectMap obj = getObject(entity);
		sc.insert({ gObjName,obj });
		lua_pop(luaScene, 1);
		if (obj.empty()) {
			//TODO: ERROR NO BLOQUANTE
			
		}
		
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

LocoMotor::ObjectMap LuaParser::getObject(luabridge::LuaRef entity) {

	lua_pushnil(entity);
	if (entity.isNil()) {
		return ObjectMap();
	}
	ObjectMap obj{};
	
	while (lua_next(entity, 0) != 0) {
		std::string compName = lua_tostring(entity, -2);

		luabridge::LuaRef component = entity[compName];
		
		lua_pushnil(component);
		ComponentMap cmp{};
		
		while (lua_next(component, 0) != 0) {
			std::string key = lua_tostring(entity, -2);
			std::string val = lua_tostring(entity, -1);
			cmp.push_back({ key,val });
			lua_pop(component, 1);
		}
		obj.insert({ compName,cmp });
		lua_pop(entity, 1);
	}
	
	return obj;
}
