#pragma once
#ifndef AUDIOLISTENER
#define AUDIOLISTENER

#include <list>

struct FMOD_VECTOR;

namespace FMOD {
	class System;
}

namespace LocoMotor {

	namespace Audio {

		class AudioManager;

		class AudioListener /*: public Component*/ {

			friend class AudioManager;

		private:

			size_t _fIndex;

			AudioManager* _man;

			std::list<AudioListener*>::iterator _thisIT;

			AudioListener();
			~AudioListener();

			/// @brief Change the index this listener is associated with in the manager
			/// @param index The new index of the listener
			/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
			unsigned short changeIndex(int index);

			/// @brief Set the world attributes of the listener
			/// @param newPos The new position of the listener (pass NULL or 0 to not update position)
			/// @param newVel The new velocity of the listener (pass NULL or 0 to not update velocity)
			/// @param forward The direction the listener is facing MUST BE NORMALIZED (pass NULL or 0 to not update)
			/// @param up The new upwards direction of the listener MUST ALSO BE NORMALIZED (pass NULL or 0 to not update)
			/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
			unsigned short setTransform(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel, const FMOD_VECTOR& forward, const FMOD_VECTOR& up);
		};
	}
}

#endif