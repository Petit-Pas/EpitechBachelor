/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

/**
 * \file
 * contains the main class for the Qix game
 */

#ifndef CPP_ARCADE_QIX_HPP
# define CPP_ARCADE_QIX_HPP

#include <vector>
#include <memory>
#include <Map.hpp>
#include "IGame.hpp"
#include "Arcade.hpp"
#include "Spark.hpp"
#include "TextureQix.hpp"
#include "Monster.hpp"
#include "Flame.hpp"

namespace ar {
	/**
	 * main class for the Qix game
	 */
	class Qix : public IGame {
	public:
		/**
		 * Just a basic struct containing 2D coordinates
		 */
		typedef struct Cell {
			int posX; /*!< the x-coordinate */
			int posY; /*!< the y-coordinate */
		} Cell;

		Qix();
		~Qix();

		const std::string getGameName() const override;
		const std::map<unsigned char, spriteCoords> &getSprites() const override;
		const std::map<unsigned char, colorVector> &getColors() const override;
		const std::string getSpritesPath() const override;
		void manageKey(const Event &) override;
		int refreshScore() override;
		int refreshTimer() override;
		bool isGameOver() override;
		void loop() override;

		/**
		 * check if the trail went over the border
		 */
		void checkTrailBorder();

		/**
		 * if the given cell should be a border, it is set back to border
		 * @param x x-coordinate of the cell to check
		 * @param y y-coordinate of the cell to check
		 */
		void checkTrailCell(int x, int y);

		Map &getMap() override;
		void setPause() override;

	private:

		/**
		 * move the players, depending on _direction
		 */
		void movePlayer();

		/**
		 * used to check a move before doing it, used to check that the player doesn't stick to his trail
		 * @param posY the x-coordinate where he tries to go
		 * @param posX the y-coordinate where he tries to go
		 * @return true if can move, false otherwise
		 */
		bool checkAround(int posY, int posX);

		/**
		 * used when the player closes a new area
		 */
		void validatePolygon();

		/**
		 * Used to detect if there is an area to close.
		 * It searches for 2 empty sets of cells
		 */
		void fillEmptyArea();

		/**
		 * Resets the differents WALLs ad BORDERs around the map to keep the BORDER correct
		 */
		void setBorder();

		/**
		 * used to check if a cell should be part of the border (is a WALL and is next to EMPTY)
		 * @param x the x-coordinate of the cell to check
		 * @param y the y-coordinate of the cell to check
		 * @return true if it is, false otherwise
		 */
		bool checkIfBorder(int x, int y);

		/**
		 * will switch every cell of the map containing 'from' to 'to'
		 * @param from the value to replace
		 * @param to the value to set
		 */
		void replaceInMap(TextureQix from, TextureQix to);

		/**
		 * Check if the Qix is in a set,
		 * Useful to know which set is the validated area and which is the walkable area when the player closes a zone
		 * @param set The set where to check
		 * @return true If the Qix is in the set
		 */
		bool isQixInSet(std::vector<Cell> set);

		/**
		 * finds the first cell of the map containing EMPTY
		 * @param x the variable in which the x-coordinate is set
		 * @param y the variable in which the y-coordinate is set
		 * \warning if no empty cell is found, x and y will contain the border of the map (0 and nullptr)
		 */
		void findEmptyCell(int &x, int &y);

		/**
		 * Create the color Vector that can be asked by the CoreManager if IDisplay::canHandleSprites()  returns false
		 */
		void initColorsVector();

		/**
		 * Create the sprite Vector that can be asked by the CoreManager if IDisplay::canHandleSprites() returns true
 		 */
		void initSpriteVector();

		/**
		 * Init the coordinates of the player
		 */
		void initPlayer();

		/**
		 * Fill the map with initial needed values
		 */
		void initMap();

		/**
		 * Create a vector of Cell with all EMPTY cells that are adjacent the one given
		 * @param x the x-coordinates of the cell from which it starts
		 * @param y the y-coordinates of the cell from which it starts
		 * @param emptyness the value to put in the map to replace EMPTY
		 * @return the newly created vector
		 */
		std::vector<Cell> findSet(int x, int y, TextureQix emptyness);

		/**
		 * Checks if the player is next to the border
		 * @return true if it is, false otherwise
		 */
		bool isPlayerNextToBorder();

		/**
		 * checks if the player is next to the trail
		 * @return true if it is, false otherwise
		 */
		bool isPlayerNextToTrail();

		/**
		 * modify the status of the game paused <--> unpaused
		 * handles the timer too
		 */
		void handlePause();

		/**
		 * checks if the given cell of the map contains the Monster
		 * @param x x-coordinate of the given cell
		 * @param y y-coordinate of the given cell
		 * @return true if it is, false otherwise
		 */
		bool isQuix(int x, int y);

		/**
		 * updates the score, depending on the fraction of the map that has been filled
		 * when reaches 2500 OR 5000 score, a new ar::Spark spanws
		 */
		void updateScore();

		/**
		 * checks if an ar::Flame should spawn, if so, makes it spawn
		 */
		void checkFlame();

		/**
		 * This function is called when the player hits the Qix or the ar::Flame
		 * It makes it go back to the border where it comes from
		 * The player can do this 3 times before losing.
		 * If the player arrives on a Spark, they are all reset
		 */
		void goBack();

		/**
		 * check if a cell is well inside the map
		 * @param x the x-coordinates of the cell to check
		 * @param y the y-coordinates of the cell to check
		 * @return true if it is, false otherwise
		 */
		bool checkIfCellIsInside(int x, int y);

		/**
		 * Spawns a flame on the border where the player comes from only if there is none on the map
		 */
		void spawnFlame();

		/**
		 * call ar::Spark::live() for every ar::Spark on the map
		 */
		void liveSparks();

		/**
		 * resets every ar::Spark on the map
		 */
		void resetSparks();

		/**
		 * checks if a move is possible and does it if so, also call ar::Qix::spawnFlame() if needed
		 * @param addonX the x to add to the actual x-coordinate of the player
		 * @param addonY the y to add to the actual y-coordinate of the player
		 */
		void checkMove(int addonX, int addonY);

		int _score; /*!< the score of the current game */
		Event _direction; /*!< the actual direction (set by IGame::manageKey()) */
		Map _map; /*!< the map of the game */
		clock_t _step; /*!< for timer calculations */
		std::map<unsigned char, ar::spriteCoords> _mapSprites; /*!< the vector of sprites coordinates */
		std::map<unsigned char, colorVector> _mapColors; /*!< the vector of colors */
		int _posX; /*!< the x-coordinates of the player */
		int _posY; /*!< the y-coordinates of the player */
		bool _gameOver; /*!< true if the game is over, false otherwise */
		bool _isDirectionValidated; /*!< used to avoid multiple directional inputs between 2 frames */
		time_t _start; /*!< timer of the start of the pause, is modified by pause */
		time_t _end; /*!< timer of end of game*/
		time_t _pause; /*!< timer of the start of the pause */
		bool _paused; /*!< true if the game is set to paused */
		TextureQix _old; /*!< the kind of cell on which was the player last turn */
		bool _trailing; /*!< true if the player is walking in the walkable central area, false if it is on the border */
		std::vector<std::unique_ptr<ar::Spark>> _sparks; /*!< vector of all the ar::Sparks on the map */
		std::unique_ptr<ar::Monster> _monster; /*!< a pointer to an instance of ar::Monster */
		std::unique_ptr<ar::Flame> _flame; /*!< a pointer to an instance of ar::Flame */
		int _lives; /*!< amount of lives left to the player */
	};
};

#endif //CPP_ARCADE_SNAKE_HPP
