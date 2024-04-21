DATA_DIRECTORY = configManager.getString(configKeys.DATA_DIRECTORY)
CORE_DIRECTORY = configManager.getString(configKeys.CORE_DIRECTORY)

dofile("data/global.lua")
dofile("data/lib/lib.lua")
dofile("data/libs/libs.lua")
dofile("data/stages.lua")
dofile("data/startup/startup.lua")
