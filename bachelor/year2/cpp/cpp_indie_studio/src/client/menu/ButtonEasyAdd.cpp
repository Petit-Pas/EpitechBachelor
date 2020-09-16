//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// button setting for simple use
//

#include "ButtonsSetting.hpp"
#include "ButtonEasyAdd.hpp"

irr::gui::IGUIButton *ButtonEasyAdd::addButton(irr::gui::IGUIEnvironment *env, irr::video::IVideoDriver *driver, size_t buttonId)
{
	if (DEFINED_BUTTONS.find(buttonId) == DEFINED_BUTTONS.end())
		throw std::runtime_error("No button with id " + std::to_string(buttonId));
	auto button = env->addButton(DEFINED_BUTTONS.at(buttonId).pos, nullptr, buttonId, DEFINED_BUTTONS.at(buttonId).text.c_str());
	button->setScaleImage(true);
	if (!DEFINED_BUTTONS.at(buttonId).pathToNormal.empty()) {
		auto texture = driver->getTexture(DEFINED_BUTTONS.at(buttonId).pathToNormal.c_str());
		if (!texture)
			throw std::runtime_error("No texture from " + DEFINED_BUTTONS.at(buttonId).pathToNormal);
		button->setImage(texture);
	}
	if (!DEFINED_BUTTONS.at(buttonId).pathToPressed.empty()) {
		auto texture = driver->getTexture(DEFINED_BUTTONS.at(buttonId).pathToPressed.c_str());
		if (!texture)
			throw std::runtime_error("No texture from " + DEFINED_BUTTONS.at(buttonId).pathToPressed);
		button->setPressedImage(texture);
	}
	return (button);
}
