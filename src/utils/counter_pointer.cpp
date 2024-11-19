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

#include "utils/counter_pointer.hpp"

#include "lib/di/container.hpp"
#include "lib/logging/logger.hpp"

SharedPtrManager &SharedPtrManager::getInstance() {
	static SharedPtrManager instance;
	return instance;
}

void SharedPtrManager::countAllReferencesAndClean() {
	for (auto it = m_sharedPtrMap.begin(); it != m_sharedPtrMap.end();) {
		const auto &sptr = it->second.lock();
		if (sptr) {
			g_logger().debug("Counting references of shared_ptr ({}): {}", it->first, sptr.use_count());
			++it;
		} else {
			g_logger().debug("Object {} was destroyed and will be removed from the map.", it->first);
			it = m_sharedPtrMap.erase(it);
		}
	}
}