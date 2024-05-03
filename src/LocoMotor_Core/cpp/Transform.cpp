#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "GraphicsManager.h"
//#include "LmVectorConverter.h"
#include <iostream>



LocoMotor::Transform::Transform() {
	_position = LMVector3();
	_direction = LMQuaternion();
	_scale = LMVector3(1, 1, 1);
}

LocoMotor::Transform::~Transform() {}


void LocoMotor::Transform::initComponent() {
	//_gameObject->registerTransform(this);
}


void LocoMotor::Transform::setParameters(ComponentMap& params) {
	//_gameObject->registerTransform(this);

	for (const auto& pair : params) {
		if (pair.first == "pos" || pair.first == "position") {
			_position = LMVector3::stringToVector(pair.second);
		}
		else if (pair.first == "rot" || pair.first == "rotation") {
			_direction = LMVector3::stringToVector(pair.second).asRotToQuaternion();
			_direction.normalize();
		}
		else if (pair.first == "size" || pair.first == "scale") {
			_scale = LMVector3::stringToVector(pair.second);
		}
	}
}

void LocoMotor::Transform::initRuntime(LMVector3 initPos, LMVector3 initRot, LMVector3 initScale) {
	//_gameObject->registerTransform(this);

	_position = initPos;
	_direction = initRot.asRotToQuaternion();
	_scale = initScale;
}

void LocoMotor::Transform::start() {
}

void LocoMotor::Transform::update(const float dt) {}


LocoMotor::LMVector3 LocoMotor::Transform::getPosition() {
	return _position;
}

void LocoMotor::Transform::setPosition(const LMVector3& newPosition) {

	//Sets Position In World Coordinates
	_position = newPosition;
}

//GETTERS
LocoMotor::LMQuaternion LocoMotor::Transform::getRotation(){
	return _direction;
}
LocoMotor::LMVector3 LocoMotor::Transform::getEulerRotation() {
	return _direction.toEuler();
}

//SET ROTATIONS

void LocoMotor::Transform::setRotationWithVector(const LMVector3& newRotation) {
	setRotation(newRotation.asRotToQuaternion());
}

void LocoMotor::Transform::setRotation(const LMQuaternion& newRotation) {


	// Si alguno de los valores no es valido, no realizar la operacion
	if (std::isnan(newRotation.getW()) || std::isnan(newRotation.getX()) || std::isnan(newRotation.getX()) || std::isnan(newRotation.getZ()))
		return;

	_direction = newRotation;
	_direction.normalize();
}



LocoMotor::LMVector3 LocoMotor::Transform::getSize() {
	return _scale;
}

void LocoMotor::Transform::setSize(const LMVector3& newSize) {
	_scale = newSize;
}

void LocoMotor::Transform::setUpwards(const LMVector3& newUpward) {
	float angle = getRotation().up().angle(newUpward);
	if (angle == 0.f) return;

	LMVector3 v1 = getRotation().up();
	LMVector3 v2 = newUpward;
	LMVector3 axis = LMVector3(
		v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
		v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
		v1.getX() * v2.getY() - v1.getY() * v2.getX());

	setRotation(getRotation().rotate(axis, angle));
}


void LocoMotor::Transform::setForward(const LMVector3& newForward) {
	float angle = getRotation().forward().angle(newForward);
	if (angle == 0.f) return;

	LMVector3 v1 = getRotation().forward();
	LMVector3 v2 = newForward;
	LMVector3 axis = LMVector3(
		v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
		v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
		v1.getX() * v2.getY() - v1.getY() * v2.getX());

	setRotation(getRotation().rotate(axis, angle));
}


void LocoMotor::Transform::lookAt(const LMVector3& lookPos) {
	LMVector3 newForward = lookPos - getPosition();
	setForward(newForward);
}


void LocoMotor::Transform::lookAt(const LMVector3& lookPos, const LMVector3& up) {
	setUpwards(up);
	LMVector3 newForward = lookPos - getPosition();
	setForward(newForward);
}
