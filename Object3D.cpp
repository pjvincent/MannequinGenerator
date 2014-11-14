#include <QDebug>
#include <stdio.h>
#include <string.h>

#include "Object3D.h"


Object3D::Object3D()
{
    m_visible = true;
    m_added = false;
    m_fileName.clear();
    m_complementFileName.clear();
}


void Object3D::drawOpaque(QGLShaderProgram * _program, GLenum _mode)
{
    if(DEBUG) qDebug() << "Object3D::drawOpaque [begin]";

    if(m_visible && m_added)
    {

        _program->setUniformValue("objectType", m_objectType);

        for(int i = 0; i < m_groups3D.count(); i++)
            if(m_groups3D[i].material()->d() == 1)
                m_groups3D[i].draw(_program, _mode);
    }

    if(DEBUG) qDebug() << "Object3D::drawOpaque [end]";
}


void Object3D::drawTransparent(QGLShaderProgram * _program, GLenum _mode)
{
    if(DEBUG) qDebug() << "Object3D::drawTransparent [begin]";

    if(m_visible && m_added)
    {

        _program->setUniformValue("objectType", m_objectType);

        for(int i = 0; i < m_groups3D.count(); i++)
            if(m_groups3D[i].material()->d() < 1)
                m_groups3D[i].draw(_program, _mode);
    }

    if(DEBUG) qDebug() << "Object3D::drawTransparent [end]";
}


bool Object3D::load(QString _fileName, ObjectType _objectType)
{
    if(DEBUG) qDebug() << "Object3D::load [begin]";

    if(m_fileName == _fileName || !m_visible || !m_added)
        return false;

    m_fileName = _fileName;
    m_objectType = _objectType;

    std::ifstream file(_fileName.toStdString().c_str(), ios::in);

    if(!file)
    {
        qDebug() << "le fichier '" << _fileName.toStdString().c_str() << "' est introuvable.";
        return false;
    }

    string buf, key;

    m_groups3D.clear();

    m_vertices.clear();
    m_normals.clear();
    m_texCoords.clear();

    while(getline(file, buf))
    {
        istringstream line(buf + " ");
        line >> key;

        if(key == "mtllib")
            m_mtllib = Global::pathFromFileName(m_fileName).append("/").append(Global::readQString(line));

        else if(key == "v")
            m_vertices.push_back(Global::readGLvector3(line));

        else if(key == "vt")
            m_texCoords.push_back(Global::readGLvector2(line));

        else if(key == "vn")
            m_normals.push_back(Global::readGLvector3(line));

        key = "";
    }

    if(DEBUG) qDebug() << "Object3D::load [end]";

    return true;
}


void Object3D::loadComplement(QString _complementFileName)
{
    if(DEBUG) qDebug() << "Object3D::loadComplement [begin]";

    m_complementFileName = _complementFileName;

    std::ifstream file(_complementFileName.toStdString().c_str(), ios::in);

    if(!file)
    {
        qDebug() << "le fichier '" << _complementFileName.toStdString().c_str() << "' est introuvable.";
        return;
    }

    string buf, key;

    m_directions.clear();
    m_chests.clear();
    m_waists.clear();
    m_arms.clear();
    m_legs.clear();

    while(getline(file, buf))
    {
        istringstream line(buf + " ");
        line >> key;

        if(key == "direction")
            m_directions.push_back(Global::readGLvector3(line));

        else if(key == "chest")
            m_chests.push_back(Global::readGLvector2(line));

        else if(key == "waist")
            m_waists.push_back(Global::readGLvector2(line));

        else if(key == "arms")
            m_arms.push_back(Global::readGLvector2(line));

        else if(key == "legs")
            m_legs.push_back(Global::readGLvector2(line));

        key = "";
    }

    if(DEBUG) qDebug() << "Object3D::loadComplement [end]";
}


void Object3D::addGroup3D(QString _mtlname, Texture * _texture, int _texturePosition)
{
    m_groups3D.append(Group3D(m_mtllib, _mtlname, _texture, _texturePosition));
    m_groups3D.last().load(this, _mtlname);
}


QVector3D Object3D::center()
{
    if(DEBUG) qDebug() << "Object3D::center [begin]";

    QVector3D vec;

    for(int i = 0; i < (int) m_vertices.size(); i++)
    {
        vec.setX(vec.x() + m_vertices.at(i).fX);
        vec.setY(vec.y() + m_vertices.at(i).fY);
        vec.setZ(vec.z() + m_vertices.at(i).fZ);
    }

    vec /= m_vertices.size();

    if(DEBUG) qDebug() << "Object3D::center [end]";

    return vec;
}


QVector3D Object3D::center2()
{
    if(DEBUG) qDebug() << "Object3D::center2 [begin]";

    QVector3D min;
    QVector3D max;

    for(int i = 0; i < (int) m_vertices.size(); i++)
    {
        if(m_vertices.at(i).fX < min.x())
            min.setX(m_vertices.at(i).fX);

        if(m_vertices.at(i).fY < min.y())
            min.setY(m_vertices.at(i).fY);

        if(m_vertices.at(i).fZ < min.z())
            min.setZ(m_vertices.at(i).fZ);

        if(m_vertices.at(i).fX > max.x())
            max.setX(m_vertices.at(i).fX);

        if(m_vertices.at(i).fY > max.y())
            max.setY(m_vertices.at(i).fY);

        if(m_vertices.at(i).fZ > max.z())
            max.setZ(m_vertices.at(i).fZ);
    }

    if(DEBUG) qDebug() << "Object3D::center2 [end]";

    return (min + max) / 2.0;
}


void Object3D::loadFace(Group3D * _group3D, Face _face, int _size)
{
    QVector2D texCoord;
    QVector3D vertex, normal, vertices[3];

    QVector3D direction = QVector3D(0, 0, 0);
    QVector2D chest = QVector2D(0, 0);
    QVector2D waist = QVector2D(0, 0);
    QVector2D arms = QVector2D(0, 0);
    QVector2D legs = QVector2D(0, 0);

    int index;

    if(_face.index.size() > 2)
    {
        for(int i = 0; i < 3; i++)
        {
            index = _face.index.at(i).fX;
            vertex = Global::gLvectorToQVector3D(m_vertices.at(index));
            _group3D->vertices()->push_back(vertex);
            _group3D->indexVertices()->push_back(index);

            if(!m_complementFileName.isEmpty())
            {
                direction = Global::gLvectorToQVector3D(m_directions.at(index));
                chest = Global::gLvectorToQVector2D(m_chests.at(index));
                waist = Global::gLvectorToQVector2D(m_waists.at(index));
                arms = Global::gLvectorToQVector2D(m_arms.at(index));
                legs = Global::gLvectorToQVector2D(m_legs.at(index));
            }

            _group3D->directions()->push_back(direction);
            _group3D->chests()->push_back(chest);
            _group3D->waists()->push_back(waist);
            _group3D->arms()->push_back(arms);
            _group3D->legs()->push_back(legs);

            index = _face.index.at(i).fY;
            texCoord = Global::gLvectorToQVector2D(m_texCoords.at(index));
            _group3D->texCoords()->push_back(texCoord);
            _group3D->indexTexCoords()->push_back(index);

            if (_size > 2)
            {
                index = _face.index.at(i).fZ;
                normal = Global::gLvectorToQVector3D(m_normals.at(index));
                _group3D->normals()->push_back(normal);
                _group3D->indexNormals()->push_back(index);

            }
            else
                vertices[i] = vertex;
        }

        if (_size <= 2)
        {
            normal = QVector3D::crossProduct(vertices[1] - vertices[0], vertices[2] - vertices[0]).normalized();

            _group3D->normals()->push_back(normal);
            _group3D->normals()->push_back(normal);
            _group3D->normals()->push_back(normal);

            _group3D->indexNormals()->push_back(0);
            _group3D->indexNormals()->push_back(0);
            _group3D->indexNormals()->push_back(0);
        }
    }
}


QList<Group3D> * Object3D::groups3D()
{
    return &m_groups3D;
}


void Object3D::rotation(QMatrix4x4 _mat)
{
    if(DEBUG) qDebug() << "Object3D::transformation [begin]";

    for(int i = 0; i < m_groups3D.count(); i++)
        m_groups3D[i].rotation(_mat);

    if(DEBUG) qDebug() << "Object3D::transformation [end]";
}


void Object3D::scaleTranslation(QMatrix4x4 _mat)
{
    if(DEBUG) qDebug() << "Object3D::transformation [begin]";

    for(int i = 0; i < m_groups3D.count(); i++)
        m_groups3D[i].scaleTranslation(_mat);

    if(DEBUG) qDebug() << "Object3D::transformation [end]";
}


QString Object3D::fileName()
{
    return m_fileName;
}


QString Object3D::complementFileName()
{
    return m_complementFileName;
}


QString Object3D::mtllib()
{
    return m_mtllib;
}


void Object3D::setVisible(bool _visible)
{
    m_visible = _visible;
}


bool Object3D::isVisible()
{
    return m_visible;
}


void Object3D::setAdded(bool _added)
{
    m_added = _added;
}


bool Object3D::isAdded()
{
    return m_added;
}



