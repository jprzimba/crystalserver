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

class CreatureEventFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerSharedClass(L, "CreatureEvent", "", CreatureEventFunctions::luaCreateCreatureEvent);
		registerMethod(L, "CreatureEvent", "type", CreatureEventFunctions::luaCreatureEventType);
		registerMethod(L, "CreatureEvent", "register", CreatureEventFunctions::luaCreatureEventRegister);
		registerMethod(L, "CreatureEvent", "onLogin", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onLogout", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onThink", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onPrepareDeath", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onDeath", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onKill", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onAdvance", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onModalWindow", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onTextEdit", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onHealthChange", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onManaChange", CreatureEventFunctions::luaCreatureEventOnCallback);
		registerMethod(L, "CreatureEvent", "onExtendedOpcode", CreatureEventFunctions::luaCreatureEventOnCallback);
	}

private:
	static int luaCreateCreatureEvent(lua_State* L);
	static int luaCreatureEventType(lua_State* L);
	static int luaCreatureEventRegister(lua_State* L);
	static int luaCreatureEventOnCallback(lua_State* L);
};
