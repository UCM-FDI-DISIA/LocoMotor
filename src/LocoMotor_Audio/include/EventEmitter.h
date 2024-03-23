#pragma once
#ifndef EVENT_EMITTER
#define EVENT_EMITTER

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

		void setEvent(const char* eventID);

		void play();

		void setVolume(float vol);

		void setPitch(float pitch);

		void setParameter(const char* paramName, float value);
		float getParameter(const char* paramName);

		void stop();

	protected:

		void setParameters(std::vector<std::pair<std::string, std::string>>& params) override;
		void start() override;
		void update(float dT) override;

	private:

		FMOD::Studio::System* _studioSys;
		FMOD::Studio::EventInstance* _currentEvent;

		bool playOnStart;

	};
}

#endif // !EVENT_EMIITER
