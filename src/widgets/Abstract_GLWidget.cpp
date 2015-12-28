

#include "Abstract_GLWidget.hpp"


#include "glheader.h"

#include "Core3_2_context.h"


#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif


#include <QTimer>


QGLFormat       getFormat()
{
    QGLFormat   glFormat;

    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >= Qt-4.8.0
    glFormat.setSampleBuffers( true );

    return (glFormat);
}

Abstract_GLWidget::Abstract_GLWidget(QWidget *parent)
    : QGLWidget( new Core3_2_context( getFormat() ), parent ),
      _loopMode(false)
{
    _pQTimer = new QTimer(this);

    connect( _pQTimer, SIGNAL(timeout()), this, SLOT(slot_timeout()) );
}

Abstract_GLWidget::~Abstract_GLWidget()
{
    setLoop(false);
}


////////////////////////////////////////////////////////////////

void	Abstract_GLWidget::initializeGL()
{
    std::cerr << "Abstract_GLWidget::initializeGL" << std::endl;

    glSetup();

    glCheckError();
}

void	Abstract_GLWidget::showEvent(QShowEvent*)
{

// #ifdef Q_WS_X11
//     XFlush(QX11Info::display());
// #endif

    updateGL();
}

////////////////////////////////////////////////////////////////

void	Abstract_GLWidget::slot_timeout()
{
    this->update();
    this->updateGL();
}

////////////////////////////////////////////////////////////////

void	Abstract_GLWidget::setLoop(bool loopMode)
{
    if (loopMode == _loopMode)
        return;

    if (!loopMode)
        _pQTimer->stop();
    else
    {
        _pQTimer->setInterval( 1.0f / 30.0f * 1000 );
        _pQTimer->start();
    }

    _loopMode = loopMode;
}

