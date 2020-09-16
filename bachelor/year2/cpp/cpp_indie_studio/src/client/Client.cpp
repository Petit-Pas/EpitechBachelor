/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include <memory>
#include "Direction.hpp"
#include "Client.hpp"
#include "Thread.hpp"
#include "ClientReceiveUpdate.hpp"
#include "LockedItem.hpp"
#include "SkinPicker.hpp"

static const std::map<Element::Type, ind::display::EntityInfo> EntityInfoG = {{Element::Type::HARDWALL,
	{RESOURCE_DIR "media/iron_block.png", RESOURCE_DIR "media/block.obj", {12, 12, 12}, false, true}},
	{Element::Type::SOFTWALL,
		{RESOURCE_DIR "media/stone01.png", RESOURCE_DIR "media/block.obj", {12, 12, 12}, false, true}},
	{Element::Type::PLAYER,
		{RESOURCE_DIR "media/player.png", RESOURCE_DIR "media/SteveAnimatedTest.ms3d", {1, 1, 1}, false, true}},
	{Element::Type::AI,
		{RESOURCE_DIR "media/player.png", RESOURCE_DIR "media/SteveAnimatedTest.ms3d", {1, 1, 1}, false, true}},
	{Element::Type::BOMB, {"", RESOURCE_DIR "media/tnt.obj", {12, 12, 12}, false, true}},
	{Element::Type::FIRE, {"", RESOURCE_DIR "media/Fire.obj", {20, 25, 20}, true, false}},
	{Element::Type::BOMB_UP, {"", RESOURCE_DIR "media/tntpack.obj", {4.5, 4.5, 4.5}, false, true}},
	{Element::Type::FIRE_UP, {"", RESOURCE_DIR "media/GunPowder.obj", {30, 30, 30}, false, true}},
	{Element::Type::SPEED_UP, {"", RESOURCE_DIR "media/Sugar.obj", {30, 30, 30}, false, true}},
	{Element::Type::WALK_THROUGH, {"", RESOURCE_DIR "media/DiamondBoots.obj", {30, 30, 30}, false, true}},
	{Element::Type::PIERCE_BOMB, {"", RESOURCE_DIR "media/GoldPickaxe.obj", {25, 25, 25}, false, true}}};

ind::display::Client::Client(int clientId, const std::string &windowName, std::shared_ptr<ClientTCP> client, const std::vector<size_t> &skinIds)
	: _clientId(clientId), _entityFactory(nullptr, nullptr, nullptr), _clientCom(client), _receiver(nullptr),
	  _isDead(false), _gameEnded(false), _skins(skinIds)
{
	srand(time(NULL));
	irr::SIrrlichtCreationParameters params;
	irr::core::stringw caption = windowName.c_str();

	endG = false;
	params.DriverType = irr::video::EDT_OPENGL;
	params.Stencilbuffer = true;
	params.Vsync = true;
	params.Doublebuffer = true;
	params.WindowSize = {1920, 1080};
	params.EventReceiver = &_receiver;
	_device = irr::createDeviceEx(params);
	_device->setWindowCaption(caption.c_str());
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_soundEngine = irrklang::createIrrKlangDevice();
	_receiver = EventReceiver(_device);
	_device->setEventReceiver(&_receiver);
	_soundEngine->setSoundVolume(0);
	_entityFactory = EntityFactory(_driver, _smgr, _soundEngine);
	_guienv = _device->getGUIEnvironment();
	_light = _smgr->addLightSceneNode(nullptr, {-200 - X_OFFSET, 1200, 200},
		irr::video::SColorf(1.0f, 1.0f, 0.99f, 1.0f), 900);
	_camera = _smgr->addCameraSceneNode(nullptr, {100, 300, 0}, {0, -30, 0});
	_camera->setFarValue(10000.0f);
	_smgr->setShadowColor(irr::video::SColor(100, 0, 0, 0));
	createFloor();
	_taskQueue = std::make_shared<TaskQueue>();
	_objectPool = std::make_unique<LockedItem<std::map<int, std::shared_ptr<AEntityClient>>>>();
	ClientReceiveUpdate clientReceiveUpdate(_clientCom, _taskQueue);
	createMenu();
	auto threadReceive = Thread<ClientReceiveUpdate>(clientReceiveUpdate);
	initModels();
	_soundEngine->setSoundVolume(0);
	_soundEngine->stopAllSounds();
	_soundEngine->setSoundVolume(0.6);
	std::string pathSound(RESOURCE_DIR);
	pathSound += "sounds/background/SongBattleGame";
	pathSound += std::to_string(rand() % 5 + 1);
	pathSound += ".ogg";
	_soundEngine->play2D( pathSound.c_str(), true);
	displayLoop();
	endG = true;
	threadReceive.getThread().join();
	_device->closeDevice();
	_device->run();
	_device->drop();
}

void ind::display::Client::handleInputServer()
{
	static packageClientServer lastOne = {MOVE, _clientId, dir::NONE};

	packageClientServer packet = {MOVE, _clientId, dir::NONE};
	if (_receiver.IsKeyDown(KEY_SPACE))
		packet = {SPAWNBOMB, _clientId, dir::NONE};
	else if (_receiver.IsKeyDown(KEY_UP))
		packet = {MOVE, _clientId, dir::UP};
	else if (_receiver.IsKeyDown(KEY_DOWN))
		packet = {MOVE, _clientId, dir::DOWN};
	else if (_receiver.IsKeyDown(KEY_LEFT))
		packet = {MOVE, _clientId, dir::LEFT};
	else if (_receiver.IsKeyDown(KEY_RIGHT))
		packet = {MOVE, _clientId, dir::RIGHT};
	if (packet.magicNumber == lastOne.magicNumber && packet.action == lastOne.action)
		return;
	lastOne = packet;
	_clientCom->sendData(packet);
}

void ind::display::Client::createEntity(const Task &task)
{
	if (_objectPool->getItem().find(task.uniqueId) == _objectPool->getItem().end()) {
		_objectPool->getItem()[task.uniqueId] = _entityFactory.createEntity(task.type, task.pos);
		if (task.type == Element::PLAYER) {
			_objectPool->getItem()[task.uniqueId]->setTexture(_driver->getTexture(ind::SKINS_PATH[_skins[task.uniqueId - 10] % ind::SKINS_PATH.size()].c_str()));
		} else if (task.type == Element::AI) {
			_objectPool->getItem()[task.uniqueId]->setTexture(_driver->getTexture(ind::AI_SKINS[_skins[task.uniqueId - 10] % ind::AI_SKINS.size()].c_str()));
		}
	}
}

void ind::display::Client::updateEntity(const Task &task)
{
	auto toUpdate = _objectPool->getItem().find(task.uniqueId);
	if (toUpdate != _objectPool->getItem().end()) {
		(*toUpdate).second->setPos(task.pos);
		(*toUpdate).second->setRotation(reinterpret_cast<const dir::directions &>(task.direction));
	}
}

void ind::display::Client::gameOver(const Task &task)
{
	if (task.uniqueId == _clientId) {
		_isDead = true;
		_gameEnded = true;
		_gameMenu->setVisible(true);
		_gameMenu->setText(L"YOU WIN");
		_text->setText(L"YOU WIN");
		_soundSettings->setEnabled(true);
		_buttonMenu->setEnabled(true);
	} else {
		_isDead = true;
		_gameEnded = true;
		_gameMenu->setVisible(true);
		_gameMenu->setText(L"YOU LOOSE");
		_text->setText(L"YOU LOOSE");
		_soundSettings->setEnabled(true);
		_buttonMenu->setEnabled(true);
	}
}

void ind::display::Client::deleteEntity(const Task &task)
{
	auto toRemove = _objectPool->getItem().find(task.uniqueId);
	if (toRemove != _objectPool->getItem().end()) {
		if (task.uniqueId == _clientId) {
			_isDead = true;
			_gameMenu->setVisible(true);
			_gameMenu->setText(L"YOU LOOSE");
			_text->setText(L"YOU LOOSE");
			_soundSettings->setEnabled(true);
		}
		if (toRemove->first < 20) {
			_dyingEntity.push_back(toRemove->second);
			toRemove->second->setDying();
		}
		_objectPool->getItem().erase(toRemove);
	}
}

void ind::display::Client::idleEntity(const Task &task)
{
	auto toIdle = _objectPool->getItem().find(task.uniqueId);
	if (toIdle != _objectPool->getItem().end()) {
		toIdle->second->setIdle();
	}
}

bool ind::display::Client::handleTask()
{
	Task tmp;
	if (_taskQueue->getTask(tmp)) {
		_objectPool->lockItem();
		switch (tmp.task) {

		case TypeTask::UNKNOWN:
			break;
		case TypeTask::CREATE:
			createEntity(tmp);
			break;
		case TypeTask::UPDATE:
			updateEntity(tmp);
			break;
		case TypeTask::DEL:
			deleteEntity(tmp);
			break;
		case TypeTask::IDLE:
			idleEntity(tmp);
			break;
		case TypeTask::GAMEOVER:
			gameOver(tmp);
			break;
		}
		_objectPool->unlockItem();
		return true;
	}
	return false;
}

void ind::display::Client::displayLoop()
{
	int lastFPS = -1;
	float lastSoundVolume = -1;
	auto image = _driver->getTexture(RESOURCE_DIR "media/GUI/background_game_blur.jpg");

	while (_device->run() && _clientCom->isOpen()) {
		while (!_gameEnded && handleTask());
		if (_device->isWindowActive()) {
			int fps = _driver->getFPS();
			if (lastFPS != fps) {
				irr::core::stringw str = L"Bomberman [";
				str += _driver->getName();
				str += "] FPS:";
				str += fps;

				_device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
			for (auto &entity : _dyingEntity) {
				if (entity->getFrame() > 95)
					entity->stopAnimation();
			}
			float soundVolumne = static_cast<float >(_soundSettings->getPos()) /
				static_cast<float >(_soundSettings->getMax());
			if (lastSoundVolume != soundVolumne) {
				lastSoundVolume = soundVolumne;
				_soundEngine->setSoundVolume(soundVolumne);
			}
			handleInputClient();
			if (!_gameMenu->isVisible() && !_isDead)
				handleInputServer();
			_driver->beginScene(true, true, irr::video::SColor(255, 66, 66, 66));
			_driver->draw2DImage(image, irr::core::position2d<irr::s32>(0, 0));
			_smgr->drawAll();
			_guienv->drawAll();
			_driver->endScene();
		} else {
			_device->yield();
		}
	}
}

void ind::display::Client::createFloor()
{
	irr::scene::IAnimatedMesh *floorMesh = _smgr->addHillPlaneMesh("floor", {24, 24}, {13, 15}, nullptr, 0, {0, 0},
		{13, 15});
	irr::scene::IAnimatedMeshSceneNode *floorNode = _smgr->addAnimatedMeshSceneNode(floorMesh);
	floorNode->setMaterialTexture(0, _driver->getTexture(RESOURCE_DIR"media/brick.png"));
	floorNode->setPosition({0, 0, 0});
	floorNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	floorNode->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, true);
}

void ind::display::Client::initModels()
{
	std::shared_ptr<AEntityClient> entityClient;
	for (auto &entity : EntityInfoG) {
		if (!EntityInfoG.at(entity.first).texture.empty())
			_driver->getTexture(EntityInfoG.at(entity.first).texture.c_str());
		irr::scene::IAnimatedMesh *mesh = _smgr->getMesh(EntityInfoG.at(entity.first).mesh.c_str());
		if (!mesh)
			throw std::runtime_error("Cannot open : " + EntityInfoG.at(entity.first).mesh);
		irr::scene::IAnimatedMeshSceneNode *node = _smgr->addAnimatedMeshSceneNode(mesh);
		if (!node)
			throw std::runtime_error("Create node with : " + EntityInfoG.at(entity.first).mesh);
		node->remove();
		entityClient.reset();
		entityClient = _entityFactory.createEntity(entity.first, {0, 0});
//		entityClient->setTexture(_driver->getTexture(RESOURCE_DIR "media/black.png"));
	}
	for (int i = 1; i < 8; ++i) {
		char buff[128];
		sprintf(buff, RESOURCE_DIR "media/stone%02i.png", i);
		_driver->getTexture(buff);
	}
	entityClient.reset();
}

void ind::display::Client::handleInputClient()
{
	static EKEY_CODE lastOne = KEY_NONE;

	if (_receiver.IsKeyDown(KEY_ESCAPE) && lastOne != KEY_ESCAPE) {
		_soundSettings->setEnabled(!_soundSettings->isEnabled());
		_gameMenu->setVisible(!_gameMenu->isVisible());
		lastOne = KEY_ESCAPE;
	} else if (!_receiver.IsKeyDown(KEY_ESCAPE)) {
		lastOne = KEY_NONE;
	}
}

ind::display::Client::~Client()
{
	_soundEngine->stopAllSounds();
}

void ind::display::Client::createMenu()
{
	_gameMenu = _guienv->addWindow(irr::core::rect<irr::s32>((_driver->getScreenSize().Width / 2) - 200,
		(_driver->getScreenSize().Height / 2) - 100, (_driver->getScreenSize().Width / 2) + 200,
		(_driver->getScreenSize().Height / 2) + 100), true, L"MENU");
	_guienv->addStaticText(L"Sound Volumne", irr::core::rect<irr::s32>(50, 70, 120, 90), false, true, _gameMenu);
	_soundSettings = _guienv->addScrollBar(true, irr::core::rect<irr::s32>(50, 90, 350, 110), _gameMenu);
	_buttonMenu = _guienv->addButton(irr::core::rect<irr::s32>(50, 130, 350, 160), _gameMenu, 10, L"Go to menu");
	_buttonMenu->setEnabled(false);
	_gameMenu->getCloseButton()->setVisible(false);
	_soundSettings->setEnabled(false);
	_soundSettings->setPos(100);
	_gameMenu->setVisible(false);
	_gameMenu->setText(L"MENU");
	_text = _guienv->addStaticText(L"MENU", irr::core::rect<irr::s32>(175, 30, 240, 60), false, true, _gameMenu);
}

