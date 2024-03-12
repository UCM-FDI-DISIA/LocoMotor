#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

//#include "SDL.h"

//namespace SDL {
//
//}


namespace LocoMotor {

	namespace Input {

		class InputManager {
		public:

			/// @brief Initializes the InputManager singleton
			/// @return Whether the initialize went well or not.
			static bool Init();
			/// @brief Returns the instance of the InputManager singleton
			static InputManager* GetInstance();
			/// @brief Deletes the instance of the InputManager singleton
			static void Release();
			

		protected:

			/// @brief Creates a new InputManager.
			InputManager();
			~InputManager();
		};
	}
}

#endif
