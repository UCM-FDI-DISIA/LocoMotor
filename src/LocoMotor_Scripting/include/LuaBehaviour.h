#pragma once
#ifndef LUABEHAVIOUR_H
#define LUABEHAVIOUR_H
#include "Component.h"
#include <unordered_map>
#include <string>
class lua_State;
namespace luabridge {
	class LuaRef;
}

namespace LocoMotor {
	namespace Scripting {
		class ScriptManager;
	}
	class LuaBehaviour : public Component {
	
		friend class Scripting::ScriptManager;
	protected:
		~LuaBehaviour();

		void awake() override {};
		void onEnable() override {};
		void start() override {};
		void update(float dt) override {};
		void fixedUpdate() override {};
		void onDisable() override {};
		void onDestroy() override {};

		void setParameters(ComponentMap& params) override {};
	private:
		LuaBehaviour();
		inline void setLuaContext(lua_State* state) {
			_luaState = state;
		}
		//??
		lua_State* _luaState;
		luabridge::LuaRef* _luaUpdate;
		luabridge::LuaRef* _luaEnable;
		luabridge::LuaRef* _luaStart;
		luabridge::LuaRef* _luaAwake;
		luabridge::LuaRef* _luaFixed;
		luabridge::LuaRef* _luaDisable;
		luabridge::LuaRef* _luaDestroy;
		std::unordered_map<std::string, luabridge::LuaRef*> _methods;
		std::unordered_map<std::string, luabridge::LuaRef*> _properties;

	};
}
#endif
