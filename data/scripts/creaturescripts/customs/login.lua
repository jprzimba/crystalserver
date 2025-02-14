local changeNameColor = CreatureEvent("ChangeNameColor")

function changeNameColor.onLogin(player)
	if player:getGroup():getId() >= GROUP_TYPE_GAMEMASTER and player:getGroup():getId() < GROUP_TYPE_TESTER then
		player:setGhostMode(true)
		player:setDisplayName(string.format('<font color="#ff0000">%s</font>&nbsp;&nbsp;', player:getName()))
	elseif player:getGroup():getId() == GROUP_TYPE_TESTER then
		player:setDisplayName(string.format('<font color="orange">%s</font>&nbsp;&nbsp;', player:getName()))
	end
	
	return true
end

changeNameColor:register()
