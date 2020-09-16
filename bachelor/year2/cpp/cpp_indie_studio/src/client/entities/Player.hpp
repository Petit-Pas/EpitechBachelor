/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#ifndef CPP_INDIE_STUDIO_PLAYER_HPP
# define CPP_INDIE_STUDIO_PLAYER_HPP

#include "AEntityClient.hpp"

namespace ind {
	namespace display {
		class Player : public AEntityClient {
		public:
			Player(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
				irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
			);
			~Player();
			void setPos(const irr::core::vector2df &pos) override;
			void setIdle() override;
			void setMoving() override;
			void setDying() override;
		private:
			bool _moving;
		};
	}
}

#endif //CPP_INDIE_STUDIO_PLAYER_HPP
