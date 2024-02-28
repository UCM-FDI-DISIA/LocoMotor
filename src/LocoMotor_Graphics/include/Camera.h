#include "Component.h"

namespace LocoMotor{

	namespace Ogre {
		class Camera;
		class Viewport;
	}

	namespace Graphics{

		class Camera : public Component {
			Camera();
			~Camera();

			friend class GraphicsManager;


		public:
			/// @brief Set the target and offset for the camera of a LocoMotor object.
			/// @param target A pointer to a GameObject that the camera will follow as its target.
			/// @param offset The offset is a vector that represents the distance and direction from the target
			/// object's position where the camera should be positioned. It is used to adjust the camera's position
			/// relative to the target object.
			//void SetTarget(GameObject* target, LMVector3 offset);

		protected:
			void init()/* override*/;
			void onEnable() override;
			void update(float dT) override;
			void onDisable() override;

		private:


			Ogre::Camera* _mCamera;
			Ogre::Viewport* _vp;
		};
	}
}