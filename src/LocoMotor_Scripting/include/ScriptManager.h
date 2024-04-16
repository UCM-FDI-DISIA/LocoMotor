#pragma once
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
class lua_State;
#include <functional>
#include <vector>
#include <iostream>
namespace LocoMotor {
	class LuaBehaviour;
	namespace Scripting {
		class MOTOR_API ScriptManager {
		public:
			static bool Init();
			static void Release();
			static ScriptManager* GetInstance();
			void hola() {
				std::cout << "HOLA" << std::endl;
			};
			void test();
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