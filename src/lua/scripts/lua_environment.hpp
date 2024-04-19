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

#include "creatures/combat/combat.hpp"
#include "declarations.hpp"
#include "lua/scripts/luascript.hpp"
#include "items/weapons/weapons.hpp"

#include "lua/global/lua_timer_event_descr.hpp"

class AreaCombat;
class Combat;
class Cylinder;
class Game;
class GlobalFunctions;

class LuaEnvironment : public LuaScriptInterface {
public:
	static bool shuttingDown;

	LuaEnvironment();
	~LuaEnvironment() override;

	lua_State* getLuaState() override;

	// non-copyable
	LuaEnvironment(const LuaEnvironment &) = delete;
	LuaEnvironment &operator=(const LuaEnvironment &) = delete;

	static LuaEnvironment &getInstance() {
		return inject<LuaEnvironment>();
	}

	bool initState() override;
	bool reInitState() override;
	bool closeState() override;

	LuaScriptInterface* getTestInterface();

	std::shared_ptr<Combat> getCombatObject(uint32_t id) const;
	std::shared_ptr<Combat> createCombatObject(LuaScriptInterface* interface);
	void clearCombatObjects(LuaScriptInterface* interface);

	template <typename T>
	std::shared_ptr<T> createWeaponObject(LuaScriptInterface* interface) {
		auto weapon = std::make_shared<T>(interface);
		auto weaponId = ++lastWeaponId;
		weaponMap[weaponId] = weapon;
		weaponIdMap[interface].push_back(weaponId);
		return weapon;
	}

	template <typename T>
	std::shared_ptr<T> getWeaponObject(uint32_t id) const {
		auto it = weaponMap.find(id);
		if (it == weaponMap.end()) {
			return nullptr;
		}
		return it->second;
	}

	void clearWeaponObjects(LuaScriptInterface* interface) {
		auto it = weaponIdMap.find(interface);
		if (it == weaponIdMap.end()) {
			return;
		}

		it->second.clear();
		weaponMap.clear();
	}

	const std::unique_ptr<AreaCombat> &getAreaObject(uint32_t id) const;
	uint32_t createAreaObject(LuaScriptInterface* interface);
	void clearAreaObjects(LuaScriptInterface* interface);
	static bool isShuttingDown() {
		return shuttingDown;
	}

	void collectGarbage() const;

private:
	void executeTimerEvent(uint32_t eventIndex);

	phmap::flat_hash_map<uint32_t, LuaTimerEventDesc> timerEvents;
	uint32_t lastEventTimerId = 1;

	phmap::flat_hash_map<uint32_t, std::unique_ptr<AreaCombat>> areaMap;
	phmap::flat_hash_map<LuaScriptInterface*, std::vector<uint32_t>> areaIdMap;
	uint32_t lastAreaId = 0;

	phmap::flat_hash_map<uint32_t, std::shared_ptr<Combat>> combatMap;
	phmap::flat_hash_map<LuaScriptInterface*, std::vector<uint32_t>> combatIdMap;
	uint32_t lastCombatId = 0;

	phmap::flat_hash_map<uint32_t, std::shared_ptr<Weapon>> weaponMap;
	phmap::flat_hash_map<LuaScriptInterface*, std::vector<uint32_t>> weaponIdMap;
	uint32_t lastWeaponId = 0;

	LuaScriptInterface* testInterface = nullptr;

	friend class LuaScriptInterface;
	friend class GlobalFunctions;
	friend class CombatSpell;
};

constexpr auto g_luaEnvironment = LuaEnvironment::getInstance;
