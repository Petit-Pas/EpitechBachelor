//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// class for adding buttons from png
//

#ifndef BUTTON_EASY_ADD_HPP_
#define BUTTON_EASY_ADD_HPP_

#include <irrlicht.h>
#include <cstring>

class ButtonEasyAdd
{
public:
        static irr::gui::IGUIButton *addButton(irr::gui::IGUIEnvironment *env, irr::video::IVideoDriver *driver, size_t buttonId);
private:
        ButtonEasyAdd() = default;
};

#endif /* !BUTTON_EASY_ADD_HPP_ */
