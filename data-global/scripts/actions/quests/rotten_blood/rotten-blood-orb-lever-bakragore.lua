local dryadPos = {
    -- unique id, destination
    -- entrance
    [37645] = Position(33012, 32389, 15),

    -- exit
}

local dryadAction = Action()

function dryadAction.onUse(player, item, target, position, fromPosition)
    -- Verificar se o jogador possui pelo menos 4 na storage 45671
    if player:getStorageValue(45671) < 4 then
        player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce precisa darrotar os 4 bosses para poder passar")
        return true
    end

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
