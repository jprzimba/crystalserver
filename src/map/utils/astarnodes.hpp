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

struct Position;
class Creature;
class Tile;

struct AStarNode {
	AStarNode* parent;
	int_fast32_t f;
	uint16_t x, y;
};

class AStarNodes {
public:
	AStarNodes(uint32_t x, uint32_t y);

	AStarNode* createOpenNode(AStarNode* parent, uint32_t x, uint32_t y, int_fast32_t f);
	AStarNode* getBestNode();
	void closeNode(const AStarNode* node);
	void openNode(const AStarNode* node);
	int_fast32_t getClosedNodes() const;
	AStarNode* getNodeByPosition(uint32_t x, uint32_t y);

	static int_fast32_t getMapWalkCost(AStarNode* node, const Position &neighborPos, bool preferDiagonal = false);
	static int_fast32_t getTileWalkCost(const std::shared_ptr<Creature> &creature, const std::shared_ptr<Tile> &tile);

private:
	static constexpr int32_t MAX_NODES = 512;
	static constexpr int32_t MAP_NORMALWALKCOST = 10;
	static constexpr int32_t MAP_PREFERDIAGONALWALKCOST = 14;
	static constexpr int32_t MAP_DIAGONALWALKCOST = 25;

	AStarNode nodes[MAX_NODES];
	bool openNodes[MAX_NODES];
	phmap::flat_hash_map<uint32_t, AStarNode*> nodeTable;
	size_t curNode;
	int_fast32_t closedNodes;
};
