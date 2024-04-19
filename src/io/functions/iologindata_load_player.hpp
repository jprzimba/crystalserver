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

#include "io/iologindata.hpp"

class IOLoginDataLoad : public IOLoginData {
public:
	static bool loadPlayerFirst(std::shared_ptr<Player> player, DBResult_ptr result);
	static bool preLoadPlayer(std::shared_ptr<Player> player, const std::string &name);
	static void loadPlayerExperience(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerBlessings(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerConditions(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerDefaultOutfit(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerSkullSystem(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerSkill(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerKills(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerGuild(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerStashItems(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerBestiaryCharms(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerInstantSpellList(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerInventoryItems(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerStoreInbox(std::shared_ptr<Player> player);
	static void loadPlayerDepotItems(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadRewardItems(std::shared_ptr<Player> player);
	static void loadPlayerInboxItems(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerStorageMap(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerVip(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerPreyClass(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerTaskHuntingClass(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerForgeHistory(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerBosstiary(std::shared_ptr<Player> player, DBResult_ptr result);
	static void loadPlayerInitializeSystem(std::shared_ptr<Player> player);
	static void loadPlayerUpdateSystem(std::shared_ptr<Player> player);

private:
	using ItemsMap = std::map<uint32_t, std::pair<std::shared_ptr<Item>, uint32_t>>;

	static void bindRewardBag(std::shared_ptr<Player> player, ItemsMap &rewardItemsMap);
	static void insertItemsIntoRewardBag(const ItemsMap &rewardItemsMap);

	static void loadItems(ItemsMap &itemsMap, DBResult_ptr result, const std::shared_ptr<Player> &player);
};
