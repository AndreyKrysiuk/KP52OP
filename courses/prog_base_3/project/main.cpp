#include "guitartuner.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuitarTuner w;
    w.show();

    return a.exec();
}
