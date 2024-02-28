#ifndef SATELLITESINFO_H
#define SATELLITESINFO_H

#include "satellite.h"
#include "printer.h"

#include <QString>
#include <QList>
#include <QDateTime>

class SatellitesInfo
{
public:
    SatellitesInfo();    
    ~SatellitesInfo();

    QDateTime asOfDate;
    QString fileName;

    void addSattelite(Satellite* sattelite);    
    void readAsDate(const QString str);    
    void print();
    bool validate();    

private:
    QList<Satellite*> satellites;
    Printer *printer;

    void correctSattellite(Satellite *s);
    void correctChars(char *ch, int size);
    bool isValid(Satellite *s);
    bool isCanAppend(Satellite *s);
    bool existSatellite(Satellite *satellite, bool checkIsValid = false);

};

#endif // SATELLITESINFO_H
