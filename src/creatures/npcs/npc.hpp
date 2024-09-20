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

#include "creatures/npcs/npcs.hpp"
#include "creatures/players/player.hpp"
#include "declarations.hpp"
#include "items/tile.hpp"
#include "lib/di/container.hpp"

class Creature;
class Game;
class SpawnNpc;

class Npc final : public Creature {
public:
	static std::shared_ptr<Npc> createNpc(const std::string &name);
	static int32_t despawnRange;
	static int32_t despawnRadius;

	explicit Npc(const std::shared_ptr<NpcType> &npcType);
	Npc() = default;

	// Singleton - ensures we don't accidentally copy it
	Npc(const Npc &) = delete;
	void operator=(const std::shared_ptr<Npc> &) = delete;

	static Npc &getInstance() {
		return inject<Npc>();
	}

	std::shared_ptr<Npc> getNpc() override {
		return static_self_cast<Npc>();
	}
	std::shared_ptr<const Npc> getNpc() const override {
		return static_self_cast<Npc>();
	}

	void setID() override {
		if (id == 0) {
			id = npcAutoID++;
		}
	}

	void removeList() override;
	void addList() override;

	const std::string &getName() const override {
		return npcType->name;
	}
	// Real npc name, set on npc creation "createNpcType(typeName)"
	const std::string &getTypeName() const override {
		return npcType->typeName;
	}
	const std::string &getNameDescription() const override {
		return npcType->nameDescription;
	}
	std::string getDescription(int32_t) override {
		return strDescription + '.';
	}

	void setName(std::string newName) {
		npcType->name = std::move(newName);
	}

	CreatureType_t getType() const override {
		return CREATURETYPE_NPC;
	}

	const Position &getMasterPos() const {
		return masterPos;
	}
	void setMasterPos(Position pos) {
		masterPos = pos;
	}

	uint8_t getSpeechBubble() const override {
		return npcType->info.speechBubble;
	}
	void setSpeechBubble(const uint8_t bubble) {
		npcType->info.speechBubble = bubble;
	}

	uint16_t getCurrency() const {
		return npcType->info.currencyId;
	}
	void setCurrency(uint16_t currency) {
		npcType->info.currencyId = currency;
	}

	std::vector<ShopBlock> getShopItemVector(uint32_t playerGUID) {
		if (playerGUID != 0) {
			auto it = shopPlayerMap.find(playerGUID);
			if (it != shopPlayerMap.end() && !it->second.empty()) {
				return it->second;
			}
		}

		return npcType->info.shopItemVector;
	}

	bool isPushable() override {
		return npcType->info.pushable;
	}

	bool isAttackable() const override {
		return false;
	}

	bool canInteract(const Position &pos, uint32_t range = 4);
	bool canSeeInvisibility() const override {
		return true;
	}
	RespawnType getRespawnType() const {
		return npcType->info.respawnType;
	}
	void setSpawnNpc(const std::shared_ptr<SpawnNpc> &newSpawn) {
		spawnNpc = newSpawn;
	}

	void setPlayerInteraction(uint32_t playerId, uint16_t topicId = 0);
	void removePlayerInteraction(std::shared_ptr<Player> player);
	void resetPlayerInteractions();

	bool isInteractingWithPlayer(uint32_t playerId) {
		if (playerInteractions.find(playerId) == playerInteractions.end()) {
			return false;
		}
		return true;
	}

	bool isPlayerInteractingOnTopic(uint32_t playerId, uint16_t topicId) {
		auto it = playerInteractions.find(playerId);
		if (it == playerInteractions.end()) {
			return false;
		}
		return it->second == topicId;
	}

	void onCreatureAppear(std::shared_ptr<Creature> creature, bool isLogin) override;
	void onRemoveCreature(std::shared_ptr<Creature> creature, bool isLogout) override;
	void onCreatureMove(const std::shared_ptr<Creature> &creature, const std::shared_ptr<Tile> &newTile, const Position &newPos, const std::shared_ptr<Tile> &oldTile, const Position &oldPos, bool teleport) override;
	void onCreatureSay(std::shared_ptr<Creature> creature, SpeakClasses type, const std::string &text) override;
	void onThink(uint32_t interval) override;
	void onPlayerBuyItem(std::shared_ptr<Player> player, uint16_t itemid, uint8_t count, uint16_t amount, bool ignore, bool inBackpacks);
	void onPlayerSellAllLoot(uint32_t playerId, uint16_t itemid, bool ignore, uint64_t totalPrice);
	void onPlayerSellItem(std::shared_ptr<Player> player, uint16_t itemid, uint8_t count, uint16_t amount, bool ignore);
	void onPlayerSellItem(std::shared_ptr<Player> player, uint16_t itemid, uint8_t count, uint16_t amount, bool ignore, uint64_t &totalPrice, std::shared_ptr<Cylinder> parent = nullptr);
	void onPlayerCheckItem(std::shared_ptr<Player> player, uint16_t itemid, uint8_t count);
	void onPlayerCloseChannel(std::shared_ptr<Creature> creature);
	void onPlacedCreature() override;

	bool canWalkTo(const Position &fromPos, Direction dir);
	bool getNextStep(Direction &nextDirection, uint32_t &flags) override;
	bool getRandomStep(Direction &moveDirection);

	void setNormalCreatureLight() override {
		internalLight = npcType->info.light;
	}

	void addShopPlayer(const std::shared_ptr<Player> &player, const std::vector<ShopBlock> &shopItems = {});
	void removeShopPlayer(const std::shared_ptr<Player> &player);
	void closeAllShopWindows();

	static uint32_t npcAutoID;

	void onCreatureWalk() override;

private:
	void onThinkYell(uint32_t interval);
	void onThinkWalk(uint32_t interval);
	void onThinkSound(uint32_t interval);

	bool isInSpawnRange(const Position &pos) const;

	std::string strDescription;

	std::map<uint32_t, uint16_t> playerInteractions;

	phmap::flat_hash_map<uint32_t, std::vector<ShopBlock>> shopPlayerMap;

	std::shared_ptr<NpcType> npcType;
	std::shared_ptr<SpawnNpc> spawnNpc;

	uint8_t speechBubble {};

	uint32_t yellTicks = 0;
	uint32_t walkTicks = 0;
	uint32_t soundTicks = 0;

	bool ignoreHeight {};

	phmap::flat_hash_set<std::shared_ptr<Player>> playerSpectators;
	Position masterPos;

	friend class LuaScriptInterface;
	friend class Map;

	void onPlayerAppear(std::shared_ptr<Player> player);
	void onPlayerDisappear(std::shared_ptr<Player> player);
	void manageIdle();
	void handlePlayerMove(std::shared_ptr<Player> player, const Position &newPos);
	void loadPlayerSpectators();
};

constexpr auto g_npc = Npc::getInstance;
