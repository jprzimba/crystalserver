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

class ResultFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerTable(L, "Result");
		registerMethod(L, "Result", "getNumber", ResultFunctions::luaResultGetNumber);
		registerMethod(L, "Result", "getString", ResultFunctions::luaResultGetString);
		registerMethod(L, "Result", "getStream", ResultFunctions::luaResultGetStream);
		registerMethod(L, "Result", "next", ResultFunctions::luaResultNext);
		registerMethod(L, "Result", "free", ResultFunctions::luaResultFree);
	}

private:
	static int luaResultFree(lua_State* L);
	static int luaResultGetNumber(lua_State* L);
	static int luaResultGetStream(lua_State* L);
	static int luaResultGetString(lua_State* L);
	static int luaResultNext(lua_State* L);
};
