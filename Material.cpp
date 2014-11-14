#include "Material.h"
#include "GLWidget.h"
#include "Global.h"

Material::Material() {}

Material::Material(QString _mtllib, QString _mtlname, Texture *_texture, int _texturePosition)
{
    load(_mtllib, _mtlname, _texture, _texturePosition);
}


void Material::load(QString _mtllib, QString _mtlname, Texture * _texture, int _texturePosition)
{
    if(DEBUG) qDebug() << "Material::load [begin]";

    m_texturePosition = _texturePosition;
    m_mtllib = _mtllib;
    m_mtlname = _mtlname;
    m_texture = _texture;

    std::ifstream file(_mtllib.toStdString().c_str(), ios::in);

    if(!file)
    {
        qDebug() << "le fichier '" << m_mtllib.toStdString().c_str() << "' est introuvable.";
        return;
    }

    string buf, key;

    bool find = false;

    while(getline(file, buf))
    {
        istringstream line(buf + " ");
        line >> key;

        if(key == "newmtl")
        {
            if(find)
                break;

            else
                if (Global::readQString(line).compare(m_mtlname) == 0)
                    find = true;
        }

        if(find)
        {
            if(key == "Ka")
                m_Ka = Global::readQVector3D(line);

            else if(key == "Kd")
                m_Kd = Global::readQVector3D(line);

            else if(key == "Ks")
                m_Ks = Global::readQVector3D(line);

            else if(key == "Ns")
                m_Ns = Global::readQString(line).toFloat();

            else if(key == "d")
                m_d = Global::readQString(line).toFloat();
        }

        key = "";
    }

    if(DEBUG) qDebug() << "Material::load [end]";
}


void Material::setUniformValue(QGLShaderProgram * _program)
{
    if(DEBUG) qDebug() << "Material::setUniformValue [begin]";

    _program->setUniformValue("texturePosition", m_texturePosition);
    _program->setUniformValue("Ka", m_Ka);
    _program->setUniformValue("Kd", m_Kd);
    _program->setUniformValue("Ks", m_Ks);
    _program->setUniformValue("Ns", m_Ns);
    _program->setUniformValue("d", m_d);

    m_texture->setUniformValue(_program);

    if(DEBUG) qDebug() << "Material::setUniformValue [end]";
}


void Material::set_Ka(QVector3D _Ka)
{
    m_Ka = _Ka;
}


void Material::set_Kd(QVector3D _Kd)
{
    m_Kd = _Kd;
}


void Material::set_Ks(QVector3D _Ks)
{
    m_Ks = _Ks;
}


void Material::set_Ns(float _Ns)
{
    m_Ns = _Ns;
}


void Material::set_d(float _d)
{
    m_d = _d;
}


QString Material::name()
{
    return m_mtlname;
}


QVector3D Material::Ka()
{
    return m_Ka;
}


QVector3D Material::Kd()
{
    return m_Kd;
}


QVector3D Material::Ks()
{
    return m_Ks;
}


float Material::Ns()
{
    return m_Ns;
}


float Material::d()
{
    return m_d;
}
