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

#include "map/map_const.hpp"

class Creature;
class Tile;
struct BasicTile;

struct Floor {
	explicit Floor(uint8_t z) :
		z(z) { }

	std::shared_ptr<Tile> getTile(uint16_t x, uint16_t y) const {
		std::shared_lock sl(mutex);
		return tiles[x & SECTOR_MASK][y & SECTOR_MASK].first;
	}

	void setTile(uint16_t x, uint16_t y, std::shared_ptr<Tile> tile) {
		tiles[x & SECTOR_MASK][y & SECTOR_MASK].first = tile;
	}

	std::shared_ptr<BasicTile> getTileCache(uint16_t x, uint16_t y) const {
		std::shared_lock sl(mutex);
		return tiles[x & SECTOR_MASK][y & SECTOR_MASK].second;
	}

	void setTileCache(uint16_t x, uint16_t y, const std::shared_ptr<BasicTile> &newTile) {
		tiles[x & SECTOR_MASK][y & SECTOR_MASK].second = newTile;
	}

	const auto &getTiles() const {
		return tiles;
	}

	uint8_t getZ() const {
		return z;
	}

	auto &getMutex() const {
		return mutex;
	}

private:
	std::pair<std::shared_ptr<Tile>, std::shared_ptr<BasicTile>> tiles[SECTOR_SIZE][SECTOR_SIZE] = {};
	mutable std::shared_mutex mutex;
	uint8_t z { 0 };
};

class MapSector {
public:
	MapSector() = default;

	// non-copyable
	MapSector(const MapSector &) = delete;
	MapSector &operator=(const MapSector &) = delete;

	// non-moveable
	MapSector(const MapSector &&) = delete;
	MapSector &operator=(const MapSector &&) = delete;

	const std::unique_ptr<Floor> &createFloor(uint32_t z) {
		return floors[z] ? floors[z] : (floors[z] = std::make_unique<Floor>(z));
	}

	const std::unique_ptr<Floor> &getFloor(uint8_t z) const {
		return floors[z];
	}

	void addCreature(const std::shared_ptr<Creature> &c);
	void removeCreature(const std::shared_ptr<Creature> &c);

private:
	static bool newSector;
	MapSector* sectorS = nullptr;
	MapSector* sectorE = nullptr;
	std::vector<std::shared_ptr<Creature>> creature_list;
	std::vector<std::shared_ptr<Creature>> player_list;
	std::unique_ptr<Floor> floors[MAP_MAX_LAYERS] = {};
	uint32_t floorBits = 0;

	friend class Spectators;
	friend class MapCache;
};