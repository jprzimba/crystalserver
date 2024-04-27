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

#include "pch.hpp"

#include "creatures/players/grouping/groups.hpp"
#include "game/game.hpp"
#include "lua/functions/creatures/player/group_functions.hpp"

int GroupFunctions::luaGroupCreate(lua_State* L) {
	// Group(id)
	uint32_t id = getNumber<uint32_t>(L, 2);

	std::shared_ptr<Group> group = g_game().groups.getGroup(id);
	if (group) {
		pushUserdata<Group>(L, group);
		setMetatable(L, -1, "Group");
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetId(lua_State* L) {
	// group:getId()
	std::shared_ptr<Group> group = getUserdataShared<Group>(L, 1);
	if (group) {
		lua_pushnumber(L, group->id);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetName(lua_State* L) {
	// group:getName()
	std::shared_ptr<Group> group = getUserdataShared<Group>(L, 1);
	if (group) {
		pushString(L, group->name);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetFlags(lua_State* L) {
	// group:getFlags()
	std::shared_ptr<Group> group = getUserdataShared<Group>(L, 1);
	if (group) {
		std::bitset<magic_enum::enum_integer(PlayerFlags_t::FlagLast)> flags;
		for (uint8_t i = 0; i < magic_enum::enum_integer(PlayerFlags_t::FlagLast); ++i) {
			if (group->flags[i]) {
				flags.set(i);
			}
		}
		lua_pushnumber(L, static_cast<lua_Number>(flags.to_ulong()));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetAccess(lua_State* L) {
	// group:getAccess()
	std::shared_ptr<Group> group = getUserdataShared<Group>(L, 1);
	if (group) {
		pushBoolean(L, group->access);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetMaxDepotItems(lua_State* L) {
	// group:getMaxDepotItems()
	std::shared_ptr<Group> group = getUserdataShared<Group>(L, 1);
	if (group) {
		lua_pushnumber(L, group->maxDepotItems);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetMaxVipEntries(lua_State* L) {
	// group:getMaxVipEntries()
	std::shared_ptr<Group> group = getUserdataShared<Group>(L, 1);
	if (group) {
		lua_pushnumber(L, group->maxVipEntries);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupHasFlag(lua_State* L) {
	// group:hasFlag(flag)
	std::shared_ptr<Group> group = getUserdataShared<Group>(L, 1);
	if (group) {
		auto flag = static_cast<PlayerFlags_t>(getNumber<int>(L, 2));
		pushBoolean(L, group->flags[Groups::getFlagNumber(flag)]);
	} else {
		lua_pushnil(L);
	}
	return 1;
}