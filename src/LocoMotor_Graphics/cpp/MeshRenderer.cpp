#include "MeshRenderer.h"
#include "OgreEntity.h"
#include <OgreMovableObject.h>
#include "GraphicsManager.h"
#include <OgreSceneManager.h>
#include <OgreStaticGeometry.h>

#include "GameObject.h"
#include "Transform.h"

#include <iostream>

LocoMotor::MeshRenderer::MeshRenderer() {
	_name = "";
	_src = "";
	_mat = "";
	_mesh = nullptr;
	_setStatic = false;
	isSelfVisible = true;
	_node = nullptr;
	_nodeScale = LMVector3(1, 1, 1);
	_nodeRotation = LMQuaternion();

	numAnimationsActive = 0;
}

LocoMotor::MeshRenderer::~MeshRenderer() {
}

void LocoMotor::MeshRenderer::setParameters(ComponentMap& params) {
	Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
	_node = man->createNode(_gameObject->getName());

	std::string meshName = "";
	std::string matName = "";

	bool visible = true;

	for (auto& param : params) {
		if (param.first == "Mesh" || param.first == "mesh") {
			meshName = param.second;
		}
		else if (param.first == "Material" || param.first == "material") {
			matName = param.second;
		}
		else if (param.first == "Static" || param.first == "static") {
			_setStatic = true;
		}
		else if (param.first == "Invisible" || param.first == "invisible") {
			visible = false;
		}
	}

	if (meshName != "") {
		setMesh(meshName);

		if (matName != "") {
			_mesh->setMaterialName(matName);
		}
		isSelfVisible = visible;
		_mesh->setVisible(visible);
	}
}

void LocoMotor::MeshRenderer::awake() {

	if (_setStatic) {
		auto sceneMan = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager();
		auto staticGeom = sceneMan->getStaticGeometry(sceneMan->getName() + "_static");
		staticGeom->addSceneNode(_node);
		_setStatic = false;
	}
}

void LocoMotor::MeshRenderer::init(const std::string& name, const std::string& file, bool istatic) {
	_name = name;
	_src = file;
	_setStatic = istatic;
	Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
	_node = man->createNode(_gameObject->getName());

	//int i = 0;
}

void LocoMotor::MeshRenderer::playAnimation(const std::string& animationName, bool loop) {

	// Sets the current animation to the specified one by name "animationName"
	currentAnimation = allAnimations[animationName];
	currentAnimation->setEnabled(true);
	currentAnimation->setLoop(loop);

	// Disable the other animations of this mesh
	for (const auto& thisAnimation : allAnimations)
		if (thisAnimation.second != currentAnimation)
			thisAnimation.second->setEnabled(false);
}

void LocoMotor::MeshRenderer::updateAnimation(double dt) {

	if (currentAnimation != nullptr)
		currentAnimation->addTime(Ogre::Real(dt));

		//int num = 0;
		//auto it = allAnimations.begin();
		//while (num != numAnimationsActive) {
		//	if (it->second->getEnabled()) {
		//		it->second->addTime(Ogre::Real(dt));
		//		num++;
		//	}
		//	it++;
		//}
}

void LocoMotor::MeshRenderer::start() {
	if (_gameObject->getComponent<Transform>() == nullptr) {
		std::cerr << "GameObject with name '" << _gameObject->getName() << "' has no Transform component\n";
		return;
	}
}

void LocoMotor::MeshRenderer::onEnable() {
	// si, ya se, este isEnabled() es sospechoso, por que onEnable se llama el primer frame aunque se haya desactivado antes
	if (isSelfVisible && _mesh != nullptr && isEnabled()) 
		_mesh->setVisible(true);
}

void LocoMotor::MeshRenderer::onDisable() {
	if (_mesh != nullptr && !isEnabled()) {
		_mesh->setVisible(false);
	}
}

void LocoMotor::MeshRenderer::update(float dt) {
	if (_gameObject->getComponent<Transform>() == nullptr)return;

	if (_setStatic) {
		auto sceneMan = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager();
		auto staticGeom = sceneMan->getStaticGeometry(sceneMan->getName() + "_static");
		staticGeom->addSceneNode(_node);
		_setStatic = false;
	}

	LMVector3 pos = _gameObject->getComponent<Transform>()->GetPosition();
	_node->setPosition(pos.GetX(), pos.GetY(), pos.GetZ());

	Ogre::Quaternion quat = Ogre::Quaternion();
	quat.w = _gameObject->getComponent<Transform>()->GetRotation().GetW();
	quat.x = _gameObject->getComponent<Transform>()->GetRotation().GetX();
	quat.y = _gameObject->getComponent<Transform>()->GetRotation().GetY();
	quat.z = _gameObject->getComponent<Transform>()->GetRotation().GetZ();
	_node->setOrientation(quat);

	LMVector3 size = _gameObject->getComponent<Transform>()->GetSize();
	_node->setScale(size.GetX(), size.GetY(), size.GetZ());
}

void LocoMotor::MeshRenderer::setVisible(bool visible) {
	isSelfVisible = visible;
	if (_mesh != nullptr && this->isEnabled()) {
		_mesh->setVisible(visible);
	}
}
void LocoMotor::MeshRenderer::setMaterial(const std::string& mat) {
	if (_mesh != nullptr) {
		_mesh->setMaterialName(mat);
	}
}

void LocoMotor::MeshRenderer::setMesh(const std::string& mesh) {
	if (Graphics::GraphicsManager::GetInstance()->getOgreSceneManager() == nullptr)
		return;
	if (Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(mesh)) {
		_mesh = LocoMotor::Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createEntity(mesh);
		if (_mesh != nullptr) {
			_node->attachObject(_mesh);
		}
	}


	// Inicializar animaciones
	allAnimations = std::unordered_map<std::string, Ogre::AnimationState*>();
	if (_mesh->getAllAnimationStates() != nullptr) {
		Ogre::AnimationStateMap mapa = _mesh->getAllAnimationStates()->getAnimationStates();

		std::cout << " ANIMATIONS LOADED : \n";

		for (auto it = mapa.begin(); it != mapa.end(); it++) {
			allAnimations.insert({ it->first, it->second });
			std::cout << it->first << "\n";
		}
		std::cout << "\n";
	}
}

Ogre::MovableObject* LocoMotor::MeshRenderer::getMovObj() {
	return _mesh;
}
