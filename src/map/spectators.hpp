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

#include "creatures/creature.hpp"

class Player;
class Monster;
class Npc;
struct Position;

struct SpectatorsCache {
	struct FloorData {
		std::optional<CreatureVector> floor;
		std::optional<CreatureVector> multiFloor;
	};

	int32_t minRangeX { 0 };
	int32_t maxRangeX { 0 };
	int32_t minRangeY { 0 };
	int32_t maxRangeY { 0 };

	FloorData creatures;
	FloorData players;
};

class Spectators {
public:
	static void clearCache();

	template <typename T>
		requires std::is_same_v<Creature, T> || std::is_same_v<Player, T>
	Spectators find(const Position &centerPos, bool multifloor = false, int32_t minRangeX = 0, int32_t maxRangeX = 0, int32_t minRangeY = 0, int32_t maxRangeY = 0) {
		constexpr bool onlyPlayers = std::is_same_v<T, Player>;
		return find(centerPos, multifloor, onlyPlayers, minRangeX, maxRangeX, minRangeY, maxRangeY);
	}

	template <typename T>
		requires std::is_base_of_v<Creature, T>
	Spectators filter();

	Spectators insert(const std::shared_ptr<Creature> &creature);
	Spectators insertAll(const CreatureVector &list);
	Spectators join(const Spectators &anotherSpectators) {
		return insertAll(anotherSpectators.creatures);
	}

	bool contains(const std::shared_ptr<Creature> &creature) const {
		return std::ranges::find(creatures, creature) != creatures.end();
	}

	bool erase(const std::shared_ptr<Creature> &creature) {
		return std::erase(creatures, creature) > 0;
	}

	bool empty() const noexcept {
		return creatures.empty();
	}

	size_t size() const noexcept {
		return creatures.size();
	}

	auto begin() const noexcept {
		return creatures.begin();
	}

	auto end() const noexcept {
		return creatures.end();
	}

	const auto &data() const noexcept {
		return creatures;
	}

private:
	static phmap::flat_hash_map<Position, SpectatorsCache> spectatorsCache;

	Spectators find(const Position &centerPos, bool multifloor = false, bool onlyPlayers = false, int32_t minRangeX = 0, int32_t maxRangeX = 0, int32_t minRangeY = 0, int32_t maxRangeY = 0);
	bool checkCache(const SpectatorsCache::FloorData &specData, bool onlyPlayers, const Position &centerPos, bool checkDistance, bool multifloor, int32_t minRangeX, int32_t maxRangeX, int32_t minRangeY, int32_t maxRangeY);

	CreatureVector creatures;
};

template <typename T>
	requires std::is_base_of_v<Creature, T>
Spectators Spectators::filter() {
	auto specs = Spectators();
	specs.creatures.reserve(creatures.size());

	for (const auto &c : creatures) {
		if constexpr (std::is_same_v<T, Player>) {
			if (c->getPlayer() != nullptr) {
				specs.insert(c);
			}
		} else if constexpr (std::is_same_v<T, Monster>) {
			if (c->getMonster() != nullptr) {
				specs.insert(c);
			}
		} else if constexpr (std::is_same_v<T, Npc>) {
			if (c->getNpc() != nullptr) {
				specs.insert(c);
			}
		}
	}

	return specs;
}
