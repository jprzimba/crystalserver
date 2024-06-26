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

#include "account/account.hpp"
#include "creatures/players/player.hpp"
#include "database/database.hpp"

using ItemBlockList = std::list<std::pair<int32_t, std::shared_ptr<Item>>>;

class IOLoginData {
public:
	static bool gameWorldAuthentication(const std::string &accountDescriptor, const std::string &sessionOrPassword, std::string &characterName, uint32_t &accountId, bool oldProcotol);
	static uint8_t getAccountType(uint32_t accountId);
	static void updateOnlineStatus(uint32_t guid, bool login);
	static bool loadPlayerById(std::shared_ptr<Player> player, uint32_t id, bool disableIrrelevantInfo = true);
	static bool loadPlayerByName(std::shared_ptr<Player> player, const std::string &name, bool disableIrrelevantInfo = true);
	static bool loadPlayer(std::shared_ptr<Player> player, DBResult_ptr result, bool disableIrrelevantInfo = false);
	static bool savePlayer(std::shared_ptr<Player> player);
	static uint32_t getGuidByName(const std::string &name);
	static bool getGuidByNameEx(uint32_t &guid, bool &specialVip, std::string &name);
	static std::string getNameByGuid(uint32_t guid);
	static bool formatPlayerName(std::string &name);
	static void increaseBankBalance(uint32_t guid, uint64_t bankBalance);
	static bool hasBiddedOnHouse(uint32_t guid);

	static std::forward_list<VIPEntry> getVIPEntries(uint32_t accountId);
	static void addVIPEntry(uint32_t accountId, uint32_t guid, const std::string &description, uint32_t icon, bool notify);
	static void editVIPEntry(uint32_t accountId, uint32_t guid, const std::string &description, uint32_t icon, bool notify);
	static void removeVIPEntry(uint32_t accountId, uint32_t guid);

private:
	static bool savePlayerGuard(std::shared_ptr<Player> player);
};
