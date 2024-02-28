#include "printer.h"
#include "iostream"

#include <QTextCodec>

Printer * Printer::pInstance = 0;
PrinterDestroyer Printer::destroyer;

PrinterDestroyer::~PrinterDestroyer() {
    delete p_instance;
}

void PrinterDestroyer::initialize(Printer* p) {
    p_instance = p;
}

Printer& Printer::getInstance() {
    if(!pInstance)     {
        pInstance = new Printer();
        destroyer.initialize(pInstance);
    }
    return *pInstance;
}

Printer::Printer()
{
    outStream = new QTextStream(stdout);
    outStream->setCodec(QTextCodec::codecForName("cp866"));

}

void Printer::showError(const int errNumber, const QString arg)
{
     QString qs;
    switch (errNumber) {
    case ERR_FILE_NOT_FOUND:
        qs = QString("File %1 not found! Processing will be terminated!").arg(arg);
        break;
    case ERR_FILE_EMPTY:
        qs = QString("File %1 is empty! Processing will be terminated!").arg(arg);
        break;
    case ERR_FILE_LARGE:
        qs = QString("File size: %1 is more than 10 MB! Processing will be terminated!").arg(arg);
        break;
    case ERR_FILE_NOT_FORMATTED:
        qs = QString("File %1 does not match the expected format! Processing will be terminated!").arg(arg);
        break;
    case ERR_FILE_READING:
        qs = QString("File %1 could not be read! Processing will be terminated!").arg(arg);
        break;
    case ERR_DIR_NOT_FOUND:
        qs = "The specified directory was not found! Processing will be terminated!";
        break;
    default:
        break;
    }
    std::cout << qs.toStdString() << "\n";
}

void Printer::showMessage(const int messNumber, const QString arg)
{
    QString qs;
    switch (messNumber) {
    case MSG_START_PARSING:
        qs = "Parser start!";
        break;
    case MSG_READ_FILE:
        qs = QString("File %1 read!").arg(arg);
        break;
    case MSG_READ_FILES_IN_DIR:
        qs = "Reading files in directory!";
        break;
    case MSG_END_PARSING:
        qs = "Parsing completed!";
        break;
    default:
        break;
    }
    std::cout << qs.toStdString() << std::endl;
}

void Printer::printText(const QString message)
{    
    std::cout << message.toStdString();
}
