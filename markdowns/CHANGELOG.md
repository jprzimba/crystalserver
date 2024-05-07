# Changelog for Crystal Server

## Version 4.0.0

### Features
  - Implemented Surprise Bags System: data/items/bags.xml ([Tryller](https://github.com/jprzimba), [dguprado](https://github.com/dguprado)).
  - New configs to chain system at config.lua "combatChainSkillFormulaMissile" is used for weapons like assassin star/viper star and others, "combatChainSkillFormulaDistance" used for weapons like arrows/bols and "combatChainSkillFormulaWandsAndRods" used for weapons like wands/rods ([Tryller](https://github.com/jprzimba)).
  - Updated npc data-global/npc/hireling.lua, now it sell imbuement packages and also buy all loots inside Gold Pouch ([Tryller](https://github.com/jprzimba)).
  - Cyclopedia item summary ([phacUFPE](https://github.com/phacUFPE))
  - Add Vibrancy imbuement ([pennaor](https://github.com/pennaor))
  - Badge system ([elsongabriel](https://github.com/elsongabriel))
  - Screenshots configurable in config.lua enableScreenshots ([Tryller](https://github.com/jprzimba)).

### Bug Fixes
  - Fixed chain system. Now works properly for Mages and Paladins ([Tryller](https://github.com/jprzimba)).
  - Fixed V.I.P List ([Tryller](https://github.com/jprzimba)).
  - Fixed damage reflection not working properly ([Tryller](https://github.com/jprzimba)).
  - Fixed imbuement system when the player adds imbuement or cancels imbuement and the imbuement window is open not updating ([Tryller](https://github.com/jprzimba)).
  - Fixed when the player dies without blessing and the bag goes to the gold puch ([Tryller](https://github.com/jprzimba))
  - Optimized onPlayerSellAllLoot in npc code to avoid long freeze ([Tryller](https://github.com/jprzimba)).
  - Fixed data/scripts/talkactions/player/refill.lua, now check if player has capacity to receive items. ([Tryller](https://github.com/jprzimba)).
  - Fixed Gold pouch using in the Obtain method ([carlospess0a](https://github.com/carlospess0a)).
  - Fixed destroy field is working inside pz ([carlospess0a](https://github.com/carlospess0a)).
  - Fixed diamond arrow static attack points ([svetrey](https://github.com/svetrey)).
  - Fixed stamina not recovering when dead ([carlospess0a](https://github.com/carlospess0a)).
  - Fixed alana sio only to "aleta som" users ([carlospess0a](https://github.com/carlospess0a)).
  - Fixed Player always logging with mount ([Tryller](https://github.com/jprzimba)).
  - Fixed quiver bugs ([phacUFPE](https://github.com/phacUFPE)).
  - Fixed avatar cooldown reduction ([phacUFPE](https://github.com/phacUFPE)).
  - Fixed imbuement elemental damage only to physical damag ([carlospess0a](https://github.com/carlospess0a)).

### Changed Features
  - Removed old "removeBeginningWeaponAmmunition" and implemented "removeBreakWeaponsCharges" at config.lua ([Tryller](https://github.com/jprzimba)).
  - Removed "useAnyDatapackFolder" at config.lua, now it's enable by default ([Tryller](https://github.com/jprzimba)).
  - Remove map download, since we share compressed .7z map ([Tryller](https://github.com/jprzimba)).

### Map and Datapack updates and Fixes
- **Fixed Quesst**
  - Combat knife Quest, getting infinite reward ([Tryller](https://github.com/jprzimba)).
  - Bear Room Quest, changed stair to hidden hole like Tibia RL ([Tryller](https://github.com/jprzimba)).
  - Katana Quest getting infinite keys ([Tryller](https://github.com/jprzimba)).

- **Rotten Blood Quest**
  - Add Rotten Blood Quest Scripts ([dguprado](https://github.com/dguprado)).
  - Add Rotten Blood Creatures and Bosses ([dguprado](https://github.com/dguprado), [Tryller](https://github.com/jprzimba)).

---

*Note: This Markdown document provides a concise overview of the changes introduced in Crystal Server version 4.0, categorized into features, bug fixes, and other updates. For a more detailed breakdown, refer to the commit history or release notes. 
In the changelog when [Tryller](https://github.com/jprzimba) is mentioned, it refers to me, [jprzimba](https://github.com/jprzimba) (João Paulo)*