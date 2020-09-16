/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#ifndef CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
# define CPP_INDIE_STUDIO_EVENTRECEIVER_HPP

#include <irrlicht.h>
#include "KeyCodes.hpp"

namespace ind {
	namespace display {

		class EventReceiver : public irr::IEventReceiver {
		public:
			/**
			 * EventReceiver constructor
			 */
			EventReceiver(irr::IrrlichtDevice *device);
			/**
			 * irr::IEventReceiver::OnEvent method override
			 * @param event The event
			 * @return return bool
			 */
			bool OnEvent(const irr::SEvent &event) override;
			/**
			 * Check if a key is pressed
			 * @param keyCode the key code to check
			 * @return if hte key is pressed
			 */
			bool IsKeyDown(EKEY_CODE keyCode) const;
		private:
			irr::IrrlichtDevice *_device;
			bool KeyIsDown[KEY_KEY_CODES_COUNT]; /*!< A array containing all the existing key */
		};
	}
}

#endif //CPP_INDIE_STUDIO_EVENTRECEIVER_HPP
