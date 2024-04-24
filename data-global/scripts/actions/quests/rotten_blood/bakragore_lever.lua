local config = {
	boss = {
		name = "Bakragore",
		position = Position(33043, 32396, 15),
	},

	timeToDefeat = 20 * 60,
	playerPositions = {
		{ pos = Position(33014, 32392, 15), teleport = Position(33043, 32407, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33013, 32392, 15), teleport = Position(33043, 32407, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33012, 32392, 15), teleport = Position(33043, 32407, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33011, 32392, 15), teleport = Position(33043, 32407, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33010, 32392, 15), teleport = Position(33043, 32407, 15), effect = CONST_ME_TELEPORT },
	},
	specPos = {
		from = Position(33034, 32388, 15),
		to = Position(33053, 32409, 15),
	},
	exit = Position(),
}

local mitmahSummons = {
	Position(33041, 32396, 15),
	Position(33049, 32396, 15),

}

local lever = BossLever(config)
lever:uid(54501)
lever:register()
