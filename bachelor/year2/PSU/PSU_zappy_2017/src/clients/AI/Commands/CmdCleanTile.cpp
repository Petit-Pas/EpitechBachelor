//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// clean a tile
//

#include "CmdCleanTile.hpp"
#include "AllCommands.hpp"

Cmd::CleanTile::CleanTile(const std::shared_ptr<Connection> &con, ADrone &, const std::unordered_map<std::string, size_t> &target)
	: AComplexCommand(con), _target(target)
{
	_actions.push_back(std::make_shared<Cmd::Look>(con));
}

Cmd::CleanTile::~CleanTile()
{
}

void Cmd::CleanTile::updateCommands(ADrone &drone)
{
	if (_actions.size() == 0 && !_toDelete) {
		auto pos = drone.getPosition();
		auto tile = drone.getMap().accessTile(pos);
		int delta = 0;

		auto tileElems = tile.getElements();
		for (const auto &elems : tileElems) {
			if (elems.first == "reliability")
				continue;
			if (_target.find(elems.first) == _target.end())
				delta = elems.second;
			else if (_target.at(elems.first) < elems.second)
				delta = elems.second - _target.at(elems.first);
			else
				delta = 0;
			for (int i = 0; i < delta; i++) {
				_actions.push_back(std::make_shared<Cmd::Take>(_com, elems.first, drone));
			}
		}
		for (const auto &elems : _target) {
			if (tileElems.find(elems.first) == tileElems.end())
				delta = elems.second;
			else
				delta = elems.second - tileElems.at(elems.first);
			for (int i = 0; i < delta; i++) {
				_actions.push_back(std::make_shared<Cmd::Set>(_com, elems.first, drone));
			}
		}
		_toDelete = true;
		_actions.push_back(std::make_shared<Cmd::Incantate>(_com));
	}
}

bool Cmd::CleanTile::unusedMessage(const std::string &, ADrone &)
{
        return (false);
}
