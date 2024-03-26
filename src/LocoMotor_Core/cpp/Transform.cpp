#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "GraphicsManager.h"
//#include "LmVectorConverter.h"
#include <iostream>



LocoMotor::Transform::Transform() {
	_position = LMVector3();
	_localPosition = LMVector3();
	_direction = LMQuaternion();
	_scale = LMVector3(1, 1, 1);

	parent = nullptr;
}

LocoMotor::Transform::~Transform() {}


void LocoMotor::Transform::initComponent() {
	//_gameObject->registerTransform(this);
}


void LocoMotor::Transform::setParameters(std::vector<std::pair<std::string, std::string>>& params) {
	//_gameObject->registerTransform(this);

	for (const auto& pair : params) {
		if (pair.first == "pos" || pair.first == "position") {
			_position = LMVector3::StringToVector(pair.second);
		}
		else if (pair.first == "rot" || pair.first == "rotation") {
			_direction = LMVector3::StringToVector(pair.second).AsRotToQuaternion();
			_direction.Normalize();
		}
		else if (pair.first == "size" || pair.first == "scale") {
			_scale = LMVector3::StringToVector(pair.second);
		}
	}
}

void LocoMotor::Transform::InitRuntime(LMVector3 initPos, LMVector3 initRot, LMVector3 initScale) {
	//_gameObject->registerTransform(this);

	_position = initPos;
	_localPosition = LMVector3(0, 0, 0);
	_direction = initRot.AsRotToQuaternion();
	_localDirection = LMQuaternion();
	_scale = initScale;
	_localScale = LMVector3(1, 1, 1);
}

void LocoMotor::Transform::start() {
	SetPosition(_position);
	SetRotation(_direction);
	SetSize(_scale);
}

void LocoMotor::Transform::update(const float dt) {}


const LocoMotor::LMVector3& LocoMotor::Transform::GetPosition() {
	return _position;
}

const LocoMotor::LMVector3& LocoMotor::Transform::GetLocalPosition() {
	return _localPosition;
}

void LocoMotor::Transform::SetPosition(const LMVector3& newPosition) {

	//Sets Position In World Coordinates
	_position = newPosition;
	

	//Sets Position of Rigidbody
	//SetPhysPosition(_position);
	////Sets Position of everychild
	if (childList.size() > 0) {
		for (auto& a : childList) {
			if (a->GetParent() == nullptr) continue;
			a->SetPosition((a->GetParent()->GetRotation() * a->_localPosition) + a->GetParent()->GetPosition());

			//If has a Parent, recalculate LocalPosition j in case
			//if(a->parent != nullptr) a->_localPosition = a->_position - a->parent->GetPosition();
		}
	}
}

void LocoMotor::Transform::SetLocalPosition(const LMVector3& newLocalPosition) {
	_localPosition = newLocalPosition;
	LMVector3 totalPos = _position + _localPosition;
	if (parent)
		totalPos = parent->GetPosition() + (parent->GetRotation() * _localPosition);
	
	//SetPhysPosition(totalPos);
}

//GETTERS
const LocoMotor::LMQuaternion& LocoMotor::Transform::GetRotation() {
	return _direction;
}
const LocoMotor::LMQuaternion& LocoMotor::Transform::GetLocalRotation() {
	return _localDirection;
}
const LocoMotor::LMVector3& LocoMotor::Transform::GetEulerRotation() {
	return _direction.ToEuler();
}
const LocoMotor::LMVector3& LocoMotor::Transform::GetLocalEulerRotation() {
	return _localDirection.ToEuler();
}

//SET ROTATIONS
void LocoMotor::Transform::SetRotation(const LMVector3& newRotation) {
	SetRotation(newRotation.AsRotToQuaternion());
}

void LocoMotor::Transform::SetRotation(const LMQuaternion& newRotation) {
	_direction = newRotation;
	_direction.Normalize();
	
	//SetPhysRotation(newRotation);
	//Set Rotation of EveryChild
	if (childList.size() > 0) {
		for (auto a : childList) {
			a->SetRotation(a->GetLocalRotation() + a->GetParent()->_direction);
		}
	}
}

void LocoMotor::Transform::SetLocalRotation(const LMVector3& newRotation) {
	SetLocalRotation(newRotation.AsRotToQuaternion());
}

void LocoMotor::Transform::SetLocalRotation(const LMQuaternion& newRotation) {
	_localDirection = newRotation;
	_localDirection.Normalize();
	
	//SetPhysRotation(newRotation);
}



const LocoMotor::LMVector3& LocoMotor::Transform::GetSize() {
	return _scale;
}

void LocoMotor::Transform::SetSize(const LMVector3& newSize) {
	_scale = newSize;
}

void LocoMotor::Transform::SetUpwards(const LMVector3& newUpward) {
	double angle = GetRotation().Up().Angle(newUpward);
	if (angle == 0.) return;

	LMVector3 v1 = GetRotation().Up();
	LMVector3 v2 = newUpward;
	LMVector3 axis = LMVector3(
		v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY(),
		v1.GetZ() * v2.GetX() - v1.GetX() * v2.GetZ(),
		v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());

	SetRotation(GetRotation().Rotate(axis, angle));
}


void LocoMotor::Transform::SetForward(const LMVector3& newForward) {
	double angle = GetRotation().Forward().Angle(newForward);
	if (angle == 0.) return;

	LMVector3 v1 = GetRotation().Forward();
	LMVector3 v2 = newForward;
	LMVector3 axis = LMVector3(
		v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY(),
		v1.GetZ() * v2.GetX() - v1.GetX() * v2.GetZ(),
		v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());

	SetRotation(GetRotation().Rotate(axis, angle));
}


void LocoMotor::Transform::LookAt(const LMVector3& lookPos) {
	LMVector3 newForward = lookPos - GetPosition();
	SetForward(newForward);
}


void LocoMotor::Transform::LookAt(const LMVector3& lookPos, const LMVector3& up) {
	SetUpwards(up);
	LMVector3 newForward = lookPos - GetPosition();
	SetForward(newForward);
}

void LocoMotor::Transform::AddChild(Transform* trToAdd, bool resetLocal) {
	childList.push_back(trToAdd);
	trToAdd->SetParent(this);
}

void LocoMotor::Transform::RemoveChild(Transform* trToRemove) {
	//childList.remove(trToRemove);
}

void LocoMotor::Transform::SetParent(Transform* trParent) {
	parent = trParent;
	_localPosition = _position - parent->GetPosition();
	_localDirection = _direction - parent->GetRotation();
	//std::cout << "\nObjecto: " << this->_gameObject->getName() << " tiene Local a: " << _localPosition.ToString() << "\n";
	//std::cout << "\nObjecto: " << this->_gameObject->getName() << " tiene Rotation Local a: " << _localDirection.ToString() << "\n";
}
LocoMotor::Transform* LocoMotor::Transform::GetParent() {
	return parent;
}
