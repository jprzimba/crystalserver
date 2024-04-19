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

#include "lua/functions/core/game/config_functions.hpp"

#include "config/configmanager.hpp"

void ConfigFunctions::init(lua_State* L) {
	registerTable(L, "configManager");
	registerMethod(L, "configManager", "getString", luaConfigManagerGetString);
	registerMethod(L, "configManager", "getNumber", luaConfigManagerGetNumber);
	registerMethod(L, "configManager", "getBoolean", luaConfigManagerGetBoolean);
	registerMethod(L, "configManager", "getFloat", luaConfigManagerGetFloat);

#define registerMagicEnumIn(L, tableName, enumValue)         \
	do {                                                     \
		auto number = magic_enum::enum_integer(enumValue);   \
		auto name = magic_enum::enum_name(enumValue).data(); \
		registerVariable(L, tableName, name, value);         \
	} while (0)
	registerTable(L, "configKeys");
	for (auto value : magic_enum::enum_values<ConfigKey_t>()) {
		auto enumName = magic_enum::enum_name(value).data();
		if (enumName) {
			registerMagicEnumIn(L, "configKeys", value);
			g_logger().debug("Registering ConfigManager enum name '{}' value '{}' to lua", enumName, fmt::underlying(value));
		}
	}
#undef registerMagicEnumIn
}

int ConfigFunctions::luaConfigManagerGetString(lua_State* L) {
	auto key = getNumber<ConfigKey_t>(L, -1);
	if (!key) {
		reportErrorFunc("Wrong enum");
		return 1;
	}

	pushString(L, g_configManager().getString(getNumber<ConfigKey_t>(L, -1), __FUNCTION__));
	return 1;
}

int ConfigFunctions::luaConfigManagerGetNumber(lua_State* L) {
	auto key = getNumber<ConfigKey_t>(L, -1);
	if (!key) {
		reportErrorFunc("Wrong enum");
		return 1;
	}

	lua_pushnumber(L, g_configManager().getNumber(getNumber<ConfigKey_t>(L, -1), __FUNCTION__));
	return 1;
}

int ConfigFunctions::luaConfigManagerGetBoolean(lua_State* L) {
	auto key = getNumber<ConfigKey_t>(L, -1);
	if (!key) {
		reportErrorFunc("Wrong enum");
		return 1;
	}

	pushBoolean(L, g_configManager().getBoolean(getNumber<ConfigKey_t>(L, -1), __FUNCTION__));
	return 1;
}

int ConfigFunctions::luaConfigManagerGetFloat(lua_State* L) {
	auto key = getNumber<ConfigKey_t>(L, -1);
	if (!key) {
		reportErrorFunc("Wrong enum");
		return 1;
	}

	lua_pushnumber(L, g_configManager().getFloat(key, __FUNCTION__));
	return 1;
}
