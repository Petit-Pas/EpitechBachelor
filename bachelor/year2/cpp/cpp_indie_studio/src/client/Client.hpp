/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#ifndef CPP_INDIE_STUDIO_CLIENT_HPP
# define CPP_INDIE_STUDIO_CLIENT_HPP

#include <memory>
#include <vector>
#include <map>
#include <irrlicht.h>
#include <entities/EntityFactory.hpp>
#include <ik_ISoundEngine.h>
#include "AEntityClient.hpp"
#include "EventReceiver.hpp"
#include "LockedItem.hpp"
#include "ClientTCP.hpp"
#include "Packet.hpp"
#include "Element.hpp"
#include "TaskQueue.hpp"

#define X_OFFSET 144.0f
#define Y_OFFSET 168.0f

namespace ind {
	namespace display {
		struct EntityInfo {
			std::string texture;
			std::string mesh;
			irr::core::vector3df scale = {1, 1, 1};
			bool hasAlpha = false;
			bool needLight = true;
		};

		class Client {
		public:
			/**
			 * Create an irrlicht window with the windowName as its name
			 * @param windowName The name of the window
			 */
			explicit Client(int clientId, const std::string &windowName, std::shared_ptr<ClientTCP>, const std::vector<size_t> &skins);
			~Client();
			void handleInputServer();
			void handleInputClient();
		private:
			void idleEntity(const Task &task);
			void createEntity(const Task &task);
			void updateEntity(const Task &task);
			void deleteEntity(const Task &task);
			void gameOver(const Task &task);
			bool handleTask();
			void displayLoop();
			void createFloor();
			void initModels();
			void createMenu();
			int _clientId;
			EntityFactory _entityFactory;
			std::shared_ptr<ClientTCP> _clientCom;
			irr::IrrlichtDevice *_device; /*!< Contains the instance of IrrlichtDevice*/
			irr::video::IVideoDriver *_driver; /*!< Contains the instance of IVideoDevice needed to create Textures*/
			irr::scene::ISceneManager *_smgr; /*!< Contains the instance of ISceneManager needed to create Nodes*/
			irr::gui::IGUIEnvironment *_guienv; /*!< Contains the instance of IGUIEnvironment*/
			irr::scene::ICameraSceneNode *_camera;  /*!< Contains the instance of ICameraSceneNode*/
			irr::scene::ILightSceneNode *_light; /*!< Contains the instance of ILightSceneNode*/
			std::unique_ptr<LockedItem<std::map<int, std::shared_ptr<AEntityClient>>>> _objectPool;  /*!< Contains all the AEntities*/
			ind::display::EventReceiver _receiver;  /*!< Contains the instance of EventReceiver*/
			std::shared_ptr<TaskQueue> _taskQueue;
			irrklang::ISoundEngine *_soundEngine;
			irr::gui::IGUIWindow *_gameMenu;
			irr::gui::IGUIScrollBar *_soundSettings;
			irr::gui::IGUIStaticText *_text;
			irr::gui::IGUIButton *_buttonMenu;
			std::vector<std::shared_ptr<AEntityClient>> _dyingEntity;
			bool _isDead;
			bool _gameEnded;
			std::vector<size_t> _skins;
		};
	}
}
#endif //CPP_INDIE_STUDIO_CLIENT_HPP
