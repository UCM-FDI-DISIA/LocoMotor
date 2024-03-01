#pragma once
#ifndef LOCOMOTOR_GAME_OBJECT
#define LOCOMOTOR_GAME_OBJECT
#include <queue>
#include <map>
#include <string>
#include "ComponentsFactory.h"

namespace LocoMotor {
	class Component;
	class Transform;
	class Scene;

	class GameObject {
		friend class Scene;
	public:
		/// @brief This method adds a new component to the GameObject
		/// @tparam T The type of the new Component
		/// @param name Name of the Component type
		/// @return returns the Component created. If the component was unique and already on the GameObject
		/// the already created Component will be returned. 
		template<class T>
		T* addComponent(const std::string& name) {
			ComponentsFactory* factory = LocoMotor::ComponentsFactory::GetInstance();
			if (_components.count(name) > 0 && factory->isUnique(name)) {
				return (T*) components[name];
			}
			else {
				Component* comp = factory->createComponent(name);
				comp->_init(this, true);
				_toStart.push(comp);
				_components.insert({ name, comp });
				return (T*) comp;
			}
		}

		/// @brief This method erases all the components with the given name on the GameObject
		/// @param name The name of the component to erase
		void removeComponents(const std::string& name);
		
		/// @brief This method sets the active state of the GameObject. 
		/// @param active The new active state of the GameObject
		inline void setActive(bool active) {
			active = _active;
		};

		/// @brief Returns the active state of the GameObject
		/// @return 
		inline bool isActive() {
			return _active;
		};
	private:
		
		std::multimap<std::string, Component*> _components;
		std::queue<LocoMotor::Component*> _toEnable;
		std::queue<LocoMotor::Component*> _toDisable;
		std::queue<LocoMotor::Component*> _toStart;
		std::queue<LocoMotor::Component*> _toDestroy;
		LocoMotor::Scene* _scene;
		LocoMotor::Transform* _transform;
		bool _active;

		GameObject();
		~GameObject();
		/// @brief This method is called every frame 
		/// @param dt The time elapsed since the last frame, measured in ms
		void update(float dt);
		/// @brief This method is called every fixed time step (16ms by default)
		void fixedUpdate();
		/// @brief This method sets the context (Scene) and the active state for the GameObject 
		/// @param scene Scene which the GO belongs to
		/// @param active Initial active state of the GameObject
		void init(LocoMotor::Scene* scene, bool active);
	};
}
#endif // !LOCOMOTOR_GAME_OBJECT

