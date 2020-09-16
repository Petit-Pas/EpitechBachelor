//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// available skins
//

#ifndef SKINPICKER_HPP_
#define SKINPICKER_HPP_

#include <vector>

namespace ind
{
	static const std::vector<std::string> SKINS_PATH = {
		/* official */
		RESOURCE_DIR "media/black.png",
		RESOURCE_DIR "media/red.png",
		RESOURCE_DIR "media/green.png",
		RESOURCE_DIR "media/pink.png",
		RESOURCE_DIR "media/yellow.png",
		RESOURCE_DIR "media/white.png",
		RESOURCE_DIR "media/blue.png",

		/* for fun */
		RESOURCE_DIR "media/mariowhite.png",
		RESOURCE_DIR "media/megaman.png",
	};

	static const std::vector<std::string> AI_SKINS = {
		RESOURCE_DIR "media/ia.png",
		RESOURCE_DIR "media/rustyia.png",
		RESOURCE_DIR "media/darkia.png",
	};
};

#endif /* !SKINPICKER_HPP_ */
