//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// launch menu
//

#include <iostream>
#include <stdexcept>
#include "Menu.hpp"

int main()
{
	try {
		Menu menu;
	} catch (std::runtime_error &err) {
		std::cerr << err.what() << std::endl;
		return (84);
	}
	return (0);
}
