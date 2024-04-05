#pragma once
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H
class lua_State;
#include <functional>
#include <vector>
namespace LocoMotor {
	namespace Scripting {
		class ScriptManager {
		public:
			static bool Init();
			static void Release();
		private:
			ScriptManager();
			~ScriptManager();
			
			bool initLua();
			void registerToLua();
			static ScriptManager* _instance;
			lua_State* _luaState;
		};
	}
}
#endif