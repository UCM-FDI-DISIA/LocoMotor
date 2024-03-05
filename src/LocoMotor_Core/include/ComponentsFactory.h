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
		/// @return This method always returns true.
		static bool Init();
		/// @brief Relases the memory allocated by the Components Factory. This should always be called after init.
		static void Release();

		/// @return The Componenst Factory instance
		static ComponentsFactory* GetInstance();

		/// @brief Creates a component of the give typename, you can provide the type by name or by string
		/// @tparam T Typename of the component type
		/// @param name Name of the component type
		/// @return A newly created Component with sufficient memory allocated for the asked type. You must cast the returned value to the desired type.
		inline Component* createComponent(const std::string& name) {
			assert(_factories.count(name) > 0, "That component name is not registered");
			return _factories[name]();
		};

		/// @brief Register a component so it can be instantiated by the factory
		/// @tparam T Type of the component
		/// @param name Typename of the component
		/// @param unique If the component is unique (a component is unique if a given GameObject can only have one instance of it)
		template <typename T>
		void registerComponent(const std::string& name) {
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
		std::map<std::string, CmpFactory> _factories;
	};
}
#endif
