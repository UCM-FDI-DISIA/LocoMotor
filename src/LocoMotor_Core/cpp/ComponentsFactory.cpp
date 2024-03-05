#include "ComponentsFactory.h"
LocoMotor::ComponentsFactory* LocoMotor::ComponentsFactory::_instance = nullptr;
bool LocoMotor::ComponentsFactory::Init() {
	assert(_instance == nullptr);
	_instance = new ComponentsFactory();
	return true;
}

void LocoMotor::ComponentsFactory::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

LocoMotor::ComponentsFactory* LocoMotor::ComponentsFactory::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}
