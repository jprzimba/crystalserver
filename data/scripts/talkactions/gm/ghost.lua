local ghost = TalkAction("/ghost")

function ghost.onSay(player, words, param)
	-- create log
	logCommand(player, words, param)

	local position = player:getPosition()
	local isGhost = not player:isInGhostMode()

	player:setGhostMode(isGhost)
	if isGhost then
		player:setDisplayName(string.format('<font color="#ff0000">%s</font>&nbsp;&nbsp;', player:getName()))
		player:sendTextMessage(MESSAGE_HOTKEY_PRESSED, "You are now invisible.")
		position:sendMagicEffect(CONST_ME_YALAHARIGHOST)
	else
		player:setDisplayName(string.format('<font color="#00B800">%s</font>&nbsp;&nbsp;', player:getName()))
		player:sendTextMessage(MESSAGE_HOTKEY_PRESSED, "You are visible again.")
		position.x = position.x + 1
		position:sendMagicEffect(CONST_ME_SMOKE)
	end
	return true
end

ghost:separator(" ")
ghost:groupType("gamemaster")
ghost:register()
