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

// Enums
enum StackPosType_t {
	STACKPOS_MOVE,
	STACKPOS_LOOK,
	STACKPOS_TOPDOWN_ITEM,
	STACKPOS_USEITEM,
	STACKPOS_USETARGET,
	STACKPOS_FIND_THING,
};

enum WorldType_t {
	WORLD_TYPE_NO_PVP = 1,
	WORLD_TYPE_PVP = 2,
	WORLD_TYPE_PVP_ENFORCED = 3,
};

enum GameState_t {
	GAME_STATE_STARTUP,
	GAME_STATE_INIT,
	GAME_STATE_NORMAL,
	GAME_STATE_CLOSED,
	GAME_STATE_SHUTDOWN,
	GAME_STATE_CLOSING,
	GAME_STATE_MAINTAIN,
};

enum QuickLootFilter_t {
	QUICKLOOTFILTER_SKIPPEDLOOT = 0,
	QUICKLOOTFILTER_ACCEPTEDLOOT = 1,
};

enum Faction_t {
	FACTION_DEFAULT = 0,
	FACTION_PLAYER = 1,
	FACTION_LION = 2,
	FACTION_LIONUSURPERS = 3,
	FACTION_MARID = 4,
	FACTION_EFREET = 5,
	FACTION_DEEPLING = 6,
	FACTION_DEATHLING = 7,
	FACTION_ANUMA = 8,
	FACTION_FAFNAR = 9,
	FACTION_LAST = FACTION_FAFNAR,
};

enum LightState_t : uint8_t {
	LIGHT_STATE_DAY,
	LIGHT_STATE_NIGHT,
	LIGHT_STATE_SUNSET,
	LIGHT_STATE_SUNRISE,
};

enum CyclopediaCharacterInfoType_t : uint8_t {
	CYCLOPEDIA_CHARACTERINFO_BASEINFORMATION = 0,
	CYCLOPEDIA_CHARACTERINFO_GENERALSTATS = 1,
	CYCLOPEDIA_CHARACTERINFO_COMBATSTATS = 2,
	CYCLOPEDIA_CHARACTERINFO_RECENTDEATHS = 3,
	CYCLOPEDIA_CHARACTERINFO_RECENTPVPKILLS = 4,
	CYCLOPEDIA_CHARACTERINFO_ACHIEVEMENTS = 5,
	CYCLOPEDIA_CHARACTERINFO_ITEMSUMMARY = 6,
	CYCLOPEDIA_CHARACTERINFO_OUTFITSMOUNTS = 7,
	CYCLOPEDIA_CHARACTERINFO_STORESUMMARY = 8,
	CYCLOPEDIA_CHARACTERINFO_INSPECTION = 9,
	CYCLOPEDIA_CHARACTERINFO_BADGES = 10,
	CYCLOPEDIA_CHARACTERINFO_TITLES = 11
};

enum CyclopediaCharacterInfo_RecentKillStatus_t : uint8_t {
	CYCLOPEDIA_CHARACTERINFO_RECENTKILLSTATUS_JUSTIFIED = 0,
	CYCLOPEDIA_CHARACTERINFO_RECENTKILLSTATUS_UNJUSTIFIED = 1,
	CYCLOPEDIA_CHARACTERINFO_RECENTKILLSTATUS_GUILDWAR = 2,
	CYCLOPEDIA_CHARACTERINFO_RECENTKILLSTATUS_ASSISTED = 3,
	CYCLOPEDIA_CHARACTERINFO_RECENTKILLSTATUS_ARENA = 4
};

enum class HighscoreCategories_t : uint8_t {
	EXPERIENCE = 0,
	FIST_FIGHTING = 1,
	CLUB_FIGHTING = 2,
	SWORD_FIGHTING = 3,
	AXE_FIGHTING = 4,
	DISTANCE_FIGHTING = 5,
	SHIELDING = 6,
	FISHING = 7,
	MAGIC_LEVEL = 8,
	LOYALTY_POINTS = 9,
	ACHIEVEMENTS = 10,
	CHARMS = 11,
	DROME = 12,
	GOSHNAR = 13,
	BOSS_POINTS = 14,
};

enum HighscoreType_t : uint8_t {
	HIGHSCORE_GETENTRIES = 0,
	HIGHSCORE_OURRANK = 1
};

enum Webhook_Colors_t : uint32_t {
	WEBHOOK_COLOR_GREEN = 0x00FF00,
	WEBHOOK_COLOR_RED = 0xFF0000,
	WEBHOOK_COLOR_YELLOW = 0xFFFF00,
	WEBHOOK_COLOR_BLUE = 0x0000FF
};