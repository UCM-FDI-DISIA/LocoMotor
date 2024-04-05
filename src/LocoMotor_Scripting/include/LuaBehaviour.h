#pragma once
#ifndef LUABEHAVIOUR_H
#define LUABEHAVIOUR_H
#include "Component.h"
class lua_State;
namespace luabridge {
	class LuaRef;
}
namespace LocoMotor {
	class LuaBehaviour : public Component {
	protected:
		~LuaBehaviour();

		void awake() override;
		void onEnable() override;
		void start() override;
		void update(float dt) override;
		void fixedUpdate() override;
		void onDisable() override;
		void onDestroy() override;

		void setParameters(ComponentMap& params) override;
	private:
		LuaBehaviour();

		//??
		lua_State* _luaState;
		luabridge::LuaRef* _object;
	};
}
#endif
