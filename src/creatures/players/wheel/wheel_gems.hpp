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

#include "creatures/players/wheel/wheel_definitions.hpp"

class PlayerWheel;

enum CombatType_t : uint8_t;
enum Vocation_t : uint16_t;

enum class WheelGemAffinity_t : uint8_t;
enum class WheelGemBasicModifier_t : uint8_t;
enum class WheelGemSupremeModifier_t : uint8_t;
enum class WheelStat_t : uint8_t;

class GemModifierStrategy {
public:
	explicit GemModifierStrategy(PlayerWheel &wheel) :
		m_wheel(wheel) { }
	virtual ~GemModifierStrategy() = default;
	virtual void execute() = 0;

protected:
	PlayerWheel &m_wheel;
};

class GemModifierResistanceStrategy final : public GemModifierStrategy {
public:
	explicit GemModifierResistanceStrategy(PlayerWheel &wheel, CombatType_t combatType, int32_t resistance) :
		GemModifierStrategy(wheel),
		m_combatType(combatType),
		m_resistance(resistance) { }

	void execute() override;

private:
	CombatType_t m_combatType;
	int32_t m_resistance;
};

class GemModifierStatStrategy final : public GemModifierStrategy {
public:
	explicit GemModifierStatStrategy(PlayerWheel &wheel, WheelStat_t stat, int32_t value) :
		GemModifierStrategy(wheel),
		m_stat(stat),
		m_value(value) { }

	void execute() override;

private:
	WheelStat_t m_stat;
	int32_t m_value {};
};

class GemModifierRevelationStrategy final : public GemModifierStrategy {
public:
	explicit GemModifierRevelationStrategy(PlayerWheel &wheel, WheelGemAffinity_t affinity, [[maybe_unused]] uint16_t value) :
		GemModifierStrategy(wheel),
		m_affinity(affinity),
		m_value(value) { }

	void execute() override;

private:
	WheelGemAffinity_t m_affinity;
	uint16_t m_value {};
};

class GemModifierSpellBonusStrategy final : public GemModifierStrategy {
public:
	explicit GemModifierSpellBonusStrategy(PlayerWheel &wheel, std::string spellName, const WheelSpells::Bonus &bonus) :
		GemModifierStrategy(wheel),
		m_spellName(std::move(spellName)),
		m_bonus(bonus) { }

	void execute() override;

private:
	std::string m_spellName;
	WheelSpells::Bonus m_bonus;
};

class WheelModifierContext {
public:
	explicit WheelModifierContext(PlayerWheel &wheel, Vocation_t vocation) :
		m_wheel(wheel), m_vocation(vocation) { }

	void addStrategies(WheelGemBasicModifier_t modifier, uint8_t grade);
	void addStrategies(WheelGemSupremeModifier_t modifier, uint8_t grade);

	void resetStrategies() {
		m_strategies.clear();
	}

	void executeStrategies() const;

private:
	std::vector<std::unique_ptr<GemModifierStrategy>> m_strategies;
	PlayerWheel &m_wheel;
	Vocation_t m_vocation;
};

class WheelGemUtils {
public:
	[[maybe_unused]] static int32_t getHealthValue(Vocation_t vocation, WheelGemBasicModifier_t modifier);
	[[maybe_unused]] static int32_t getManaValue(Vocation_t vocation, WheelGemBasicModifier_t modifier);
	[[maybe_unused]] static int32_t getCapacityValue(Vocation_t vocation, WheelGemBasicModifier_t modifier);
};