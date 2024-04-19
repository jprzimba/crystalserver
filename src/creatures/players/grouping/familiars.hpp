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

#include "declarations.hpp"
#include "lib/di/container.hpp"

class Familiars {
public:
	static Familiars &getInstance() {
		return inject<Familiars>();
	}
	bool loadFromXml();
	const std::vector<Familiar> &getFamiliars(uint16_t vocation) const {
		return familiars[vocation];
	}
	const Familiar* getFamiliarByLookType(uint16_t vocation, uint16_t lookType) const;

private:
	std::vector<Familiar> familiars[VOCATION_LAST + 1];
};
