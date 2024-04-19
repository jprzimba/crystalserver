local dryadPos = {
	-- unique id, destination
	-- entrance
	[37636] = Position(33809, 31816, 13),

	-- exit
	[37637] = Position(34091, 32006, 14),
}


local dryadAction = Action()

function dryadAction.onUse(player, item, target, position, fromPosition)
	local destination = dryadPos[item.uid]
	if not destination then
		return true
	end

	player:teleportTo(destination)
	player:getPosition():sendMagicEffect(14)
	return true
end

for i, x in pairs(dryadPos) do
	dryadAction:uid(i)
end

dryadAction:register()