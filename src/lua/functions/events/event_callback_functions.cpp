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

#include "lua/functions/events/event_callback_functions.hpp"

#include "lua/callbacks/event_callback.hpp"
#include "lua/callbacks/events_callbacks.hpp"
#include "utils/tools.hpp"
#include "items/item.hpp"
#include "creatures/players/player.hpp"

/**
 * @class EventCallbackFunctions
 * @brief Class providing Lua functions for manipulating event callbacks.
 *
 * @note This class is derived from LuaScriptInterface and defines several static functions that are exposed to the Lua environment.
 * @details It allows Lua scripts to create, configure, and register event callbacks.
 *
 * @see LuaScriptInterface
 */

void EventCallbackFunctions::init(lua_State* luaState) {
	registerSharedClass(luaState, "EventCallback", "", EventCallbackFunctions::luaEventCallbackCreate);
	registerMethod(luaState, "EventCallback", "type", EventCallbackFunctions::luaEventCallbackType);
	registerMethod(luaState, "EventCallback", "register", EventCallbackFunctions::luaEventCallbackRegister);
}

int EventCallbackFunctions::luaEventCallbackCreate(lua_State* luaState) {
	const auto eventCallback = std::make_shared<EventCallback>(getScriptEnv()->getScriptInterface());
	pushUserdata<EventCallback>(luaState, eventCallback);
	setMetatable(luaState, -1, "EventCallback");
	return 1;
}

int EventCallbackFunctions::luaEventCallbackType(lua_State* luaState) {
	auto callback = getUserdataShared<EventCallback>(luaState, 1);
	if (!callback) {
		reportErrorFunc("EventCallback is nil");
		return 0;
	}

	auto typeName = getString(luaState, 2);
	auto lowerTypeName = asLowerCaseString(typeName);
	bool found = false;
	for (auto enumValue : magic_enum::enum_values<EventCallback_t>()) {
		std::string enumName = std::string(magic_enum::enum_name(enumValue));
		auto lowerEnumTypeName = asLowerCaseString(enumName);

		if (lowerEnumTypeName == lowerTypeName) {
			callback->setType(enumValue);
			callback->setScriptTypeName(typeName);
			found = true;
			break;
		}
	}

	if (!found) {
		g_logger().error("[{}] No valid event name: {}", __func__, typeName);
		pushBoolean(luaState, false);
	}

	pushBoolean(luaState, true);
	return 1;
}

int EventCallbackFunctions::luaEventCallbackRegister(lua_State* luaState) {
	auto callback = getUserdataShared<EventCallback>(luaState, 1);
	if (!callback) {
		reportErrorFunc("EventCallback is nil, failed to register script");
		return 0;
	}

	if (!callback->isLoadedCallback()) {
		return 0;
	}

	g_callbacks().addCallback(callback);
	pushBoolean(luaState, true);
	return 1;
}

// Callback functions
int EventCallbackFunctions::luaEventCallbackLoad(lua_State* luaState) {
	auto callback = getUserdataShared<EventCallback>(luaState, 1);
	if (!callback) {
		reportErrorFunc("EventCallback is nil");
		return 1;
	}

	if (!callback->loadCallback()) {
		reportErrorFunc("Cannot load callback");
		return 1;
	}

	callback->setLoadedCallback(true);
	pushBoolean(luaState, true);
	return 1;
}
