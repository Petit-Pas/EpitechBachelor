//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// broadcast related functions
//

#ifndef ZAPPY_BROADCAST_HPP_
#define ZAPPY_BROADCAST_HPP_

#include <string>
#include <vector>

namespace Broadcast
{
	/**
	 * This class parses a broadcast message
	 */
	class Message
	{
	public:
		Message(const std::string &);

		/**
		 * get first part of message
		 */
		const std::string &getFunction() const;

		/**
		 * get the params splitted at ' '
		 */
		const std::vector<std::string> &getParams() const;

		/**
		 * get the params in a single string
		 */
		const std::string &getParamsLine() const;

		/**
		 * get the orientation of message
		 */
		int getOrientation() const;
	private:
		void setOrientation(const std::string &);
	private:
		std::string _fullMsg;
		std::string _function;
		std::vector<std::string> _params;
		std::string _fullParams;
		int _orientation;
	};

	class Broadcast
	{
	public:
		static bool isMessage(const std::string &);
	private:
		Broadcast() = default;
	};
};

#endif /* !ZAPPY_BROADCAST_HPP_ */
