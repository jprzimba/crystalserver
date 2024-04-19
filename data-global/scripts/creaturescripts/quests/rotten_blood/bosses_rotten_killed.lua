local bossStorage = 45671

local bosses = {
    ["murcion"] = true,
    ["vemiath"] = true,
    ["chagorz"] = true,
    ["ichgahal"] = true,
}

local RottenBloodBossKill = CreatureEvent("RottenBloodBossDeath")
function RottenBloodBossKill.onDeath(creature, corpse, lasthitkiller, mostdamagekiller, lasthitunjustified, mostdamageunjustified)
    local targetName = creature:getName():lower()
    if bosses[targetName] then
        local player = mostdamagekiller
        if player and player:isPlayer() then
            local newValue = math.max(0, player:getStorageValue(bossStorage)) + 1
            player:setStorageValue(bossStorage, newValue)
            player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Parabens!")
        end
    end
    return true
end

RottenBloodBossKill:register()
