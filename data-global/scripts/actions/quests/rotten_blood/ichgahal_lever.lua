local config = {
	boss = {
		name = "Ichgahal",
		position = Position(33008, 32330, 15),
	},

	timeToDefeat = 20 * 60,
	playerPositions = {
		{ pos = Position(32978, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32977, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33976, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33975, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33974, 32333, 15), teleport = Position(33004, 32341, 15), effect = CONST_ME_TELEPORT },
	},
	specPos = {
		from = Position(33033, 32326, 15),
		to = Position(33052, 32343, 15),
	},
	exit = Position(),
}

local mitmahSummons = {
	Position(),
	Position(),

}

local lever = BossLever(config)
lever:uid(54502)
lever:register()
