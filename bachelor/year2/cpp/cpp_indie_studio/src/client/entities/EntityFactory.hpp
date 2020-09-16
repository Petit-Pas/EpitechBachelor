/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#ifndef CPP_INDIE_STUDIO_ENTITYFACTORY_HPP
# define CPP_INDIE_STUDIO_ENTITYFACTORY_HPP

#include <ISceneManager.h>
#include <Element.hpp>
#include <map>
#include "AEntityClient.hpp"

namespace ind {
	namespace display {
		class EntityFactory {
		public:
			EntityFactory(irr::video::IVideoDriver *_driver, irr::scene::ISceneManager *_smgr,
				irrklang::ISoundEngine *_soundEngine
			);
			std::shared_ptr<AEntityClient> createBomb(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createEmpty(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createBombUp(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createFire(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createFireUp(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createHardWall(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createPierceBomb(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createPlayer(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createAI(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createSoftWall(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createSpeedUp(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createWalkThrough(const irr::core::vector2df &pos);
			std::shared_ptr<AEntityClient> createEntity(Element::Type type, const irr::core::vector2df &pos
			);
		private:
			irr::video::IVideoDriver *_driver; /*!< Contains the instance of IVideoDevice needed to create Textures*/
			irr::scene::ISceneManager *_smgr; /*!< Contains the instance of ISceneManager needed to create Nodes*/
			irrklang::ISoundEngine *_soundEngine;
			std::map<Element::Type, std::shared_ptr<ind::display::AEntityClient> (EntityFactory::*)(
				const irr::core::vector2df &pos
			)> _dico;
		};
	}
}

#endif //CPP_INDIE_STUDIO_ENTITYFACTORY_HPP
