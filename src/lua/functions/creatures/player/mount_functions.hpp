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

#include "lua/scripts/luascript.hpp"

class MountFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerSharedClass(L, "Mount", "", MountFunctions::luaCreateMount);
		registerMetaMethod(L, "Mount", "__eq", MountFunctions::luaUserdataCompare);

		registerMethod(L, "Mount", "getName", MountFunctions::luaMountGetName);
		registerMethod(L, "Mount", "getId", MountFunctions::luaMountGetId);
		registerMethod(L, "Mount", "getClientId", MountFunctions::luaMountGetClientId);
		registerMethod(L, "Mount", "getSpeed", MountFunctions::luaMountGetSpeed);
	}

private:
	static int luaCreateMount(lua_State* L);
	static int luaMountGetName(lua_State* L);
	static int luaMountGetId(lua_State* L);
	static int luaMountGetClientId(lua_State* L);
	static int luaMountGetSpeed(lua_State* L);
};
