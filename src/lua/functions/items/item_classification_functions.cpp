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

#include "game/game.hpp"
#include "lua/functions/items/item_classification_functions.hpp"

int ItemClassificationFunctions::luaItemClassificationCreate(lua_State* L) {
	// ItemClassification(id)
	if (isNumber(L, 2)) {
		const ItemClassification* itemClassification = g_game().getItemsClassification(getNumber<uint8_t>(L, 2), false);
		if (itemClassification) {
			pushUserdata<const ItemClassification>(L, itemClassification);
			setMetatable(L, -1, "ItemClassification");
			pushBoolean(L, true);
		}
	}

	lua_pushnil(L);
	return 1;
}

int ItemClassificationFunctions::luaItemClassificationAddTier(lua_State* L) {
	// itemClassification:addTier(id, core, regularPrice, convergenceFusionPrice, convergenceTransferPrice)
	ItemClassification* itemClassification = getUserdata<ItemClassification>(L, 1);
	if (itemClassification) {
		itemClassification->addTier(
			getNumber<uint8_t>(L, 2),
			getNumber<uint8_t>(L, 3),
			getNumber<uint64_t>(L, 4),
			getNumber<uint64_t>(L, 5),
			getNumber<uint64_t>(L, 6)
		);
		pushBoolean(L, true);
	} else {
		lua_pushnil(L);
	}

	return 1;
}
