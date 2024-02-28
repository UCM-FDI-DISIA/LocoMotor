#include "ParticleSystem.h"

void LocoMotor::Graphics::ParticleSystem::init() {}

void LocoMotor::Graphics::ParticleSystem::onEnable() {}

void LocoMotor::Graphics::ParticleSystem::update(float dT) {

	// Actualizar la posicion del nodo asignado al ParticleSystem para que siga al GameObject asignado

	//_gameObject->

	if (_node != nullptr) {
	//	float x = (float) _gameObject->GetTransform()->GetPosition().GetX();
	//	float y = (float) gameObject->GetTransform()->GetPosition().GetY();
	//	float z = (float) gameObject->GetTransform()->GetPosition().GetZ();
	//	_node->SetPosition(x, y, z);
	}
}

void LocoMotor::Graphics::ParticleSystem::onDisable() {}

LocoMotor::Graphics::ParticleSystem::ParticleSystem() {}

LocoMotor::Graphics::ParticleSystem::~ParticleSystem() {}
