//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// IA definition
//

#ifndef IADEFINITION_HPP_
#define IADEFINITION_HPP_

#include "IASetting.hpp"

class IADefinition
{
public:
	IADefinition(ind::ia::Types);
	~IADefinition() = default;

	void setType(ind::ia::Types);
	ind::ia::Types getType() const;
	size_t getSkinId() const;
private:
	ind::ia::Types _type;
	size_t _skinId;
};

#endif /* !IADEFINITION_HPP_ */
