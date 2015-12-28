
#include "widgets/perlin3dviewerwidget.h"

#include <QApplication>

#include "widgets/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    MainWindow      w;
    w.show();

    return (app.exec());
}
