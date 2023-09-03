MeteorFalls_B1F_2R_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_B1F_2R_OnLoad
	.byte 0

MeteorFalls_B1F_2R_OnLoad:
	call_if_unset FLAG_REGI_DOORS_OPENED, MeteorFalls_B1F_2R_CloseRegiEntrance
	end

MeteorFalls_B1F_2R_CloseRegiEntrance::
	setmetatile 5, 6, METATILE_General_CalmWater, FALSE
	setmetatile 4, 7, METATILE_General_CalmWater, FALSE
	setmetatile 5, 7, METATILE_General_CalmWater, FALSE
	setmetatile 6, 7, METATILE_General_CalmWater, FALSE
	setmetatile 4, 8, METATILE_General_CalmWater, FALSE
	setmetatile 5, 8, METATILE_General_CalmWater, FALSE
	setmetatile 6, 8, METATILE_General_CalmWater, FALSE
	setmetatile 4, 9, METATILE_General_CalmWater, FALSE
	setmetatile 5, 9, METATILE_General_CalmWater, FALSE
	setmetatile 6, 9, METATILE_General_CalmWater, FALSE
	setmetatile 4, 10, METATILE_General_CalmWater, FALSE
	setmetatile 5, 10, METATILE_General_CalmWater, FALSE
	setmetatile 6, 10, METATILE_General_CalmWater, FALSE
	setmetatile 4, 11, METATILE_General_CalmWater, FALSE
	setmetatile 5, 11, METATILE_General_CalmWater, FALSE
	setmetatile 6, 11, METATILE_General_CalmWater, FALSE
	setmetatile 5, 12, METATILE_General_CalmWater, FALSE
	return
