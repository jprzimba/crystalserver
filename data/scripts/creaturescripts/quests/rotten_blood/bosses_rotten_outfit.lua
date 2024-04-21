local bossStorage = 45672

local bosses = {
    ["bakragore"] = true,
}

local RottenBloodBossOutFitKill = CreatureEvent("RottenBloodBossOutFitDeath")
function RottenBloodBossOutFitKill.onDeath(creature, corpse, lasthitkiller, mostdamagekiller, lasthitunjustified, mostdamageunjustified)
    local targetName = creature:getName():lower()
    if bosses[targetName] then
        local player = mostdamagekiller
        if player and player:isPlayer() then
            if player:getStorageValue(bossStorage) < 1 then
                local newValue = player:getStorageValue(bossStorage) + 1
                player:setStorageValue(bossStorage, newValue)
                player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Parabens! Voce ganhou o Decaying Defender Outfit")
                if player:getSex() == PLAYERSEX_FEMALE then
                    player:addOutfitAddon(1663, 3) -- Female outfit addon
                else
                    player:addOutfitAddon(1662, 3) -- Male outfit addon
                end
            end
        end
    end
    return true
end

RottenBloodBossOutFitKill:register()

