#pragma once
#ifndef AUDIOSOURCE
#define AUDIOSOURCE

#include <unordered_map>

struct FMOD_VECTOR;
namespace FMOD {
	class Channel;
}
namespace LocoMotor {

	namespace Audio {
		class AudioManager;
	}

	struct ChannelData {
		FMOD::Channel* channel;
		float ogFrec;
	};

	class AudioSource {
	public:

		AudioSource();
		~AudioSource();

		/// @brief Adds a sound to the manager's system, for later use
		/// @param Name that will be used to refer to this sound upon being created
		/// @param File to get the sound from
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short addSound(const char* fileName);

		/// @brief Plays a sound from this source
		/// @param fileName The sound to play
		/// @param loops Amount of loops the sound will do (-1 for infinite)
		/// @param loopBegin When should the sound begin its loop section (in miliseconds)
		/// @param loopEnd When should the sound end its loop section (in miliseconds)
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short playSound(const char* fileName, int loops = 0, unsigned int loopBegin = 0, unsigned int loopEnd = 0xffffffff);

		/// @brief Plays a sound independently of this source, meaning i won�t update its position, with a randomized pitch
		/// @param fileName The sound to play
		/// @param position Position where the sound will come from
		/// @param volume Volume modifier of the sound
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short playOneShot(const char* fileName, const FMOD_VECTOR& position, const float volume = 1.f);

		/// @brief Plays a sound independently of this source, meaning i won�t update its position
		/// @param fileName The sound to play
		/// @param position Position where the sound will come from
		/// @param volume Volume modifier of the sound
		/// @param pitch Pitch modifier of the sound
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short playOneShot(const char* fileName, const FMOD_VECTOR& position, const float volume, const float pitch);

		/// @brief Pauses a specific sound playing in this source
		/// @param fileName The sound to play
		/// @param pause should the sound be paused? or unpaused?
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short pauseSound(const char* fileName, bool pause = true);

		/// @brief Pauses all sounds playing in this source
		/// @param pause should the sound be paused? or unpaused)
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short pause(bool pause = true);

		/// @brief Stop a specific sound playing in this source
		/// @param fileName The sound to stop
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short stopSound(const char* fileName);

		/// @brief Stop all sounds playing in this source
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short stop();

		/// @brief Set the volume of a specific sound playing in this source
		/// @param fileName The sound to set the volume to
		/// @param volume 0.f = mute, 1.f = max volume
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short setSoundVolume(const char* fileName, const float volume);

		/// @brief Set the volume of all sounds that are playing and will play from this source
		/// @param volume 0.f = mute, 1.f = max volume
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short setVolume(const float volume);

		/// @brief Vary the frequency of a specific sound that is already playing
		/// @param id The id of the sound to modify
		/// @param freqMult The value that will be multiplied to the original frequency
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short setSoundFreq(const char* fileName, const float freqMult);

		/// @brief Vary the frequency of a specific sound that is already playing
		/// @param id The id of the sound to modify
		/// @param freqMult The value that will be multiplied to the original frequency
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short setFrequency(const float freqMult);

		/// @brief Set the source to play sounds in world space
		void setMode3D();

		/// @brief Set the source to play sounds with no regard of its position
		void setMode2D();

	protected:

		void init()/* override*/;

	private:

		Audio::AudioManager* _man;

		FMOD_VECTOR* _posRemember;

		std::unordered_map<const char*, ChannelData> _chMap;

		float _volumeMult;

		int _mode;

		/// @brief Set the position and velocity of this source. It will be applied to all sounds that are currently playing
		/// @param newPos The new position of the source
		/// @param newVel The new velocity of the source
		void setPositionAndVelocity(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel);

		/// @brief Set the position of this source and automatically update its velocity. It will be applied to all sounds that are currently playing
		/// @param newPos The new position of the source
		/// @param delta The delta time used to calculate the velocity
		void setPositionAndVelocity(const FMOD_VECTOR& newPos, float delta);
	};
}


#endif // !AUDIOSOURCE

