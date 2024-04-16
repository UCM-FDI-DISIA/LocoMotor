#pragma once
#ifndef LOCOMOTOR_COMPONENT
#define LOCOMOTOR_COMPONENT

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <vector>
#include <string>

#include "CheckML.h"
#include "SceneDefs.h"
namespace LocoMotor {
	class GameObject;
	
	class MOTOR_API Component {
		friend class GameObject;
		friend class Scene;
	public:
		/// @brief This method checks for the enabled state of the component
		/// @return true if the component is enabled
		bool isEnabled();
		/// @brief This method chages the enabled state of the component
		/// @param enable The state to which you want to change the component
		/// @remarks If the component was in the same state as the parameter given, this method does nothing
		void setEnabled(bool enable);
	protected:

		virtual ~Component() {};

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

		/// @brief This function is called when the scene loads the parameters of the components
		virtual void setParameters(ComponentMap& params) = 0;

		GameObject* _gameObject = nullptr;
	private:

		/// @brief Initializes the component with its context (GameObject) and enabled state
		/// @param gameObject The GameObject which the components belongs to
		/// @param enable The initial enabled state of the component.
		void init(GameObject* gameObject, bool enable);
		bool _started = false;
		bool _active = false;
	};
}
#endif