#include <QCoreApplication>
#include <handler.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Handler handler;
    handler.run();
    
    return a.exec();
}
