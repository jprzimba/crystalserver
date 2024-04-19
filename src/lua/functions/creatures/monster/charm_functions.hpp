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

class CharmFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerSharedClass(L, "Charm", "", CharmFunctions::luaCharmCreate);
		registerMetaMethod(L, "Charm", "__eq", CharmFunctions::luaUserdataCompare);

		registerMethod(L, "Charm", "name", CharmFunctions::luaCharmName);
		registerMethod(L, "Charm", "description", CharmFunctions::luaCharmDescription);
		registerMethod(L, "Charm", "type", CharmFunctions::luaCharmType);
		registerMethod(L, "Charm", "points", CharmFunctions::luaCharmPoints);
		registerMethod(L, "Charm", "damageType", CharmFunctions::luaCharmDamageType);
		registerMethod(L, "Charm", "percentage", CharmFunctions::luaCharmPercentage);
		registerMethod(L, "Charm", "chance", CharmFunctions::luaCharmChance);
		registerMethod(L, "Charm", "messageCancel", CharmFunctions::luaCharmMessageCancel);
		registerMethod(L, "Charm", "messageServerLog", CharmFunctions::luaCharmMessageServerLog);
		registerMethod(L, "Charm", "effect", CharmFunctions::luaCharmEffect);
		registerMethod(L, "Charm", "castSound", CharmFunctions::luaCharmCastSound);
		registerMethod(L, "Charm", "impactSound", CharmFunctions::luaCharmImpactSound);
	}

private:
	static int luaCharmCreate(lua_State* L);
	static int luaCharmName(lua_State* L);
	static int luaCharmDescription(lua_State* L);
	static int luaCharmType(lua_State* L);
	static int luaCharmPoints(lua_State* L);
	static int luaCharmDamageType(lua_State* L);
	static int luaCharmPercentage(lua_State* L);
	static int luaCharmChance(lua_State* L);
	static int luaCharmMessageCancel(lua_State* L);
	static int luaCharmMessageServerLog(lua_State* L);
	static int luaCharmEffect(lua_State* L);
	static int luaCharmCastSound(lua_State* L);
	static int luaCharmImpactSound(lua_State* L);
};
