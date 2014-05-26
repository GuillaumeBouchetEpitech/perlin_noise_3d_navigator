#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMdiArea>

#include "widgets/perlin3dviewerwidget.h"
#include "widgets/chunkpropertieswidget.h"


class MainWindow : public QMainWindow
{
private :
    Q_OBJECT

private :
//    QMdiArea*   _pQMdiArea;
    Perlin3DViewerWidget*   _pPerlin3DViewerWidget;
    ChunkPropertiesWidget*  _pChunkPropertiesWidget;

public :
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected :
    virtual void    closeEvent( QCloseEvent* );

signals :

public slots :
    void    askWindow_GenerationProperties();

};


#endif // MAINWINDOW_H
