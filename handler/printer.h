#ifndef PRINTER_H
#define PRINTER_H

#include <QTextStream>

// коды ошибок
const int ERR_FILE_NOT_FOUND = 0;
const int ERR_FILE_EMPTY = 1;
const int ERR_FILE_LARGE = 2;
const int ERR_FILE_NOT_FORMATTED = 3;
const int ERR_FILE_READING = 4;
const int ERR_DIR_NOT_FOUND = 5;

// коды сообщений
const int MSG_START_PARSING = 0;
const int MSG_READ_FILES_IN_DIR = 1;
const int MSG_END_PARSING = 2;
const int MSG_READ_FILE = 3;

class Printer;

class PrinterDestroyer
{

private:
    Printer* p_instance;

public:
    ~PrinterDestroyer();
    void initialize(Printer* p);
};

class Printer
{
    static Printer* pInstance;
    static PrinterDestroyer destroyer;

public:
    static Printer& getInstance();
    void printText(const QString message);
    void showError(const int errNumber, const QString arg = QString());
    void showMessage(const int messNumber, const QString arg = QString());

protected:
    Printer();
    Printer(const Printer&);
    Printer& operator=(Printer&);
    ~Printer() { }
    friend class PrinterDestroyer;

private:
    QTextStream *outStream;

};

#endif // PRINTER_H
