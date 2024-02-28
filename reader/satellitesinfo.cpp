#include "satellitesinfo.h"
#include "consts.h"
#include "iostream"


#include <QDateTime>
#include <QLocale>

SatellitesInfo::SatellitesInfo()
{
    printer = &Printer::getInstance();
}

SatellitesInfo::~SatellitesInfo()
{
    foreach (Satellite *s, satellites)
        delete s;
}

void SatellitesInfo::addSattelite(Satellite* sattelite)
{    
    correctSattellite(sattelite);
    sattelite->isValide = isValid(sattelite);
    sattelite->isDup = existSatellite(sattelite);
    if (isCanAppend(sattelite))
        satellites.append(sattelite);
    else
        delete sattelite;
}

void SatellitesInfo::readAsDate(const QString str)
{
    QLocale locale(QLocale("en_US"));
    QString strAsDate = str.mid(INDEX_AS_OF_DATE, SIZE_AS_OF_DATE);
    QDateTime dt = locale.toDateTime(strAsDate,  "MMM dd yyyy hh:mm:ss");
    if (dt.isValid())
        asOfDate = dt;
}

void SatellitesInfo::print()
{
    if (!validate())
        return;

    printer->printText(STR_DOTS);
    printer->printText(QString("File: " + fileName + "\n"));
    QString asDate = "Date of measurement: ";
    asDate = asDate + asOfDate.toString("dd.mm.yyyy hh:mm:ss") + "\n";
    printer->printText(asDate);
    printer->printText("Satellites:\n");
    foreach (Satellite *s, satellites) {
        if (!s->isValide)
            continue;

        QString str = QString(&s->name[0]) + "\n";
        if (s->isDup)
            str = "+" + str;
        printer->printText(str);
    }
    printer->printText("\n");
}

bool SatellitesInfo::validate()
{
    return asOfDate.isValid();
}

void SatellitesInfo::correctSattellite(Satellite *s)
{
    s->isDup = false;
    correctChars(&s->name[0], sizeof(s->name));
    correctChars(&s->startDate[0], sizeof(s->startDate));
    correctChars(&s->endDate[0], sizeof(s->endDate));
    correctChars(&s->receiverType[0], sizeof(s->receiverType));
    correctChars(&s->antennaType[0], sizeof(s->antennaType));
    correctChars(&s->centerMassX[0], sizeof(s->centerMassX));
    correctChars(&s->centerMassY[0], sizeof(s->centerMassY));
    correctChars(&s->centerMassZ[0], sizeof(s->centerMassZ));
    correctChars(&s->numberStations[0], sizeof(s->numberStations));
    correctChars(&s->observationTypes[0], sizeof(s->observationTypes));
    correctChars(&s->type[0], sizeof(s->type));
    correctChars(&s->rinexVersion[0], sizeof(s->rinexVersion));
}

void SatellitesInfo::correctChars(char *ch, int size)
{
    char *t = ch;
    for (int i = 0; i < size; i++) {
        if (*t == '\n') {
            *t = 0;
            return;
        }
        t++;
    }
    ch = ch + size - 1;
    for (int k = size - 1; k >= 0; k--) {
        if (*ch != 32)
            break;
        else
            *ch = 0;
        ch--;
    }
}

bool SatellitesInfo::isValid(Satellite *s)
{
    return s->name[0] && s->startDate[0] && s->endDate[0] && s->receiverType[0] &&
            s->antennaType[0] && s->centerMassX[0] && s->centerMassY[0]&& s->centerMassZ[0] &&
            s->numberStations[0] && s->observationTypes[0] && s->type[0] && s->rinexVersion[0];
}

bool SatellitesInfo::isCanAppend(Satellite *s)
{
    if ((s->isValide && !s->isDup) || !s->isValide)
        return true;

    if (s->isValide && !existSatellite(s, true))
        return true;

    return false;
}

bool SatellitesInfo::existSatellite(Satellite *satellite, bool checkIsValid)
{
    foreach (Satellite *s, satellites) {
        if ((s != satellite) && ((!strcmp(&s->name[0], &satellite->name[0]) && !checkIsValid) ||
                                 (!strcmp(&s->name[0], &satellite->name[0]) && checkIsValid && s->isValide))) {
            s->isDup = true;
            return true;
        }
    }
    return false;
}

