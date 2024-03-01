#include "ComponentsFactory.h"

inline bool LocoMotor::ComponentsFactory::Init() {
	assert(_instance == nullptr);
	_instance = new ComponentsFactory();
}

inline void LocoMotor::ComponentsFactory::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

inline LocoMotor::ComponentsFactory* LocoMotor::ComponentsFactory::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}
