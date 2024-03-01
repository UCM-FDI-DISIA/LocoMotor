#pragma once
#ifndef LOCOMOTOR_COMPONENTS_FACTORY
#define LOCOMOTOR_COMPONENTS_FACTORY
#include <string>
#include <cassert>
#include <map>

//TODO: Programar ComponentsFactory
namespace LocoMotor {
	class ComponentsFactory {
	public:
		static bool Init() {
			assert(_instance == nullptr);
			_instance = new ComponentsFactory();
		}

		static void Release() {
			assert(_instance != nullptr);
			delete _instance;
			_instance = nullptr;
		}
		static ComponentsFactory* GetInstance() {
			assert(_instance != nullptr);
			return _instance;
		}
		template <class T>
		Component* createComponent(const std::string& name) {
			return nullptr;
		};
		template <class T>
		bool isUnique(const std::string& name) {
			return unique[name];
		}
	private:
		ComponentsFactory() {
		};
		~ComponentsFactory() {
		};
		static ComponentsFactory* _instance;
		std::map<std::string, bool> unique;
	};
}

#endif
