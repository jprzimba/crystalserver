local config = {
	boss = {
		name = "Vemiath",
		position = Position(33043, 32332, 15),
	},

	timeToDefeat = 20 * 60,
	playerPositions = {
		{ pos = Position(33078, 32333, 15), teleport = Position(33043, 32342, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33077, 32333, 15), teleport = Position(33043, 32342, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33076, 32333, 15), teleport = Position(33043, 32342, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33075, 32333, 15), teleport = Position(33043, 32342, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33074, 32333, 15), teleport = Position(33043, 32342, 15), effect = CONST_ME_TELEPORT },
	},
	specPos = {
		from = Position(33033, 32326, 15),
		to = Position(33052, 32343, 15),
	},
	exit = Position(),
}

local mitmahSummons = {
	Position(33041, 32332, 15),
	Position(33049, 32332, 15),

}

local lever = BossLever(config)
lever:uid(54503)
lever:register()
