#include "Camera.h"
#include <OgreCamera.h>
#include <OgreViewport.h>
#include "GraphicsManager.h"
#include "OgreSceneManager.h"
#include "GameObject.h"
#include "Transform.h"
#include <OgreRenderWindow.h>
#include <iostream>


LocoMotor::Camera::Camera() : _mCamera(nullptr), _target(nullptr), _vp(nullptr), _node(nullptr), _man(nullptr) {
	_offset = LMVector3(0, 0, 0);
	_nodeScale = LMVector3(1, 1, 1);
	_nodeRotation = LMQuaternion();
}

LocoMotor::Camera::~Camera() {
	_man->getOgreSceneManager()->destroyCamera(_mCamera);
	_man->destroyNode(_node->getName());
}

void LocoMotor::Camera::SetTarget(GameObject* target, LMVector3 offset)
{
	_target = target;
	_offset = offset;
}

void LocoMotor::Camera::SetFOV(float newFov)
{
	_mCamera->setFOVy(Ogre::Radian(newFov * 3.14f / 180));
}

void LocoMotor::Camera::SetViewportRatio(int viewportIndex, int modeIndex)
{
	if (modeIndex == 0) {
		_vp->setDimensions(0.0f, 0.0f, 1.0f, 1.0f);
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (modeIndex == 1) {
		_vp->setDimensions(0.0f, 0.0f, 1.0f, 0.5f);
		_vp->update();
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (modeIndex == 2) {
		_vp->setDimensions(0.0f, 0.5f, 1.0f, 0.5f);
		_vp->update();
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
}

void LocoMotor::Camera::SetClippingPlane(int nearPlane, int farPlane) {
	_mCamera->setNearClipDistance(nearPlane);
	_mCamera->setFarClipDistance(farPlane);
}

void LocoMotor::Camera::start() {}

void LocoMotor::Camera::setParameters(std::vector<std::pair<std::string, std::string>>& params) {
	init();
	for (auto& param : params) {
		if (param.first == "CameraMode") {
			try {
				int modeIndex = std::stoi(param.second);
				SetViewportRatio(1, modeIndex); //ViewportIndex = 1 TEMPORAL
			}
			catch (...) {
			}
		}
		else if (param.first == "FOV" || param.first == "fov") {
			try {
				float fov = std::stof(param.second);
				SetFOV(fov);
			}
			catch (...) {
			}
		}
		else if (param.first == "target") {
			//_target = param.second;
		}
		else if (param.first == "main") {
			//gameObject->GetScene()->SetCamObj(gameObject);
		}
	}
}

void LocoMotor::Camera::render() {
	_vp->update();
}

// Funcionalidad componentes

void LocoMotor::Camera::init()
{
	_man = Graphics::GraphicsManager::GetInstance();
	_node = _man->createNode(_gameObject->getName() + "_cam");
	_mCamera = _man->getOgreSceneManager()->createCamera(_gameObject->getName() + "_cam");
	_node->attachObject(_mCamera);
	_target = nullptr;
	_offset = LMVector3(0, 0, 0);
	_vp = _man->getRenderWindow()->addViewport(_mCamera, 0);
	_vp->setBackgroundColour(Ogre::ColourValue(0.6f, 0.7f, 0.8f));
}
void LocoMotor::Camera::onEnable()
{
}
void LocoMotor::Camera::update(float dT)
{
	if (_gameObject->getComponent<Transform>() == nullptr)return;

	_node->setPosition(_gameObject->getComponent<Transform>()->GetPosition().GetX(), _gameObject->getComponent<Transform>()->GetPosition().GetY(), _gameObject->getComponent<Transform>()->GetPosition().GetZ());

	Ogre::Quaternion quat = Ogre::Quaternion();
	if (_nodeRotation.GetW() != _gameObject->getComponent<Transform>()->GetRotation().GetW()) {
		quat.w = _gameObject->getComponent<Transform>()->GetRotation().GetW();
		_nodeRotation.SetW(_gameObject->getComponent<Transform>()->GetRotation().GetW());
	}
	if (_nodeRotation.GetX() != _gameObject->getComponent<Transform>()->GetRotation().GetX()) {
		quat.x = _gameObject->getComponent<Transform>()->GetRotation().GetX();
		_nodeRotation.SetX(_gameObject->getComponent<Transform>()->GetRotation().GetX());
	}
	if (_nodeRotation.GetY() != _gameObject->getComponent<Transform>()->GetRotation().GetY()) {
		quat.y = _gameObject->getComponent<Transform>()->GetRotation().GetY();
		_nodeRotation.SetY(_gameObject->getComponent<Transform>()->GetRotation().GetY());
	}
	if (_nodeRotation.GetZ() != _gameObject->getComponent<Transform>()->GetRotation().GetZ()) {
		quat.z = _gameObject->getComponent<Transform>()->GetRotation().GetZ();
		_nodeRotation.SetZ(_gameObject->getComponent<Transform>()->GetRotation().GetZ());
	}
	_node->rotate(quat, Ogre::Node::TS_LOCAL);

	if (_nodeScale.GetX() != _gameObject->getComponent<Transform>()->GetSize().GetX()) {
		_node->scale(_gameObject->getComponent<Transform>()->GetSize().GetX(), 1, 1);
		_nodeScale.SetX(_gameObject->getComponent<Transform>()->GetSize().GetX());
	}
	if (_nodeScale.GetY() != _gameObject->getComponent<Transform>()->GetSize().GetY()) {
		_node->scale(1, _gameObject->getComponent<Transform>()->GetSize().GetY(), 1);
		_nodeScale.SetY(_gameObject->getComponent<Transform>()->GetSize().GetY());
	}
	if (_nodeScale.GetZ() != _gameObject->getComponent<Transform>()->GetSize().GetZ()) {
		_node->scale(1, 1, _gameObject->getComponent<Transform>()->GetSize().GetZ());
		_nodeScale.SetZ(_gameObject->getComponent<Transform>()->GetSize().GetZ());
	}
}
void LocoMotor::Camera::onDisable()
{
}
