/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#ifndef CPP_INDIE_STUDIO_BOMB_HPP
# define CPP_INDIE_STUDIO_BOMB_HPP

#include "AEntityClient.hpp"

namespace ind {
	namespace display {
		class Bomb : public AEntityClient {
		public:
			Bomb(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
				irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
			);
			virtual ~Bomb();
		};
	}
}

#endif //CPP_INDIE_STUDIO_BOMB_HPP
