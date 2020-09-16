/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#ifndef CPP_INDIE_STUDIO_WALKTHROUGH_HPP
# define CPP_INDIE_STUDIO_WALKTHROUGH_HPP

#include "AEntityClient.hpp"

namespace ind {
	namespace display {
		class WalkThrough : public AEntityClient {
		public:
			WalkThrough(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
				irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
			);
		};
	}
}

#endif //CPP_INDIE_STUDIO_WALKTHROUGH_HPP
