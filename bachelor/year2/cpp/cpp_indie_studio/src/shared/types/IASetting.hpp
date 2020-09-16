//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// Communications about IA
//

#ifndef IA_SETTING_HPP_
#define IA_SETTING_HPP_

#include <unordered_map>

namespace ind
{
	namespace ia
	{
		enum Types
		{
			PLAYER = 0,
			COWARD = 1,
			HUNTER_MEDIUM,
			HUNTER_HARD,
			STRATEGIST_MEDIUM,
			STRATEGIST_HARD,
		};

		ind::ia::Types operator+(const ind::ia::Types type, size_t nb);
		ind::ia::Types operator-(const ind::ia::Types type, size_t nb);
		ind::ia::Types operator+(const ind::ia::Types type, int nb);
		ind::ia::Types operator-(const ind::ia::Types type, int nb);

		static const std::unordered_map<ind::ia::Types, std::string> IA_MAPPING = {
			{ind::ia::Types::STRATEGIST_HARD, "Strategist Hard"},
			{ind::ia::Types::STRATEGIST_MEDIUM, "Strategist Medium"},
			{ind::ia::Types::HUNTER_HARD, "Hunter Hard"},
			{ind::ia::Types::HUNTER_MEDIUM, "Hunter Medium"},
			{ind::ia::Types::COWARD, "Coward"},
			{ind::ia::Types::PLAYER, "Player"},// needs to be last for UX
		};
	};
};

#endif /* !IA_SETTING_HPP_ */
