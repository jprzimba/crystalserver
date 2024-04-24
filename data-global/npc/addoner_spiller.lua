local internalNpcName = "Addoner"
local npcType = Game.createNpcType(internalNpcName)
local npcConfig = {}

npcConfig.name = internalNpcName
npcConfig.description = internalNpcName

npcConfig.health = 100
npcConfig.maxHealth = npcConfig.health
npcConfig.walkInterval = 2000
npcConfig.walkRadius = 2

npcConfig.outfit = {
	lookType = 130,
	lookHead = 115,
	lookBody = 39,
	lookLegs = 96,
	lookFeet = 118,
	lookAddons = 3
}

npcConfig.flags = {
	floorchange = false
}

npcConfig.voices = {
	interval = 15000,
	chance = 50,
	{text = 'Come see my Addons bro!'}
}

local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)

npcType.onThink = function(npc, interval)
	npcHandler:onThink(npc, interval)
end

npcType.onAppear = function(npc, creature)
	npcHandler:onAppear(npc, creature)
end

npcType.onDisappear = function(npc, creature)
	npcHandler:onDisappear(npc, creature)
end

npcType.onMove = function(npc, creature, fromPosition, toPosition)
	npcHandler:onMove(npc, creature, fromPosition, toPosition)
end

npcType.onSay = function(npc, creature, type, message)
	npcHandler:onSay(npc, creature, type, message)
end

npcType.onCloseChannel = function(npc, creature)
	npcHandler:onCloseChannel(npc, creature)
end

addoninfo = {
    ['first citizen addon'] = {cost = 50000000, items = {}, outfit_female = 136, outfit_male = 128, addon = 1, storageID = Storage.OutfitQuest.Citizen.AddonBackpack},
    ['second citizen addon'] = {cost = 50000000, items = {}, outfit_female = 136, outfit_male = 128, addon = 2, storageID = Storage.OutfitQuest.Citizen.AddonHat},
    ['first hunter addon'] = {cost = 50000000, items = {}, outfit_female = 137, outfit_male = 129, addon = 1, storageID = Storage.OutfitQuest.Hunter.AddonHat},
    ['second hunter addon'] = {cost = 50000000, items = {}, outfit_female = 137, outfit_male = 129, addon = 2, storageID = Storage.OutfitQuest.Hunter.AddonGlove},
    ['first knight addon'] = {cost = 50000000, items = {}, outfit_female = 139, outfit_male = 131, addon = 1, storageID = Storage.OutfitQuest.Knight.AddonSword},
    ['second knight addon'] = {cost = 50000000, items = {}, outfit_female = 139, outfit_male = 131, addon = 2, storageID = Storage.OutfitQuest.Knight.AddonHelmet},
    ['first mage addon'] = {cost = 50000000, items = {}, outfit_female = 138, outfit_male = 130, addon = 1, storageID = Storage.OutfitQuest.MageSummoner.AddonWand},
    ['second mage addon'] = {cost = 50000000, items = {}, outfit_female = 138, outfit_male = 130, addon = 2, storageID = Storage.OutfitQuest.MageSummoner.AddonHatCloak},
    ['first summoner addon'] = {cost = 50000000, items = {}, outfit_female = 141, outfit_male = 133, addon = 1, storageID = Storage.OutfitQuest.MageSummoner.AddonBelt},
    ['second summoner addon'] = {cost = 50000000, items = {}, outfit_female = 141, outfit_male = 133, addon = 2, storageID = Storage.OutfitQuest.MageSummoner.AddonWandTimer},
    ['first barbarian addon'] = {cost = 50000000, items = {}, outfit_female = 147, outfit_male = 143, addon = 1, storageID = 51032},
    ['second barbarian addon'] = {cost = 50000000, items = {}, outfit_female = 147, outfit_male = 143, addon = 2, storageID = 51033},
    ['first druid addon'] = {cost = 50000000, items = {}, outfit_female = 148, outfit_male = 144, addon = 1, storageID = Storage.OutfitQuest.DruidHatAddon},
    ['second druid addon'] = {cost = 50000000, items = {}, outfit_female = 148, outfit_male = 144, addon = 2, storageID = Storage.OutfitQuest.DruidBodyAddon},
    ['first nobleman addon'] = {cost = 50000000, items = {}, outfit_female = 140, outfit_male = 132, addon = 1, storageID = Storage.OutfitQuest.NoblemanFirstAddon},
    ['second nobleman addon'] = {cost = 50000000, items = {}, outfit_female = 140, outfit_male = 132, addon = 2, storageID = Storage.OutfitQuest.NoblemanSecondAddon},
    ['first oriental addon'] = {cost = 50000000, items = {}, outfit_female = 150, outfit_male = 146, addon = 1, storageID = Storage.OutfitQuest.FirstOrientalAddon},
    ['second oriental addon'] = {cost = 50000000, items = {}, outfit_female = 150, outfit_male = 146, addon = 2, storageID = Storage.OutfitQuest.SecondOrientalAddon},
    ['first warrior addon'] = {cost = 50000000, items = {}, outfit_female = 142, outfit_male = 134, addon = 1, storageID = Storage.OutfitQuest.WarriorShoulderAddon},
    ['second warrior addon'] = {cost = 50000000, items = {}, outfit_female = 142, outfit_male = 134, addon = 2, storageID = Storage.OutfitQuest.WarriorSwordAddon},
    ['first wizard addon'] = {cost = 50000000, items = {}, outfit_female = 149, outfit_male = 145, addon = 1, storageID = 51034},
    ['second wizard addon'] = {cost = 50000000, items = {}, outfit_female = 149, outfit_male = 145, addon = 2, storageID = 51035},
    ['first assassin addon'] = {cost = 50000000, items = {}, outfit_female = 156, outfit_male = 152, addon = 1, storageID = Storage.OutfitQuest.AssassinFirstAddon},
    ['second assassin addon'] = {cost = 50000000, items = {}, outfit_female = 156, outfit_male = 152, addon = 2, storageID = Storage.OutfitQuest.AssassinSecondAddon},
    ['first beggar addon'] = {cost = 50000000, items = {}, outfit_female = 157, outfit_male = 153, addon = 1, storageID = Storage.OutfitQuest.BeggarFirstAddonDoor},
    ['second beggar addon'] = {cost = 50000000, items = {}, outfit_female = 157, outfit_male = 153, addon = 2, storageID = Storage.OutfitQuest.BeggarSecondAddon},
    ['first pirate addon'] = {cost = 50000000, items = {}, outfit_female = 155, outfit_male = 151, addon = 1, storageID = Storage.OutfitQuest.PirateSabreAddon},
    ['second pirate addon'] = {cost = 50000000, items = {}, outfit_female = 155, outfit_male = 151, addon = 2, storageID = Storage.OutfitQuest.PirateHatAddon},
    ['first shaman addon'] = {cost = 50000000, items = {}, outfit_female = 158, outfit_male = 154, addon = 1, storageID = 51036},
    ['second shaman addon'] = {cost = 50000000, items = {}, outfit_female = 158, outfit_male = 154, addon = 2, storageID = 51037},
    ['first norseman addon'] = {cost = 50000000, items = {}, outfit_female = 252, outfit_male = 251, addon = 1, storageID = 51038},
    ['second norseman addon'] = {cost = 50000000, items = {}, outfit_female = 252, outfit_male = 251, addon = 2, storageID = 51039}
}

local o = {'citizen', 'hunter', 'knight', 'mage', 'nobleman', 'summoner', 'warrior', 'barbarian', 'druid', 'wizard', 'oriental', 'pirate', 'assassin', 'beggar', 'shaman', 'norseman'}
local rtnt = {}

local function creatureSayCallback(npc, creature, type, message)
    local talkUser = creature
    local player = Player(creature)
    local playerId = player:getId()

    local talkState = {}
    if not npcHandler:checkInteraction(npc, creature) then
		return false
	end

    if addoninfo[message] ~= nil then
        local itemsTable = addoninfo[message].items
        local items_list = ''
        if (getPlayerStorageValue(creature, addoninfo[message].storageID) ~= -1) then
                npcHandler:say('You already have this addon!', npc, creature)
                npcHandler:resetNpc(creature)
                return true
        elseif table.maxn(itemsTable) > 0 then
            for i = 1, table.maxn(itemsTable) do
                local item = itemsTable[i]
                items_list = items_list .. item[2] .. ' ' .. ItemType(item[1]):getName()
                if i ~= table.maxn(itemsTable) then
                    items_list = items_list .. ', '
                end
            end
        end
        local text = ''
        if (addoninfo[message].cost > 0) then
            text = addoninfo[message].cost .. ' gp'
        elseif table.maxn(addoninfo[message].items) then
            text = items_list
        elseif (addoninfo[message].cost > 0) and table.maxn(addoninfo[message].items) then
            text = items_list .. ' and ' .. addoninfo[message].cost .. ' gp'
        end
        npcHandler:say('For ' .. message .. ' you will need ' .. text .. '. Do you have it all with you?', npc, creature)
        rtnt = message
        talkState[talkUser] = addoninfo[message].storageID
        npcHandler:setTopic(playerId, 2)
        return true
    elseif npcHandler:getTopic(playerId) == 2 then
        if MsgContains(message, "yes") then
            local items_number = 0
            if table.maxn(addoninfo[rtnt].items) > 0 then
                for i = 1, table.maxn(addoninfo[rtnt].items) do
                    local item = addoninfo[rtnt].items[i]
                    if (getPlayerItemCount(creature,item[1]) >= item[2]) then
                        items_number = items_number + 1
                    end
                end
            end

            if(player:getMoney() + player:getBankBalance() >= addoninfo[rtnt].cost) and (items_number == table.maxn(addoninfo[rtnt].items)) then
                if player:removeMoneyBank(addoninfo[rtnt].cost) then
                    if table.maxn(addoninfo[rtnt].items) > 0 then
                        for i = 1, table.maxn(addoninfo[rtnt].items) do
                            local item = addoninfo[rtnt].items[i]
                            doPlayerRemoveItem(creature,item[1],item[2])
                        end
                    end
                    doPlayerAddOutfit(creature, addoninfo[rtnt].outfit_male, addoninfo[rtnt].addon)
                    doPlayerAddOutfit(creature, addoninfo[rtnt].outfit_female, addoninfo[rtnt].addon)
                    setPlayerStorageValue(creature,addoninfo[rtnt].storageID, 1)
                    npcHandler:say('Here you are.', npc, creature)
                end
            else
                npcHandler:say('You do not have required items!', npc, creature)
            end

            rtnt = nil
            talkState[talkUser] = 0
            npcHandler:resetNpc(creature)
            return true
        end
    elseif MsgContains(message, "addon") then
        npcHandler:say('I can give you {first} or {second} addons for {' .. table.concat(o, "}, {") .. '} outfits.', npc, creature)
        rtnt = nil
        talkState[talkUser] = 0
        npcHandler:resetNpc(creature)
        return true
    elseif MsgContains(message, "help") then
        npcHandler:say('You must say \'first NAME addon\', for the first addon or \'second NAME addon\' for the second.', npc, creature)
        rtnt = nil
        talkState[talkUser] = 0
        npcHandler:resetNpc(creature)
        return true
    else
        if talkState[talkUser] ~= nil then
            if talkState[talkUser] > 0 then
            npcHandler:say('Come back when you get these items.', npc, creature)
            rtnt = nil
            talkState[talkUser] = 0
            npcHandler:resetNpc(creature)
            return true
            end
        end
    end
    return true
end

npcHandler:setMessage(MESSAGE_GREET, 'Welcome |PLAYERNAME|! If you want some addons, just ask me! Do you want to see my {addons}, or are you decided? If you are decided, just ask me like this: {first citizen addon}')
npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new(), npcConfig.name, true, true, true)
npcType:register(npcConfig)