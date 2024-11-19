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

#include "declarations.hpp"
class ConfigFunctions {
public:
	static void init(lua_State* L);

private:
	/**
	 * @brief Retrieves a float configuration value from the configuration manager, with an optional rounding.
	 *
	 * This function is a Lua binding used to get a float value from the configuration manager. It requires
	 * a key as the first argument, which should be a valid enumeration. An optional second boolean argument
	 * specifies whether the retrieved float should be rounded to two decimal places.
	 *
	 * @param L Pointer to the Lua state. The first argument must be a valid enum key, and the second argument (optional)
	 * can be a boolean indicating whether to round the result.
	 *
	 * @return Returns 1 after pushing the result onto the Lua stack, indicating the number of return values.
	 *
	 * @exception reportErrorFunc Throws an error if the first argument is not a valid enum.
	 *
	 * Usage:
	 *  local result = ConfigManager.getFloat(ConfigKey.SomeKey)
	 *  local result_rounded = ConfigManager.getFloat(ConfigKey.SomeKey, false)
	 *
	 * Detailed behavior:
	 * 1. Extracts the key from the first Lua stack argument as an enumeration of type `ConfigKey_t`.
	 * 2. Checks if the second argument is provided; if not, defaults to true for rounding.
	 * 3. Retrieves the float value associated with the key from the configuration manager.
	 * 4. If rounding is requested, rounds the value to two decimal places.
	 * 5. Logs the method call and the obtained value using the debug logger.
	 * 6. Pushes the final value (rounded or original) back onto the Lua stack.
	 * 7. Returns 1 to indicate a single return value.
	 */
	static int luaConfigManagerGetFloat(lua_State* L);
	static int luaConfigManagerGetBoolean(lua_State* L);
	static int luaConfigManagerGetNumber(lua_State* L);
	static int luaConfigManagerGetString(lua_State* L);
};