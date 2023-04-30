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

# pokeemerald Expansion

## What is the pokeemerald Expansion?

The Pokeemerald Expansion is a collection of feature branches that can be integrated into existing [pokeemerald](https://github.com/pret/pokeemerald) projects.

## What features are included?
- Upgraded battle engine.
    - Fairy Type.
    - Physical/Special/Status Category Split.
    - New moves and abilities up to SwSh.
    - Options to change behaviors and data by generation.
    - Mega Evolution and Primal Reversion
    - Z-Moves
- Pokémon Species from newer Generations (with the option to disable them if needed).
    - Updates Hoenn's Regional Dex to match ORAS'.
    - Updates National Dex incorporating all the new species.
    - Option to change base stats by generation.
    - New evolution methods.
    - Hidden Abilities data (How to make them available is up to the user).
- Items from newer Generations and updated item effects for battle and field use.

Certain mechanics, moves, abilities and species sprites are missing. For more information, see [the project's milestones](https://github.com/rh-hideout/pokeemerald-expansion/milestones).

### [Documentation on features can be found here](https://github.com/rh-hideout/pokeemerald-expansion/wiki)

## Who maintains the project?

The project was originally started by DizzyEgg alongside other contributors.

The project has now gotten larger and DizzyEgg is now maintaining the project as part of the ROM Hacking Hideout community. Some members of this community are taking on larger roles to help maintain the project.

### Please consider crediting the entire [list of contributors](https://github.com/rh-hideout/pokeemerald-expansion/wiki/Credits) in your project, as they have all worked hard to develop this project :)

## Can I contribute even if I'm not a member of ROM Hacking Hideout?

Yes! Contributions are welcome via Pull Requests and they will be reviewed by maintainers. Don't feel discouraged if we take a bit to review your PR, we'll get to it.

## What is ROM Hacking Hideout?

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
- More to be added

## TODO
- Add team rocket story
- Add Kanto and Johto gym leaders with Kanto E4
    - Brock in granite cave
    - Misty on the beach
    - Surge in new mauville trying to catch zapdos. Can't catch zapdos until he is defeated.
    - Erika in verdantuff
    - Koga in the rainy route with ninjas. "See these ninjas? I'm training them."
    - Sabrina talks to a rock which has psychic powers. Talking to the rocks says "just an ordinary rock".
    - Blaine in start of magma hideout (Hohoho I dug too far!)
    - Giovanni (rocket event)
    - Falkner in petalburg school?
    - Bugsy in petalburg woods, eastern part in a new location?
    - Whitney in a contest hall, corresponding gym is not opened because you have not proven your worth until you have defeated the strong trainer lurking around the contest hall
    - Morty in mt pyre
    - Chuck in desert
    - Jasmine 
    - Pryce & Lorelei in Ice cave double battle
    - Clair & Lance in Meteor Falls double battle
    - Bruno in the route with the currents, "training by swimming against the currents"
    - Agatha in mt pyre post-game
- Add Red rivalry
- Add mega stones & Z crystals
- Add legendary events
    - Gen1:
        - Articuno in Shoal Cave
        - Moltres in Fiery path
        - Zapdos in New Mauville
        - Mewtwo in a room of new mauville or in a lab, postgame
        - Mew in birth island
    - Gen2:
        - Dogs: roamers
        - Celebi: petalburg woods using unowns?
        - Hooh & Lugia: Navel rock if available or ported?
    - Gen3:
        - Lati@s roamers?
        - Deoxys?
        - Jirachi?
    - Gen4:
        - Dialga & Palkia: event related to space center
        - Giratina afterwards, using a wormhole portal (summit of mt pyre?)
        - Arceus afterwards, player resting in his room?
        - Darkrai, player resting in his room, at night?
        - Heatran in groudon's lava under mt chimney
        - Regigigas in a cave after catching the 3 hoenn regis
        - Cresselia, lake trio, shaymin, phione, manaphy
    - Gen5:
        - cobalion, terrakion, virizion
        - tornadus, thundurus, landorus are roamers
        - reshiram, zekrom, kuyrem
        - victini, keldeo, meloetta, genesect
    - Gen6:
        - xerneas, yveltal, zygarde
        - dianci, hoopa, volcanion
    - Gen7:
    - Gen8: 
        - Galarian kanto birds roamers ?

    

- Add new locations
- Buy starters in mauville game corner
- Change wild encounters & trainer parties
- Change pc access in pokenav to first menu, and move ribbons to condition submenu
- Add a means to make trade evos (see Bill's teleporter in hackrom)
- ReUse of origin cave post-game
- Buff the encounters at Sky Pillar after the conflict in Sootopolis is solved.
- When a Gym Leader rematch is ready to happen, make said gym's trainers battle the Player again.
- Add a NPC that changes IVs, another one that changes EVs, and a last one that changes nature. See Evie&Ivy in IE.
- Free up some space for flags and vars by checking trainer flags or if player has items + useless flags like FLAG_SYS_B_DASH
- Free up some trainers (Rival, Aqua/Magma leaders) by checking MAPSECs and other story-related flags. Could use a generic TrainerPartyOverride func 
- Try to recover the item desc header native behavior by checking if the player has the item. destroying window could be checked by its window id
- Add a teleporter to be able to change between regionals forms of pokemons? (galarian birds, alola, galar...)
- Add soaring & Eon flute?
