# Changelog for Crystal Server

## Version 4.0

### Features
- **Surprise Bags System**
  - Implemented Surprise Bags System: data/items/bags.xml (Tryller, dgprado)

- **Chain System**
  - New configs to chain system at config.lua combatChainSkillFormulaMissile is used for weapons like assassin star/viper star and others, combatChainSkillFormulaDistance used for weapons like arrows/bols and combatChainSkillFormulaWandAndRods used for weapons like wands/rods (Tryller)

- **Take Screenshoot**
  - Implemented take screen shoot on player advance/death (Tryller, TFS)

- **Hirelings**
  - Updated npc data-global/npc/hireling.lua, now it sell imbuement packages and also buy all loots from Loot Pouch. (Tryller)

### Bug Fixes
- **Chain System**
  - Now chain system works properly for Mages and distance weapowns (Tryller).

- **onPlayerSellAllLoot**
  - Optimized onPlayerSellAllLoot in npc code to avoid long freeze (Tryller).
  
- **TalkActions**
  - Fix data/scripts/talkactions/player/refill.lua, now check if player has capacity to receive items. (Tryller).

### Changed Features
- **removeBeginningWeaponAmmunition**
  - Removed old removeBeginningWeaponAmmunition and implemented removeBreakWeaponsCharges at config.lua (Tryller)

### Map and Datapack updates
- **Rotten Blood Quest**
  - Add Rottten Blood Quest Scripts (dgprado).
  - Add Rotten Blood Creatures and Bosses. (dgprado, Tryller)

---

*Note: This Markdown document provides a concise overview of the changes introduced in Crystal Server version 4.0, categorized into features, bug fixes, and other updates. For a more detailed breakdown, refer to the commit history or release notes. 
In the changelog when Tryller is mentioned, it refers to me, jprzimba (João Paulo)*