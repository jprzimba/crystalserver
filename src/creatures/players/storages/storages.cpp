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

#include "creatures/players/storages/storages.hpp"

#include "config/configmanager.hpp"

bool Storages::loadFromXML() {
	pugi::xml_document doc;
	std::string folder = "data/XML/storages.xml";
	pugi::xml_parse_result result = doc.load_file(folder.c_str());

	if (!result) {
		g_logger().error("[{}] parsed with errors", folder);
		g_logger().warn("Error description: {}", result.description());
		g_logger().warn("Error offset: {}", result.offset);
		return false;
	}

	std::vector<std::pair<uint32_t, uint32_t>> ranges;

	for (pugi::xml_node range : doc.child("storages").children("range")) {
		uint32_t start = range.attribute("start").as_uint();
		uint32_t end = range.attribute("end").as_uint();

		for (const auto &existingRange : ranges) {
			if ((start >= existingRange.first && start <= existingRange.second) || (end >= existingRange.first && end <= existingRange.second)) {
				g_logger().warn("[{}] Storage range from {} to {} conflicts with a previously defined range", __func__, start, end);
				continue;
			}
		}

		ranges.emplace_back(start, end);

		for (pugi::xml_node storage : range.children("storage")) {
			std::string name = storage.attribute("name").as_string();
			uint32_t key = storage.attribute("key").as_uint();

			for (char c : name) {
				if (std::isupper(c)) {
					g_logger().warn("[{}] Storage from storages.xml with name: {}, contains uppercase letters. Please use dot notation pattern", __func__, name);
					break;
				}
			}

			// Add the start of the range to the key
			key += start;

			if (key > end) {
				g_logger().error("[{}] Storage from storages.xml with name: {}, has key outside of its range", __func__, name);
				continue;
			}

			m_storageMap[name] = key;
		}
	}

	return true;
}

const std::map<std::string, uint32_t> &Storages::getStorageMap() const {
	return m_storageMap;
}
