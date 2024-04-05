#pragma once
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H
class lua_State;
namespace LocoMotor {
	namespace Scripting {
		class ScriptManager {
		public:
			static bool Init();
			static void Release();
		private:
			ScriptManager();
			~ScriptManager();
			
			static ScriptManager* _instance;
			lua_State* _luaState;
		};
	}
}
#endif