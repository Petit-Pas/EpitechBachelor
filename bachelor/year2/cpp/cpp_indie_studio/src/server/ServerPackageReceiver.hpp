/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#ifndef CPP_INDIE_STUDIO_SERVERPACKAGEMANAGER_HPP
# define CPP_INDIE_STUDIO_SERVERPACKAGEMANAGER_HPP

#include <vector>
#include "AMovable.hpp"
#include "LockedItem.hpp"
#include "TimedObject.hpp"
#include "Packet.hpp"
#include "PlayerCommunication.hpp"

class ServerPackageReceiver {
public:

	/**
 	 * constructor
 	 * @param players a protected pointer to one of the vector used by gameManager
 	 * @param blocking a protected pointer to one of the vector used by gameManager
 	 * @param fire a protected pointer to one of the vector used by gameManager
 	 * @param bomb a protected pointer to one of the vector used by gameManager
 	 * @param bonuses a protected pointer to one of the vector used by gameManager
 	 * @param vanishing a protected pointer to one of the vector used by gameManager
 	 */
	ServerPackageReceiver(std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
		std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> playerCom
	);

	ServerPackageReceiver() = default;

	/**
	 * destructor
	 */
	~ServerPackageReceiver();

	/**
	 * loop called by std::thread in Thread()
 	 */
	void run();

private:

	/**
	 * get 1 UDP package
	 * @return a struct packageClientServer red in the UDP socket
	 */
	packageClientServer getPackage();

	/**
	 * spawns a bomb depending at a given pos if the given player hasn't reached his maximum amount of bombs
	 * and if there is no bomb at this location yet
	 * @param input the packageClientServer that is received by the clients and that contains needed information to spawn a bomb
	 */
	void spawnBomb(packageClientServer &input);

	/**
	 * just set the direction for the given player
	 * @param input the packageClientServer that is received by the clients and that contains the information about the move
	 */
	void movePlayer(packageClientServer &input);

	/**
	 * used to get a new ID to be given to an item of the game
	 * @return the new ID
	 */
	int getNewUniqueID();

	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> _players; /*!< contains the players */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> _blocking; /*!< contains walls and breakables */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> _fires; /*!< contains explosions(aka Fire) */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> _bombs; /*!< contains Bombs */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> _bonuses; /*!< contains every kind of bonus */
	int _uniqueIDAvailable;
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> _playerCom;
};

#endif //CPP_INDIE_STUDIO_SERVERPACKAGEMANAGER_HPP
