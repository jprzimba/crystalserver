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
#include "lua/functions/creatures/combat/condition_functions.hpp"
#include "lua/functions/creatures/combat/spell_functions.hpp"
#include "lua/functions/creatures/combat/variant_functions.hpp"

class CombatFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerSharedClass(L, "Combat", "", CombatFunctions::luaCombatCreate);
		registerMetaMethod(L, "Combat", "__eq", CombatFunctions::luaUserdataCompare);

		registerMethod(L, "Combat", "setParameter", CombatFunctions::luaCombatSetParameter);
		registerMethod(L, "Combat", "setFormula", CombatFunctions::luaCombatSetFormula);

		registerMethod(L, "Combat", "setArea", CombatFunctions::luaCombatSetArea);
		registerMethod(L, "Combat", "addCondition", CombatFunctions::luaCombatSetCondition);
		registerMethod(L, "Combat", "setCallback", CombatFunctions::luaCombatSetCallback);
		registerMethod(L, "Combat", "setOrigin", CombatFunctions::luaCombatSetOrigin);

		registerMethod(L, "Combat", "execute", CombatFunctions::luaCombatExecute);

		ConditionFunctions::init(L);
		SpellFunctions::init(L);
		VariantFunctions::init(L);
	}

private:
	static int luaCombatCreate(lua_State* L);

	static int luaCombatSetParameter(lua_State* L);
	static int luaCombatSetFormula(lua_State* L);

	static int luaCombatSetArea(lua_State* L);
	static int luaCombatSetCondition(lua_State* L);
	static int luaCombatSetCallback(lua_State* L);
	static int luaCombatSetOrigin(lua_State* L);

	static int luaCombatExecute(lua_State* L);
};
