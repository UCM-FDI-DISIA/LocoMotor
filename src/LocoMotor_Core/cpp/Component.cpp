#include "Component.h"

bool LocoMotor::Component::isEnabled() {
	return _active;
}

void LocoMotor::Component::setEnabled(bool enable) {
	if (!_started) _started = true;
	this->_active = enable;
}

void LocoMotor::Component::_init(GameObject* gameObject, bool enable) {
	_gameObject = gameObject;
	_active = enable;
}