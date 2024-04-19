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

class ShopFunctions final : LuaScriptInterface {
public:
	static void init(lua_State* L) {
		registerSharedClass(L, "Shop", "", ShopFunctions::luaCreateShop);
		registerMethod(L, "Shop", "setId", ShopFunctions::luaShopSetId);
		registerMethod(L, "Shop", "setIdFromName", ShopFunctions::luaShopSetIdFromName);
		registerMethod(L, "Shop", "setNameItem", ShopFunctions::luaShopSetNameItem);
		registerMethod(L, "Shop", "setCount", ShopFunctions::luaShopSetCount);
		registerMethod(L, "Shop", "setBuyPrice", ShopFunctions::luaShopSetBuyPrice);
		registerMethod(L, "Shop", "setSellPrice", ShopFunctions::luaShopSetSellPrice);
		registerMethod(L, "Shop", "setStorageKey", ShopFunctions::luaShopSetStorageKey);
		registerMethod(L, "Shop", "setStorageValue", ShopFunctions::luaShopSetStorageValue);
		registerMethod(L, "Shop", "addChildShop", ShopFunctions::luaShopAddChildShop);
	}

private:
	static int luaCreateShop(lua_State* L);
	static int luaShopSetId(lua_State* L);
	static int luaShopSetIdFromName(lua_State* L);
	static int luaShopSetNameItem(lua_State* L);
	static int luaShopSetCount(lua_State* L);
	static int luaShopSetBuyPrice(lua_State* L);
	static int luaShopSetSellPrice(lua_State* L);
	static int luaShopSetStorageKey(lua_State* L);
	static int luaShopSetStorageValue(lua_State* L);
	static int luaShopAddChildShop(lua_State* L);
};
