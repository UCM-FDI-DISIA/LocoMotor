#pragma once

#ifndef LOCOMOTOR_COMPONENT
#define LOCOMOTOR_COMPONENT


namespace LocoMotor {
	class GameObject;
	class Component {
		friend class GameObject;
	public:
		/// @brief This method checks for the enabled state of the component
		/// @return true if the component is enabled
		bool isEnabled();
		/// @brief This method chages the enabled state of the component
		/// @param enable The state to which you want to change the component
		/// @remarks If the component was in the same state as the parameter given, this method does nothing
		void setEnabled(bool enable);
	protected:
		/// @brief This function is called on every frame 
		/// @param dt The time elapsed since the last update, measured in ms
		virtual void update(float dt) = 0;
		/// @brief This function is called on every fixed time update (by default each 16ms)
		virtual void fixedUpdate() {
		};
		/// @brief This function is called each time the component is enabled
		/// @remarks On scene startup, if the component is enabled, onEnable() is called before start() but after awake()
		virtual void onEnable() {
		};
		/// @brief This function is called each time the component is disabled
		/// @remarks On scene termination or component destruction, onDisable() is called before onDestroy()
		virtual void onDisable() {
		};
		/// @brief This function is called when the component is enabled for the first time
		/// @remarks On scene startup, if the component is enabled, onEnable() is called before start() but after awake()
		virtual void start() = 0;
		/// @brief This function is ALWAYS called only once on scene startup
		/// @remarks On scene startup, if the component is enabled, onEnable() is called before start() but after awake()
		virtual void awake() {
		};
		/// @brief This function is called when a component is removed from an object, or on scene termination
		/// @remarks On scene termination or component destruction, onDisable() is called before onDestroy()
		virtual void onDestroy() {
		};
	private:
		void _init(GameObject* gameObject, bool enable);
		GameObject* _gameObject;
		bool _started;
		bool _active;
	};
}
#endif