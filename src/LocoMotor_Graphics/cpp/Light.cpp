#include "Light.h"

LocoMotor::Light::Light() {
	_light = nullptr;
	
}

void LocoMotor::Light::init(Ogre::Light* l, Ogre::Light::LightTypes type) {
	_light = l;
	_light->setType(type);
}
void LocoMotor::Light::start() {

}

void LocoMotor::Light::update(float dt) {
	//to do: hacer que la luz pueda moverse con el transform
}

LocoMotor::Light::~Light() {
	//buscar destructora de luz en ogre
}

Ogre::MovableObject* LocoMotor::Light::GetMovObj() {
	return _light;
}

void LocoMotor::Light::setDiffuse(float r, float g, float b) {
	_light->setDiffuseColour(r, g, b);
}

void LocoMotor::Light::setSpecular(float r, float g, float b) {
	_light->setSpecularColour(r, g, b);
}