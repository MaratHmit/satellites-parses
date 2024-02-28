#ifndef SATELLITE_H
#define SATELLITE_H

#include <QString>

struct Satellite
{
    char name[13];
    char startDate[20];
    char endDate[20];
    char receiverType[25];
    char antennaType[17];
    char centerMassX[8];
    char centerMassY[8];
    char centerMassZ[8];
    char numberStations[9];
    char observationTypes[31];
    char type[5];
    char rinexVersion[7];
    bool isDup;
    bool isValide;

};

#endif // SATELLITE_H
