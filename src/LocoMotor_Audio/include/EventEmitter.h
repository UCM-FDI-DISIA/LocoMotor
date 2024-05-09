#pragma once
#ifndef EVENT_EMITTER
#define EVENT_EMITTER

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Component.h"

namespace FMOD {
	namespace Studio {
		class System;
		class EventInstance;
	}
}

namespace LocoMotor {
	class EventEmitter : public Component {

	public:
		EventEmitter();
		~EventEmitter();

		/// @brief Sets the event to be played from this emitter
		/// @param eventID the id of the event to play. The event must have had its bank loaded and is written in the format: ("event:/{BankName}/{EventName}")
		MOTOR_API void setEvent(const char* eventID);

		/// @brief Plays the emitter with the specified event, if no event has been set, this method does nothing
		MOTOR_API void play();

		/// @brief Sets the volume of the emitter
		/// @param vol: the desired volume in the range 0.f to 1.f
		MOTOR_API void setVolume(float vol);

		/// @brief Sets the pitch of the emitter
		/// @param vol: the desired pitch in the range 0.f to 1.f
		MOTOR_API void setPitch(float pitch);

		/// @brief Set the value of a parameter in the event, set in FMOD Studio
		/// @param paramName: the name of the parameter to modify. If it doesn't exist, this method does nothing
		/// @param value: the desired value for the chosen parameter
		MOTOR_API void setParameter(const char* paramName, float value);

		/// @brief Get the value of a parameter in the event, set in FMOD Studio
		/// @param paramName: the name of the parameter to retrieve. If it doesn't exist, this method returns 0
		/// @returns the value of the chosen parameter
		MOTOR_API float getParameter(const char* paramName);

		/// @brief Stops the emitter from playing
		MOTOR_API void stop();

	protected:

		bool setParameters(ComponentMap& params) override;
		void start() override;
		void update(float dT) override;

	private:

		FMOD::Studio::System* _studioSys;
		FMOD::Studio::EventInstance* _currentEvent;

		bool playOnStart;

	};
}

#endif // !EVENT_EMIITER
