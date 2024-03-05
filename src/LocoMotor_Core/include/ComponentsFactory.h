#pragma once
#ifndef LOCOMOTOR_COMPONENTS_FACTORY
#define LOCOMOTOR_COMPONENTS_FACTORY
#include <string>
#include <functional>
#include <cassert>
#include <map>

//TODO: Programar ComponentsFactory
namespace LocoMotor {
	class Component;
	typedef Component* (*CmpFactory)();
	class ComponentsFactory {
	public:
		/// @brief Initializes the Components Factory instance
		/// @return This method always returna true.
		static bool Init();
		/// @brief Relases the memory allocated by the Components Factory. This should always be called after init.
		static void Release();

		/// @return The Componenst Factory instance
		static ComponentsFactory* GetInstance();

		/// @brief Creates a component of the give typename, you can provide the type by name or by string
		/// @tparam T Typename of the component type
		/// @param name Name of the component type
		/// @return A newly created Component with sufficient memory allocated for the asked type. You must cast the returned value to the desired type.
		template <class T>
		Component* createComponent(const std::string& name) {
			assert(_factories.count(name) > 0, "That component name is not registered");
			return _factories[name]();
		};

		/// @param name Name of the component type
		/// @return true if the given component type is unique, false if not
		inline bool isUnique(const std::string& name) {
			assert(_unique.count(name) > 0, "That component name is not registered");
			return _unique[name];
		}

		template <typename T>
		void registerComponent(const std::string& name, bool unique) {
			assert(_factories.count(name) == 0, "That component name is already registered");
			CmpFactory fac = (CmpFactory)[]() {
				return static_cast<Component*>(new T());
			};
			_factories.insert({ name,fac });
			_unique.insert({ name,unique });
		}
	private:
		ComponentsFactory() {
		};
		~ComponentsFactory() {
		};
		static ComponentsFactory* _instance;
		std::map<std::string, bool> _unique;
		std::map<std::string, CmpFactory> _factories;
	};
}
#endif
