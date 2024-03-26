#pragma once

#include "Component.h"
#include "LMVector.h"

namespace Ogre {
	class Light;
	class SceneNode;
}

namespace LocoMotor {

	namespace Graphics {
		class GraphicsManager;
	}
	class Light:public Component {
		friend class Graphics::GraphicsManager;
	public:
		
		Light();
		~Light();
		/// @brief Sets the diffuse value of the light
		void setDiffuse(float x, float y, float z);
		/// @brief Sets the specular value of the light
		void setSpecular(float x, float y, float z);
		
	protected:
		Ogre::Light* _light;
		
		void start() override;
		void update(float dt) override;

		void setParameters(std::vector<std::pair<std::string, std::string>>& params) override;

	private:
		
		Ogre::SceneNode* _node;
		LMVector3 _nodeScale;
		LMQuaternion _nodeRotation;
	};
	
}