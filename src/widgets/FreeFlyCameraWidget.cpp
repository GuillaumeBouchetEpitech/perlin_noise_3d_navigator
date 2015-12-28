
#include "FreeFlyCameraWidget.hpp"


#include "../myGL/GL_Matrix.hpp"

#include <QMouseEvent>

#include <iostream>


FreeFlyCameraWidget::FreeFlyCameraWidget(QWidget *parent)
    : Abstract_GLWidget(parent)
{

    //setMinimumSize(400, 300);
    //setMinimumSize(600, 480);
    setMinimumSize(800, 600);

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    {

        _FreeFly._mouse_dec_x = 0;
        _FreeFly._mouse_dec_y = 0;
        _FreeFly._sens_l = 0;
        _FreeFly._sens_f = 0;
        _FreeFly.advance( _viewMatrix, 0.0f );

    }

}

FreeFlyCameraWidget::~FreeFlyCameraWidget()
{
}

/////////////////////////////////////////////////////////////////

void	FreeFlyCameraWidget::focusOutEvent(QFocusEvent*)
{

    if (this->getLoop())
    {
        QCursor	c = cursor();
        c.setShape(Qt::ArrowCursor);
        setCursor(c);

        _FreeFly._mouse_dec_x = 0;
        _FreeFly._mouse_dec_y = 0;
        _FreeFly._sens_f = 0;
        _FreeFly._sens_l = 0;

        setLoop(false);
    }

}

void    FreeFlyCameraWidget::closeEvent(QCloseEvent *event)
{
    (void)event;

    setLoop(false);
}

/////////////////////////////////////////////////////////////////

void	FreeFlyCameraWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!this->getLoop())
        return;

    _FreeFly._mouse_dec_x = static_cast<float>(event->x()) - static_cast<float>(width()) / 8 * 3;
    _FreeFly._mouse_dec_y = static_cast<float>(event->y()) - static_cast<float>(height()) / 2;
}

void	FreeFlyCameraWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if (!this->getLoop())
    {
        QCursor	c = cursor();
        c.setPos( mapToGlobal( QPoint(width() / 8 * 3, height() / 2) ) );
        c.setShape(Qt::BlankCursor);
        setCursor(c);

        setLoop(true);
    }

    else
    {
        QCursor	c = cursor();
        c.setShape(Qt::ArrowCursor);
        setCursor(c);

        _FreeFly._mouse_dec_x = 0;
        _FreeFly._mouse_dec_y = 0;
        _FreeFly._sens_f = 0;
        _FreeFly._sens_l = 0;

        setLoop(false);
    }

}

void    FreeFlyCameraWidget::managekey_Event(QKeyEvent* keyEvent, float value)
{
    if (!this->getLoop())
        return;

    switch (keyEvent->key())
    {
    case Qt::Key_W: // qwerty
    case Qt::Key_Z: // azerty
        _FreeFly._sens_f = +value;
        break;

    case Qt::Key_S:
        _FreeFly._sens_f = -value;
        break;

    case Qt::Key_A: // qwerty
    case Qt::Key_Q: // azerty
        _FreeFly._sens_l = -value;
        break;

    case Qt::Key_D:
        _FreeFly._sens_l = +value;
        break;

        /**
    case Qt::Key_Space :

        myGL::Vec2f Target(this->width() / 2, this->height() / 2);
        myGL::Vec3f Position;
        std::cerr << "pos : " << _FreeFly.getPosition().x << " / " << _FreeFly.getPosition().y << " / " << _FreeFly.getPosition().z << std::endl;

        if (_FreeFly.get3DPoint( Target, Position ))
            std::cerr << "space : " << Position.x << " / " << Position.y << " / " << Position.z << std::endl;
        else
            std::cerr << "space : fail" << std::endl;
        break;
        //*/

    }
}

void	FreeFlyCameraWidget::keyPressEvent(QKeyEvent* keyEvent)
{
    managekey_Event( keyEvent, 1 );
}

void	FreeFlyCameraWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
    managekey_Event( keyEvent, 0 );
}
//*/

/////////////////////////////////////////////////////////////////

void	FreeFlyCameraWidget::initializeGL()
{
    Abstract_GLWidget::initializeGL();

    ///

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    /**
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //*/

    glEnable(GL_LINE_SMOOTH);

    glCheckError();
}

void    FreeFlyCameraWidget::update()
{

    if (this->getLoop())
    {
        //_FreeFly.advance( 1.0f / 30.0f );
        _FreeFly.advance( _viewMatrix, 1.0f / 30.0f );

        QCursor	c = cursor();
        c.setPos( mapToGlobal( QPoint(width() / 8 * 3, height() / 2) ) );
        setCursor(c);

        _FreeFly._mouse_dec_x = 0;
        _FreeFly._mouse_dec_y = 0;
    }

    {
        int tmp_width = this->width();
        int tmp_height = std::max(this->height(), 1);

        tmp_width = tmp_width / 4 * 3;

        glViewport(0, 0, tmp_width, tmp_height);

        //resizeGL(width, height);
        //mannual_resize(width, height);
    }

    _Frustum.calculateFrustum( _projectionMatrix, _viewMatrix );
}

void    FreeFlyCameraWidget::manual_resize(int width, int height)
{
    if (height == 0)
        height = 1;

    width = width / 4 * 3;

    glViewport(0, 0, width, height);

    //_FreeFly.resize(width / 4 * 3, height);

    double  aspectRatio = static_cast<double>(width) / height;
    _projectionMatrix.Make_Perspective( 70.0, aspectRatio, 1.0,100.0 );

    glCheckError();
}

void	FreeFlyCameraWidget::resizeGL(int width, int height)
{
    manual_resize(width, height);
}

/**
void	FreeFlyCameraWidget::paintGL()
{
}
//*/

