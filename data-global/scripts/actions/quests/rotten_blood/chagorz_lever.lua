local config = {
	boss = {
		name = "Chagorz",
		position = Position(33043, 32364, 15),
	},

	timeToDefeat = 20 * 60,
	playerPositions = {
		{ pos = Position(33078, 32367, 15), teleport = Position(33045, 32372, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33077, 32367, 15), teleport = Position(33045, 32372, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33076, 32367, 15), teleport = Position(33045, 32372, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33075, 32367, 15), teleport = Position(33045, 32372, 15), effect = CONST_ME_TELEPORT },
		{ pos = Position(33074, 32367, 15), teleport = Position(33045, 32372, 15), effect = CONST_ME_TELEPORT },
	},
	specPos = {
		from = Position(33033, 32357, 15),
		to = Position(33053, 32376, 15),
	},
	exit = Position(),
}

local mitmahSummons = {
	Position(33039, 32363, 15),
	Position(33048, 32364, 15),

}

local lever = BossLever(config)
lever:uid(54504)
lever:register()
