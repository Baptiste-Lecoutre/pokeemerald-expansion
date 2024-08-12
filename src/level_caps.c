#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "pokemon.h"


u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 15},
        {FLAG_BADGE02_GET, 21},
        {FLAG_BADGE03_GET, 32},
        {FLAG_MET_ARCHIE_METEOR_FALLS, 43},
        {FLAG_BADGE04_GET, 47},
        {FLAG_BADGE05_GET, 50},
        {FLAG_BADGE06_GET, 60},
        {FLAG_BADGE07_GET, 70},
        {FLAG_BADGE08_GET, 80},
        {FLAG_IS_CHAMPION, 90},
    };

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[7] = { 2, 3, 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetRelativePartyScalingExpValue(u32 level, u32 expValue)
{
    static const double sRelativePartyScaling[27] = {
        3.00, 2.75, 2.50, 2.33, 2.25,
        2.00, 1.80, 1.70, 1.60, 1.50,
        1.40, 1.30, 1.20, 1.10, 1.00,
        0.95, 0.90, 0.85, 0.80, 0.75,
        0.70, 0.65, 0.60, 0.55, 0.55,
        0.50, 0.50,
    };

    s32 avgDiff;
    u32 avgLevel, i;

    if (!B_EXP_RELATIVE_PARTY)
        return expValue;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE)
            avgLevel += gPlayerParty[i].level;
        else
            break;
    }
    avgLevel /= i+1;

    avgDiff = level - avgLevel;
    if (avgDiff >= 12)
        avgDiff = 12;
    else if (avgDiff <= -14)
        avgDiff = -14;
    avgDiff += 14;

    return expValue * sRelativePartyScaling[avgDiff];
}
