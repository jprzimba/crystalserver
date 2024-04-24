local config = {
	boss = {
		name = "Murcion",
		position = Position(33008, 32365, 15),
	},

	timeToDefeat = 20 * 60,
	playerPositions = {
		{ pos = Position(32978, 32365, 15), teleport = Position(33009, 32371, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32977, 32365, 15), teleport = Position(33009, 32371, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32976, 32365, 15), teleport = Position(33009, 32371, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32975, 32365, 15), teleport = Position(33009, 32371, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(32974, 32365, 15), teleport = Position(33009, 32371, 15), effect = CONST_ME_TELEPORT },
	},
	specPos = {
		from = Position(33000, 32358, 15),
		to = Position(33018, 32375, 15),
	},
	exit = Position(),
}

local mitmahSummons = {
	Position(33006, 32365, 15),
	Position(33010, 32365, 15),

}

local lever = BossLever(config)
lever:uid(54505)
lever:register()
