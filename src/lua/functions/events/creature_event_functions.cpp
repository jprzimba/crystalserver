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

#include "lua/creature/creatureevent.hpp"
#include "lua/functions/events/creature_event_functions.hpp"
#include "utils/tools.hpp"

int CreatureEventFunctions::luaCreateCreatureEvent(lua_State* L) {
	// CreatureEvent(eventName)
	auto creatureEvent = std::make_shared<CreatureEvent>(getScriptEnv()->getScriptInterface());
	creatureEvent->setName(getString(L, 2));
	pushUserdata<CreatureEvent>(L, creatureEvent);
	setMetatable(L, -1, "CreatureEvent");
	return 1;
}

int CreatureEventFunctions::luaCreatureEventType(lua_State* L) {
	// creatureevent:type(callback)
	const auto creatureEvent = getUserdataShared<CreatureEvent>(L, 1);
	if (creatureEvent) {
		std::string typeName = getString(L, 2);
		std::string tmpStr = asLowerCaseString(typeName);
		if (tmpStr == "login") {
			creatureEvent->setEventType(CREATURE_EVENT_LOGIN);
		} else if (tmpStr == "logout") {
			creatureEvent->setEventType(CREATURE_EVENT_LOGOUT);
		} else if (tmpStr == "think") {
			creatureEvent->setEventType(CREATURE_EVENT_THINK);
		} else if (tmpStr == "preparedeath") {
			creatureEvent->setEventType(CREATURE_EVENT_PREPAREDEATH);
		} else if (tmpStr == "death") {
			creatureEvent->setEventType(CREATURE_EVENT_DEATH);
		} else if (tmpStr == "kill") {
			creatureEvent->setEventType(CREATURE_EVENT_KILL);
		} else if (tmpStr == "advance") {
			creatureEvent->setEventType(CREATURE_EVENT_ADVANCE);
		} else if (tmpStr == "modalwindow") {
			creatureEvent->setEventType(CREATURE_EVENT_MODALWINDOW);
		} else if (tmpStr == "textedit") {
			creatureEvent->setEventType(CREATURE_EVENT_TEXTEDIT);
		} else if (tmpStr == "healthchange") {
			creatureEvent->setEventType(CREATURE_EVENT_HEALTHCHANGE);
		} else if (tmpStr == "manachange") {
			creatureEvent->setEventType(CREATURE_EVENT_MANACHANGE);
		} else if (tmpStr == "extendedopcode") {
			creatureEvent->setEventType(CREATURE_EVENT_EXTENDED_OPCODE);
		} else {
			g_logger().error("[CreatureEventFunctions::luaCreatureEventType] - "
							 "Invalid type for creature event: {}",
							 typeName);
			pushBoolean(L, false);
		}
		creatureEvent->setLoaded(true);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int CreatureEventFunctions::luaCreatureEventRegister(lua_State* L) {
	// creatureevent:register()
	const auto creatureEvent = getUserdataShared<CreatureEvent>(L, 1);
	if (creatureEvent) {
		if (!creatureEvent->isLoadedCallback()) {
			pushBoolean(L, false);
			return 1;
		}
		pushBoolean(L, g_creatureEvents().registerLuaEvent(creatureEvent));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int CreatureEventFunctions::luaCreatureEventOnCallback(lua_State* L) {
	// creatureevent:onLogin / logout / etc. (callback)
	const auto creatureEvent = getUserdataShared<CreatureEvent>(L, 1);
	if (creatureEvent) {
		if (!creatureEvent->loadCallback()) {
			pushBoolean(L, false);
			return 1;
		}
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}
