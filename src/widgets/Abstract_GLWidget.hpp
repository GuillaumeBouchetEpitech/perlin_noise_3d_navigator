

#ifndef	WIDGET_MYGL_HPP
#define WIDGET_MYGL_HPP



//#include "GL_Header.hpp"

#include "glheader.h"

#include <QtGlobal>

#include <QGLContext>
#include <QGLWidget>


class Abstract_GLWidget : public QGLWidget
{
    Q_OBJECT

private :

    QTimer* _pQTimer;
    bool    _loopMode;

public :

    explicit Abstract_GLWidget(QWidget *parent = 0);
    virtual ~Abstract_GLWidget();

public :

    virtual void initializeGL();
    virtual void update() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;

public :

    void	showEvent(QShowEvent*);

public :

    void	setLoop(bool loopMode);
    inline bool	getLoop() const { return (_loopMode); }

private slots :

    virtual void slot_timeout();

};


#endif	// WIDGET_MYGL_HPP

