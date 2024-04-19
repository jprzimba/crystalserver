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

#include "pch.hpp"

#include "lua/callbacks/events_callbacks.hpp"

#include "lua/callbacks/event_callback.hpp"

/**
 * @class EventsCallbacks
 * @brief Class managing all event callbacks.
 *
 * @note This class is a singleton that holds all registered event callbacks.
 * @details It provides functions to add new callbacks and retrieve callbacks by type.
 */
EventsCallbacks::EventsCallbacks() = default;

EventsCallbacks::~EventsCallbacks() = default;

EventsCallbacks &EventsCallbacks::getInstance() {
	return inject<EventsCallbacks>();
}

void EventsCallbacks::addCallback(const std::shared_ptr<EventCallback> callback) {
	m_callbacks.push_back(callback);
}

std::vector<std::shared_ptr<EventCallback>> EventsCallbacks::getCallbacks() const {
	return m_callbacks;
}

std::vector<std::shared_ptr<EventCallback>> EventsCallbacks::getCallbacksByType(EventCallback_t type) const {
	std::vector<std::shared_ptr<EventCallback>> eventCallbacks;
	for (auto callback : getCallbacks()) {
		if (callback->getType() != type) {
			continue;
		}

		eventCallbacks.push_back(callback);
	}

	return eventCallbacks;
}

void EventsCallbacks::clear() {
	m_callbacks.clear();
}
