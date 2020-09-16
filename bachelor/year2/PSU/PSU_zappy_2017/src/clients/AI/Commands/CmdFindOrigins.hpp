//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// find origin (first player or not)
//

#ifndef CMD_FIND_ORIGINS_HPP_
#define CMD_FIND_ORIGINS_HPP_

#include <string>
#include <unordered_map>

#include "AComplexCommand.hpp"
#include "Broadcast.hpp"

namespace Cmd
{
	class FindOrigins;

	typedef bool (Cmd::FindOrigins::*broadHandle)(const ::Broadcast::Message &, ADrone &);
	typedef std::unordered_map<std::string, broadHandle> broadcastMap;

	class FindOrigins : public AComplexCommand
	{
	public:
		FindOrigins(const std::shared_ptr<Connection> &);
	private:
		void findId();
		void findRealId(ADrone &);

		void updateCommands(ADrone &) override ;
                bool unusedMessage(const std::string &, ADrone &) override ;

		bool addPlayer(const std::string &);
		void setPlayerList(const std::string &, bool);

		void sendListPlayers();

		bool notFirst(const ::Broadcast::Message &, ADrone &);
		bool recvNew(const ::Broadcast::Message &, ADrone &);
		bool addPlayer(const ::Broadcast::Message &, ADrone &);
		bool recvListPlayers(const ::Broadcast::Message &, ADrone &);
	private:
		broadcastMap BROADCAST_HANDLE;
		//left : playerID, right : is list OK
		std::unordered_map<std::string, bool> _players;

		std::string _ID;
	};
};

#endif /* !CMD_FIND_ORIGINS_HPP_ */
