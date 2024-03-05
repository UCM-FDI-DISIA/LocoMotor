#pragma once
#ifndef AUDIOMANAGER
#define AUDIOMANAGER

#include <unordered_map>
#include <string>

namespace FMOD {
	class System;
	class ChannelGroup;
	class Channel;
	class Sound;
}

namespace LocoMotor {

	class AudioListener;

	namespace Audio {

		class AudioManager {

		public:

		#pragma region Singletone
			static bool Init();
			static bool Init(int numChannels);

			static AudioManager* GetInstance();

			static void Release();
		#pragma endregion

			/// @brief Updates the Fmod API to change channel output depending on positions and velocity
			/// @param deltaTime Bruh
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short update();

			/// @brief Adds a sound to the system, for later use
			/// @param Name that will be used to refer to this sound upon being created
			/// @param File to get the sound from
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short addSound(const char* fileName, bool ui = false);

			/// @brief Plays an already added sound
			/// @param Name of the sound to play
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short playSound(const char* id);

			/// @brief Plays an already added sound, but gives access to the channel its being played
			/// @param Name of the sound to play
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short playSoundwChannel(const char* id, FMOD::Channel** channel);

			/// @brief Adds a listener to Fmod
			/// @param index The index of the newly created listener
			/// @return The iterator to the position in the listeners list where it is stored;
			std::list<AudioListener*>::iterator addListener(AudioListener* curr, size_t& index);

			/// @brief Removes the listener
			/// @param The listener to remove
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short removeListener(std::list<AudioListener*>::iterator it, size_t indexToRemove);

			/// @brief Gets the FMOD::System object from this manager
			/// @return The System in question
			FMOD::System* getSystem() const;

			/// @brief Gets the sound using an id
			FMOD::Sound* getSound(const char* id);

			/// @brief Get the fmod error corresponding to the param passed
			/// @param errorCode Param to get the Fmod error corresponding to it
			/// @return The Fmod error message
			const char* getError(const unsigned short& errorCode);

		private:

			static AudioManager* _instance;

			FMOD::System* _sys = nullptr;
			FMOD::ChannelGroup* _main = nullptr;

			std::unordered_map<std::string, FMOD::Sound*> _soundLib;

			std::list<::LocoMotor::AudioListener*> _listeners;

			/// @brief Constructor is set to private, use the 'GetInstance' method for access to the instance of this object
			AudioManager();

			~AudioManager();

			bool init(int numChannels);

		};
	}
}

#endif // !AUDIOMANAGER
