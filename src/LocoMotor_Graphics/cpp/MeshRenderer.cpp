#include "MeshRenderer.h"
#include "OgreEntity.h"

LocoMotor::MeshRenderer::MeshRenderer() {
	_gObj = nullptr;
	_name = "";
	_src = "";
	_mat = "";
	_mesh = nullptr;
	_isStatic = false;
}

void LocoMotor::MeshRenderer::init(std::string name, std::string file,bool istatic) {
	_name = name;
	_src = file;
	_isStatic = istatic;
}

void LocoMotor::MeshRenderer::start() {

}


void LocoMotor::MeshRenderer::update(float dt) {

}

void LocoMotor::MeshRenderer::setVisible(bool visible) {
	if (_mesh != nullptr) {
		_mesh->setVisible(visible);
	}
}
void LocoMotor::MeshRenderer::setMaterial(std::string mat) {
	if (_mesh != nullptr) {
		_mesh->setMaterialName(mat);
	}
}

Ogre::MovableObject* LocoMotor::MeshRenderer::getMovObj() {
	return _mesh;
}
