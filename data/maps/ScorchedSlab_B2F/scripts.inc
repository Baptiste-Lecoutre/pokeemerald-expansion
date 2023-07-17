ScorchedSlab_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, ScorchedSlab_B2F_OnLoad
	.byte 0

ScorchedSlab_B2F_OnLoad:
	call ScorchedSlab_B2F_EventScript_HideRegiEntrance
	end

ScorchedSlab_B2F_EventScript_HideRegiEntrance::
	setmetatile 17, 3, METATILE_Cave_EntranceCover, TRUE
	setmetatile 18, 3, METATILE_Cave_EntranceCover, TRUE
	setmetatile 19, 3, METATILE_Cave_EntranceCover, TRUE
	setmetatile 17, 4, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 18, 4, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 19, 4, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return
