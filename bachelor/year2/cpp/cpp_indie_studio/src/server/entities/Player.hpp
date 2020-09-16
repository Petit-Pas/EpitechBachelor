/*
** EPITECH PROJECT, 2018
** refactured_entities
** File description:
** Created by vincent,
*/
#ifndef REFACTURED_ENTITIES_PLAYER_HPP
#define REFACTURED_ENTITIES_PLAYER_HPP

#include "AMovable.hpp"
#include "Bomb.hpp"

class Player : public AMovable {
public:
	Player(const std::pair<float, float> &pos, int id);

	void bombAvailable();

	bool isBombAvailable() const;

	bool isBlocked(const std::pair<float, float> &pos, const std::vector<AEntity> &blocking,
		const std::vector<AEntity> &explosions
	) const;

	void checkDeath(const std::vector<std::unique_ptr<Fire>> &explosions);

	void checkBonus(std::vector<AEntity> &);

	virtual void addBomb();

	void addFirePower();

	int getFirePower() const;

	int getAmountBombs();

	int getAmountBombsMax();

	int getBombTimer();

	float getSpeed();

	virtual void incrementSpeed();

	void removeBomb();

	bool canWalkThrough();

	void addWalkThrough();

	void setInAWall(bool value);
	bool isInAWall();

	void addBigBomb();
	bool hasBigBomb();

	void setIdle();
	void unsetIdle();
	void setIdleSend();
	bool isIdle() const;
	bool isIdleSend() const;

protected:
	short _nbLives;
	short _nbBombMax;
	short _nbBombDrop;
	short _firePower;
	short _bombTimer;
	float _speed;
	short _ghostWall;
	bool _isInAWall;
	int _bigBomb;
	bool _idle;
	bool _idleSend;
};

#endif //REFACTURED_ENTITIES_PLAYER_HPP
