local dryadPos = {
	-- unique id, destination
	-- entrance
	[37634] = Position(34119, 31877, 14),

	-- exit
	[37635] = Position(34119, 32009, 15),
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