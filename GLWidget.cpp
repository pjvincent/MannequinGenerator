#include <QtOpenGL>
#include <QDebug>
#include <QtGui>

#include "GLWidget.h"

GLWidget::GLWidget(QWidget *_parent) : QGLWidget(_parent)
{

    connect(&m_tmrFluidMovement, SIGNAL(timeout()), this, SLOT(movement()));

    // m_camEye    = QVector3D(0, 0, 400);

    m_tmrFluidMovement.start(10);

    m_camEye = QVector3D(0, 0, 212.576);

    m_camCentre = QVector3D(0, 0, 0) ;
    m_camUp     = QVector3D(0, 1, 0);
    m_lightPos  = QVector3D(50, 50, 50);
    m_rotation  = QVector2D(0, 0);
}


void GLWidget::movement()
{
    int dx = m_mouseMoving.x();
    int dy = m_mouseMoving.y();

    if(m_mouseMoving != QPoint(0, 0))
    {
        if (m_mouseButton == Qt::RightButton)
            rotate(dy, dx);

        else if (m_mouseButton == Qt::LeftButton)
            translate(-dx, dy);
    }

    if(m_mouseMoving != QPoint(0, 0))
        m_mouseMoving = QPoint(m_mouseMoving.x() * 0.9,
                               m_mouseMoving.y() * 0.9);
}


void GLWidget::initializeGL()
{
    initializeGLFunctions(context());

    // glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(2);
    qglClearColor(QColor(216, 216, 216));

    m_program = new QGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QGLShader::Vertex, ":/vertex.glsl");
    m_program->addShaderFromSourceFile(QGLShader::Fragment, ":/fragment.glsl");

    // m_program->addShaderFromSourceFile(QGLShader::Geometry, ":/geometry.glsl");
    // m_program->setGeometryInputType(GL_TRIANGLES);
    // m_program->setGeometryOutputType(GL_TRIANGLES);
    // m_program->setGeometryOutputVertexCount(3);

    m_program->bindAttributeLocation("vertex",      PROGRAM_VERTEX_ATTRIBUTE);
    m_program->bindAttributeLocation("texCoord",    PROGRAM_TEXCOORD_ATTRIBUTE);
    m_program->bindAttributeLocation("normal",      PROGRAM_NORMAL_ATTRIBUTE);

    m_program->bindAttributeLocation("direction",   PROGRAM_DIRECTION_ATTRIBUTE);
    m_program->bindAttributeLocation("chest",       PROGRAM_CHEST_ATTRIBUTE);
    m_program->bindAttributeLocation("waist",       PROGRAM_WAIST_ATTRIBUTE);
    m_program->bindAttributeLocation("arms",        PROGRAM_ARMS_ATTRIBUTE);
    m_program->bindAttributeLocation("legs",        PROGRAM_LEGS_ATTRIBUTE);

    m_program->bindAttributeLocation("indexVertex",     PROGRAM_INDEX_VERTEX_ATTRIBUTE);
    m_program->bindAttributeLocation("indexTexCoord",   PROGRAM_INDEX_TEXCOORD_ATTRIBUTE);
    m_program->bindAttributeLocation("indexNormal",     PROGRAM_INDEX_NORMAL_ATTRIBUTE);

    m_program->link();

    QMatrix4x4 initTranslation, initRotation;

    // initTranslation.translate(-QVector3D(0.586947, 163.801, 38.1504));
    initTranslation.translate(-QVector3D(0.586947, 88.971, 38.1504));
    initRotation.rotate(10, 0, 1, 0);

    m_program->bind();
    m_program->setUniformValue("initRotation", initRotation);
    m_program->setUniformValue("initTranslation", initTranslation);
    m_program->release();

    GLint max;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
    qDebug() << "max" << max;
}


void GLWidget::resizeGL(int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}


void GLWidget::paintGL()
{
    qDebug() << "paintGL";

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 model, view, projection;

    view.lookAt(m_camEye, m_camCentre, m_camUp);

    model.rotate(m_rotation.x(), 1.0, 0.0, 0.0);
    model.rotate(m_rotation.y(), 0.0, 1.0, 0.0);

    projection.perspective(50.0, 1.0 * width() / height(), 1, 1000.0);

    // projection.ortho(-100, width() * 200.0 / height() - 100, -100, 100, 0.1, 10000.0);

    m_program->bind();

    m_program->setUniformValue("model", model);
    m_program->setUniformValue("view", view);
    m_program->setUniformValue("perspective", projection);

    m_program->setUniformValue("height", height());
    m_program->setUniformValue("width", width());
    m_program->setUniformValue("pixelWidth", (GLfloat) (2.0 / width()));
    m_program->setUniformValue("pixelHeight", (GLfloat) (2.0 / height()));

    m_program->setUniformValue("lightPos", m_lightPos);
    m_program->setUniformValue("eyePos", m_camEye);

    m_program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    m_program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    m_program->enableAttributeArray(PROGRAM_NORMAL_ATTRIBUTE);

    m_program->enableAttributeArray(PROGRAM_DIRECTION_ATTRIBUTE);
    m_program->enableAttributeArray(PROGRAM_CHEST_ATTRIBUTE);
    m_program->enableAttributeArray(PROGRAM_WAIST_ATTRIBUTE);
    m_program->enableAttributeArray(PROGRAM_ARMS_ATTRIBUTE);
    m_program->enableAttributeArray(PROGRAM_LEGS_ATTRIBUTE);

    m_program->enableAttributeArray(PROGRAM_INDEX_VERTEX_ATTRIBUTE);
    m_program->enableAttributeArray(PROGRAM_INDEX_TEXCOORD_ATTRIBUTE);
    m_program->enableAttributeArray(PROGRAM_INDEX_NORMAL_ATTRIBUTE);

    m_objects3D[0]->drawOpaque(m_program, GL_TRIANGLES);

    for(int i = 1; i < m_objects3D.count(); i++)
        m_objects3D[i]->drawOpaque(m_program, GL_TRIANGLES);


    m_objects3D[0]->drawTransparent(m_program, GL_TRIANGLES);

    for(int i = 1; i < m_objects3D.count(); i++)
        m_objects3D[i]->drawTransparent(m_program, GL_TRIANGLES);

    m_program->release();
}


void GLWidget::mousePressEvent(QMouseEvent *_event)
{
    m_last_pos = _event->pos();
}


void GLWidget::mouseMoveEvent(QMouseEvent *_event)
{
    //    int dx = _event->x() - m_last_pos.x();
    //    int dy = _event->y() - m_last_pos.y();

    if (_event->buttons() & Qt::RightButton)
        m_mouseButton = Qt::RightButton;

    else if (_event->buttons() & Qt::LeftButton)
        m_mouseButton = Qt::LeftButton;

    m_mouseMoving = _event->pos() - m_last_pos;
    m_last_pos = _event->pos();

    qDebug() << "m_mouseMoving " << m_mouseMoving;
}


void GLWidget::wheelEvent(QWheelEvent *_event)
{
    float zoom = 0.9f;

    if(_event->delta() < 0)
        zoom = 1.0 / zoom;

    m_camEye.setZ(m_camEye.z() * zoom);

    qDebug() << "m_camEye " << m_camEye;

    update();
}


void GLWidget::rotate(int _x, int _y)
{
    Q_UNUSED(_x);

    m_rotation += QVector2D(_x, _y) * QVector2D(0.1, 0.2);

    float verticalLimit = 30;

    if(qAbs(m_rotation.x()) > verticalLimit)
        m_rotation.setX(verticalLimit * m_rotation.x() / qAbs(m_rotation.x()));

    update();
}


void GLWidget::translate(int _x, int _y)
{
    Q_UNUSED(_x);
    QVector3D vec = QVector3D(0, _y, 0) * m_camEye.z() / 1800.0;

    m_camCentre += vec;
    m_camEye += vec;

    float verticalLimit = 70;

    if(qAbs(m_camCentre.y()) >  verticalLimit)
    {
        float correction = (qAbs(m_camCentre.y()) -  verticalLimit) * m_camCentre.y() / qAbs(m_camCentre.y());
        m_camCentre.setY(m_camCentre.y() - correction);
        m_camEye.setY(m_camEye.y() - correction);
    }

    qDebug() << "m_camEye " << m_camEye;
    qDebug() << "m_camCentre " << m_camCentre;

    update();
}


void GLWidget::append(Object3D * _object)
{
    _object->setAdded(true);
    m_objects3D.append(_object);
}

