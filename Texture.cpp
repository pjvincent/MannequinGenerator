#include "Texture.h"
#include "GLWidget.h"


Texture::Texture()
{
    m_tourPoitrine      = 0;
    m_tourHanches       = 0;
    m_tourVentre        = 0;
    m_tourCou           = 0;
    m_tourBras          = 0;
    m_tourJambes        = 0;
    m_longBras          = 0;
    m_longJambes        = 0;
    m_nbrTextureParts   = 1;
}


void Texture::setUniformValue(QGLShaderProgram * _program)
{
    _program->setUniformValue("tourPoitrine",    m_tourPoitrine);
    _program->setUniformValue("tourHanches",     m_tourHanches);
    _program->setUniformValue("tourVentre",      m_tourVentre);
    _program->setUniformValue("tourCou",         m_tourCou);
    _program->setUniformValue("tourBras",        m_tourBras);
    _program->setUniformValue("tourJambes",      m_tourJambes);
    _program->setUniformValue("nbrTextureParts", m_nbrTextureParts);

    _program->setUniformValue("longBras",        m_longBras);
    _program->setUniformValue("longJambes",      m_longJambes);

    _program->setUniformValue("hairColor", QVector4D(m_hairColor.red(),
                                                     m_hairColor.green(),
                                                     m_hairColor.blue(),
                                                     m_hairColor.alpha()) / 255.0);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}


void Texture::load()
{
    if(m_enlargementFileName.isNull())
        m_pixmap = QPixmap(m_colorFileName);

    else
    {
        m_pixmap = QPixmap(m_enlargementFileName);

        QPainter painter(&m_pixmap);
        painter.drawPixmap(0, 0, QPixmap(m_colorFileName));
        painter.end();
    }
}


void Texture::bind(GLWidget * _widget)
{
    m_textureId = _widget->bindTexture(m_pixmap);
}


void Texture::setTourPoitrine(float _val)
{
    m_tourPoitrine = _val;
}


void Texture::setTourHanches(float _val)
{
    m_tourHanches = _val;
}


void Texture::setTourVentre(float _val)
{
    m_tourVentre = _val;
}


void Texture::setTourCou(float _val)
{
    m_tourCou = _val;
}


void Texture::setTourBras(float _val)
{
    m_tourBras = _val;
}


void Texture::setTourJambes(float _val)
{
    m_tourJambes = _val;
}


void Texture::setLongBras(float _val)
{
    m_longBras = _val;
}


void Texture::setLongJambes(float _val)
{
    m_longJambes = _val;
}


void Texture::setHairColor(QColor _color)
{
    m_hairColor = _color;
}


void Texture::setNbrTextureParts(int _nbr)
{
    m_nbrTextureParts = _nbr;
}


void Texture::setColorFileName(QString _fileName)
{
    m_colorFileName = _fileName;
}


QString Texture::colorFileName()
{
    return m_colorFileName;
}


void Texture::setEnlargementFileName(QString _fileName)
{
    m_enlargementFileName = _fileName;
}


QString Texture::enlargementFileName()
{
    return m_enlargementFileName;
}



