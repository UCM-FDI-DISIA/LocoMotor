#pragma once
#ifndef LOCOMOTOR_SCRIPTMANAGER
#define  LOCOMOTOR_SCRIPTMANAGER


#include <string>
#include <unordered_map>
#include <optional>
#include <variant>
struct lua_State;
namespace luabridge {
	class LuaRef;
}

namespace LocoMotor {
	class SceneManager;
	class GameObject;
	class Scene;


	class LuaParser {

	public:
		enum class LuaType {
			Object,
			String,
			Number,
			Bool
		};
		typedef std::vector<std::pair<std::string, std::string>> LuaComponent;
		typedef std::unordered_map<std::string, LuaComponent> LuaObject;
		typedef std::unordered_map<std::string, LuaObject> LuaScene;
		LuaParser();
		~LuaParser();
		/// @brief Reads a lua file and builds the scene from that file
		/// @param path The path to find the lua file
		std::optional<LocoMotor::LuaParser::LuaScene> loadSceneFromFile(const std::string& path, const std::string& sceneName);
	private:
		/// @brief Reads the lua script 
		/// @param path The path to find the lua script
		int readLua(const std::string path);
		/// @brief Reports errors giving a status when reading lua
		/// @param status 
		void reportErrors(int status);
		/// @brief Get a param from lua file giving the name of the param
		luabridge::LuaRef getFromLua(std::string name);
		/// @brief Sets the param read from lua to the gameobject and scene
		LuaObject getObject(luabridge::LuaRef entity);	
		
		lua_State* _luaState;
		
	};
}

#endif // !_SCRIPT_MANAGER_H
