#ifndef GUARD_TRAINER_RADAR_H
#define GUARD_TRAINER_RADAR_H

struct RouteTrainers
{
    const u16 *routeTrainers;
    u8 numTrainers;
};

extern const struct RouteTrainers gRouteTrainers[];

void CB2_TrainerRadar(void);
void InitTrainerRadar(MainCallback callback);
void Task_OpenTrainerRadarFromPokenav(u8 taskId);
u32 PokeNavMenuTrainerRadarCallback(void);

#endif
