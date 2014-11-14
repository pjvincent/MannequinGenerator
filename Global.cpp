#include <QDebug>

#include "Global.h"


Global::Global() {}


GLvector Global::readGLvector2(istringstream& _line)
{
    float x = 0, y = 0;

    _line >> x >> y;
    GLvector vec;
    vec.fX = x;
    vec.fY = y;

    return vec;
}


GLvector Global::readGLvector3(istringstream& _line)
{
    float x = 0, y = 0, z = 0;

    _line >> x >> y >> z;
    GLvector vec;
    vec.fX = x;
    vec.fY = y;
    vec.fZ = z;

    return vec;
}


QVector3D Global::readQVector3D(istringstream& _line)
{
    float x = 0, y = 0, z = 0;
    _line >> x >> y >> z;
    return QVector3D(x, y, z);
}


QVector2D Global::readQVector2D(istringstream& _line)
{
    float x = 0, y = 0;
    _line >> x >> y;
    return QVector2D(x, y);
}


QString Global::readQString(istringstream& _line)
{
    string word;
    _line >> word;
    return QString(word.c_str());
}


QString Global::pathFromFileName(QString _fileName)
{
    QString path0 = "", path1;

    while(true)
    {
        path0 = _fileName.left(_fileName.indexOf("/", path0.length() + 1));

        if(path0.length() == _fileName.length())
            break;

        path1 = path0;
    }

    return path1;
}


GLvector Global::qVector3DToGLvector(QVector3D _vector)
{
    GLvector vec;

    vec.fX = _vector.x();
    vec.fY = _vector.y();
    vec.fZ = _vector.z();

    return vec;
}


GLvector Global::qVector2DToGLvector(QVector2D _vector)
{
    GLvector vec;

    vec.fX = _vector.x();
    vec.fY = _vector.y();

    return vec;
}


QVector3D Global::gLvectorToQVector3D(GLvector _vector)
{
    return QVector3D(_vector.fX, _vector.fY, _vector.fZ);
}


QVector2D Global::gLvectorToQVector2D(GLvector _vector)
{
    return QVector2D(_vector.fX, _vector.fY);
}



