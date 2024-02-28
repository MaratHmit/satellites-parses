#include "reader.h"
#include "handler.h"
#include "iostream"

#include <QDir>
#include <QFileInfoList>
#include <QTextStream>
#include <QTextCodec>
#include <QObject>
#include <QThread>

Handler::Handler(QObject *parent) :
    QObject(parent)
{
    printer = &Printer::getInstance();
}

void Handler::run()
{
    printer->showMessage(MSG_START_PARSING);
    QString path = getPathFolder();
    if (path.isNull())
        return;

    QList<QThread*> listThreads;
    QList<Reader*> listReaders;
    QStringList listFiles = readFiles(path);    
    foreach(QString item, listFiles) {
        QThread *thread = new QThread();
        Reader *reader = new Reader(item);
        reader->moveToThread(thread);
        listThreads.append(thread);
        listReaders.append(reader);
        connect(thread, SIGNAL(started()), reader, SLOT(run()));                
        thread->start();
    }

    foreach (QThread *thread, listThreads) {
        thread->wait();
        thread->deleteLater();
    }

    foreach (Reader *reader, listReaders) {
        reader->printData();
        delete reader;
    }


    printer->showMessage(MSG_END_PARSING);
}

QString Handler::getPathFolder()
{
    char dirFiles[255];

    printer->printText("Enter the path to the directory with files *.status (sample: D:\\MyFiles): ");
    std::cin >> dirFiles;

    QString dir = QString::fromUtf8(dirFiles);

    if (QDir(dir).exists())
        return dir;

    printer->showError(ERR_DIR_NOT_FOUND);
    return QString();
}

QStringList Handler::readFiles(QString path)
{
    QStringList result;

    printer->showMessage(MSG_READ_FILES_IN_DIR);

    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    QStringList filters;
    filters << QString("*.status");
    dir.setNameFilters(filters);

    QFileInfoList listTmp = dir.entryInfoList();
    foreach(QFileInfo item, listTmp) {

        result.append(item.absoluteFilePath());
    }

    return result;
}

