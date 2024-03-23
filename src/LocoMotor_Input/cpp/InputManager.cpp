#include "InputManager.h"
#include <iostream>
#include <algorithm>

#include "SDL_Scancode.h"
#include "SDL_keyboard.h"
#include <SDL_events.h>
#include <SDL_gamecontroller.h>
#include "LMInputs.h"

#include <cassert>

using namespace LocoMotor;
using namespace Input;

InputManager* InputManager::_instance = nullptr;

InputManager::InputManager() {
	_joystickAxis[0] = 0.f;
	_joystickAxis[1] = 0.f;
	_joystickAxis[2] = 0.f;
	_joystickAxis[3] = 0.f;
	_triggersValue[0] = 0.f;
	_triggersValue[1] = 0.f;
	_mousePos.first = 0;
	_mousePos.second = 0;
}

bool InputManager::Init() {
	assert(_instance == nullptr);
	_instance = new InputManager();

	if (!_instance->init()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}

	return true;
}

bool InputManager::init() {

	return true;
}

InputManager* InputManager::GetInstance() {
	return _instance;
}

void InputManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

// KEYBOARD
bool InputManager::GetKeyDown(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].down;
}

bool InputManager::GetKey(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].isPressed;
}

bool InputManager::GetKeyUp(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].up;
}

// MOUSE
bool InputManager::GetMouseButtonDown(const int& buttonCode) {
	return _mouseButtons[buttonCode].down;
}

bool InputManager::GetMouseButton(const int& buttonCode) {
	return _mouseButtons[buttonCode].isPressed;
}

bool InputManager::GetMouseButtonUp(const int& buttonCode) {
	return _mouseButtons[buttonCode].up;
}

std::pair<int, int> InputManager::GetMousePos() {
	return _mousePos;
}

// CONTROLLER

	// BUTTONS
bool InputManager::GetButtonDown(ControllerId controllerId, const int& buttonCode) {
	return connectedControllers[controllerId]._controllerButtons[buttonCode].down;
}

bool InputManager::GetButton(ControllerId controllerId, const int& buttonCode) {
	return connectedControllers[controllerId]._controllerButtons[buttonCode].isPressed;
}

bool InputManager::GetButtonUp(ControllerId controllerId, const int& buttonCode) {
	return connectedControllers[controllerId]._controllerButtons[buttonCode].up;
}

	// JOYSTICKS
float InputManager::GetJoystickValue(ControllerId controllerId, const int& joystickIndex, const Axis& axis) {

	if (joystickIndex == 0) {

		if (axis == Horizontal)
			return connectedControllers[controllerId]._joystickAxis[0];
		else if (axis == Vertical)
			return connectedControllers[controllerId]._joystickAxis[1];
	}
	else if (joystickIndex == 1) {

		if (axis == Horizontal)
			return connectedControllers[controllerId]._joystickAxis[2];
		else if (axis == Vertical)
			return connectedControllers[controllerId]._joystickAxis[3];
	}
	return 0.f;
}

	// TRIGGER
float InputManager::GetTriggerValue(ControllerId controllerId, const int& triggerIndex) {
	if (triggerIndex == 0 || triggerIndex == 1)
		return connectedControllers[controllerId]._triggersValue[triggerIndex];
		//return _triggersValue[triggerIndex];
	else
		return 0.0f;
}


bool InputManager::RegisterEvents() {

	// RESETEAR TECLAS Y BOTONES

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (_keyboardInputs_ToReset.size() != 0)
		ResetKeyboardInputs();

	if (_mouseInputs_ToReset.size() != 0)
		ResetMouseInputs();

	// Borrar los inputs a resetear de cada mando conectado
	ResetControllerInputs();

	// RESETEAR LISTAS DE MANDOS
	onConnectControllers.clear();
	onDisconnectControllers.clear();


	// Recoger todos los eventos de esta ejecucion y procesarlos uno a uno
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		SDL_Scancode scanCode = event.key.keysym.scancode;

		// Eventos para salir del bucle principal
		if (event.type == SDL_QUIT)
			return true;


		// Manejar todos los tipos de eventos

		// Almacenar eventos de teclado en el array "keyboardKeys"
		ManageKeyboardEvents(event);

		// Gestionar eventos del raton
		ManageMouseEvents(event);

		// Almacenar eventos de mando en el array "controllerButtons" (a parte de eventos Add/Remove del mando)
		ManageControllerEvents(event);
	}
	return false;
}

void InputManager::ManageKeyboardEvents(const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = _keyboardKeys[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisKey.isPressed) {
			thisKey.down = true;
			thisKey.isPressed = true;
			_keyboardInputs_ToReset.push_back(scanCode);
		}
	}

	else if (event.type == SDL_KEYUP) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = _keyboardKeys[scanCode];

		thisKey.isPressed = false;
		thisKey.up = true;
		_keyboardInputs_ToReset.push_back(scanCode);
	}
}

void InputManager::ManageControllerEvents(const SDL_Event& event) {

	if (event.type == SDL_CONTROLLERDEVICEADDED) {

		// Mando que ha generado el evento
		SDL_GameController* handler = SDL_GameControllerOpen(event.cdevice.which);
		SDL_Joystick* joystick = SDL_GameControllerGetJoystick(handler);
		SDL_JoystickID joystickID = SDL_JoystickInstanceID(joystick);
		ControllerId connectedDevice = joystickID;

		ControllerDeviceAdded(connectedDevice);
		std::cout << "Controller added" << "\n";
	}

	if (event.type == SDL_CONTROLLERDEVICEREMOVED) {

		// Mando que ha generado el evento
		SDL_GameController* handler = SDL_GameControllerFromInstanceID(event.cdevice.which);
		SDL_Joystick* joystick = SDL_GameControllerGetJoystick(handler);
		SDL_JoystickID joystickID = SDL_JoystickInstanceID(joystick);
		ControllerId disconnectedDevice = joystickID;

		// Cerrar mando de SDL
		SDL_GameControllerClose(handler);

		ControllerDeviceRemoved(disconnectedDevice);
		std::cout << "Controller removed" << "\n";
	}

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {

		int buttonCode = event.cbutton.button;
		ControllerId id = 0;
		KeyState& thisButton = connectedControllers[event.jaxis.which]._controllerButtons[buttonCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;

			connectedControllers[event.jaxis.which]._controllerInputs_ToReset.push_back(buttonCode);
		}
	}

	if (event.type == SDL_CONTROLLERBUTTONUP) {

		int buttonCode = event.cbutton.button;
		ControllerId id = 0;
		KeyState& thisButton = connectedControllers[event.cdevice.which]._controllerButtons[buttonCode];

		// Actualizar valores
		thisButton.isPressed = false;
		thisButton.up = true;

		connectedControllers[event.jaxis.which]._controllerInputs_ToReset.push_back(buttonCode);
	}

	if (event.type == SDL_CONTROLLERAXISMOTION) {

		Sint16 joystickValue = event.caxis.value;

		// Limitador maximo
		if (joystickValue > _JOYSTICKDEADZONE_MAX)
			joystickValue = _JOYSTICKDEADZONE_MAX;
		else if (joystickValue < -_JOYSTICKDEADZONE_MAX)
			joystickValue = -_JOYSTICKDEADZONE_MAX;




		int axis = event.caxis.axis;
		if (axis < 4) {
			// Si se inclina el joystick lo suficiente, guardar su valor
			if (joystickValue > _JOYSTICKDEADZONE_MIN
				|| joystickValue < -_JOYSTICKDEADZONE_MIN) {

				float absJoystickValue = fabsf(joystickValue);
				int sign = (int) (joystickValue / absJoystickValue);

				// Convertir el valor en un valor entre 0 y 1
				float normalizedValue = ((float) (absJoystickValue - _JOYSTICKDEADZONE_MIN)) / ((float) (_JOYSTICKDEADZONE_MAX - _JOYSTICKDEADZONE_MIN));

				normalizedValue *= sign;

				connectedControllers[event.jaxis.which]._joystickAxis[axis] = normalizedValue;
			}
			else
				connectedControllers[event.jaxis.which]._joystickAxis[axis] = 0;
		}

	}
	if (event.type == SDL_JOYAXISMOTION) {

		Sint16 triggerValue = event.jaxis.value;

		int axis = event.jaxis.axis;
		if (axis > 3) {
			axis -= 4;
			float auxValue = triggerValue + _TRIGGERSVALUE_MAX / 2.f;
			float finalValue = std::clamp(auxValue / _TRIGGERSVALUE_MAX, 0.0f, 1.0f);

			if (axis == 0 || axis == 1)
				connectedControllers[event.jaxis.which]._triggersValue[axis] = finalValue;
		}
	}

}

void InputManager::ManageMouseEvents(const SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION) {
		_mousePos.first = event.motion.x;
		_mousePos.second = event.motion.y;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int scanCode = event.button.button;
		KeyState& thisButton = _mouseButtons[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;
			_mouseInputs_ToReset.push_back(scanCode);
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		int scanCode = event.button.button;
		KeyState& thisButton = _mouseButtons[scanCode];

		thisButton.isPressed = false;
		thisButton.up = true;
		_mouseInputs_ToReset.push_back(scanCode);
	}
}

void InputManager::ControllerDeviceAdded(const ControllerId& controllerAdded) {

	onConnectControllers.push_back(controllerAdded);

	connectedControllers.insert({ controllerAdded, LMController() });
}

void InputManager::ControllerDeviceRemoved(const ControllerId& controllerRemoved) {

	onDisconnectControllers.push_back(controllerRemoved);

	connectedControllers.erase(controllerRemoved);
}


// RESET

void InputManager::ResetKeyboardInputs() {
	for (int i = 0; i < _keyboardInputs_ToReset.size(); i++) {
		// Saber el codigo de la tecla almacenado en el vector "keysToReset"
		int scanCode = _keyboardInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisKey = _keyboardKeys[scanCode];
		thisKey.up = false;
		thisKey.down = false;
	}

	// Limpiar las teclas ya reseteadas
	_keyboardInputs_ToReset.clear();
}

void InputManager::ResetMouseInputs() {
	for (int i = 0; i < _mouseInputs_ToReset.size(); i++) {
		// Saber el codigo del boton del mando
		int buttonCode = _mouseInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisButton = _mouseButtons[buttonCode];
		thisButton.up = false;
		thisButton.down = false;
	}

	// Limpiar las teclas ya reseteadas
	_mouseInputs_ToReset.clear();
}

void InputManager::ResetControllerInputs() {

	for (auto& pair : connectedControllers) {

		LMController& thisController = pair.second;

		for (int i = 0; i < thisController._controllerInputs_ToReset.size(); i++) {
			// Saber el codigo del boton del mando
			int buttonCode = thisController._controllerInputs_ToReset[i];
			// Crear una referencia a la tecla y resetear sus variables a false
			KeyState& thisButton = thisController._controllerButtons[buttonCode];

			thisButton.up = false;
			thisButton.down = false;
		}

		// Limpiar las teclas ya reseteadas
		thisController._controllerInputs_ToReset.clear();
	}
}



// FUNCIONALIDADES DE MANDO EXTRA

// Luz LED
void InputManager::SetControllerLedColor(ControllerId controllerId, int r, int g, int b) {

	SDL_GameController* gameController = SDL_GameControllerFromInstanceID(controllerId);

	if (gameController != nullptr && SDL_GameControllerHasLED(gameController))
		SDL_GameControllerSetLED(gameController, r, g, b);
	else
		std::cout << "[ERROR] Could not change LED color of controller, it has not LED support";
}

// Vibracion
void InputManager::RumbleController(ControllerId controllerId, const float& intensity, const float& durationInSec) {

	if (intensity > 1 || intensity < 0) {
		std::cout << "[ERROR] Could not Rumble controller: Rumble intensity out of range";
		return;
	}

	SDL_GameController* gameController = SDL_GameControllerFromInstanceID(controllerId);

	//if (_currentController != nullptr) {

	if (gameController != nullptr && SDL_GameControllerHasRumble(gameController)) {

		Uint16 rumbleIntensity = (Uint16) (intensity * UINT16_MAX);
		SDL_GameControllerRumble(gameController, rumbleIntensity, rumbleIntensity, (Uint32) (durationInSec * 1000));
	}
	else
		std::cout << "[ERROR] Could not Rumble controller, it has not Rumble support";
}