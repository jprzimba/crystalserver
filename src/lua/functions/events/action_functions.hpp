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

class ActionFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerSharedClass(L, "Action", "", ActionFunctions::luaCreateAction);
		registerMethod(L, "Action", "onUse", ActionFunctions::luaActionOnUse);
		registerMethod(L, "Action", "register", ActionFunctions::luaActionRegister);
		registerMethod(L, "Action", "id", ActionFunctions::luaActionItemId);
		registerMethod(L, "Action", "aid", ActionFunctions::luaActionActionId);
		registerMethod(L, "Action", "uid", ActionFunctions::luaActionUniqueId);
		registerMethod(L, "Action", "position", ActionFunctions::luaActionPosition);
		registerMethod(L, "Action", "allowFarUse", ActionFunctions::luaActionAllowFarUse);
		registerMethod(L, "Action", "blockWalls", ActionFunctions::luaActionBlockWalls);
		registerMethod(L, "Action", "checkFloor", ActionFunctions::luaActionCheckFloor);
		registerMethod(L, "Action", "position", ActionFunctions::luaActionPosition);
	}

private:
	static int luaCreateAction(lua_State* L);
	static int luaActionOnUse(lua_State* L);
	static int luaActionRegister(lua_State* L);
	static int luaActionItemId(lua_State* L);
	static int luaActionActionId(lua_State* L);
	static int luaActionUniqueId(lua_State* L);
	static int luaActionPosition(lua_State* L);
	static int luaActionAllowFarUse(lua_State* L);
	static int luaActionBlockWalls(lua_State* L);
	static int luaActionCheckFloor(lua_State* L);
};
