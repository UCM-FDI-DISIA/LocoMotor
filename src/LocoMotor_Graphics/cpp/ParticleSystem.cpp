#include "ParticleSystem.h"

#include <OgreParticleEmitter.h>


void LocoMotor::Graphics::ParticleSystem::init() {

	//_renderScn = nullptr;
	//_particleHelper = nullptr;

	_filename = "";
	_name = "";
}

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

Ogre::ParticleEmitter* LocoMotor::Graphics::ParticleSystem::GetEmitter(std::string name) {
	if (_emitters.find(name) != _emitters.end())
		return _emitters[name];
}

Ogre::Vector3 LocoMotor::Graphics::ParticleSystem::LmVectorToOgreVector(const LMVector3 lmVector) {
	return Ogre::Vector3(lmVector.GetX(), lmVector.GetY(), lmVector.GetZ());
}

void LocoMotor::Graphics::ParticleSystem::AddEmitter(std::string name, const LMVector3 position) {

	// Comprobar que no se ha creado un emitter anterior con el mismo nombre
	if (_emitters.find(name) == _emitters.end()) {
		_emitters.insert({ name, _particleSystem->addEmitter(name) });
		_emitters[name]->setPosition(LmVectorToOgreVector(position));
	}
}

void LocoMotor::Graphics::ParticleSystem::RemoveEmitter(std::string name) {

	if (_emitters.find(name) != _emitters.end()) {
		_particleSystem->removeEmitter(_emitters[name]);
		_emitters.erase(name);
	}
}

void LocoMotor::Graphics::ParticleSystem::MoveEmitter(std::string name, const LMVector3 position) {
	Ogre::ParticleEmitter* emitter = GetEmitter(name);
	emitter->setPosition(LmVectorToOgreVector(position));
}

void LocoMotor::Graphics::ParticleSystem::RotateEmitter(std::string name, const LMVector3 rotation) {
	Ogre::ParticleEmitter* emitter = GetEmitter(name);
	emitter->setDirection(LmVectorToOgreVector(rotation));
}

void LocoMotor::Graphics::ParticleSystem::SetEmitting(std::string name, bool emitting) {
	Ogre::ParticleEmitter* emitter = GetEmitter(name);
	emitter->setEnabled(emitting);
}