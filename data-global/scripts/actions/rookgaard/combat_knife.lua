local combatKnifeQuest = Action()

function combatKnifeQuest.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local rewardId = 3292
	if not player:canGetReward(rewardId, "combat knife") then
		return true
	end
	player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "You have found a combat knife.")
	player:addItem(rewardId, 1)
	player:questKV("combat knife"):set("completed", true)
	return true
end

combatKnifeQuest:uid(64119)
combatKnifeQuest:register()
