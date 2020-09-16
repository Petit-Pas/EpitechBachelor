/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** internal functions
*/

#include "MasterGUI.hpp"

plz::GUI::MasterGUI::MasterGUI(int amountThreads, unsigned int width, unsigned int height, unsigned int frameRate,
	const std::string &name
) : Master(amountThreads),
	_display(std::shared_ptr<plz::GUI::Display>(new plz::GUI::Display(width, height, frameRate, name)))
{
}

void plz::GUI::MasterGUI::manageCmdLoop()
{
	while (!endG) {
		std::vector<Task> commands;
		try {
			commands = _parser.parseLine(_display.get()->loop());
		} catch (std::runtime_error &e) {
			break;
		}
		for (auto &it : commands) {
			setOutfileName(it);
		}
		sendCommandList(commands);
		updateDisplay();
		usleep(100);
	}
	endG = true;
}

void plz::GUI::MasterGUI::updateDisplay()
{
	for (auto &it: _slaves) {
		_display.get()->updateSlave(it.id, it.data.usePercentage, it.data.waitingListState);
	}
}

void plz::GUI::MasterGUI::eraseFromSlaves(int id)
{
	_display.get()->setDeadSlave(id);
}

void plz::GUI::MasterGUI::sendCommandList(std::vector<plz::Task> toSend)
{
	refreshSlavesData();
	for (auto &it : toSend) {
		sendCommand(it);
		updateDisplay();
	}
}
