local dryadPos = {
	-- unique id, destination
	-- entrance
	[37638] = Position(34100, 31679, 13),

	-- exit
	[37639] = Position(34117, 31979, 14),
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