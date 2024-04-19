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

#include "creatures/npcs/npcs.hpp"
#include "lua/functions/creatures/npc/shop_functions.hpp"

int ShopFunctions::luaCreateShop(lua_State* L) {
	// Shop() will create a new shop item
	pushUserdata<Shop>(L, std::make_shared<Shop>());
	setMetatable(L, -1, "Shop");
	return 1;
}

int ShopFunctions::luaShopSetId(lua_State* L) {
	// shop:setId(id)

	if (const auto &shop = getUserdataShared<Shop>(L, 1)) {
		if (isNumber(L, 2)) {
			shop->shopBlock.itemId = getNumber<uint16_t>(L, 2);
			pushBoolean(L, true);
		} else {
			g_logger().warn("[ShopFunctions::luaShopSetId] - "
							"Unknown shop item shop, int value expected");
			lua_pushnil(L);
		}
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ShopFunctions::luaShopSetIdFromName(lua_State* L) {
	// shop:setIdFromName(name)
	const auto &shop = getUserdataShared<Shop>(L, 1);
	if (shop && isString(L, 2)) {
		auto name = getString(L, 2);
		auto ids = Item::items.nameToItems.equal_range(asLowerCaseString(name));

		if (ids.first == Item::items.nameToItems.cend()) {
			g_logger().warn("[ShopFunctions::luaShopSetIdFromName] - "
							"Unknown shop item {}",
							name);
			lua_pushnil(L);
			return 1;
		}

		if (std::next(ids.first) != ids.second) {
			g_logger().warn("[ShopFunctions::luaShopSetIdFromName] - "
							"Non-unique shop item {}",
							name);
			lua_pushnil(L);
			return 1;
		}

		shop->shopBlock.itemId = ids.first->second;
		pushBoolean(L, true);
	} else {
		g_logger().warn("[ShopFunctions::luaShopSetIdFromName] - "
						"Unknown shop item shop, string value expected");
		lua_pushnil(L);
	}
	return 1;
}

int ShopFunctions::luaShopSetNameItem(lua_State* L) {
	// shop:setNameItem(name)
	if (const auto &shop = getUserdataShared<Shop>(L, 1)) {
		shop->shopBlock.itemName = getString(L, 2);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ShopFunctions::luaShopSetCount(lua_State* L) {
	// shop:setCount(count)
	if (const auto &shop = getUserdataShared<Shop>(L, 1)) {
		shop->shopBlock.itemSubType = getNumber<uint32_t>(L, 2);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ShopFunctions::luaShopSetBuyPrice(lua_State* L) {
	// shop:setBuyPrice(price)
	if (const auto &shop = getUserdataShared<Shop>(L, 1)) {
		shop->shopBlock.itemBuyPrice = getNumber<uint32_t>(L, 2);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ShopFunctions::luaShopSetSellPrice(lua_State* L) {
	// shop:setSellPrice(chance)
	if (const auto &shop = getUserdataShared<Shop>(L, 1)) {
		shop->shopBlock.itemSellPrice = getNumber<uint32_t>(L, 2);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ShopFunctions::luaShopSetStorageKey(lua_State* L) {
	// shop:setStorageKey(storage)
	if (const auto &shop = getUserdataShared<Shop>(L, 1)) {
		shop->shopBlock.itemStorageKey = getNumber<uint32_t>(L, 2);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ShopFunctions::luaShopSetStorageValue(lua_State* L) {
	// shop:setStorageValue(value)
	if (const auto &shop = getUserdataShared<Shop>(L, 1)) {
		shop->shopBlock.itemStorageValue = getNumber<uint32_t>(L, 2);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int ShopFunctions::luaShopAddChildShop(lua_State* L) {
	// shop:addChildShop(shop)
	if (const auto &shop = getUserdataShared<Shop>(L, 1)) {
		shop->shopBlock.childShop.push_back(getUserdataShared<Shop>(L, 2)->shopBlock);
	} else {
		lua_pushnil(L);
	}
	return 1;
}
