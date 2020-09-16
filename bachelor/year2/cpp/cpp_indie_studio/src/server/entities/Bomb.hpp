/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_BOMB_HPP
# define CPP_INIDIE_STUDIO_BOMB_HPP

#include <memory>
#include "AEntity.hpp"
#include "Fire.hpp"

class Bomb : public AEntity {
public:
	Bomb(std::pair<float, float> pos, int radius, int explosionTimer, int idPlayer, int id, bool isBig);
	void update();
	bool isOver();
	void forceExplosion();
	std::vector<Fire> getFire(const std::vector<std::unique_ptr<AEntity>> &_blocking, int &id);
	std::vector<Fire> getFire(const std::vector<std::unique_ptr<AEntity>> &blocking, int xModifier, int yModifier,
		std::vector<Fire> &toFill, int &id
	);
	int getPlayerId();
	bool isBig();
	int getRadius() const;
	unsigned short getPercentageBeforeExplosion() const;
private:
	int _radius;
	int _time;
	int _idPlayer;
	bool _isExploded;
	std::chrono::steady_clock::time_point _tikTak;
	bool _isBig;
};

#endif //CPP_INIDIE_STUDIO_BOMB_HPP
