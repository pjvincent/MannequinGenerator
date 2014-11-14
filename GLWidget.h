#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFunctions>
#include <QtGui>

#include "Object3D.h"

class GLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

public:

    GLWidget(QWidget *_parent = NULL);
    void append(Object3D * _object);

protected:

    void initializeGL();
    void resizeGL(int _width, int _height);
    void paintGL();
    void mousePressEvent(QMouseEvent *_event);
    void mouseMoveEvent(QMouseEvent *_event);
    void wheelEvent(QWheelEvent *_event);

private slots:

    void movement();

private:

    void rotate(int _x, int _y);
    void translate(int _x, int _y);

    QList<Object3D *>   m_objects3D;
    QGLShaderProgram  * m_program;
    QVector3D           m_camCentre;
    QVector3D           m_camEye;
    QVector3D           m_camUp;
    QVector3D           m_lightPos;
    QVector2D           m_rotation;
    QPoint              m_last_pos;

    QPoint              m_mouseMoving;

    QTimer              m_tmrFluidMovement;

    Qt::MouseButton     m_mouseButton;
};

#endif  /* _GLWIDGET_H */
