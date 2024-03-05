#include "ScriptManager.h"
#include "Scene.h"
#include "SceneManager.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <LuaBridge/LuaBridge.h>
#include "GameObject.h"
//#include "Transform.h"
using namespace LocoMotor;

ScriptManager* ScriptManager::_instance = nullptr;

luabridge::LuaRef ScriptManager::getFromLua(std::string name) {
	return luabridge::getGlobal(_luaState, name.c_str());
}

void ScriptManager::report_errors(int status) {
	if (status == 0) {
		return;
	}

	

	// remove error message from Lua state
	lua_pop(_luaState, 1);
}

int ScriptManager::readLuaScript(const std::string path) {

	// load some code from Lua file
	int scriptLoadStatus = luaL_dofile(_luaState, path.c_str());

	// define error reporter for any Lua error
	report_errors(scriptLoadStatus);
	return scriptLoadStatus;
}

bool ScriptManager::loadSceneFromFile(std::string path) {
	bufferedScene = "NONE";
	if (readLuaScript(path) != 0) {
		return false;
	}
	Scene* scene = _scMan->getSceneByName(path);
	if (scene == nullptr) {
		scene = _scMan->createScene(path);
	}

	luabridge::LuaRef allEnts = getFromLua("entities");
	int numEnts = allEnts.length();

	for (int i = 1; i <= numEnts; i++) {
		luabridge::LuaRef entity = getFromLua(allEnts[i]);

		//Cargo las entidades 
		GameObject* gObj = scene->getObjectByName(allEnts[i]);
		if (gObj == nullptr) {
			gObj = scene->addGameobject(allEnts[i]);
		}
		if (!setParams(entity, gObj, nullptr, "layer")) {
			scene->removeGameobject(allEnts[i]);
		}
	}
	_scMan->changeScene(path);

	return true;
}

void LocoMotor::ScriptManager::checkChangeScene() {
	if (bufferedScene == "NONE") return;
	std::cout << "\nTHERE IS A BUFFERED SCENE; CHANGING NOW!";
	loadSceneFromFile(bufferedScene);
}

std::string LocoMotor::ScriptManager::getBufferedScene() {
	return bufferedScene;
}

void LocoMotor::ScriptManager::tryChangeScene(std::string path) {
	bufferedScene = path;
}

LocoMotor::ScriptManager::ScriptManager() {
	_luaState = luaL_newstate();
	_scMan = SceneManager::GetInstance();
	bufferedScene = "NONE";
	luaL_openlibs(_luaState);
}

LocoMotor::ScriptManager::~ScriptManager() {
	lua_close(_luaState);
}

bool ScriptManager::setParams(luabridge::LuaRef entity, GameObject* ent, Scene* s, std::string layer) {

	lua_pushnil(entity);
	if (entity.isNil()) {
		return false;
	}
	while (lua_next(entity, 0) != 0) {
		std::string compName = lua_tostring(entity, -2);
		std::string key;

		luabridge::LuaRef component = entity[compName];
		lua_pushnil(component);

		std::vector<std::pair<std::string, std::string>> parameters;

		while (lua_next(component, 0) != 0) {
			std::string key = lua_tostring(entity, -2);
			std::string val = lua_tostring(entity, -1);

			parameters.push_back({ key, val });
			lua_pop(component, 1);
		}


		ent->addComponent(compName, parameters);
		lua_pop(entity, 1);
	}
	if (ent->getComponent<Transform>() == nullptr)
		ent->addComponent("Transform");
	return true;
}
