#include <QDebug>
#include <QVector2D>

#include "Group3D.h"
#include "Object3D.h"

Group3D::Group3D(QString _mtllib, QString _mtlname, Texture * _texture, int _texturePosition)
{
    m_material = Material(_mtllib, _mtlname, _texture, _texturePosition);

    m_vertices.clear();
    m_texCoords.clear();
    m_normals.clear();

    m_directions.clear();
    m_chests.clear();
    m_waists.clear();
    m_arms.clear();
    m_legs.clear();

    m_indexVertices.clear();
    m_indexTexCoords.clear();
    m_indexNormals.clear();
}


void Group3D::load(Object3D * _object3D, QString _mtlname)
{
    if(DEBUG) qDebug() << "Object3D::load [begin]";

    std::ifstream file(_object3D->fileName().toStdString().c_str(), ios::in);

    if(!file)
    {
        qDebug() << "le fichier '" << _object3D->fileName().toStdString().c_str() << "' est introuvable.";
        return;
    }

    string buf, key;

    bool currentGroup = false;

    while(getline(file, buf))
    {
        istringstream line(buf + " ");
        line >> key;

        if(key == "usemtl")
        {
            if(Global::readQString(line).compare(_mtlname) == 0)
                currentGroup = true;

            else
                currentGroup = false;
        }

        if(currentGroup)
            if(key == "f")
                readFace(_object3D, line);

        key = "";
    }

    qDebug() << _object3D->fileName().toStdString().c_str() << m_vertices.count();

    if(DEBUG) qDebug() << "Object3D::load [end]";
}


void Group3D::readFace(Object3D * _object3D, istringstream& _line)
{
    Face face;
    string vertex;
    vector<string> index;
    GLvector I;
    int size = 0;

    _line >> vertex;

    while(!_line.eof())
    {
        split(vertex, index, "/");

        I.fX = strtoul(index[0].c_str(), NULL, 10) - 1; // position
        I.fY = strtoul(index[1].c_str(), NULL, 10) - 1; // texture

        if (index.size() > 2)
            I.fZ = strtoul(index[2].c_str(), NULL, 10) - 1; // normal

        face.index.push_back(I);
        size++;
        _line >> vertex;
    }

    _object3D->loadFace(this, face, index.size());

    if (size == 4)
    {
        Face face2;
        face2.index.push_back(face.index.at(0));
        face2.index.push_back(face.index.at(2));
        face2.index.push_back(face.index.at(3));
        _object3D->loadFace(this, face2, index.size());
        if(DEBUG) qDebug() << "Face avec 4 sommets";
    }

    else if (size > 4)
        if(DEBUG) qDebug() << "Face avec plus de 4 sommets";

}


inline void Group3D::split(const std::string& _string, std::vector<std::string>& _tokens, const std::string& _delim)
{
    _tokens.clear();
    for (std::string::size_type p1 = 0, p2 = 0; p1 != std::string::npos; )
    {
        p1 = _string.find_first_not_of(_delim, p1);
        if (p1 != std::string::npos)
        {
            p2 = _string.find_first_of(_delim , p1);
            _tokens.push_back(_string.substr(p1, p2 - p1));
            p1 = p2;
        }
    }
}


void Group3D::draw(QGLShaderProgram * _program, GLenum _mode)
{
    m_material.setUniformValue(_program);

    _program->setAttributeArray(PROGRAM_VERTEX_ATTRIBUTE,   m_vertices.constData());
    _program->setAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE, m_texCoords.constData());
    _program->setAttributeArray(PROGRAM_NORMAL_ATTRIBUTE,   m_normals.constData());

    _program->setAttributeArray(PROGRAM_DIRECTION_ATTRIBUTE,    m_directions.constData());
    _program->setAttributeArray(PROGRAM_CHEST_ATTRIBUTE,        m_chests.constData());
    _program->setAttributeArray(PROGRAM_WAIST_ATTRIBUTE,        m_waists.constData());
    _program->setAttributeArray(PROGRAM_ARMS_ATTRIBUTE,         m_arms.constData());
    _program->setAttributeArray(PROGRAM_LEGS_ATTRIBUTE,         m_legs.constData());

    _program->setAttributeArray(PROGRAM_INDEX_VERTEX_ATTRIBUTE,   m_indexVertices.constData(),  1);
    _program->setAttributeArray(PROGRAM_INDEX_TEXCOORD_ATTRIBUTE, m_indexTexCoords.constData(), 1);
    _program->setAttributeArray(PROGRAM_INDEX_NORMAL_ATTRIBUTE,   m_indexNormals.constData(),   1);

    glDrawArrays(_mode, 0, m_vertices.size());
}


void Group3D::rotation(QMatrix4x4 _mat)
{
    for (int i = 0; i < m_vertices.size(); i++)
    {
        m_vertices.replace(i, _mat * m_vertices.at(i));
        m_normals.replace(i, _mat * m_normals.at(i));
    }

}


void Group3D::scaleTranslation(QMatrix4x4 _mat)
{
    for (int i = 0; i < m_vertices.size(); i++)
        m_vertices.replace(i, _mat * m_vertices.at(i));
}


QVector<QVector3D> * Group3D::vertices()
{
    return &m_vertices;
}


QVector<QVector2D> * Group3D::texCoords()
{
    return &m_texCoords;
}


QVector<QVector3D> * Group3D::normals()
{
    return &m_normals;
}


QVector<QVector3D> * Group3D::directions()
{
    return &m_directions;
}


QVector<QVector2D> * Group3D::chests()
{
    return &m_chests;
}


QVector<QVector2D> * Group3D::waists()
{
    return &m_waists;
}


QVector<QVector2D> * Group3D::arms()
{
    return &m_arms;
}


QVector<QVector2D> * Group3D::legs()
{
    return &m_legs;
}


QVector<GLfloat> * Group3D::indexVertices()
{
    return &m_indexVertices;
}


QVector<GLfloat> * Group3D::indexTexCoords()
{
    return &m_indexTexCoords;
}


QVector<GLfloat> * Group3D::indexNormals()
{
    return &m_indexNormals;
}


Material * Group3D::material()
{
    return &m_material;
}

