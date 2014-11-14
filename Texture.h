#ifndef TEXTURE_H
#define TEXTURE_H

#include <QVector4D>
#include <QGLShaderProgram>

class GLWidget;

class Texture
{

public:

    Texture();

    QString colorFileName();
    QString enlargementFileName();

    void load();
    void bind(GLWidget *_widget);

    void setUniformValue(QGLShaderProgram * _program);

    void setTourPoitrine(float _val);
    void setTourHanches (float _val);
    void setTourVentre  (float _val);
    void setTourCou     (float _val);
    void setTourBras    (float _val);
    void setTourJambes  (float _val);
    void setLongBras    (float _val);
    void setLongJambes  (float _val);

    void setHairColor   (QColor _color);
    void setNbrTextureParts(int _nbr);
    void setColorFileName(QString _fileName);
    void setEnlargementFileName(QString _fileName);

private:

    QPixmap     m_pixmap;

    QString     m_colorFileName;
    QString     m_enlargementFileName;

    QColor      m_hairColor;

    float   m_tourPoitrine;
    float   m_tourHanches;
    float   m_tourVentre;
    float   m_tourCou;
    float   m_tourBras;
    float   m_tourJambes;

    float   m_longBras;
    float   m_longJambes;

    GLuint      m_textureId;

    int         m_nbrTextureParts;
};

#endif // TEXTURE_H
