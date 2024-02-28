#ifndef HANDLER_H
#define HANDLER_H

#include "satellite.h"
#include "satellitesinfo.h"
#include "printer.h"

#include <QString>
#include <QTextStream>
#include <QByteArray>
#include <QObject>

class Reader : public QObject
{
    Q_OBJECT

public:
    explicit Reader(QString path);
    virtual ~Reader();

    void printData();

private:
    QString pathFile;
    QTextStream *outStream;    
    QByteArray buffer;    
    QList<Satellite> listSatellite;
    int maxFileSize;
    SatellitesInfo *satellitesInfo;
    Printer *printer;

    bool checkFile();
    void readFile();

public slots:
    void run();

signals:
    void finished(bool);
};

#endif // HANDLER_H
