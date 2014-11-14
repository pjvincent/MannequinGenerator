#ifndef OBJET_H
#define OBJET_H

#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <QtGui>
#include <QGLShader>
#include <QVector3D>

#include "Group3D.h"
#include "Global.h"

using namespace std;

enum ObjectType { HAIR, SKIN, EYES, OTHER };

class Object3D
{

public:

    Object3D();

    QVector3D center();
    QVector3D center2();
    QString fileName();
    QString complementFileName();
    QString mtllib();

    QList<Group3D> * groups3D();

    void addGroup3D(QString _mtlname, Texture *_texture, int _texturePosition = 0);
    bool load(QString _fileName, ObjectType _objectType);
    void loadComplement(QString _complementFileName);
    void drawOpaque(QGLShaderProgram *_program, GLenum _mode);
    void drawTransparent(QGLShaderProgram * _program, GLenum _mode);
    void rotation(QMatrix4x4 _mat);
    void scaleTranslation(QMatrix4x4 _mat);

    void loadFace(Group3D *_group3D, Face _face, int _size);

    void setVisible(bool _visible);
    void setAdded(bool _added);

    bool isAdded();
    bool isVisible();

private:

    vector<GLvector>    m_texCoords;
    vector<GLvector>    m_vertices;
    vector<GLvector>    m_normals;

    vector<GLvector>    m_directions;
    vector<GLvector>    m_chests;
    vector<GLvector>    m_waists;
    vector<GLvector>    m_arms;
    vector<GLvector>    m_legs;

    QList<Group3D>      m_groups3D;
    QString             m_fileName;
    QString             m_complementFileName;
    QString             m_mtllib;

    ObjectType          m_objectType;

    bool                m_visible;
    bool                m_added;

};

#endif // OBJET_H
