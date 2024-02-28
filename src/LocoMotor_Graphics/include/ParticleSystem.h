#include "Component.h"
#include <string>


namespace Ogre {
	class ParticleHelper;
	class Node;
	class RenderScene;
}

namespace LocoMotor{

	class Scene;
	class GameObject;

	namespace Graphics{

		class ParticleSystem : public Component {

			friend class GraphicsManager;

		protected:
			void init()/* override*/;
			void onEnable() override;
			void update(float dT) override;
			void onDisable() override;


		private:

			// Nodo de ogre
			Ogre::Node* _node;
			//OgreWrapper::RenderScene* _renderScn;
			//OgreWrapper::ParticleHelper* _particleHelper;

			std::string _filename;
			std::string _name;


			ParticleSystem();
			~ParticleSystem();

		public:

		};
	}
}