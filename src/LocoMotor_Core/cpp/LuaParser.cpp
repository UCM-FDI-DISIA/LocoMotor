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

std::optional<LocoMotor::SceneMap> LuaParser::loadSceneFromFile(const std::string& path,const std::string& sceneName) {
	if (readLua(path) != 0) {
		std::cerr << "No existe el archivo " << path << std::endl;
		return std::nullopt;
	}

	SceneMap sc = SceneMap();
	luabridge::LuaRef luaScene = getFromLua(sceneName);
	lua_pushnil(luaScene);
	if (luaScene.isNil()) {
		std::cout << "Escena fue null xdxd\n";
		return std::nullopt;
	}
	while (lua_next(luaScene, 0) != 0) {
		std::string gObjName = lua_tostring(luaScene, -2);
		luabridge::LuaRef entity = luaScene[gObjName];
		ObjectMap obj = getObject(entity);
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
