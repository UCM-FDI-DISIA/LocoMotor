#pragma once
#ifndef LOCOMOTOR_SCRIPTMANAGER

#define  LOCOMOTOR_SCRIPTMANAGER


//#ifdef _MOTORDLL
//#define MOTOR_API __declspec(dllexport)
//#else
//#define MOTOR_API __declspec(dllimport)
//#endif

#include <string>

struct lua_State;
namespace luabridge {
	class LuaRef;
}

namespace LocoMotor {
	class SceneManager;
	class GameObject;
	class Scene;
	class ScriptManager {
		
	public:
		static bool Init();
		static void Release();
		/// @brief Reads a lua file and builds the scene from that file
		/// @param path The path to find the lua file
		bool loadSceneFromFile(std::string path);

		/// @brief Checks if theres a scene in buffer waiting to be changed
		void checkChangeScene();
		std::string getBufferedScene();
		void tryChangeScene(std::string path);

	private:
		/// @brief Reads the lua script 
		/// @param path The path to find the lua script
		int readLuaScript(const std::string path);
		/// @brief Reports errors giving a status when reading lua
		/// @param status 
		void report_errors(int status);
		/// @brief Get a param from lua file giving the name of the param
		luabridge::LuaRef getFromLua(std::string name);
		/// @brief Sets the param read from lua to the gameobject and scene
		bool setParams(luabridge::LuaRef entity, GameObject* ent, Scene* s, std::string layer);
		ScriptManager();
		~ScriptManager();
		lua_State* _luaState;
		SceneManager* _scMan;
		//@brief Scene waiting to be changed
		std::string bufferedScene;
		static ScriptManager* _instance;
	};
}

#endif // !_SCRIPT_MANAGER_H
