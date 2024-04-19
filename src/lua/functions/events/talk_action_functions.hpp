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

class TalkActionFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerSharedClass(L, "TalkAction", "", TalkActionFunctions::luaCreateTalkAction);
		registerMethod(L, "TalkAction", "onSay", TalkActionFunctions::luaTalkActionOnSay);
		registerMethod(L, "TalkAction", "groupType", TalkActionFunctions::luaTalkActionGroupType);
		registerMethod(L, "TalkAction", "register", TalkActionFunctions::luaTalkActionRegister);
		registerMethod(L, "TalkAction", "separator", TalkActionFunctions::luaTalkActionSeparator);
		registerMethod(L, "TalkAction", "getName", TalkActionFunctions::luaTalkActionGetName);
		registerMethod(L, "TalkAction", "getGroupType", TalkActionFunctions::luaTalkActionGetGroupType);
	}

private:
	static int luaCreateTalkAction(lua_State* L);
	static int luaTalkActionOnSay(lua_State* L);
	static int luaTalkActionGroupType(lua_State* L);
	static int luaTalkActionRegister(lua_State* L);
	static int luaTalkActionSeparator(lua_State* L);
	static int luaTalkActionGetName(lua_State* L);
	static int luaTalkActionGetGroupType(lua_State* L);
};
