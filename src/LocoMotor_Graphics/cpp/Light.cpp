
#include "Light.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Node.h"
#include <OgreLight.h>

LocoMotor::Light::Light() {
	_light = nullptr;
	_node = nullptr;
}

void LocoMotor::Light::init(std::string name, int type) {
	_name = name;
	_light = Graphics::GraphicsManager::GetInstance()->createMainLight();
	_light->setType(Ogre::Light::LT_DIRECTIONAL);
	Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
	_node = man->createNode(_gameObject->getName());
	_node->Attach(_light);
	setDiffuse(1, 1, 1);
	_node->SetDirection(-1, -1, -1);

}
void LocoMotor::Light::start() {

}

void LocoMotor::Light::update(float dt) {
	//to do: hacer que la luz pueda moverse con el transform
}

LocoMotor::Light::~Light() {
	//buscar destructora de luz en ogre
}

//Ogre::MovableObject* LocoMotor::Light::getMovObj() {
//	return _light;
//}
Ogre::Light* LocoMotor::Light::getLight() {
	return _light;
}

void LocoMotor::Light::setDiffuse(float r, float g, float b) {
	_light->setDiffuseColour(r, g, b);
}

void LocoMotor::Light::setSpecular(float r, float g, float b) {
	_light->setSpecularColour(r, g, b);
}

void LocoMotor::Light::setParameters(std::vector<std::pair<std::string, std::string>>& params){

}