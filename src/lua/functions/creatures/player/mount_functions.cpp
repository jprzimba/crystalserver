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

#include "creatures/appearance/mounts/mounts.hpp"
#include "game/game.hpp"
#include "lua/functions/creatures/player/mount_functions.hpp"

int MountFunctions::luaCreateMount(lua_State* L) {
	// Mount(id or name)
	std::shared_ptr<Mount> mount;
	if (isNumber(L, 2)) {
		mount = g_game().mounts.getMountByID(getNumber<uint8_t>(L, 2));
	} else if (isString(L, 2)) {
		std::string mountName = getString(L, 2);
		mount = g_game().mounts.getMountByName(mountName);
	} else {
		mount = nullptr;
	}

	if (mount) {
		pushUserdata<Mount>(L, mount);
		setMetatable(L, -1, "Mount");
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int MountFunctions::luaMountGetName(lua_State* L) {
	// mount:getName()
	const std::shared_ptr<Mount> mount = getUserdataShared<Mount>(L, 1);
	if (mount) {
		pushString(L, mount->name);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int MountFunctions::luaMountGetId(lua_State* L) {
	// mount:getId()
	const std::shared_ptr<Mount> mount = getUserdataShared<Mount>(L, 1);
	if (mount) {
		lua_pushnumber(L, mount->id);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int MountFunctions::luaMountGetClientId(lua_State* L) {
	// mount:getClientId()
	const std::shared_ptr<Mount> mount = getUserdataShared<Mount>(L, 1);
	if (mount) {
		lua_pushnumber(L, mount->clientId);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int MountFunctions::luaMountGetSpeed(lua_State* L) {
	// mount:getSpeed()
	const std::shared_ptr<Mount> mount = getUserdataShared<Mount>(L, 1);
	if (mount) {
		lua_pushnumber(L, mount->speed);
	} else {
		lua_pushnil(L);
	}

	return 1;
}
