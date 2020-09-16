/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#ifndef CPP_INDIE_STUDIO_AENTITIESCLIENT_HPP
# define CPP_INDIE_STUDIO_AENTITIESCLIENT_HPP

#include <memory>
#include <vector>
#include <irrKlang.h>
#include <irrlicht.h>
#include <Direction.hpp>
#include "Element.hpp"

namespace ind {
	namespace display {
		class AEntityClient {
		public:
			/**
			 * Entities constructor
			 * @param uId An unique id
			 * @param pos X and Y of the model
			 * @param texture The texture created with driver->getTexture(<PATH>)
			 * @param node smgr->addAnimatedMeshSceneNode(smgr->getMesh(<PATH>))
			 * @param scale The scale of the model
			 * @param hasAlpha Set to true if the texture has an alpha channel (default: false)
			 * @param needLight Set to false if the texture doesn't need custom light (default: true)
			 */
			AEntityClient(irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos,
				irr::video::ITexture *texture, irr::scene::IAnimatedMeshSceneNode *node,
				const irr::core::vector3df &scale, bool hasAlpha = false, bool needCulling = true
			);

			virtual ~AEntityClient();

			/**
			 * Change the scale of the model
			 * @param scale The new scale
			 */
			void setScale(const irr::core::vector3df &scale);

			/**
			 * Change the position of the model
			 * @param pos The new position
			 */
			virtual void setPos(const irr::core::vector2df &_pos);
			/**
			 * Change facing direction based on asked direction
			 * @param direction The new direction
			 */
			void setRotation(const dir::directions &direction);

			/**
			 * Return the position of the model
			 * @return pos The actual position
			 */
			const irr::core::vector2df &getPos() const;

			/**
			 * Return the state of the model
			 * @return the actual state
			 */
			void setTexture(irr::video::ITexture *_texture);
			virtual void setIdle();
			virtual void setMoving();
			virtual void setDying();
			virtual int getFrame();
			virtual void stopAnimation();
		protected:
			irr::core::vector2df _pos;
			irr::video::ITexture *_texture;
			irrklang::ISoundEngine *_soundEngine;
			irr::scene::IAnimatedMeshSceneNode *_node;
		};
	}
}

#endif //CPP_INDIE_STUDIO_AENTITIESCLIENT_HPP
