

#ifndef	FreeFlyCameraWidget_HPP
#define	FreeFlyCameraWidget_HPP


#include "Abstract_GLWidget.hpp"

#include "myGL/GL_FreeFlyController.hpp"


class	FreeFlyCameraWidget : public Abstract_GLWidget
{
    Q_OBJECT

public :
    explicit FreeFlyCameraWidget(QWidget *parent = 0);
    virtual ~FreeFlyCameraWidget();

protected :
    myGL::GL_FreeFlyController  _FreeFly;
    myGL::GL_FrustumCulling     _Frustum;

    myGL::GL_Matrix             _projectionMatrix, _viewMatrix;

    ///

public :
    virtual void	focusOutEvent(QFocusEvent*);

protected:
    virtual void    closeEvent(QCloseEvent *event);

    virtual void	mouseMoveEvent(QMouseEvent* event);
    virtual void	mousePressEvent(QMouseEvent* event);

    void            managekey_Event(QKeyEvent* keyEvent, float value);
    virtual void	keyPressEvent(QKeyEvent* keyEvent);
    virtual void	keyReleaseEvent(QKeyEvent* keyEvent);

public :

    virtual void	initializeGL();
    virtual void    update();
    void            manual_resize(int width, int height);
    virtual void	resizeGL(int width, int height);

};


#endif	// FreeFlyCameraWidget_HPP

