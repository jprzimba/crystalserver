# Changelog for Crystal Server

## Version 4.0

### Features
  - Implemented Surprise Bags System: data/items/bags.xml (Tryller, dgprado).
  - New configs to chain system at config.lua "combatChainSkillFormulaMissile" is used for weapons like assassin star/viper star and others, "combatChainSkillFormulaDistance" used for weapons like arrows/bols and "combatChainSkillFormulaWandsAndRods" used for weapons like wands/rods (Tryller).
  - Updated npc data-global/npc/hireling.lua, now it sell imbuement packages and also buy all loots inside Gold Pouch (Tryller).

### Bug Fixes
  - Fixed chain system. Now works properly for Mages and distance weapowns (Tryller).
  - Fixed V.I.P List (Tryller).
  - Fixed damage reflection not working properly (Tryller).
  - Fixed imbuement system when the player adds imbuement or cancels imbuement and the imbuement window is open (Tryller).
  - Fixed when the player dies without blessing and the bag goes to the gold puch (Tryller)
  - Optimized onPlayerSellAllLoot in npc code to avoid long freeze (Tryller).
  - Fixed data/scripts/talkactions/player/refill.lua, now check if player has capacity to receive items. (Tryller).
  - Fixed Gold pouch using in the Obtain method (carlospess0a).
  - Fixed destroy field is working inside pz (carlospess0a).
  - Fixed diamond arrow static attack points (svetrey).
  - Fixed stamina not recovering when dead (carlospess0a).
  - Fixed alana sio only to "aleta som" users (carlospess0a).

### Changed Features
  - Removed old "removeBeginningWeaponAmmunition" and implemented "removeBreakWeaponsCharges" at config.lua (Tryller).
  - Removed "useAnyDatapackFolder" at config.lua, now it's enable by default (Tryller).
  - Removed "dataPackDirectory" and "coreDirectory" at config.lua, now server use only one data pack (Tryller).
  - Move  all files from old "coreDirectory" to data pack (Tryller).

### Map and Datapack updates
- **Rotten Blood Quest**
  - Add Rotten Blood Quest Scripts (dgprado).
  - Add Rotten Blood Creatures and Bosses (dgprado, Tryller).

---

*Note: This Markdown document provides a concise overview of the changes introduced in Crystal Server version 4.0, categorized into features, bug fixes, and other updates. For a more detailed breakdown, refer to the commit history or release notes. 
In the changelog when Tryller is mentioned, it refers to me, jprzimba (João Paulo)*