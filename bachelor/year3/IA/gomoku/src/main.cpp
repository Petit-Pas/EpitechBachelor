#include <iostream>
#include <fstream>
#include <string>
#include <memory.h>
#include "Parser.hpp"
#include "Board.hpp"
#include "Brain.hpp"

int main()
{
	Parser parser;
	gom::state status = gom::UNKNOWN;

	srand(static_cast<unsigned int>(time(nullptr)));
	while (status != gom::START) {
		status = parser.parse();
		if (status == gom::END)
			return 0;
	}
	Brain brain(parser);
	brain.process();
	return 0;
}
