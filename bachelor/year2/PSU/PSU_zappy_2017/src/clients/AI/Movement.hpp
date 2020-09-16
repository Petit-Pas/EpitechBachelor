//
// EPITECH PROJECT, 2018
// zappy
// File description:
// methods of movement and space recognition
//

#ifndef ZAPPY_SIZE_HPP_
#define ZAPPY_SIZE_HPP_

#include <vector>
#include <iostream>

class ElementMap;

class Orientation;

struct Size
{
	std::size_t height;
	std::size_t width;
};

struct Position
{
	int y;
	int x;

	Position &operator=(const Orientation &);
	Position &operator()(const Orientation &);
	Position &operator+=(const Orientation &);
	Position operator+(const Orientation &) const;
	Position &operator+=(const Position &);
	Position operator+(const Position &) const;
	Position operator*(int) const;
	bool operator==(const Position &) const;
	bool operator!=(const Position &) const;
	void scaleToMap(const ElementMap &);
};

enum class Direction
{
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3,
};

#include "ElementMap.hpp"

class Orientation
{
public:
	Orientation() : _i(0), DIRECTIONS({{0, -1}, {-1, 0}, {0, 1}, {1, 0}}) {};
	Orientation(Direction);
	Orientation(int);
	~Orientation() = default;
	Orientation &operator++(int);
	Orientation &operator--(int);
	Orientation &operator+=(int);
	Orientation &operator=(const Orientation &);
	bool operator==(const Orientation &) const;

	std::size_t getNbMovements(const Position &, const Position &, const ElementMap &) const;

	const Position &getDir() const;
	int getIndex() const;
private:
	int _i;
	const std::vector<Position> DIRECTIONS;
};


std::ostream &operator<<(std::ostream &, const Position &);
std::ostream &operator<<(std::ostream &, const Orientation &);

#endif /* !ZAPPY_SIZE_HPP_ */
