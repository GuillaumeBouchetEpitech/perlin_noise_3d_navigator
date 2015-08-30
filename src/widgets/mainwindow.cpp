#include "mainwindow.h"


#include "navigator_globalvalue.h"


#include <QAction>

#include <QApplication>

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include <QMdiSubWindow>


#include <QPoint>   /// this->pos()


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    Navigator_GlobalValue::pTest = new Navigator_GlobalValue;

    QAction*    pQAction_Quit = new QAction("&Quit", this);
    connect( pQAction_Quit, SIGNAL(triggered()), qApp, SLOT(quit()) );

    QAction*    pQAction_SwitchViewMode = new QAction("&SwitchViewMode", this);
    connect( pQAction_SwitchViewMode, SIGNAL(triggered()),
             this, SLOT(askWindow_GenerationProperties()) );

    {
        QMenu*  pQMenu_File = menuBar()->addMenu("&File");
        pQMenu_File->addAction( pQAction_Quit );

        QMenu*  pQMenu_View = menuBar()->addMenu("&View");
        pQMenu_View->addAction( pQAction_SwitchViewMode );
    }

    {
        QToolBar*   pQToolBar = addToolBar("File");

//        pQToolBar->addAction( pQAction_Quit );
        pQToolBar->addAction( pQAction_SwitchViewMode );
    }

    {
//        _pQMdiArea = new QMdiArea;

//        QMdiSubWindow*  pQMdiSubWindow1 = _pQMdiArea->addSubWindow(new Perlin3DViewerWidget);
//        QMdiSubWindow*  pQMdiSubWindow2 = _pQMdiArea->addSubWindow(new ChunkPropertiesWidget);

//        setCentralWidget(_pQMdiArea);

        _pPerlin3DViewerWidget = new Perlin3DViewerWidget(this);

        setCentralWidget( _pPerlin3DViewerWidget );

        _pChunkPropertiesWidget = new ChunkPropertiesWidget(NULL);
        _pChunkPropertiesWidget->setVisible(false);
    }

}

MainWindow::~MainWindow()
{
    delete _pChunkPropertiesWidget;
}

void    MainWindow::closeEvent( QCloseEvent* )
{
    _pChunkPropertiesWidget->close();
}

void    MainWindow::askWindow_GenerationProperties()
{
    _pChunkPropertiesWidget->setVisible( !_pChunkPropertiesWidget->isVisible() );

    if (_pChunkPropertiesWidget->isVisible())
        _pChunkPropertiesWidget->move( this->x(), this->y() );
}


