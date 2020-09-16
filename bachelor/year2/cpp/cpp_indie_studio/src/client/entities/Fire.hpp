/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#ifndef CPP_INDIE_STUDIO_FIRE_HPP
# define CPP_INDIE_STUDIO_FIRE_HPP

#include "AEntityClient.hpp"

namespace ind {
	namespace display {
		class Fire : public AEntityClient {
		public:
			Fire(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
				irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
			);
			~Fire();
		private:
			irrklang::ISound *_fireSound;
		};
	}
}

#endif //CPP_INDIE_STUDIO_FIRE_HPP
