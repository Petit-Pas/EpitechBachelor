//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// join broadcast direction
//

#ifndef CMD_JOIN_PEOPLE_HPP_
#define CMD_JOIN_PEOPLE_HPP_

#include "AComplexCommand.hpp"

namespace Cmd
{
	class JoinPeople : public AComplexCommand
	{
	public:
		JoinPeople(const std::shared_ptr<Connection> &, ADrone &, size_t id, int dir);
		JoinPeople(const std::shared_ptr<Connection> &con, ADrone &drone, std::vector<std::pair<std::size_t, std::unordered_map<std::string, size_t>>> &ids);
		//bool isDone() const;
		~JoinPeople();

		enum Mode
		{
			FAR,
			PHARE,
			JOIN
		};

		void updateCommands(ADrone &) override;
		bool unusedMessage(const std::string &, ADrone &) override;

	private:
		void joinBroadcast(ADrone &);
		void sendIncantation(ADrone &, size_t, bool = true);
		static int getChangeDelta(int, int);
		bool isEverybodyHere() const;
		bool isAnyStrangerHere() const;
		bool isConcern(size_t) const;
		static bool compareId(const std::pair<std::size_t, std::unordered_map<std::string, size_t>> &, const std::pair<std::size_t, std::unordered_map<std::string, size_t>> &);
	private:
		int _initialDir;
		int _actualDir;
		size_t _actualLvl;
		size_t _idJoin;
		size_t _idBroadcast;
		size_t _lastBroadcast;
		size_t _lastBroadcastTick;
		Mode _mode;
		Orientation _globalDir;
		std::vector<std::size_t>  _peopleJoined;
		std::vector<std::pair<std::size_t, std::unordered_map<std::string, size_t>>> _peopleToJoin;
		std::vector<std::pair<std::size_t, std::unordered_map<std::string, size_t>>> _fullPeople;
		ADrone &_drone;
		static const int MAX_DELTA;
	};
};

#endif /* !CMD_JOIN_PEOPLE_HPP_ */
