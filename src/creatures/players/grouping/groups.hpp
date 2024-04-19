////////////////////////////////////////////////////////////////////////
// Crystal Server - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#pragma once

#include "declarations.hpp"

struct Group {
	std::string name;
	std::array<bool, magic_enum::enum_integer(PlayerFlags_t::FlagLast)> flags { false };
	uint32_t maxDepotItems;
	uint32_t maxVipEntries;
	uint16_t id;
	bool access;
};

class Groups {
public:
	static uint8_t getFlagNumber(PlayerFlags_t playerFlags);
	static PlayerFlags_t getFlagFromNumber(uint8_t value);
	bool reload() const;
	bool load();
	Group* getGroup(uint16_t id);
	std::vector<Group> &getGroups() {
		return groups_vector;
	}

private:
	std::vector<Group> groups_vector;
};
