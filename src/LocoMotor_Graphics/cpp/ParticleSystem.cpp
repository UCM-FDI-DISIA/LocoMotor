#include "ParticleSystem.h"


#include <OgreParticleEmitter.h>
#include <OgreParticleSystem.h>



void LocoMotor::ParticleSystem::init() {

	//_renderScn = nullptr;
	//_particleHelper = nullptr;

	_filename = "";
	_name = "";
}

void LocoMotor::ParticleSystem::onEnable() {}

void LocoMotor::ParticleSystem::update(float dT) {

	// Actualizar la posicion del nodo asignado al ParticleSystem para que siga al GameObject asignado

	//_gameObject->

	if (_node != nullptr) {
	//	float x = (float) _gameObject->GetTransform()->GetPosition().GetX();
	//	float y = (float) gameObject->GetTransform()->GetPosition().GetY();
	//	float z = (float) gameObject->GetTransform()->GetPosition().GetZ();
	//	_node->SetPosition(x, y, z);
	}
}

void LocoMotor::ParticleSystem::onDisable() {}


LocoMotor::ParticleSystem::ParticleSystem() {}

LocoMotor::ParticleSystem::~ParticleSystem() {}

Ogre::ParticleEmitter* LocoMotor::ParticleSystem::GetEmitter(std::string name) {
	if (_emitters.find(name) != _emitters.end())
		return _emitters[name];
}

//Ogre::Vector3 LocoMotor::ParticleSystem::LmVectorToOgreVector(const LMVector3 lmVector) {
//	return Ogre::Vector3(lmVector.GetX(), lmVector.GetY(), lmVector.GetZ());
//}

void LocoMotor::ParticleSystem::setParameters(std::vector<std::pair<std::string, std::string>>& params) {

	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "name") {
			_name = params[i].second;
		}
		else if (params[i].first == "file") {
			_filename = params[i].second;
		}
	}
}

void LocoMotor::ParticleSystem::AddEmitter(std::string name, const LMVector3 position) {

	// Comprobar que no se ha creado un emitter anterior con el mismo nombre
	if (_emitters.find(name) == _emitters.end()) {
		_emitters.insert({ name, _particleSystem->addEmitter(name) });
		//_emitters[name]->setPosition(LmVectorToOgreVector(position));
	}
}

void LocoMotor::ParticleSystem::RemoveEmitter(std::string name) {

	if (_emitters.find(name) != _emitters.end()) {
		_particleSystem->removeEmitter(_emitters[name]);
		_emitters.erase(name);
	}
}

void LocoMotor::ParticleSystem::MoveEmitter(std::string name, const LMVector3 position) {
	Ogre::ParticleEmitter* emitter = GetEmitter(name);
	//emitter->setPosition(LmVectorToOgreVector(position));
}

void LocoMotor::ParticleSystem::RotateEmitter(std::string name, const LMVector3 rotation) {
	Ogre::ParticleEmitter* emitter = GetEmitter(name);
	//emitter->setDirection(LmVectorToOgreVector(rotation));
}

void LocoMotor::ParticleSystem::SetEmitting(std::string name, bool emitting) {
	Ogre::ParticleEmitter* emitter = GetEmitter(name);
	emitter->setEnabled(emitting);
}