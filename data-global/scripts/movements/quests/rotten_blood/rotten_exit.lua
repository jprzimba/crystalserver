local teleportEvent = MoveEvent()

-- Posição onde o jogador deve pisar para ser teleportado
local PLAYER_POSITION = Position(34070, 31974, 14)

-- Posição para onde o jogador será teleportado
local DESTINATION_POSITION = Position(32958, 32398, 9)

function teleportEvent.onStepIn(creature, item, position, fromPosition, toPosition)
    local player = creature:getPlayer()
    if not player then
        return true
    end

    -- Verifica se o jogador pisou na posição correta para ser teleportado
    if position == PLAYER_POSITION then
        -- Teleporta o jogador para a posição de destino
        player:teleportTo(DESTINATION_POSITION)
        player:getPosition():sendMagicEffect(CONST_ME_TELEPORT)
        return true
    end
end

-- Defina o ID, AID ou Position do evento de movimento
teleportEvent:position(PLAYER_POSITION) -- ou: teleportEvent:id(1) ou teleportEvent:aid(0)

teleportEvent:type("stepin")
teleportEvent:register()
