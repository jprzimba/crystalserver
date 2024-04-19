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

class IOLoginDataSave : public IOLoginData {
public:
	static bool savePlayerFirst(std::shared_ptr<Player> player);
	static bool savePlayerStash(std::shared_ptr<Player> player);
	static bool savePlayerSpells(std::shared_ptr<Player> player);
	static bool savePlayerKills(std::shared_ptr<Player> player);
	static bool savePlayerBestiarySystem(std::shared_ptr<Player> player);
	static bool savePlayerItem(std::shared_ptr<Player> player);
	static bool savePlayerDepotItems(std::shared_ptr<Player> player);
	static bool saveRewardItems(std::shared_ptr<Player> player);
	static bool savePlayerInbox(std::shared_ptr<Player> player);
	static bool savePlayerPreyClass(std::shared_ptr<Player> player);
	static bool savePlayerTaskHuntingClass(std::shared_ptr<Player> player);
	static bool savePlayerForgeHistory(std::shared_ptr<Player> player);
	static bool savePlayerBosstiary(std::shared_ptr<Player> player);
	static bool savePlayerStorage(std::shared_ptr<Player> player);

protected:
	using ItemBlockList = std::list<std::pair<int32_t, std::shared_ptr<Item>>>;
	using ItemDepotList = std::list<std::pair<int32_t, std::shared_ptr<Item>>>;
	using ItemRewardList = std::list<std::pair<int32_t, std::shared_ptr<Item>>>;
	using ItemInboxList = std::list<std::pair<int32_t, std::shared_ptr<Item>>>;

	static bool saveItems(std::shared_ptr<Player> player, const ItemBlockList &itemList, DBInsert &query_insert, PropWriteStream &stream);
};
