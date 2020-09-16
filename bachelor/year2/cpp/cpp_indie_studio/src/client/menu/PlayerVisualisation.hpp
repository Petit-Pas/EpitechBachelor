//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// player visu for lobby
//

#ifndef	PLAYER_VISUALISATION_HPP_
#define	PLAYER_VISUALISATION_HPP_

#include <irrlicht.h>

class PlayerVisualisation {
public:
	PlayerVisualisation(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, size_t skinId, int human, size_t nbPlayer);
	~PlayerVisualisation();

	void modifyTexture(size_t skinId, int human);
	void rotate(irr::core::vector3df rot);
private:
	void setTexture(size_t skinId, int human);
private:
	irr::scene::ISceneManager *_smgr;
	irr::video::IVideoDriver *_driver;
	size_t _skinId;
	int _human;
	irr::scene::IAnimatedMeshSceneNode *_node;
};

#endif /* !PLAYER_VISUALISATION_HPP_ */
