#ifndef GUARD_METATILE_BEHAVIOR_H
#define GUARD_METATILE_BEHAVIOR_H

// Return values for MetatileBehavior_GetBridgeType
enum {
    BRIDGE_TYPE_OCEAN, // For log bridges over 'ocean' style water (Routes 110/119 use this).
    BRIDGE_TYPE_POND_LOW,
    BRIDGE_TYPE_POND_MED,
    BRIDGE_TYPE_POND_HIGH,
};

bool8 MetatileBehavior_IsATile(u8);
bool8 MetatileBehavior_IsEncounterTile(u8);
bool8 MetatileBehavior_IsJumpEast(u8);
bool8 MetatileBehavior_IsJumpWest(u8);
bool8 MetatileBehavior_IsJumpNorth(u8);
bool8 MetatileBehavior_IsJumpSouth(u8);
bool8 MetatileBehavior_IsPokeGrass(u8);
bool8 MetatileBehavior_IsSandOrDeepSand(u8);
bool8 MetatileBehavior_IsDeepSand(u8);
bool8 MetatileBehavior_IsReflective(u8);
bool8 MetatileBehavior_IsIce(u8);
bool8 MetatileBehavior_IsWarpDoor(u8);
bool8 MetatileBehavior_IsDoor(u8);
bool8 MetatileBehavior_IsEscalator(u8);
bool8 MetatileBehavior_IsLadder(u8);
bool8 MetatileBehavior_IsNonAnimDoor(u8);
bool8 MetatileBehavior_IsDeepSouthWarp(u8);
bool8 MetatileBehavior_IsSurfableWaterOrUnderwater(u8);
bool8 MetatileBehavior_IsEastArrowWarp(u8);
bool8 MetatileBehavior_IsWestArrowWarp(u8);
bool8 MetatileBehavior_IsNorthArrowWarp(u8);
bool8 MetatileBehavior_IsSouthArrowWarp(u8);
bool8 MetatileBehavior_IsArrowWarp(u8);
bool8 MetatileBehavior_IsForcedMovementTile(u8);
bool8 MetatileBehavior_IsIce_2(u8);
bool8 MetatileBehavior_IsTrickHouseSlipperyFloor(u8);
bool8 MetatileBehavior_IsWalkNorth(u8);
bool8 MetatileBehavior_IsWalkSouth(u8);
bool8 MetatileBehavior_IsWalkWest(u8);
bool8 MetatileBehavior_IsWalkEast(u8);
bool8 MetatileBehavior_IsNorthwardCurrent(u8);
bool8 MetatileBehavior_IsSouthwardCurrent(u8);
bool8 MetatileBehavior_IsWestwardCurrent(u8);
bool8 MetatileBehavior_IsEastwardCurrent(u8);
bool8 MetatileBehavior_IsSlideNorth(u8);
bool8 MetatileBehavior_IsSlideSouth(u8);
bool8 MetatileBehavior_IsSlideWest(u8);
bool8 MetatileBehavior_IsSlideEast(u8);
bool8 MetatileBehavior_IsCounter(u8);
bool8 MetatileBehavior_IsPlayerFacingTVScreen(u8 tile, u8 playerDir);
bool8 MetatileBehavior_IsPC(u8);
bool8 MetatileBehavior_IsCableBoxResults1(u8);
bool8 MetatileBehavior_IsOpenSecretBaseDoor(u8);
bool8 MetatileBehavior_IsSecretBaseCave(u8);
bool8 MetatileBehavior_IsSecretBaseTree(u8);
bool8 MetatileBehavior_IsSecretBaseShrub(u8);
bool8 MetatileBehavior_IsSecretBasePC(u8);
bool8 MetatileBehavior_IsRecordMixingSecretBasePC(u8);
bool8 MetatileBehavior_IsSecretBaseTrainerSpot(u8);
bool8 MetatileBehavior_IsSecretBaseImpassable(u8);
bool8 MetatileBehavior_IsSecretBaseDecorationBase(u8);
bool8 MetatileBehavior_IsSecretBasePoster(u8);
bool8 MetatileBehavior_IsNormal(u8);
bool8 MetatileBehavior_IsSecretBaseNorthWall(u8);
bool8 MetatileBehavior_HoldsSmallDecoration(u8);
bool8 MetatileBehavior_HoldsLargeDecoration(u8);
bool8 MetatileBehavior_IsSecretBaseHole(u8);
bool8 MetatileBehavior_IsSecretBaseBalloon(u8);
bool8 MetatileBehavior_IsSecretBaseBreakableDoor(u8);
bool8 MetatileBehavior_IsSecretBaseSoundMat(u8);
bool8 MetatileBehavior_IsSecretBaseGlitterMat(u8);
bool8 MetatileBehavior_IsSecretBaseSandOrnament(u8);
bool8 MetatileBehavior_IsSecretBaseShieldOrToyTV(u8);
bool8 MetatileBehavior_IsPlayerRoomPCOn(u8);
bool8 MetatileBehavior_HasRipples(u8);
bool8 MetatileBehavior_IsPuddle(u8);
bool8 MetatileBehavior_IsTallGrass(u8);
bool8 MetatileBehavior_IsLongGrass(u8);
bool8 MetatileBehavior_IsBerryTreeSoil(u8);
bool8 MetatileBehavior_IsAshGrass(u8);
bool8 MetatileBehavior_IsFootprints(u8);
bool8 MetatileBehavior_IsBridgeOverWater(u8);
u8 MetatileBehavior_GetBridgeType(u8);
bool8 MetatileBehavior_IsBridgeOverWaterNoEdge(u8);
bool8 MetatileBehavior_IsLandWildEncounter(u8);
bool8 MetatileBehavior_IsWaterWildEncounter(u8);
bool8 MetatileBehavior_IsIndoorEncounter(u8);
bool8 MetatileBehavior_IsMountain(u8);
bool8 MetatileBehavior_IsDiveable(u8);
bool8 MetatileBehavior_IsUnableToEmerge(u8);
bool8 MetatileBehavior_IsShallowFlowingWater(u8);
bool8 MetatileBehavior_IsThinIce(u8);
bool8 MetatileBehavior_IsCrackedIce(u8);
bool8 MetatileBehavior_IsDeepOrOceanWater(u8);
bool8 MetatileBehavior_IsSurfableAndNotWaterfall(u8);
bool8 MetatileBehavior_IsEastBlocked(u8);
bool8 MetatileBehavior_IsWestBlocked(u8);
bool8 MetatileBehavior_IsNorthBlocked(u8);
bool8 MetatileBehavior_IsSouthBlocked(u8);
bool8 MetatileBehavior_IsShortGrass(u8);
bool8 MetatileBehavior_IsHotSprings(u8);
bool8 MetatileBehavior_IsWaterfall(u8);
bool8 MetatileBehavior_IsFortreeBridge(u8);
bool8 MetatileBehavior_IsPacifidlogVerticalLogTop(u8);
bool8 MetatileBehavior_IsPacifidlogVerticalLogBottom(u8);
bool8 MetatileBehavior_IsPacifidlogHorizontalLogLeft(u8);
bool8 MetatileBehavior_IsPacifidlogHorizontalLogRight(u8);
bool8 MetatileBehavior_IsPacifidlogLog(u8);
bool8 MetatileBehavior_IsTrickHousePuzzleDoor(u8);
bool8 MetatileBehavior_IsRegionMap(u8);
bool8 MetatileBehavior_IsClosedSootopolisDoor(u8);
bool8 MetatileBehavior_IsSkyPillarClosedDoor(u8);
bool8 MetatileBehavior_IsRoulette(u8);
bool8 MetatileBehavior_IsPokeblockFeeder(u8);
bool8 MetatileBehavior_IsSecretBaseJumpMat(u8);
bool8 MetatileBehavior_IsSecretBaseSpinMat(u8);
bool8 MetatileBehavior_IsLavaridgeB1FWarp(u8);
bool8 MetatileBehavior_IsLavaridge1FWarp(u8);
bool8 MetatileBehavior_IsAquaHideoutWarp(u8);
bool8 MetatileBehavior_IsUnionRoomWarp(u8);
bool8 MetatileBehavior_IsMossdeepGymWarp(u8);
bool8 MetatileBehavior_IsSurfableFishableWater(u8);
bool8 MetatileBehavior_IsMtPyreHole(u8);
bool8 MetatileBehavior_IsCrackedFloorHole(u8);
bool8 MetatileBehavior_IsCrackedFloor(u8);
bool8 MetatileBehavior_IsMuddySlope(u8);
bool8 MetatileBehavior_IsBumpySlope(u8);
bool8 MetatileBehavior_IsIsolatedVerticalRail(u8);
bool8 MetatileBehavior_IsIsolatedHorizontalRail(u8);
bool8 MetatileBehavior_IsVerticalRail(u8);
bool8 MetatileBehavior_IsHorizontalRail(u8);
bool8 MetatileBehavior_IsSeaweed(u8);
bool8 MetatileBehavior_IsRunningDisallowed(u8);
bool8 MetatileBehavior_IsCuttableGrass(u8);
bool8 MetatileBehavior_IsRunningShoesManual(u8);
bool8 MetatileBehavior_IsPictureBookShelf(u8);
bool8 MetatileBehavior_IsBookShelf(u8);
bool8 MetatileBehavior_IsPokeCenterBookShelf(u8);
bool8 MetatileBehavior_IsVase(u8);
bool8 MetatileBehavior_IsTrashCan(u8);
bool8 MetatileBehavior_IsShopShelf(u8);
bool8 MetatileBehavior_IsBlueprint(u8);
bool8 MetatileBehavior_IsBattlePyramidWarp(u8);
bool8 MetatileBehavior_IsPlayerFacingWirelessBoxResults(u8 tile, u8 playerDir);
bool8 MetatileBehavior_IsCableBoxResults2(u8 tile, u8 playerDir);
bool8 MetatileBehavior_IsQuestionnaire(u8);
bool8 MetatileBehavior_IsLongGrass_Duplicate(u8);
bool8 MetatileBehavior_IsLongGrassSouthEdge(u8);
bool8 MetatileBehavior_IsTrainerHillTimer(u8);
bool8 MetatileBehavior_IsSpinRight(u8);
bool8 MetatileBehavior_IsSpinLeft(u8);
bool8 MetatileBehavior_IsSpinUp(u8);
bool8 MetatileBehavior_IsSpinDown(u8);
bool8 MetatileBehavior_IsRockClimbable(u8 metatileBehavior);

#endif // GUARD_METATILE_BEHAVIOR_H
