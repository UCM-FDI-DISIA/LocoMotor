#include "InputManager.h"
#include "SDL_Scancode.h"
#include "SDL_keyboard.h"
#include <SDL_events.h>
#include <iostream>
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
	//return _controllerButtons[buttonCode].down;
}

bool InputManager::GetButton(const int& buttonCode) {
	return _controllerButtons[buttonCode].isPressed;
}

bool InputManager::GetButtonUp(const int& buttonCode) {
	return _controllerButtons[buttonCode].up;
}

	// JOYSTICKS
float InputManager::GetJoystickValue(const int& joystickIndex, const Axis& axis) {

	if (joystickIndex == 0) {

		if (axis == Horizontal)
			return _joystickAxis[0];
		else if (axis == Vertical)
			return _joystickAxis[1];
	}
	else if (joystickIndex == 1) {

		if (axis == Horizontal)
			return _joystickAxis[2];
		else if (axis == Vertical)
			return _joystickAxis[3];
	}
	return 0.f;
}

	// TRIGGER
float InputManager::GetTriggerValue(const int& triggerIndex) {
	if (triggerIndex == 0 || triggerIndex == 1)return _triggersValue[triggerIndex];
	return 0.0f;
}


// EVENT MANAGMENT
bool InputManager::ControllerConnected() {
	return _currentController != nullptr;
}

bool InputManager::RegisterEvents() {

	// RESETEAR TECLAS Y BOTONES

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (_keyboardInputs_ToReset.size() != 0)
		ResetKeyboardInputs();

	if (_mouseInputs_ToReset.size() != 0)
		ResetMouseInputs();

	if (_controllerInputs_ToReset.size() != 0)
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

		// Almacenar eventos de mando en el array "controllerButtons" (a parte de eventos Add/Remove del mando)
		ManageControllerEvents(event);

		// Gestionar eventos del raton
		ManageMouseEvents(event);

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

		// Mando conectado que ha generado el evento
		Sint32 connectedDevice = event.cdevice.which;

		if (ControllerDeviceAdded(connectedDevice))
			std::cout << "Controller added" << "\n";
		else
			std::cout << "Controller could not be added: A controller is already in use" << "\n";
	}

	if (event.type == SDL_CONTROLLERDEVICEREMOVED) {

		// Mando conectado que ha generado el evento
		Sint32 connectedDevice = event.cdevice.which;

		ControllerDeviceRemoved(connectedDevice);
		std::cout << "Controller removed" << "\n";
	}

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {

		int buttonCode = event.cbutton.button;
		//KeyState& thisButton = _controllerButtons[buttonCode];
		ControllerId id = 0;
		KeyState& thisButton = connectedControllers[event.cdevice.which]._controllerButtons[buttonCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;
			_controllerInputs_ToReset.push_back(buttonCode);

			connectedControllers[event.cdevice.which]._controllerInputs_ToReset.push_back(buttonCode);
		}
	}

	if (event.type == SDL_CONTROLLERBUTTONUP) {

		int buttonCode = event.cbutton.button;
		KeyState& thisButton = _controllerButtons[buttonCode];

		thisButton.isPressed = false;
		thisButton.up = true;
		_controllerInputs_ToReset.push_back(buttonCode);
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

				_joystickAxis[axis] = normalizedValue;
				std::cout << normalizedValue << "\n";
			}

			else
				_joystickAxis[axis] = 0;
		}

	}
	if (event.type == SDL_JOYAXISMOTION) {

		Sint16 triggerValue = event.jaxis.value;



		int axis = event.jaxis.axis;
		if (axis > 3) {
			axis -= 4;
			float auxValue = triggerValue + _TRIGGERSVALUE_MAX / 2.f;
			if (axis == 0 || axis == 1)_triggersValue[axis] = auxValue / _TRIGGERSVALUE_MAX;
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

bool InputManager::ControllerDeviceAdded(const int32_t& controllerAdded) {

	// Si ya hay un mando conectado, ignorar este
	if (_currentController != nullptr)
		return false;

	_currentController = SDL_GameControllerOpen(controllerAdded);

	///////////////////////

	onConnectControllers.push_back(controllerAdded);

	connectedControllers.insert({ controllerAdded, LMController(SDL_GameControllerOpen(controllerAdded)) });

	return true;
}

void InputManager::ControllerDeviceRemoved(const int32_t& controllerRemoved) {

	_currentController = nullptr;

	// Eliminar inputs guardados actualmente
	for (KeyState controllerButton : _controllerButtons) {
		controllerButton.down = false;
		controllerButton.isPressed = false;
		controllerButton.up = false;
	}
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


	////////////////////////////////////////////
	for (int i = 0; i < _controllerInputs_ToReset.size(); i++) {
		// Saber el codigo del boton del mando
		int buttonCode = _controllerInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisButton = _controllerButtons[buttonCode];
		thisButton.up = false;
		thisButton.down = false;
	}

	// Limpiar las teclas ya reseteadas
	_controllerInputs_ToReset.clear();
}



// FUNCIONALIDADES DE MANDO EXTRA

// Luz LED
void InputManager::SetControllerLedColor(int r, int g, int b) {

	if (_currentController != nullptr) {

		if (SDL_GameControllerHasLED(_currentController))
			SDL_GameControllerSetLED(_currentController, r, g, b);
	}

}

// Vibracion
void InputManager::RumbleController(const float& intensity, const float& durationInSec) {

	if (intensity > 1 || intensity < 0) {
		std::cout << "[ERROR] Could not Rumble controller: Rumble intensity out of range";
		return;
	}

	if (_currentController != nullptr) {

		if (SDL_GameControllerHasRumble(_currentController)) {
			Uint16 rumbleIntensity = (Uint16) (intensity * UINT16_MAX);
			SDL_GameControllerRumble(_currentController, rumbleIntensity, rumbleIntensity, (Uint32) (durationInSec * 1000));
		}
		else
			std::cout << "[ERROR] Could not Rumble controller: currentController has not Rumble support";
	}
	else std::cout << "[ERROR] Could not Rumble controller: currentController not assigned";
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//#include "InputManager.h"
//#include "SDL_Scancode.h"
//#include "SDL_keyboard.h"
//#include <SDL_events.h>
//#include <iostream>
//#include <SDL_gamecontroller.h>
//#include "LMInputs.h"
//
//#include <cassert>
//
//using namespace LocoMotor;
//using namespace Input;
//
//InputManager* InputManager::_instance = nullptr;
//
//InputManager::InputManager() {
//	_joystickAxis[0] = 0.f;
//	_joystickAxis[1] = 0.f;
//	_joystickAxis[2] = 0.f;
//	_joystickAxis[3] = 0.f;
//	_triggersValue[0] = 0.f;
//	_triggersValue[1] = 0.f;
//	_mousePos.first = 0;
//	_mousePos.second = 0;
//}
//
//bool InputManager::Init() {
//	assert(_instance == nullptr);
//	_instance = new InputManager();
//
//	if (!_instance->init()) {
//		delete _instance;
//		_instance = nullptr;
//		return false;
//	}
//
//	return true;
//}
//
//bool InputManager::init() {
//
//	return true;
//}
//
//InputManager* InputManager::GetInstance() {
//	return _instance;
//}
//
//void InputManager::Release() {
//
//}
//
//// KEYBOARD
//bool InputManager::GetKeyDown(const LMScanCode& scanCode) {
//	return _keyboardKeys[scanCode].down;
//}
//
//bool InputManager::GetKey(const LMScanCode& scanCode) {
//	return _keyboardKeys[scanCode].isPressed;
//}
//
//bool InputManager::GetKeyUp(const LMScanCode& scanCode) {
//	return _keyboardKeys[scanCode].up;
//}
//
//// MOUSE
//bool InputManager::GetMouseButtonDown(const int& buttonCode) {
//	return _mouseButtons[buttonCode].down;
//}
//
//bool InputManager::GetMouseButton(const int& buttonCode) {
//	return _mouseButtons[buttonCode].isPressed;
//}
//
//bool InputManager::GetMouseButtonUp(const int& buttonCode) {
//	return _mouseButtons[buttonCode].up;
//}
//
//std::pair<int, int> InputManager::GetMousePos() {
//	return _mousePos;
//}
//
//// CONTROLLER
//
//	// BUTTONS
//bool InputManager::GetButtonDown(const int& buttonCode) {
//	return _controllerButtons[buttonCode].down;
//}
//
//bool InputManager::GetButton(const int& buttonCode) {
//	return _controllerButtons[buttonCode].isPressed;
//}
//
//bool InputManager::GetButtonUp(const int& buttonCode) {
//	return _controllerButtons[buttonCode].up;
//}
//
//	// JOYSTICKS
//float InputManager::GetJoystickValue(const int& joystickIndex, const Axis& axis) {
//
//	if (joystickIndex == 0) {
//
//		if (axis == Horizontal)
//			return _joystickAxis[0];
//		else if (axis == Vertical)
//			return _joystickAxis[1];
//	}
//	else if (joystickIndex == 1) {
//
//		if (axis == Horizontal)
//			return _joystickAxis[2];
//		else if (axis == Vertical)
//			return _joystickAxis[3];
//	}
//	return 0.f;
//}
//
//	// TRIGGER
//float InputManager::GetTriggerValue(const int& triggerIndex) {
//	if (triggerIndex == 0 || triggerIndex == 1)return _triggersValue[triggerIndex];
//	return 0.0f;
//}
//
//
//// EVENT MANAGMENT
//bool InputManager::ControllerConnected() {
//	return _currentController != nullptr;
//}
//
//bool InputManager::RegisterEvents() {
//
//	// RESETEAR TECLAS Y BOTONES
//
//	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
//	if (_keyboardInputs_ToReset.size() != 0)
//		ResetKeyboardInputs();
//
//	if (_mouseInputs_ToReset.size() != 0)
//		ResetMouseInputs();
//
//	if (_controllerInputs_ToReset.size() != 0)
//		ResetControllerInputs();
//
//	// Recoger todos los eventos de esta ejecucion y procesarlos uno a uno
//	SDL_Event event;
//	while (SDL_PollEvent(&event)) {
//
//		SDL_Scancode scanCode = event.key.keysym.scancode;
//
//		// Eventos para salir del bucle principal
//		if (event.type == SDL_QUIT || scanCode == SDL_SCANCODE_ESCAPE)
//			return true;
//
//
//		// Manejar todos los tipos de eventos
//
//		// Almacenar eventos de teclado en el array "keyboardKeys"
//		ManageKeyboardEvents(event);
//
//		// Almacenar eventos de mando en el array "controllerButtons" (a parte de eventos Add/Remove del mando)
//		ManageControllerEvents(event);
//
//		// Gestionar eventos del raton
//		ManageMouseEvents(event);
//
//	}
//	return false;
//}
//
//void InputManager::ManageKeyboardEvents(const SDL_Event& event) {
//
//	if (event.type == SDL_KEYDOWN) {
//		SDL_Scancode scanCode = event.key.keysym.scancode;
//		KeyState& thisKey = _keyboardKeys[scanCode];
//
//		// Comprobar si la tecla no esta siendo presionada actualmente
//		if (!thisKey.isPressed) {
//			thisKey.down = true;
//			thisKey.isPressed = true;
//			_keyboardInputs_ToReset.push_back(scanCode);
//		}
//	}
//
//	else if (event.type == SDL_KEYUP) {
//		SDL_Scancode scanCode = event.key.keysym.scancode;
//		KeyState& thisKey = _keyboardKeys[scanCode];
//
//		thisKey.isPressed = false;
//		thisKey.up = true;
//		_keyboardInputs_ToReset.push_back(scanCode);
//	}
//}
//
//void InputManager::ManageControllerEvents(const SDL_Event& event) {
//
//	if (event.type == SDL_CONTROLLERDEVICEADDED) {
//
//		// Mando conectado que ha generado el evento
//		Sint32 connectedDevice = event.cdevice.which;
//
//		if (ControllerDeviceAdded(connectedDevice))
//			std::cout << "Controller added" << "\n";
//		else
//			std::cout << "Controller could not be added: A controller is already in use" << "\n";
//	}
//
//	if (event.type == SDL_CONTROLLERDEVICEREMOVED) {
//
//		// Mando conectado que ha generado el evento
//		Sint32 connectedDevice = event.cdevice.which;
//
//		ControllerDeviceRemoved(connectedDevice);
//		std::cout << "Controller removed" << "\n";
//	}
//
//	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
//
//		int buttonCode = event.cbutton.button;
//		KeyState& thisButton = _controllerButtons[buttonCode];
//
//		// Comprobar si la tecla no esta siendo presionada actualmente
//		if (!thisButton.isPressed) {
//			thisButton.down = true;
//			thisButton.isPressed = true;
//			_controllerInputs_ToReset.push_back(buttonCode);
//		}
//	}
//
//	if (event.type == SDL_CONTROLLERBUTTONUP) {
//
//		int buttonCode = event.cbutton.button;
//		KeyState& thisButton = _controllerButtons[buttonCode];
//
//		thisButton.isPressed = false;
//		thisButton.up = true;
//		_controllerInputs_ToReset.push_back(buttonCode);
//	}
//
//	if (event.type == SDL_CONTROLLERAXISMOTION) {
//
//		Sint16 joystickValue = event.caxis.value;
//
//		// Limitador maximo
//		if (joystickValue > _JOYSTICKDEADZONE_MAX)
//			joystickValue = _JOYSTICKDEADZONE_MAX;
//		else if (joystickValue < -_JOYSTICKDEADZONE_MAX)
//			joystickValue = -_JOYSTICKDEADZONE_MAX;
//
//
//
//
//		int axis = event.caxis.axis;
//		if (axis < 4) {
//			// Si se inclina el joystick lo suficiente, guardar su valor
//			if (joystickValue > _JOYSTICKDEADZONE_MIN
//				|| joystickValue < -_JOYSTICKDEADZONE_MIN) {
//
//				float absJoystickValue = fabsf(joystickValue);
//				int sign = (int) (joystickValue / absJoystickValue);
//
//				// Convertir el valor en un valor entre 0 y 1
//				float normalizedValue = ((float) (absJoystickValue - _JOYSTICKDEADZONE_MIN)) / ((float) (_JOYSTICKDEADZONE_MAX - _JOYSTICKDEADZONE_MIN));
//
//				normalizedValue *= sign;
//
//				_joystickAxis[axis] = normalizedValue;
//				std::cout << normalizedValue << "\n";
//			}
//
//			else
//				_joystickAxis[axis] = 0;
//		}
//
//	}
//	if (event.type == SDL_JOYAXISMOTION) {
//
//		Sint16 triggerValue = event.jaxis.value;
//
//
//
//		int axis = event.jaxis.axis;
//		if (axis > 3) {
//			axis -= 4;
//			float auxValue = triggerValue + _TRIGGERSVALUE_MAX / 2.f;
//			if (axis == 0 || axis == 1)_triggersValue[axis] = auxValue / _TRIGGERSVALUE_MAX;
//		}
//
//
//	}
//
//}
//
//void InputManager::ManageMouseEvents(const SDL_Event& event) {
//	if (event.type == SDL_MOUSEMOTION) {
//		_mousePos.first = event.motion.x;
//		_mousePos.second = event.motion.y;
//	}
//	if (event.type == SDL_MOUSEBUTTONDOWN) {
//		int scanCode = event.button.button;
//		KeyState& thisButton = _mouseButtons[scanCode];
//
//		// Comprobar si la tecla no esta siendo presionada actualmente
//		if (!thisButton.isPressed) {
//			thisButton.down = true;
//			thisButton.isPressed = true;
//			_mouseInputs_ToReset.push_back(scanCode);
//		}
//	}
//	if (event.type == SDL_MOUSEBUTTONUP) {
//		int scanCode = event.button.button;
//		KeyState& thisButton = _mouseButtons[scanCode];
//
//		thisButton.isPressed = false;
//		thisButton.up = true;
//		_mouseInputs_ToReset.push_back(scanCode);
//	}
//}
//
//bool InputManager::ControllerDeviceAdded(const int32_t& controllerAdded) {
//
//	// Si ya hay un mando conectado, ignorar este
//	if (_currentController != nullptr)
//		return false;
//
//	_currentController = SDL_GameControllerOpen(controllerAdded);
//
//	return true;
//}
//
//void InputManager::ControllerDeviceRemoved(const int32_t& controllerRemoved) {
//
//	_currentController = nullptr;
//
//	// Eliminar inputs guardados actualmente
//	for (KeyState controllerButton : _controllerButtons) {
//		controllerButton.down = false;
//		controllerButton.isPressed = false;
//		controllerButton.up = false;
//	}
//}
//
//
//// RESET
//
//void InputManager::ResetKeyboardInputs() {
//	for (int i = 0; i < _keyboardInputs_ToReset.size(); i++) {
//		// Saber el codigo de la tecla almacenado en el vector "keysToReset"
//		int scanCode = _keyboardInputs_ToReset[i];
//		// Crear una referencia a la tecla y resetear sus variables a false
//		KeyState& thisKey = _keyboardKeys[scanCode];
//		thisKey.up = false;
//		thisKey.down = false;
//	}
//
//	// Limpiar las teclas ya reseteadas
//	_keyboardInputs_ToReset.clear();
//}
//
//void InputManager::ResetMouseInputs() {
//	for (int i = 0; i < _mouseInputs_ToReset.size(); i++) {
//		// Saber el codigo del boton del mando
//		int buttonCode = _mouseInputs_ToReset[i];
//		// Crear una referencia a la tecla y resetear sus variables a false
//		KeyState& thisButton = _mouseButtons[buttonCode];
//		thisButton.up = false;
//		thisButton.down = false;
//	}
//
//	// Limpiar las teclas ya reseteadas
//	_mouseInputs_ToReset.clear();
//}
//
//void InputManager::ResetControllerInputs() {
//
//	for (int i = 0; i < _controllerInputs_ToReset.size(); i++) {
//		// Saber el codigo del boton del mando
//		int buttonCode = _controllerInputs_ToReset[i];
//		// Crear una referencia a la tecla y resetear sus variables a false
//		KeyState& thisButton = _controllerButtons[buttonCode];
//		thisButton.up = false;
//		thisButton.down = false;
//	}
//
//	// Limpiar las teclas ya reseteadas
//	_controllerInputs_ToReset.clear();
//}
//
//
//
//// FUNCIONALIDADES DE MANDO EXTRA
//
//// Luz LED
//void InputManager::SetControllerLedColor(int r, int g, int b) {
//
//	if (_currentController != nullptr) {
//
//		if (SDL_GameControllerHasLED(_currentController))
//			SDL_GameControllerSetLED(_currentController, r, g, b);
//	}
//
//}
//
//// Vibracion
//void InputManager::RumbleController(const float& intensity, const float& durationInSec) {
//
//	if (intensity > 1 || intensity < 0) {
//		std::cout << "[ERROR] Could not Rumble controller: Rumble intensity out of range";
//		return;
//	}
//
//	if (_currentController != nullptr) {
//
//		if (SDL_GameControllerHasRumble(_currentController)) {
//			Uint16 rumbleIntensity = (Uint16) (intensity * UINT16_MAX);
//			SDL_GameControllerRumble(_currentController, rumbleIntensity, rumbleIntensity, (Uint32) (durationInSec * 1000));
//		}
//		else
//			std::cout << "[ERROR] Could not Rumble controller: currentController has not Rumble support";
//	}
//	else std::cout << "[ERROR] Could not Rumble controller: currentController not assigned";
//}