/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifdef _WIN32
	#include <windows.h>
#endif
#ifdef __linux__

	#include <sys/types.h>
	#include <dirent.h>

#endif

#include <iostream>
#include <fstream>
#include "Breakable.hpp"
#include "MapGenerator.hpp"
#include "Wall.hpp"

MapGenerator::MapGenerator() : _fileName("")
{
}

std::vector<std::string> MapGenerator::getFilesInPath(const std::string &name
) const
{
	std::vector<std::string> vector = {};
	#ifdef _WIN32
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
		vector.push_back(data.cFileName);
	} while (FindNextFile(hFind, &data) != 0);
	FindClose(hFind);
    }
	#endif

	#ifdef __linux__
	DIR *dirp = opendir(name.c_str());
	if (dirp == nullptr) {
		return vector;
	}
	struct dirent *dp;
	while ((dp = readdir(dirp)) != nullptr) {
		if ((std::string(dp->d_name)).find(".map") != static_cast<unsigned long>(-1))
			vector.emplace_back(dp->d_name);
	}
	closedir(dirp);
	#endif
	return vector;
}

bool MapGenerator::GetNewTemplate()
{
	std::vector<std::string> files = getFilesInPath(RESOURCE_DIR "maps");
	if (files.empty())
		return false;
	auto num = static_cast<int>(rand() % files.size());
	_fileName = files.at(num);
	_fileName = RESOURCE_DIR "maps/" + _fileName;
	return true;
}

void MapGenerator::setEntities(std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> toFill)
{
	int id = 100;
	if (_fileName.empty()) {
		std::cerr << "Error while loading map" << std::endl;
		return;
	}

	std::ifstream stream(_fileName);
	if (!stream.is_open()) {
		std::cerr << "Error while opening map" << std::endl;
		return;
	}

	int x = 0;
	int y = 0;
	char c;

	while (stream.get(c)) {
		if (!isCorner(x, y))
			switch (c) {
			case '#':
				toFill->getItem().push_back(
					std::make_unique<Wall>(std::pair<float, float>(y + 0.5, x + 0.5), id));
				id += 1;
				break;
			case ' ':
				if (rand() % 3 != 0) {
					toFill->getItem().push_back(
						std::make_unique<Breakable>(std::pair<float, float>(y + 0.5, x + 0.5),
							id));
					id += 1;
				}
				break;
			case '\n':
				y += 1;
				x = -1;
				break;
			default:
				std::cerr << "file \"" << _fileName << "\" might be corrupted" << std::endl;
				break;
			}
		x += 1;
	}
}

bool MapGenerator::isCorner(int x, int y)
{
	int arr[12][2] = {{1, 1}, {1, 2}, {2, 1}, {12, 1}, {13, 1}, {13, 2}, {1, 10}, {1, 11}, {2, 11}, {12, 11},
		{13, 11}, {13, 10}};
	for (int i = 0; i != 12; i++) {
		if (arr[i][0] == x && arr[i][1] == y)
			return true;
	}
	return false;
}
