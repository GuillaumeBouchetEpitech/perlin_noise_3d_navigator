
#include "widgets/perlin3dviewerwidget.h"

#include <QApplication>

/**
int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);

    Perlin3DViewerWidget    w;
    w.show();

    return (a.exec());
}

/**

#include <QTabWidget>

#include "widgets/chunkpropertieswidget.h"

#include "navigator_globalvalue.h"


int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    Navigator_GlobalValue::pTest = new Navigator_GlobalValue;

    QTabWidget      w;
    w.setMinimumSize(500, 400);

    Perlin3DViewerWidget*   pChild1 = new Perlin3DViewerWidget;
    ChunkPropertiesWidget*  pChild2 = new ChunkPropertiesWidget;

    w.addTab( pChild1, QString("Child1"));
    w.addTab( pChild2, QString("Child2"));

    w.show();

    return (app.exec());
}

//*/


#include "widgets/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    MainWindow      w;
    w.show();

    return (app.exec());
}
