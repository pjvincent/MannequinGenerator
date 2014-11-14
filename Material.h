#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include <QVector3D>
#include <QPixmap>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Texture.h"

class GLWidget;

class Material
{
public:

    Material();
    Material(QString _mtllib, QString _mtlname, Texture * _texture, int _texturePosition);

    QVector3D Ka();
    QVector3D Kd();
    QVector3D Ks();

    QString name();

    void set_d(float _d);
    void set_Ns(float _Ns);
    void set_Ka(QVector3D _Ka);
    void set_Kd(QVector3D _Kd);
    void set_Ks(QVector3D _Ks);
    void setUniformValue(QGLShaderProgram *_program);
    void load(QString _mtllib, QString _mtlname, Texture *_texture, int _texturePosition);

    float Ns();
    float d();

private:

    Texture * m_texture;

    QString   m_mtlname;
    QString   m_mtllib;

    QVector3D m_Ka;
    QVector3D m_Kd;
    QVector3D m_Ks;

    float     m_Ns;
    float     m_d;

    int       m_texturePosition;

};

#endif // MATERIAL_H
