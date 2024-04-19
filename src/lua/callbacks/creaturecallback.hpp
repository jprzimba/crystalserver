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

class Creature;

class CreatureCallback {
public:
	CreatureCallback(LuaScriptInterface* scriptInterface, std::shared_ptr<Creature> targetCreature) :
		scriptInterface(scriptInterface), m_targetCreature(targetCreature) {};
	~CreatureCallback() { }

	bool startScriptInterface(int32_t scriptId);

	void pushSpecificCreature(std::shared_ptr<Creature> creature);

	bool persistLuaState() {
		return params > 0 && scriptInterface->callFunction(params);
	}

	void pushCreature(std::shared_ptr<Creature> creature) {
		params++;
		LuaScriptInterface::pushUserdata<Creature>(L, creature);
		LuaScriptInterface::setCreatureMetatable(L, -1, creature);
	}

	void pushPosition(const Position &position, int32_t stackpos = 0) {
		params++;
		LuaScriptInterface::pushPosition(L, position, stackpos);
	}

	void pushNumber(int32_t number) {
		params++;
		lua_pushnumber(L, number);
	}

	void pushString(const std::string &str) {
		params++;
		LuaScriptInterface::pushString(L, str);
	}

	void pushBoolean(const bool str) {
		params++;
		LuaScriptInterface::pushBoolean(L, str);
	}

protected:
	static std::string getCreatureClass(std::shared_ptr<Creature> creature);

private:
	LuaScriptInterface* scriptInterface;
	std::weak_ptr<Creature> m_targetCreature;
	uint32_t params = 0;
	lua_State* L = nullptr;
};
