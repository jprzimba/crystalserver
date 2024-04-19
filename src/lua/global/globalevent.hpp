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

#include "utils/utils_definitions.hpp"
#include "lua/scripts/scripts.hpp"

class GlobalEvent;
using GlobalEventMap = std::map<std::string, std::shared_ptr<GlobalEvent>>;

class GlobalEvents final : public Scripts {
public:
	GlobalEvents();
	~GlobalEvents();

	// non-copyable
	GlobalEvents(const GlobalEvents &) = delete;
	GlobalEvents &operator=(const GlobalEvents &) = delete;

	static GlobalEvents &getInstance() {
		return inject<GlobalEvents>();
	}

	void startup() const;

	void timer();
	void think();
	void execute(GlobalEvent_t type) const;

	GlobalEventMap getEventMap(GlobalEvent_t type);

	bool registerLuaEvent(const std::shared_ptr<GlobalEvent> globalEvent);
	void clear();

private:
	GlobalEventMap thinkMap, serverMap, timerMap;
	uint64_t thinkEventId = 0, timerEventId = 0;
};

constexpr auto g_globalEvents = GlobalEvents::getInstance;

class GlobalEvent final : public Script {
public:
	explicit GlobalEvent(LuaScriptInterface* interface);

	bool executePeriodChange(LightState_t lightState, LightInfo lightInfo) const;
	bool executeRecord(uint32_t current, uint32_t old);
	bool executeEvent() const;

	GlobalEvent_t getEventType() const {
		return eventType;
	}
	void setEventType(GlobalEvent_t type) {
		eventType = type;
	}

	const std::string &getName() const {
		return name;
	}
	void setName(std::string eventName) {
		name = eventName;
	}
	uint32_t getInterval() const {
		return interval;
	}
	void setInterval(uint32_t eventInterval) {
		interval |= eventInterval;
	}

	int64_t getNextExecution() const {
		return nextExecution;
	}
	void setNextExecution(int64_t time) {
		nextExecution = time;
	}

private:
	GlobalEvent_t eventType = GLOBALEVENT_NONE;

	std::string getScriptTypeName() const override;

	std::string name;
	int64_t nextExecution = 0;
	uint32_t interval = 0;
};
