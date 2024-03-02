#include "Node.h"

#include <OgreSceneNode.h>
#include <OgreMovableObject.h>
#include <OgreNode.h>

using namespace LocoMotor::Graphics;

Node::Node(Ogre::SceneNode* node, std::string name) {
	_node = node;
	_name = name;
	_ent = std::vector<Ogre::MovableObject*>();
}

Node::~Node() {
	for (std::vector<Ogre::MovableObject*>::iterator it = _ent.begin(); it != _ent.end(); it = _ent.erase(it)) {
		delete* it;
	}
}

void Node::Translate(float x, float y, float z) {
	_node->translate(x, y, z, Ogre::Node::TS_LOCAL);
}

void Node::Rotate(float x, float y, float z) {
	_node->pitch(Ogre::Degree(x));
	_node->yaw(Ogre::Degree(y));
	_node->roll(Ogre::Degree(z));
}

void Node::RotateLocal(float x, float y, float z) {
	_node->pitch(Ogre::Degree(x), Ogre::Node::TS_LOCAL);
	_node->yaw(Ogre::Degree(y), Ogre::Node::TS_LOCAL);
	_node->roll(Ogre::Degree(z), Ogre::Node::TS_LOCAL);
}

void Node::Scale(float x, float y, float z) {
	_node->scale(x, y, z);
}

void Node::LookAt(float x, float y, float z) {
	_node->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_WORLD);
}

void Node::SetDirection(float x, float y, float z) {
	_node->setDirection(x, y, z);
}

void Node::Attach(Ogre::MovableObject* obj) {

	_node->attachObject(obj);
	_ent.push_back(obj);
}

Node* Node::CreateChild(const std::string& name) {
	Node* child = new Node(_node->createChildSceneNode(), name);
	return child;
}

void Node::DestroyChild(Node* nod) {
	_node->removeAndDestroyChild(nod->_node);
	delete nod;
}

std::string Node::GetName() {
	return _name;
}


void Node::SetPosition(float x, float y, float z) {
	_node->setPosition(x, y, z);
}

float Node::GetPosition_X() {
	return _node->getPosition().x;
}

float Node::GetPosition_Y() {
	return _node->getPosition().y;
}

float Node::GetPosition_Z() {
	return _node->getPosition().z;
}

float Node::GetRotation_W() {
	return _node->getOrientation().w;
}

float Node::GetRotation_X() {
	return _node->getOrientation().x;
}

float Node::GetRotation_Y() {
	return _node->getOrientation().y;
}

float Node::GetRotation_Z() {
	return _node->getOrientation().z;
}

float Node::GetScale_X() {
	return _node->getScale().x;
}

float Node::GetScale_Y() {
	return _node->getScale().y;
}

float Node::GetScale_Z() {
	return _node->getScale().z;
}

void Node::SetScale(float x, float y, float z) {
	_node->setScale(x, y, z);
}

void Node::ResetOrientation() {
	_node->resetOrientation();
}

void Node::SetOrientation(Ogre::Quaternion& q) {
	_node->setOrientation(q.w, q.x, q.y, q.z);
}
