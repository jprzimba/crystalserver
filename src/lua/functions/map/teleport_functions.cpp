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

#include "game/movement/teleport.hpp"
#include "items/item.hpp"
#include "lua/functions/map/teleport_functions.hpp"

// Teleport
int TeleportFunctions::luaTeleportCreate(lua_State* L) {
	// Teleport(uid)
	uint32_t id = getNumber<uint32_t>(L, 2);

	std::shared_ptr<Item> item = getScriptEnv()->getItemByUID(id);
	if (item && item->getTeleport()) {
		pushUserdata(L, item);
		setMetatable(L, -1, "Teleport");
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int TeleportFunctions::luaTeleportGetDestination(lua_State* L) {
	// teleport:getDestination()
	std::shared_ptr<Teleport> teleport = getUserdataShared<Teleport>(L, 1);
	if (teleport) {
		pushPosition(L, teleport->getDestPos());
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int TeleportFunctions::luaTeleportSetDestination(lua_State* L) {
	// teleport:setDestination(position)
	std::shared_ptr<Teleport> teleport = getUserdataShared<Teleport>(L, 1);
	if (teleport) {
		teleport->setDestPos(getPosition(L, 2));
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}
