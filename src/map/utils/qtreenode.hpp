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

struct Floor;
class QTreeLeafNode;
class Creature;

class QTreeNode {
public:
	constexpr QTreeNode() = default;

	virtual ~QTreeNode() { }

	// non-copyable
	QTreeNode(const QTreeNode &) = delete;
	QTreeNode &operator=(const QTreeNode &) = delete;

	bool isLeaf() const {
		return leaf;
	}

	template <typename Leaf, typename Node>
	static Leaf getLeafStatic(Node node, uint32_t x, uint32_t y) {
		do {
			node = node->child[((x & 0x8000) >> 15) | ((y & 0x8000) >> 14)];
			if (!node) {
				return nullptr;
			}

			x <<= 1;
			y <<= 1;
		} while (!node->leaf);
		return static_cast<Leaf>(node);
	}

	QTreeLeafNode* getLeaf(uint32_t x, uint32_t y);
	QTreeLeafNode* getBestLeaf(uint32_t x, uint32_t y, uint32_t level);

	QTreeLeafNode* createLeaf(uint32_t x, uint32_t y, uint32_t level);

protected:
	QTreeNode* child[4] = {};
	bool leaf = false;
};

class QTreeLeafNode final : public QTreeNode {
public:
	QTreeLeafNode() {
		QTreeNode::leaf = true;
		newLeaf = true;
	}

	// non-copyable
	QTreeLeafNode(const QTreeLeafNode &) = delete;
	QTreeLeafNode &operator=(const QTreeLeafNode &) = delete;

	const std::unique_ptr<Floor> &createFloor(uint32_t z) {
		return array[z] ? array[z] : (array[z] = std::make_unique<Floor>(z));
	}

	const std::unique_ptr<Floor> &getFloor(uint8_t z) const {
		return array[z];
	}

	void addCreature(const std::shared_ptr<Creature> &c);
	void removeCreature(std::shared_ptr<Creature> c);

private:
	static bool newLeaf;
	QTreeLeafNode* leafS = nullptr;
	QTreeLeafNode* leafE = nullptr;

	std::unique_ptr<Floor> array[MAP_MAX_LAYERS] = {};

	std::vector<std::shared_ptr<Creature>> creature_list;
	std::vector<std::shared_ptr<Creature>> player_list;

	friend class Map;
	friend class MapCache;
	friend class QTreeNode;
	friend class Spectators;
};
