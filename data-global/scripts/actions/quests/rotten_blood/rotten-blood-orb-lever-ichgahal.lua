local dryadPos = {
	-- unique id, destination
	-- entrance
	[37643] = Position(32976, 32331, 15),

	-- exit

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