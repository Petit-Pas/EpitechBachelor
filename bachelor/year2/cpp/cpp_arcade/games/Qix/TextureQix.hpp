/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#ifndef CPP_ARCADE_TEXTUREQIX_HPP
# define CPP_ARCADE_TEXTUREQIX_HPP

namespace ar {
	/**
	 * set of texture used for the Qix
	 */
	enum TextureQix {
		EMPTY = 2, /*!< Empty  cell */
		BORDER = 3, /*!< The border on which player and sparks can walk */
		PLAYER = 4, /*!< The player */
		TRAIL = 5, /*!< The trail of the player when not walking on border */
		EATEN = 6, /*!< Eaten areas */
		WALL = 7, /*!< former border */
		SPARK1 = 8, /*!< 1st sprite of the sparks */
		SPARK2 = 9, /*!< 2nd sprite of the sparks */
		QIXHEAD = 10, /*!< Head of Qix */
		QIXARMLEFT = 11, /*!< Left arm of the Qix */
		QIXARMRIGHT = 12, /*!< Right arm of the Qix */
		QIXLEGLEFT = 13, /*!< Left leg of the Qix */
		QIXLEGRIGHT = 14, /*!< Right leg of the qix */
		QIXBODY1 = 15, /*!< qix Body piece 1 */
		QIXBODY2 = 16, /*!< qix Body piece 2 */
		QIXBODY3 = 17, /*!< qix Body piece 3 */
		QIXBODY4 = 18, /*!< qix Body piece 4 */
		QIXBODY5 = 19, /*!< qix Body piece 5 */
		QIXBODY6 = 20, /*!< qix Body piece 6 */
		QIXBODY7 = 21, /*!< qix Body piece 7 */
		QIXBODY8 = 22, /*!< qix Body piece 8 */
		QIXBODY9 = 23, /*!< qix Body piece 9 */
		QIXUTIL = 24, /*!< for processing purpose */

		FLAME1 = 25, /*!< 1st sprite of the spark */
		FLAME2 = 26, /*!< 2nd sprite of the spark */
		EMPTY1, /*!< for processing purpose */
		EMPTY2 /*!< for processing purpose */
	};
}

#endif //CPP_ARCADE_TEXTUREQIX_HPP
