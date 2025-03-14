local internalNpcName = "Sherlock"
local npcType = Game.createNpcType(internalNpcName)
local npcConfig = {}

npcConfig.name = internalNpcName
npcConfig.description = internalNpcName

npcConfig.health = 100
npcConfig.maxHealth = npcConfig.health
npcConfig.walkInterval = 2000
npcConfig.walkRadius = 2

npcConfig.outfit = {
	lookType = 151,
	lookHead = 78,
	lookBody = 51,
	lookLegs = 85,
	lookFeet = 126,
	lookAddons = 3,
}

npcConfig.flags = {
	floorchange = false,
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

-- Travel
local function addTravelKeyword(keyword, cost, destination)
	local travelKeyword = keywordHandler:addKeyword({ keyword }, StdModule.say, { npcHandler = npcHandler, text = "Do you want go to the " .. keyword:titleCase() .. " for |TRAVELCOST|?", cost = cost })
	travelKeyword:addChildKeyword({ "yes" }, StdModule.travel, { npcHandler = npcHandler, premium = false, cost = cost, destination = destination })
	travelKeyword:addChildKeyword({ "no" }, StdModule.say, { npcHandler = npcHandler, text = "Alright then!", reset = true })
end

addTravelKeyword("karmia", 100, Position(577, 492, 6))
addTravelKeyword("mistrock", 100, Position(843, 537, 7))

-- Basic
keywordHandler:addKeyword({ "travel" }, StdModule.say, { npcHandler = npcHandler, text = "I can take you to {Mistrock} and {Karmia}!" })
keywordHandler:addAliasKeyword({ "passage" })
keywordHandler:addKeyword({ "job" }, StdModule.say, { npcHandler = npcHandler, text = "I am Maris, Captain of this ship." })
keywordHandler:addAliasKeyword({ "captain" })

npcHandler:setMessage(MESSAGE_GREET, "I hope you have a good reason to step near my ship, say {travel}, |PLAYERNAME|.")
npcHandler:setMessage(MESSAGE_FAREWELL, "Yeah, bye or whatever.")
npcHandler:setMessage(MESSAGE_WALKAWAY, "Bye.")

npcHandler:addModule(FocusModule:new(), npcConfig.name, true, true, true)

-- npcType registering the npcConfig table
npcType:register(npcConfig)
