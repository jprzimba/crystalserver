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

class ImbuementFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerClass(L, "Imbuement", "", ImbuementFunctions::luaCreateImbuement);
		registerMetaMethod(L, "Imbuement", "__eq", ImbuementFunctions::luaUserdataCompare);

		registerMethod(L, "Imbuement", "getName", ImbuementFunctions::luaImbuementGetName);
		registerMethod(L, "Imbuement", "getId", ImbuementFunctions::luaImbuementGetId);
		registerMethod(L, "Imbuement", "getItems", ImbuementFunctions::luaImbuementGetItems);
		registerMethod(L, "Imbuement", "getBase", ImbuementFunctions::luaImbuementGetBase);
		registerMethod(L, "Imbuement", "getCategory", ImbuementFunctions::luaImbuementGetCategory);
		registerMethod(L, "Imbuement", "isPremium", ImbuementFunctions::luaImbuementIsPremium);
		registerMethod(L, "Imbuement", "getElementDamage", ImbuementFunctions::luaImbuementGetElementDamage);
		registerMethod(L, "Imbuement", "getCombatType", ImbuementFunctions::luaImbuementGetCombatType);
	}

private:
	static int luaCreateImbuement(lua_State* L);
	static int luaImbuementGetName(lua_State* L);
	static int luaImbuementGetId(lua_State* L);
	static int luaImbuementGetItems(lua_State* L);
	static int luaImbuementGetBase(lua_State* L);
	static int luaImbuementGetCategory(lua_State* L);
	static int luaImbuementIsPremium(lua_State* L);
	static int luaImbuementGetElementDamage(lua_State* L);
	static int luaImbuementGetCombatType(lua_State* L);
};
