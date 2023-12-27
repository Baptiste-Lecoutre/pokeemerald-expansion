# About this branch
This branch adds 5 new pockets to the bag based on changes to it from later generations:
* Medicine (HP, PP and status recovery items)
* Power-Up (Evolution Items, Vitamins, Mints, Candies)
* Battle Items (X items, Pokédoll/FluffyTail and hold items with battle effects)
* Mega Stones
* Z-Crystals

The new order for the pockets is the following:
* Items
* Medicine
* Poké Balls
* Battle Items
* Berries
* Power-Up
* Mega Stones
* Z-Crystals
* TMs & HMs
* Key Items

However, it reuses the original pocket sprites.

# pokeemerald-expansion

## What is pokeemerald-expansion?

pokeemerald-expansion is a decomp hack base project based off pret's [pokeemerald](https://github.com/pret/pokeemerald) decompilation project. It's recommended that any new projects that plan on using it, to clone this repository instead of pret's vanilla repository, as we regurlarly incorporate pret's documentation changes. This is ***NOT*** a standalone romhack, and as such, most features will be unavailable and/or unbalanced if played as is.

If you use pokeemerald-expansion in your hack, please add RHH (Rom Hacking Hideout) to your credits list. Optionally, you can list the version used, so it can help players know what features to expect.
You can phrase it as the following:
```
Based off RHH's pokeemerald-expansion v1.7.0 https://github.com/rh-hideout/pokeemerald-expansion/
```

## What features are included?
- ***IMPORTANT*❗❗ Read through these to learn what features you can toggle**:
    - [Battle configurations](/include/config/battle.h)
    - [Pokémon configurations](/include/config/pokemon.h)
    - [Item configurations](/include/config/item.h)
    - [Overworld configurations](/include/config/overworld.h)
    - [Debug configurations](/include/config/debug.h)
- ***Upgraded battle engine.***
    - Gen5+ damage calculation.
    - 2v2 Wild battles support.
    - 1v2/2v1 battles support.
    - Fairy Type (configurable).
    - Physical/Special/Status Category (configurable).
    - New moves and abilities up to Scarlet and Violet.
        - Custom Contest data up to SwSh, newer moves are WIP. ([source](https://pokemonurpg.com/info/contests/rse-move-list/))
    - Mega Evolution
    - Primal Reversion
    - Ultra Burst
    - Z-Moves
        - Gen 8+ damaging moves are given power extrapolated from Gen 7.
        - Gen 8+ status moves have no additional effects, like Healing Wish.
    - Dynamax
        - Gigantamax forms
    - Initial battle parameters
        - Queueing stat boosts (aka, Totem Boosts)
        - Setting Terrains.
    - Mid-turn speed recalculation.
    - Quick Poké Ball selection in Wild Battles
        - Press `R` to use last selected Poké Ball.
        - Hold `R` to change selection with the D-Pad.
    - Run option shortcut
    - Faster battle intro
        - Message and animation/cry happens at the same time.
    - Faster HP drain.
    - Battle Debug menu.
        - Accessed by pressing `Select` on the "Fight/Bag/Pokémon/Run" menu.
    - Option to use AI flags in wild Pokémon battles.
    - FRLG/Gen4+ whiteout money calculation.
    - Configurable experience settings
        - Experience on catch.
        - Splitting experience.
        - Trainer experience.
        - Scaled experience.
        - Unevolved experience boost.
    - Frostbite.
        - Doesn't replace freezing unless a config is enabled, so you can mix and match.
    - Critical capture.
    - Removed badge boosts (configurable).
    - Recalculating stats at the end of every battle.
    - Level 100 Pokémon can earn EVs.
    - Inverse battle support.
    - TONS of other features listed [here](/include/config/battle.h).
- ***Full Trainer customization***
    - Nickname, EVs, IVs, moves, ability, ball, friendship, nature, gender, shininess.
    - Custom tag battle support (teaming up an NPC in a double battle).
    - Sliding trainer messages.
    - Upgraded Trainer AI
        - Considers newer move effects.
        - New flag options to let you customize the intelligence of your trainers.
        - Faster calculations.
    - Specify Poké Balls by Trainer class.
- ***Pokémon Species from Generations 1-9.***
    - Simplified process to add new Pokémon.
    - Option to disable unwanted families.
    - Updated sprites to DS style.
    - Updated stats, types, abilities and egg groups (configurable).
    - Updated Hoenn's Regional Dex to match ORAS' (configurable).
    - Updated National Dex incorporating the new species.
    - Sprite and animation visualizer.
        - Accesible by pressing `Select` on a Pokémon's Summary screen.
    - Gen4+ evolution methods, with some changes:
        - Mossy Rock, Icy Rock and Magnetic Field locations match ORAS'.
            - Leaf, Ice and Thunder Stones may also be used.
        - Inkay just needs level 30 to evolve.
            - You can't physically have both the RTC and gyroscope, so we skip this requirement.
        - Sylveon uses Gen8+'s evolution method (friendship + Fairy Move).
        - Option to use hold evolution items directly like stones.
    - Hidden Abilities.
        - Available via Ability Patch.
        - Compatible with Ghoul's DexNav branch.
    - All gender differences.
        - Custom female icons for female Hippopotas Hippowdon, Pikachu and Wobbufett
    - 3 Perfect IVs on Legendaries, Mythicals and Ultra Beasts.
- ***Customizable form change tables. Full list of methods [here](/include/constants/form_change_types.h).***
    - Item holding (eg. Giratina/Arceus)
    - Item using (eg. Oricorio)
        - Time of day option for Shaymin
    - Fainting
    - Battle begin and end (eg. Xerneas)
        - Move change option for Zacian/Zamazenta
    - Battle end in terrains (eg. Burmy)
    - Switched in battle (eg. Palafin)
    - HP Threshold (eg. Darmanitan)
    - Weather (eg. Castform)
    - End of turn (eg. Morpeko)
    - Time of day (Shaymin)
- ***Breeding Improvements***
    - Incense Baby Pokémon now happen automatically (configurable).
    - Level 1 eggs (configurable).
    - Poké Ball inheriting (configurable).
    - Egg Move Transfer, including Mirror Herb (configurable).
    - Nature inheriting 100% of the time with Everstone (configurable)
    - Gen6+ Ability inheriting (configurable).
- ***Items from newer Generations. Full list [here](/include/constants/items.h).***
    - ***Gen 6+ Exp. Share*** (configurable)
    - Berserk Gene
    - Most battle items from Gen 4+
    - Existing item data but missing effects:
        - Mints
        - Dynamax Candy
        - Mulches
        - Gimmighoul Coin
        - Booster Energy
        - Tera Shards
        - Tera Orb
- ***Feature branches incorporated (with permission):***
    - [RHH intro credits](https://github.com/Xhyzi/pokeemerald/tree/rhh-intro-credits) by @Xhyzi.
        - A small signature from all of us to show the collective effort in the project :)
    - [Overworld debug](https://github.com/TheXaman/pokeemerald/tree/tx_debug_system) by @TheXaman
        - May be disabled.
        - Accesible by pressing `R + Start` in the overworld by default.
        - **Additional features**:
            - *Clear Boxes*: cleans every Pokémon from the Boxes.
            - *Hatch an Egg*: lets you choose an Egg in your party and immediatly hatch it.
    - [HGSS Pokédex](https://github.com/TheXaman/pokeemerald/tree/tx_pokedexPlus_hgss) by @TheXaman
        - May be disabled.
        - **Additional features**:
            - *Support for new evolution methods*.
            - *Dark Mode*.
    - [Nature Colors](https://github.com/DizzyEggg/pokeemerald/tree/nature_color) in summary screen by @DizzyEggg
- ***Other features***
    - Pressing B while holding a Pokémon drops them like in modern games (configurable).
    - Running indoors (configurable).
    - Configurable overworld poison damage.
    - Configurable flags for disabling Wild encounters and Trainer battles.
    - Configurable flags for forcing or disabling Shinies.
    - Reusable TM (configurable).
    - B2W2+ Repel system that also supports LGPE's Lures
    - Gen6+'s EV cap.
    - All bugfixes from pret included.
    - Fixed overworld snow effect.

There are some mechanics, moves and abilities that are missing and being developed. Check [the project's milestones](https://github.com/rh-hideout/pokeemerald-expansion/milestones) to see which ones.


### [Documentation on features can be found here](https://github.com/rh-hideout/pokeemerald-expansion/wiki)

## If I already have a project based on regular pokeemerald, can I use pokeemerald-expansion?
Yes! Keep in mind that we keep up with pret's documentation of pokeemerald, which means that if your project a bit old, you might get merge conflicts that you need to solve manually.
- If you haven't set up a remote, run the command `git remote add RHH https://github.com/rh-hideout/pokeemerald-expansion`.
- Once you have your remote set up, run the command `git pull RHH master`.

With this, you'll get the latest version of pokeemerald-expansion, plus a couple of bugfixes that haven't been released into the next patch version :)

## **How do I update my version of pokeemerald-expansion?**
- If you haven't set up a remote, run the command `git remote add RHH https://github.com/rh-hideout/pokeemerald-expansion`.
- Once you have your remote set up, run the command `git pull RHH expansion/1.7.0`.

### Please consider crediting the entire [list of contributors](https://github.com/rh-hideout/pokeemerald-expansion/wiki/Credits) in your project, as they have all worked hard to develop this project :)

## There's a bug in the project. How do I let you guys know?
Please submit any issues with the project [here](https://github.com/rh-hideout/pokeemerald-expansion/issues). Make sure that the issue wasn't reported by someone else by searching using the filters.

## Can I contribute even if I'm not a member of ROM Hacking Hideout?

Yes! Contributions are welcome via Pull Requests and they will be reviewed by maintainers. Don't feel discouraged if we take a bit to review your PR, we'll get to it.

## Who maintains the project?

The project was originally started by DizzyEgg alongside other contributors.

The project has now gotten larger and DizzyEgg is now maintaining the project as part of the ROM Hacking Hideout community. Some members of this community are taking on larger roles to help maintain the project.

## What is the ROM Hacking Hideout?

A Discord-based ROM hacking community that has many members who hack using the disassembly and decompilation projects for Pokémon. Quite a few contributors to the original feature branches by DizzyEgg were members of ROM Hacking Hideout. You can call it RHH for short!

[Click here to join the RHH Discord Server!](https://discord.gg/6CzjAG6GZk)

## What has changed from RHH repo?

- Added TheXaman's HGSS syled Pokedex
- Added TheXaman's DS style Party screen
- Added TheXaman's registeresd items wheel icons
- Added Lunos' wonder trade
- Added Lunos' quick swap in party menu
- Added Lunos' 999 items stack
- Added Lunos' bike gears switch
- Added Ghoulslash's item description header
- Added Ghoulslash's dexnav + access in pokenav
- Added Ghoulslash's autorun
- Added Devolov's PC access in the Pokenav
- Added AsparagusEduardo's better bag
- Added Buffelsalts' PokeVial
- Changed text boxes graphics 
- Added "Sound OFF" and "Instant text speed" options
- Pressing B in wild battle puts the cursor onto the run option
- Added type icons during battle move selection
- HMs can be forgotten
- Added cdt's better direction handling
- Bag & Summary screen warp around
- Switch keyboard to lower case after first letter
- Display IVs & EVs in summary screen (press A in skill page) & nature colored stats
- Reusable, unsellable & unholdable TMs
- Repeated use of candies & medicine in party menu
- Display move split icons during battle
- Display move info when pressing L during move selection
- Fixed "Last used ball" sprite going 1px too far
- Pressing R with start menu opened saves the game as in later gens
- Pressing L with start menu opened opens the map if the player has the pokenav, and the fly map is the player can use fly
- No need to learn move to use the HM
- Decapitalization of the game
- Party icons are shown in the "Continue" window in main menu
- Move held items in party
- Fast surf by pressing B
- Check ash amout using SootSack
- Surf blob dismounting ground effects
- No need to water berries in rainy routes
- Free premier balls every 10 balls bougth
- Use balls outside of battle to change a mon ball
- Repeated medicine use
- Change clock time by pressing start when looking at the clock
- Show enemy mon you're switching into
- Ghoul's Better reflection system
- Added Merrp's lighting: DNS, OW-expansion (ghoul), followers (disabled for palette issues), dynamic OW palettes and more
- Check enemy trainer's party in pokemon summary screen by using the "last used ball" asset (dummied for now, I'll have to find a proper implementation or battle mode)
- major battle are forced in SET mode
- option to do fast field move, skipping most text and mon showcase
- restored the shred battle transition
- added a base stat equalizer to 100 so that some mons become more usable
- option to remove low health beeps
- option to hatch egg faster (need less steps)
- option to fasten the evolution scene
- option to remove the need to reel while fishing
- shop items by badge count
- clock in start menu
- level cap option
- inverse type chart option
- Berry trees no longer die and EV-reducing berries grow faster with more yields
- When lvling up in battle, use vanilla's unused blue gradient anim of healthbox if mon can evolve (credits to Lunos & Flametix for their implementation)
- Set up an advanced version of RHH PR#2909 for GEN6+ XP SHARE
- Added the mints functionnality based on Ghoulslash's implementation & Merrp's algorithm to change personnality to obtain the correct nature
- Herb shop in Lavaridge sells every mint
- Added Evie&Ivy from inclement emerald
- TMs in OW are in a yellow ball, megastones glitter
- Move relearner can teach moves from pre-evos
- Added Rocket & Boss trainer classes, with the rocket battle transition from crytaldust
- Can choose any starter from the 8 first generation by pressing L or R to change pocket during starter selection
- Brendan/May gives 30 cherrish balls after obtaining the pokedex instead of 5 pokeballs
- Added a teleporter in Lanette's house, allows to change regional forms of a pokemon by cycling though the gFormSpeciesIdTables
- Added a scientist in Devon Corp to trigger trade evolutions (ported from Exalted Emerald, credits to segabl)
- Added soaring with mon showcase & flyout effect (credits to camthesaxman, paccy, and devolov)
- Starters are available in Mauville game corner
- Changed Mosdeep music to Dewford
- Mom gives old rod instead of running shoes (enabled at newgame). Old rod fisherman in Dewford gives an eviolite instead. Good rod is given by a new fisherman in Route 114. Fisherman on Route 118 gives gyaradosite instead. Super rod is unchanged. (Ported from Inclement Emerald)
- Random item drops when cutting trees or smashing rocks
- Can select the ball in lastusedball window during battle
- Can view enemy party summaryscreen if player has scanner (item to be changed, dummied for now)
- Added Agustin's wild item drops
- Added costumes based on PokeClassic's code. Dresser added to the player's room
- Updates Mirage-Island mechanics (credits to segabl)
- All Pokemon Centers now have a NPC for movetutor/relearner/deleter & more
- Mon that can mega evolve are displayed as such in HoF
- Add bobbing effect for follower pokemon
- added Dynamax and dynamax raids
- More to be added

## TODO
- Add team rocket story
    - Possibly a small event before new mauville in the game corner
- Add Red rivalry
    - Victory Road, double battle with Wally & ingame partner. 12v12? partner: may/brendan or leaf?
- Add Z crystals
- Give access to islands:
    - Eon ticket given by rematching the rival in route 103 in IE (southern island, lati@s)
    X Old sea map is found in abandonned ship (faraway island, mew)
    - mystic ticket is given by cynthia in mosdeep (navel rock, hooh lugia)
    - aurora ticket is given by steven in meteorfalls (birth island, deoxys)


- Add legendary events
    - Gen1:
        - Articuno in Shoal Cave
        - Moltres in Ember path
        - Zapdos in New Mauville
        - Mewtwo in a room of new mauville or in a lab, postgame
        - Mew in birth island
    - Gen2:
        - Dogs: roamers
        - Celebi: petalburg woods using unowns?
        - Hooh & Lugia: Navel rock
    - Gen3:
        - Lati@s both in southern island
        - Deoxys?
        - Jirachi?
    - Gen4:
        - Dialga & Palkia: event related to space center
        - Giratina afterwards, using a wormhole portal (summit of mt pyre?)
        - Arceus afterwards, player resting in his room?
        - Darkrai, player resting in his room, at night?
        - Heatran in groudon's lava under mt chimney
        - Regigigas in a scorchedslab after catching the 3 hoenn regis
        - Cresselia, lake trio, shaymin, phione, manaphy
    - Gen5:
        - cobalion, terrakion, virizion
        - tornadus, thundurus, landorus are roamers
        - reshiram, zekrom, kuyrem
        - victini, keldeo, meloetta, genesect
    - Gen6:
        - xerneas, yveltal, zygarde
        - diancie, hoopa, volcanion
    - Gen7:
    - Gen8: 
        - ZaZa & Galarian kanto birds roamers -> kanto birds? there's the teleporter... 
        - Eternatus
        - Regieleki & Regidrago in new caves with puzzles like other Regis

    
- Add new locations
- Look at GetHighestLevelInPlayerParty in IE
- Change trainer parties
- Change pc access in pokenav to first menu, and move ribbons to condition submenu
- Make the sootopolis rayquaza calming groudon and kyogre a double battle (player + rayquaza against groudon and kyogre) mid scene. original idea by devolov
- Look at Lunos' todo list in his megamoddedexpansion project
- Free up some trainers (Rival) by checking starter VAR. Could use a generic TrainerPartyOverride func 
- do some pokemon swarms + held items: https://github.com/i0brendan0/pokeemerald-expanded/commit/692223d5c9a2f4517097a052e6e6e15bbb001530
- Change some interfaces to have a visual identity
    - Text boxes
    - palettes and/or some UI layouts (see Missiri posts in discord & Reddit post about seasons in gen4)
    - healthboxes & mega-zmoves triggers
    - bag sprites
    - make magma bright during the night -> change the DNS from Merpp to Sierra? 
    - dexnav interface
