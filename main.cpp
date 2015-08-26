#include "Headcookerwindow.h"
#include <QApplication>


using namespace std;
void test();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HeadcookerWindow w;
    w.show();

    return a.exec();
}
