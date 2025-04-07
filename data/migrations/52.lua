function onUpdateDatabase()
	logger.info("Updating database to version 52 (Reborn System)")

	db.query([[
        ALTER TABLE `players`
            ADD `rebirth` int(11) NOT NULL DEFAULT '0';
    ]])
end

