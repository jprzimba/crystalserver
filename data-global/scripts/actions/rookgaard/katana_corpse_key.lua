local katanaCorpseKey = Action()

function katanaCorpseKey.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local rewardId = 2969
	if not player:canGetRewardFromCorpse(rewardId, "katana_silver_key") then
		return true
	end

	player:addItem(rewardId, 1)
	player:questKV("katana_silver_key"):set("completed", true)
	return true
end

katanaCorpseKey:uid(64110)
katanaCorpseKey:register()
