/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Internal functions
*/

/**
 * \file
 * The file containing the class ar::Parser.
 * It is used to initialize the CoreManager, DisplayInterface and the GameInterface.
 */

#ifndef CPP_ARCADE_PARSER_HPP
# define CPP_ARCADE_PARSER_HPP

#include "CoreManager.hpp"

namespace ar {
	/**
	 * The parser class
	 */
	class Parser {
	public:
		/**
		 * Parser constructor
		 * @param ac Number of arguments received in main()
		 * @param av Array of arguments received in main()
		 * @param manager ar::CoreManager to be initialized
		 * @param gamesNames An empty vector, which will be filled with game names received from IGame::getGameName()
		 * @param displayNames An empty vector, which will be filled with libraries names parsed in ./lib
		 */
		Parser(int ac, char **av, ar::CoreManager &manager, std::vector<std::string> &gamesNames,
			std::vector<std::string> &displayNames
		);

		/**
		 * Display help message with the right binary Name
		 * @param binaryName The binary name
		 */
		void printHelp(const std::string &binaryName);

		/**
		 * Open and parse the libraries
		 * @param dir The directory that will be parsed
		 * @param files A vector containing all the libraries name found in the directory
		 * @return 84 in case of an error 0 otherwise
		 */
		int getDir(const std::string &dir, std::vector<std::string> &files);

		/**
		 * Call getDir() and handle all the duplicate if there is any
		 * @return 84 in case of an error, 0 if the program display the help message and 1 otherwise
		 */
		int parse();
		/**
		 * A destructor
		 */
		virtual ~Parser();
	private:
		int _ac; /*!< Number of argument received in the main */
		char **_av; /*!< All the argument received in the main */
		ar::CoreManager &_manager; /*!< A reference to the CoreManager*/
		std::vector<std::string> &_gamesNames; /*!< A vector containing all the games libraries names*/
		std::vector<std::string> &_displayNames; /*!< A vector containing all the graphical libraries names*/
	};
}

#endif //CPP_ARCADE_PARSER_HPP
