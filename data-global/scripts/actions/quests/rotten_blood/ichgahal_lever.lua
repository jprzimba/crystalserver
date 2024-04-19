local config = {
	boss = {
		name = "Ichgahal",
		position = Position(33008, 32330, 15),
	},

	timeToDefeat = 20 * 60,
	playerPositions = {
		{ pos = Position(32978, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32977, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32976, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32975, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32974, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
	},
	specPos = {
		from = Position(32999, 32325, 15),
		to = Position(33017, 32344, 15),
	},
	exit = Position(),
}

local mitmahSummons = {
	Position(33002, 32330, 15),
	Position(33009, 32330, 15),

}

local lever = BossLever(config)
lever:uid(54502)
lever:register()
