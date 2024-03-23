#pragma once
#ifndef AUDIOSOURCE
#define AUDIOSOURCE

#include <unordered_map>
#include "Component.h"
#include "LMVector.h"

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

	class AudioSource : public Component {
	public:

		AudioSource();
		~AudioSource();

		/// @brief Adds a sound to the manager's system, for later use
		/// @param Name that will be used to refer to this sound upon being created
		/// @param File to get the sound from
		void addSound(const char* fileName);

		/// @brief Plays a sound from this source
		/// @param fileName The sound to play
		/// @param loops Amount of loops the sound will do (-1 for infinite)
		/// @param loopBegin When should the sound begin its loop section (in miliseconds)
		/// @param loopEnd When should the sound end its loop section (in miliseconds)
		void playSound(const char* fileName, int loops = 0, unsigned int loopBegin = 0, unsigned int loopEnd = 0xffffffff);

		/// @brief Plays a sound independently of this source, meaning i won´t update its position, with a randomized pitch
		/// @param fileName The sound to play
		/// @param position Position where the sound will come from
		/// @param volume Volume modifier of the sound
		void playOneShot(const char* fileName, const LMVector3& position, const float volume = 1.f);

		/// @brief Plays a sound independently of this source, meaning it won´t update its position
		/// @param fileName The sound to play
		/// @param position Position where the sound will come from
		/// @param volume Volume modifier of the sound
		/// @param pitch Pitch modifier of the sound
		void playOneShot(const char* fileName, const LMVector3& position, const float volume, const float pitch);

		/// @brief Pauses a specific sound playing in this source
		/// @param fileName The sound to play
		/// @param pause should the sound be paused? or unpaused?
		void pauseSound(const char* fileName, bool pause = true);

		/// @brief Pauses all sounds playing in this source
		/// @param pause should the sound be paused? or unpaused)
		void pause(bool pause = true);

		/// @brief Stop a specific sound playing in this source
		/// @param fileName The sound to stop
		void stopSound(const char* fileName);

		/// @brief Stop all sounds playing in this source
		void stop();

		/// @brief Set the volume of a specific sound playing in this source
		/// @param fileName The sound to set the volume to
		/// @param volume 0.f = mute, 1.f = max volume
		void setSoundVolume(const char* fileName, const float volume);

		/// @brief Set the volume of all sounds that are playing and will play from this source
		/// @param volume 0.f = mute, 1.f = max volume
		void setVolume(const float volume);

		/// @brief Vary the frequency of a specific sound that is already playing
		/// @param id The id of the sound to modify
		/// @param freqMult The value that will be multiplied to the original frequency
		void setSoundFreq(const char* fileName, const float freqMult);

		/// @brief Vary the frequency of a specific sound that is already playing
		/// @param id The id of the sound to modify
		/// @param freqMult The value that will be multiplied to the original frequency
		void setFrequency(const float freqMult);

		/// @brief Set the source to play sounds in world space
		void setMode3D();

		/// @brief Set the source to play sounds with no regard of its position
		void setMode2D();

	protected:

		void setParameters(std::vector<std::pair<std::string, std::string>>& params) override;
		void start() override;
		void update(float dT) override;

	private:

		Audio::AudioManager* _man;

		std::unordered_map<const char*, ChannelData> _chMap;

		float _volumeMult;

		int _mode;

		std::string _playOnStart;
	};
}


#endif // !AUDIOSOURCE


