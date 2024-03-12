#include <cstdint>
#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

//#include "SDL.h"

//namespace SDL {
//
//}

union SDL_Event;
typedef struct _SDL_GameController SDL_GameController;

namespace LocoMotor {

	namespace Input {

		class InputManager {
		public:
			enum Axis {
				Horizontal, Vertical
			};

			/// @brief Initializes the InputManager singleton
			/// @return Whether the initialize went well or not.
			static bool Init();
			/// @brief Returns the instance of the InputManager singleton
			static InputManager* GetInstance();
			/// @brief Deletes the instance of the InputManager singleton
			static void Release();




		// KEYBOARD
		/// @brief Returns true only in the frame that key is pressed
			bool GetKeyDown(const LMScanCode& scanCode);
			/// @brief Returns true when key is pressed
			bool GetKey(const LMScanCode& scanCode);
			/// @brief Returns true when key is stop pressed
			bool GetKeyUp(const LMScanCode& scanCode);

			// MOUSE
			/// @brief Returns true only in the frame that mouse is pressed
			bool GetMouseButtonDown(const int& buttonCode);
			/// @brief Returns true when mouse is pressed
			bool GetMouseButton(const int& buttonCode);
			/// @brief Returns true when mouse is stop pressed
			bool GetMouseButtonUp(const int& buttonCode);
			/// @brief Returns the position of the mouse in screen
			std::pair<int, int> GetMousePos();

			// Controller

			/// @brief Returns true only in the frame that controller button is pressed
			bool GetButtonDown(const int& buttonCode);
			/// @brief Returns true when controller button is pressed
			bool GetButton(const int& buttonCode);
			/// @brief Returns true when controller button is stop pressed
			bool GetButtonUp(const int& buttonCode);
			/// @brief Returns the inclination value of the joystick
			/// @param joystickIndex 0 -> left joystick | 1 ->right joystick
			/// @param axis Horizontal o Vertical
			float GetJoystickValue(const int& joystickIndex, const Axis& axis);
			/// @brief Returns the inclination value of the joystick
			/// @param triggerIndex 0 -> left trigger | 1 ->right trigger
			float GetTriggerValue(const int& triggerIndex);


			// EVENT MANAGER

			/// @brief Returns true when controller is connected
			bool ControllerConnected();

			/// @brief Register all input related events and save it in the respective value
			bool RegisterEvents();

			/// @brief Manages keyboard events
			void ManageKeyboardEvents(const SDL_Event& event);
			/// @brief Manages controller events
			void ManageControllerEvents(const SDL_Event& event);
			/// @brief Manages mouse events
			void ManageMouseEvents(const SDL_Event& event);

			/// @brief Returns true if controller is ready to use
			bool ControllerDeviceAdded(const int32_t& controller);
			/// @brief Removes the controller
			void ControllerDeviceRemoved(const int32_t& controller);

			// Las teclas que hayan llamado a los eventos SDL_KEYDOWN y SDL_KEYUP en el frame anterior,
			// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
			// la funcion de este metodo es resetear esas variables y ponerlas a False

			/// @brief Resets the last frame keyboard inputs boolean
			void ResetKeyboardInputs();
			// Los botones que hayan llamado a los eventos SDL_MOUSEBUTTONDOWN y SDL_MOUSEBUTTONUP en el frame anterior,
			// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
			// la funcion de este metodo es resetear esas variables y ponerlas a False

			/// @brief Resets the last frame mouse inputs boolean
			void ResetMouseInputs();
			// Los botones que hayan llamado a los eventos SDL_CONTROLLERBUTTONDOWN y SDL_CONTROLLERBUTTONUP en el frame anterior,
			// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
			// la funcion de este metodo es resetear esas variables y ponerlas a False

			/// @brief Resets the last frame controller inputs boolean
			void ResetControllerInputs();


			// EXTRA CONTROLLER UTILITY

			/// @brief Sets the controller led in RGB
			void SetControllerLedColor(int r, int g, int b);

			/// @brief Sets the controller rumble with a intensity and a duration in seconds
			void RumbleController(const float& intensity, const float& durationInSec);

			// Gyroscope

			/// @brief Comunicate to the manager to active the gyroscope when controller is connected 
			void ActivateGyroscopeWhenConnected();
			/// @brief Check is the controller supports gyroscope and activate it.
			bool EnableControllerGyroscope();
			/// @brief Desactivate the gyroscope
			bool DisableControllerGyroscope();
			/// @brief Returns the normalized angle of the gyroscope
			/// @param axis 
			/// @return 1 : 90 grados // -1 : -90 grados
			float GetGyroscopeAngle(const Axis& axis = Horizontal);
			/// @brief Gets the angular speed of the gyroscope
			/// @param axis 
			float GetGyroscopeAngularSpeed(const Axis& axis = Horizontal);
			/// @brief Resets the gyroscope
			void ResetGyroscope();


			

		protected:

			/// @brief Creates a new InputManager.
			InputManager();
			~InputManager();
		};
	}
}

#endif
