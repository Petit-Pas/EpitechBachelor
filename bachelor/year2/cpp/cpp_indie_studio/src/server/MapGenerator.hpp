/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_MAPGENERATOR_HPP
# define CPP_INIDIE_STUDIO_MAPGENERATOR_HPP

#include <vector>
#include <string>
#include <memory>
#include "LockedItem.hpp"
#include "AEntity.hpp"

class MapGenerator {
public:

	MapGenerator();
	~MapGenerator() = default;

	/**
	 * load a new template file from "map/" directory
	 * @return true if it found a valid file
	 */
	bool GetNewTemplate();

	/**
	 * get the vector of entites from template (empty cells have a given percentage chance to spawn a breakable wall)
	 * @return the newly created vector
	 */
	void setEntities(std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> toFill);

private:

	/**
	 * this function returns a vector with the .map contained on a given directory
	 * @param directory the directory to look in
	 * @return a vector containing the names
	 */
	std::vector<std::string> getFilesInPath(const std::string &directory) const;

	/**
	 * this function is used to know if a given coordinate is one of the 4 corner of the map
	 * a corner being made of 3 cells in an 'L' form
	 * @param x x-coordinate
	 * @param y y-coordinate
	 * @return true is it is one of the corner
	 */
	bool isCorner(int x, int y);

	std::string _fileName;
};

#endif //CPP_INIDIE_STUDIO_MAPGENERATOR_HPP
