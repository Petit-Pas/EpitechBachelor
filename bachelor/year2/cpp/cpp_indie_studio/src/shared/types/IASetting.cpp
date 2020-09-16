//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// IA definition of overload
//

#include "IASetting.hpp"

ind::ia::Types ind::ia::operator+(const ind::ia::Types type, size_t nb) {
	auto newType = static_cast<ind::ia::Types>(static_cast<size_t>(type) + nb);
	return (newType);
}

ind::ia::Types ind::ia::operator-(const ind::ia::Types type, size_t nb) {
	auto newType = static_cast<ind::ia::Types>(static_cast<size_t>(type) - nb);
	return (newType);
}

ind::ia::Types ind::ia::operator+(const ind::ia::Types type, int nb) {
	auto newType = static_cast<ind::ia::Types>(static_cast<int>(type) + nb);
	return (newType);
}

ind::ia::Types ind::ia::operator-(const ind::ia::Types type, int nb) {
	auto newType = static_cast<ind::ia::Types>(static_cast<int>(type) - nb);
	return (newType);
}
