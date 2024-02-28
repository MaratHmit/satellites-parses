#ifndef READER_H
#define READER_H

#include "printer.h"

#include <QObject>

class Handler : public QObject
{
    Q_OBJECT

public:
    explicit Handler(QObject *parent=0);
    void run();

private:
    Printer *printer;

    QString getPathFolder();
    QStringList readFiles(QString path);

};

#endif // READER_H
