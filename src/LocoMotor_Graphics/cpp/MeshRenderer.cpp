#include "MeshRenderer.h"
#include "OgreEntity.h"
#include <OgreMovableObject.h>
#include "GraphicsManager.h"
#include <OgreSceneManager.h>

LocoMotor::MeshRenderer::MeshRenderer() {
	_gObj = nullptr;
	_name = "";
	_src = "";
	_mat = "";
	_mesh = nullptr;
	_isStatic = false;
}

LocoMotor::MeshRenderer::~MeshRenderer()
{
}

void LocoMotor::MeshRenderer::setParameters(std::vector<std::pair<std::string, std::string>>& params)
{
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

void LocoMotor::MeshRenderer::setMesh(std::string mesh) {
	if (Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(mesh))
		_mesh = LocoMotor::Graphics::GraphicsManager::GetInstance()->createRenderer(mesh);
}

Ogre::MovableObject* LocoMotor::MeshRenderer::getMovObj() {
	return _mesh;
}
