#include "reader.h"
#include "consts.h"
#include "satellite.h"

#include <QThread>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTextCodec>

Reader::Reader(QString path) :
    pathFile(path)
{
    maxFileSize = MAX_FILE_SIZE_MB * 1024 * 1024;
    printer = &Printer::getInstance();
}

Reader::~Reader()
{
    delete satellitesInfo;
}

void Reader::run()
{
    satellitesInfo = new SatellitesInfo();    

    if (!checkFile()) {
        this->thread()->quit();        
        return;
    }

    readFile();
}

bool Reader::checkFile()
{
    QFileInfo fileInfo(pathFile);

    if (!fileInfo.exists() || !fileInfo.isFile()) {
        printer->showError(ERR_FILE_NOT_FOUND, pathFile);
        return false;
    }

    if (!fileInfo.size()) {
        printer->showError(ERR_FILE_EMPTY, pathFile);
        return false;
    }

    if (fileInfo.size() > maxFileSize) {
        printer->showError(ERR_FILE_LARGE, pathFile);
        return false;
    }

    satellitesInfo->fileName = fileInfo.fileName();

    return true;
}

void Reader::readFile()
{
    int sizeSatellite = sizeof(Satellite);

    QFile file(pathFile);
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
    {        
        int i = 0;
        printer->showMessage(MSG_READ_FILE, pathFile);
        while(!file.atEnd())
        {
            if (i >= HEADER_ROW_COUNT) {
                Satellite *s = new Satellite();
                int size = file.readLine(reinterpret_cast<char*>(s), sizeSatellite);
                if (size)
                    satellitesInfo->addSattelite(s);
            } else {
                QString str = file.readLine();
                if (!i)
                    satellitesInfo->readAsDate(str);
            }
            i++;
        }
        if (!satellitesInfo->validate()) {
            printer->showError(ERR_FILE_NOT_FORMATTED, pathFile);
            this->thread()->quit();            
            return;
        }        
    }
    else
        printer->showError(ERR_FILE_READING, pathFile);        
    this->thread()->quit();
}

void Reader::printData()
{
    satellitesInfo->print();
}
