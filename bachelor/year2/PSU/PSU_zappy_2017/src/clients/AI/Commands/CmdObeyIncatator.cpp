//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// master of puppets
//

#include "CmdObeyIncatator.hpp"
#include "AllCommands.hpp"
#include "CmdSet.hpp"

Cmd::ObeyIncantator::ObeyIncantator(const std::shared_ptr<Connection> &con, ADrone &drone)
	: AComplexCommand(con)
{
	_actions.push_back(std::make_shared<Broadcast>(_com, "INCANT_HERE " + std::to_string(drone.getId())));
}

/**
 * L'immobiliser temps que l'incantation est pas finis
 */
void Cmd::ObeyIncantator::updateCommands(ADrone &drone)
{
	if (_actions.empty() && !_toDelete)
		_actions.push_back(std::make_shared<Cmd::SharedInventory>(_com, drone));
}

bool Cmd::ObeyIncantator::unusedMessage(const std::string &serverMsg, ADrone &drone)
{
	if (::Broadcast::Broadcast::isMessage(serverMsg)) {
		::Broadcast::Message message(serverMsg);
		const auto &params = message.getParams();
		if (message.getFunction() == "OBEY" && params.size() > 0 && params[0] == std::to_string(drone.getId())) {
			for (size_t i = 1; i < params.size(); i += 2) {
				const auto nbOfDrop = std::stoul(params[2]);
				for (size_t j = 0; j < nbOfDrop; ++j)
					_actions.push_back(std::make_shared<Cmd::Set>(_com, params[i], drone));
			}
			_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, "DROP_END " + std::to_string(drone.getId())));
			return true;
		} else if (message.getFunction() == "INCANT_OVER" && params.size() > 0 && params[0] == std::to_string(drone.getId())) {
			_toDelete = true;
			return (true);
		}
	}
	return false;
}
