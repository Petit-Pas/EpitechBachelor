/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_TIMERMANAGER_HPP
# define CPP_INIDIE_STUDIO_TIMERMANAGER_HPP

#include <vector>
#include "TimedObject.hpp"
#include "Fire.hpp"
#include "AMovable.hpp"
#include "LockedItem.hpp"
#include "AEntity.hpp"
#include "Player.hpp"
#include "ABonus.hpp"
#include "PlayerCommunication.hpp"

class TimerManager {
public:

	/**
	 * default constructor
	 */
	TimerManager() = default;

	/**
	 * constructor
	 * @param players a protected pointer to one of the vector used by gameManager
	 * @param blocking a protected pointer to one of the vector used by gameManager
	 * @param explosives a protected pointer to one of the vector used by gameManager
	 * @param bonuses a protected pointer to one of the vector used by gameManager
	 * @param vanishing a protected pointer to one of the vector used by gameManager
	 */
	TimerManager(std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fires,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bombs,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
		std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> playerCom
	);

	TimerManager(TimerManager &toCopy);

	/**
	 * destructor
	 */
	~TimerManager();

	/**
	 * loop called by std::thread in Thread()
	 */
	void run();
private:
	/**
	 * checks the whole vector of explosives for bombs that should explode
	 */
	void explodeBombs();

	/**
	 * checks the whole vector of explosives for fire that should dispawn
	 */
	void dispawnFires();

	/**
	 * create all fire from the explosion and call spawnExplosion for each of them
	 */
	void explodeBomb(Bomb *bomb);

	/**
	 * will find the player to whom the bomb belongs, and remove one from his active bombs
	 * @param bomb a Bomb entity that contains the playerID
	 */
	void removeBombFromPlayer(Bomb *bomb);

	/**
	 * takes a newly spawning Fire as a parameter and checks collision with every other item
	 * @param fire the fire that spawns
	 */
	void spawnExplosion(Fire &fire);

	/**
	 * moves every player if they have a direction, and if Player::playerCanMove returns true;
	 */
	void movePlayers();

	/**
	 * A function that checks if the move of a player is possible, and triggers any consequences of that move,such as dying or getting a bonus
	 * @param player the player to check wether or not he can move
	 * @return true if the movement is validated, false otherwise
	 */
	bool playerCanMove(Player *player);

	/**
	 * add a random bonus
	 */
	void addBonus(const std::pair<float, float> &);

	/**
	 * check players deconnection
	 */
	void checkDeconnection();

	int getNewUniqueID();

	void sendDeleteObject(AEntity *object);
	void sendIdleObject(AEntity *object);
	void sendCreateObject(AEntity *object);

	bool checkHitboxBlocking(const std::pair<float, float> &plannedPos, Player *player);
	bool checkHitboxBombs(const std::pair<float, float> &plannedPos, Player *player);
	bool checkHitboxFires(const std::pair<float, float> &plannedPos, Player *player);
	bool checkHitboxBonuses(const std::pair<float, float> &plannedPos, Player *player);

	bool checkWalkThrough(Player *player);

	void updateAIs();
	//bool checkPlayerCollision(std::unique_ptr<AEntity> &object, std::pair<float, float> pos);

	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> _players; /*!< contains the players */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> _blocking; /*!< contains walls and breakables */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> _fires; /*!< contains Bombs and explosions(aka Fire) */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> _bombs; /*!< contains Bombs and explosions(aka Fire) */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> _bonuses; /*!< contains every kind of bonus */
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> _playerCom;
	int _uniqueID;
	bool _startAI;
};

#endif //CPP_INIDIE_STUDIO_TIMERMANAGER_HPP
