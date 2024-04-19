local hex_monster = {
	author = "Marcosvf132",
	date = "19/02/2021",
	version = "1.0",
	organization = "###### OTServ-Br #####",
	objective = " [OTServ-Br 12.x project] \
		Export hex code to create and insert custom creatures on the client protocol 12.xx \
		This system will create a '.txt' file with all the monsters bytes, to insert it on the client you will need to do it \
		manually using a Hex editor (HxD is a good option). \
		-> With this script the user can insert custom monsters with any outfit on bestiary, prey and boosted creature.\
		-> This script was created to work with OTBR repository, this probably won't work with other repository, so don't ask support for it. \
		-> Created based on the client 12.61 protocol, future protocols may have some problems, if so, seek for updates on the OTBR Forum. \
		-> Important note: This script reads all monsters that have raceId registered on the server, if you wan't to remove, edit or create monsters on the client \
			you need to just remove/edit/add it on their repective '.lua' \
		--> The .txt file will be created on /data/ folder -'hex-monster.txt'-. "
}

local hexmonster = TalkAction("/hexmonster")

local function randomValueToHex(nValue)
	return string.format("%2X ", nValue)
end

local function bigDecimalTohex(value)
	local value = bit.bor(value, 0)
	local jumpEscape = value < 64
	local result = ""
	while (true) do
		local byte = bit.band(value, 0x7f)
		value = bit.rshift(value, 7)
		if ((value == 0) and ((bit.band(byte, 0x40)) == 0)) or ((value == -1) and ((bit.band(byte, 0x40)) ~= 0)) then
			if byte < 10 then
				result = result .. " 0" .. tostring(tonumber(randomValueToHex(tostring(byte)))):gsub("%s+", "") .. " "
			elseif byte < 16 then
				result = result .. " 0" .. randomValueToHex(byte):gsub("%s+", "") .. " "
			else
				result = result .. " " .. randomValueToHex(byte):gsub("%s+", "") .. " "
			end
			result = result:gsub("  ", " ")
			return result
		end
		local borBit = bit.bor(byte, 0x80)
		if borBit < 10 then
			result = result .. " 0" .. tostring(tonumber(randomValueToHex(tostring(borBit)))):gsub("%s+", "") .. " "
		elseif borBit < 16 then
			result = result .. " 0" .. randomValueToHex(borBit):gsub("%s+", "") .. " "
		else
			result = result .. " " .. randomValueToHex(borBit):gsub("%s+", "") .. " "
		end
		jumpEscape = false
	end
end

local function retNumberToHex(look_value)
	local ret = look_value > 64 and tostring(randomValueToHex(look_value)) or randomValueToHex(look_value)
	if look_value < 16 then
		ret = ret:gsub("%s+", "")
		ret = "0" .. ret
	end	
	return ret
end

local function stringTextToHexChar(str)
    return (str:gsub('.', function (c)
        return string.format('%02X ', string.byte(c))
    end))
end

local function numberToHex(value)
	local ret = tostring(randomValueToHex(tostring(value))):gsub("%s+", "")
	if value < 10 then
		ret = "0" .. tonumber(ret)
	elseif value < 16 then
		ret = retNumberToHex(value)
	end
	return ret
end

function hexmonster.onSay(player, words, param)
	if not player:getGroup():getAccess() or player:getAccountType() < ACCOUNT_TYPE_GOD then
		return true
	end

	local alreadyImplementedRaceId = {}
	local file = io.open("data/hex-monster.txt", "wb")
	if file then
		for index, monsterName in pairs(Game.getBestiaryList()) do
			local mType = MonsterType(monsterName)
			if mType and not(table.contains(alreadyImplementedRaceId, mType:raceId())) then
				local name = mType:name():lower()
				local outfit = mType:outfit()
				local monsterid_bit = bigDecimalTohex(mType:raceId())
				local nameDigits = numberToHex(string.len(name))
				local lookt_bit = bigDecimalTohex(outfit.lookType)
				local looka_bot = numberToHex(outfit.lookAddons)
				local lookh_bot = outfit.lookHead < 128 and numberToHex(outfit.lookHead) or (numberToHex(outfit.lookHead) .. " 01")
				local lookb_bot = outfit.lookBody < 128 and numberToHex(outfit.lookBody) or (numberToHex(outfit.lookBody) .. " 01")
				local lookl_bot = outfit.lookLegs < 128 and numberToHex(outfit.lookLegs) or (numberToHex(outfit.lookLegs) .. " 01")
				local lookf_bot = outfit.lookFeet < 128 and numberToHex(outfit.lookFeet) or (numberToHex(outfit.lookFeet) .. " 01")
		
				local counter_09 = 0
				if outfit.lookType < 128 then
					lookt_bit = " " .. numberToHex(outfit.lookType) .. " "
				end
				if outfit.lookHead >= 128 then
					lookh_bot = numberToHex(outfit.lookHead - 19)
				end
				if outfit.lookBody >= 128 then
					counter_09 = counter_09 + 1
				end
				if outfit.lookLegs >= 128 then
					counter_09 = counter_09 + 1
					if counter_09 > 1 then
						counter_09 = counter_09 - 1
						lookl_bot = numberToHex(outfit.lookLegs - 19)
					end
				end
				if outfit.lookFeet >= 128 then
					counter_09 = counter_09 + 1
					if counter_09 > 1 then
						counter_09 = counter_09 - 1
						lookf_bot = numberToHex(outfit.lookFeet - 19)
					end
				end
				local byteIncrease = "08"
				if counter_09 > 0 then
					byteIncrease = "09"
				end
				local look_case = ""
				if counter_09 > 0 then
					look_case = "10"
				else
					if outfit.lookType < 128 then
						look_case = "0E"
					else
						look_case = "0F"
					end
				end
				local stringHex, size_bit, return_hex = "", "", ""
				if outfit.lookType == 0 and outfit.lookTypeEx ~= 0 then
					local looke_bit = ItemType(outfit.lookTypeEx) and ItemType(outfit.lookTypeEx):getClientId() or 0
					stringHex = " 08" .. monsterid_bit .. "12 " .. nameDigits .. " " .. stringTextToHexChar(name) .. "1A 03 20" .. bigDecimalTohex(looke_bit)
					size_bit = numberToHex(string.len(stringHex:gsub("%s+", ""))/2)
					return_hex = "0A " .. size_bit .. stringHex .. " "
				elseif outfit.lookTypeEx == 0 then
					stringHex = " 08" .. monsterid_bit .. "12 " .. nameDigits .. " " .. stringTextToHexChar(name) .. "1A ".. look_case .. " 08" .. lookt_bit .. "12"
					stringHex = stringHex .. " " .. byteIncrease .. " 08 " .. lookh_bot ..  " 10 " .. lookb_bot .. " 18 " .. lookl_bot .. " 20 " .. lookf_bot .. " 18 " .. looka_bot
					size_bit = numberToHex(string.len(stringHex:gsub("%s+", ""))/2)
					return_hex = "0A " .. size_bit .. stringHex .. " "
				end
				table.insert(alreadyImplementedRaceId, mType:raceId())
				return_hex = return_hex:gsub("  ", " ")
				file:write(return_hex)
			end
		end
		player:sendCancelMessage("Data file has been succesfully created.")
		io.close(file)
	end
	return true
end

hexmonster:separator(" ")
hexmonster:groupType("god")
hexmonster:register()