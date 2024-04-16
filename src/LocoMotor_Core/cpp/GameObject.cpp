#include "GameObject.h"
#include "Component.h"

LocoMotor::Component* LocoMotor::GameObject::addComponent(const std::string& name,std::vector<std::pair<std::string, std::string>>& params)
{
	ComponentsFactory* factory = LocoMotor::ComponentsFactory::GetInstance();
	if (_components.count(name) > 0) {
		return _components[name];
	}
	else {
		Component* comp = factory->createComponent(name);
		if (comp == nullptr)
			return nullptr;
		comp->init(this, true);
		_toStart.push(comp);
		_components.insert({ name, comp });
		comp->setParameters(params);
		return comp;
	}
}

void LocoMotor::GameObject::removeComponents(const std::string& name) {
	if (_components.count(name) == 0) {
		return;
	}
	auto comps = _components.equal_range(name);
	for (auto comp = comps.first; comp != comps.second; ++comp) {
		_toDestroy.push(comp->second);
	}
	_components.erase(comps.first, comps.second);
}

LocoMotor::GameObject::GameObject(std::string name) : _components(), _toEnable(), _toDisable(), _toStart(), _toDestroy(), _scene(nullptr), _transform(nullptr), _active(true), _gobjName(name), shouldCallAwake(true) {}

LocoMotor::GameObject::~GameObject() {
	for (auto& pair : _components) {
		Component* cmp = pair.second;
		cmp->onDisable();
		cmp->onDestroy();
		delete cmp;
		cmp = nullptr;
		
	}
	_components.clear();
}

void LocoMotor::GameObject::update(float dt) {

	while (!_toDestroy.empty()) {
		Component* cmp = _toDestroy.front();
		cmp->onDisable();
		cmp->onDestroy();
		delete cmp;
		_toDestroy.pop();
	}
	while (!_toDisable.empty()) {
		Component* cmp = _toDisable.front();
		cmp->onDisable();
		_toDisable.pop();
	}
	while (!_toStart.empty()) {
		Component* cmp = _toStart.front();
		if (shouldCallAwake) {
			cmp->awake();
		}
		cmp->onEnable();
		cmp->start();
		_toStart.pop();
	}
	shouldCallAwake = false;
	while (!_toEnable.empty()) {
		Component* cmp = _toEnable.front();
		cmp->onEnable();
		_toEnable.pop();
	}
	for (auto& pair : _components) {

		Component* cmp = pair.second;
		if (cmp->isEnabled()) cmp->update(dt);
	}
}

void LocoMotor::GameObject::fixedUpdate() {
	for (auto& pair : _components) {
		Component* cmp = pair.second;
		if (cmp->isEnabled()) cmp->fixedUpdate();
	}
}

void LocoMotor::GameObject::init(LocoMotor::Scene* scene, bool active) {
	_scene = scene;
	_active = active;
}

bool LocoMotor::GameObject::hasToBeDestroyed() {
	return _toDestroyThis;
}

void LocoMotor::GameObject::setToDestroy() {
	_toDestroyThis = true;
}

std::string LocoMotor::GameObject::getName() {
	return _gobjName;
}
