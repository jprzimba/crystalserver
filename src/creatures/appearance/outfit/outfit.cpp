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

#include "creatures/appearance/outfit/outfit.hpp"
#include "utils/pugicast.hpp"
#include "utils/tools.hpp"
#include "game/game.hpp"

bool Outfits::loadFromXml() {
	pugi::xml_document doc;
	auto folder = g_configManager().getString(CORE_DIRECTORY, __FUNCTION__) + "/XML/outfits.xml";
	pugi::xml_parse_result result = doc.load_file(folder.c_str());
	if (!result) {
		printXMLError(__FUNCTION__, folder, result);
		return false;
	}

	for (auto outfitNode : doc.child("outfits").children()) {
		pugi::xml_attribute attr;
		if ((attr = outfitNode.attribute("enabled")) && !attr.as_bool()) {
			continue;
		}

		if (!(attr = outfitNode.attribute("type"))) {
			g_logger().warn("[Outfits::loadFromXml] - Missing outfit type");
			continue;
		}

		uint16_t type = pugi::cast<uint16_t>(attr.value());
		if (type > PLAYERSEX_LAST) {
			g_logger().warn("[Outfits::loadFromXml] - Invalid outfit type {}", type);
			continue;
		}

		pugi::xml_attribute lookTypeAttribute = outfitNode.attribute("looktype");
		if (!lookTypeAttribute) {
			g_logger().warn("[Outfits::loadFromXml] - Missing looktype on outfit");
			continue;
		}

		if (uint16_t lookType = pugi::cast<uint16_t>(lookTypeAttribute.value());
			g_configManager().getBoolean(WARN_UNSAFE_SCRIPTS, __FUNCTION__) && lookType != 0
			&& !g_game().isLookTypeRegistered(lookType)) {
			g_logger().warn("[Outfits::loadFromXml] An unregistered creature looktype type with id '{}' was ignored to prevent client crash.", lookType);
			continue;
		}

		outfits[type].emplace_back(std::make_shared<Outfit>(
			outfitNode.attribute("name").as_string(),
			pugi::cast<uint16_t>(lookTypeAttribute.value()),
			outfitNode.attribute("premium").as_bool(),
			outfitNode.attribute("unlocked").as_bool(true),
			outfitNode.attribute("from").as_string()
		));
	}
	for (uint8_t sex = PLAYERSEX_FEMALE; sex <= PLAYERSEX_LAST; ++sex) {
		outfits[sex].shrink_to_fit();
	}
	return true;
}

std::shared_ptr<Outfit> Outfits::getOutfitByLookType(PlayerSex_t sex, uint16_t lookType) const {
	for (const auto &outfit : outfits[sex]) {
		if (outfit->lookType == lookType) {
			return outfit;
		}
	}
	return nullptr;
}

/**
 * Get the oposite sex equivalent outfit
 * @param sex current sex
 * @param lookType current looktype
 * @return <b>const</b> pointer to the outfit or <b>nullptr</b> if it could not be found.
 */

std::shared_ptr<Outfit> Outfits::getOpositeSexOutfitByLookType(PlayerSex_t sex, uint16_t lookType) {
	PlayerSex_t searchSex = (sex == PLAYERSEX_MALE) ? PLAYERSEX_FEMALE : PLAYERSEX_MALE;

	for (uint16_t i = 0; i < outfits[sex].size(); i++) {
		if (outfits[sex].at(i)->lookType == lookType) {
			if (outfits[searchSex].size() > i) {
				return outfits[searchSex].at(i);
			} else { // looktype found but the oposite sex array doesn't have this index.
				return nullptr;
			}
		}
	}
	return nullptr;
}
