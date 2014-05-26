#ifndef PERLINCHUNKVIEWER_WIDGET_H
#define PERLINCHUNKVIEWER_WIDGET_H

#include <QWidget>

#include "FreeFlyCameraWidget.hpp"


class PerlinChunkViewer_Widget : public QWidget
{
    Q_OBJECT

private :
    FreeFlyCameraWidget*    _pFreeFlyCameraWidget;

public:
    explicit PerlinChunkViewer_Widget(QWidget *parent = 0);

signals:

public slots:

};

#endif // PERLINCHUNKVIEWER_WIDGET_H
