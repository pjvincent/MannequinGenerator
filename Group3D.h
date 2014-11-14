#ifndef GROUP3D_H
#define GROUP3D_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QGLShaderProgram>

#include "Material.h"
#include "Global.h"

using namespace std;

class Object3D;

struct Face
{
    vector<GLvector> index;
};

class Group3D
{
public:

    Group3D(QString _mtllib, QString _mtlname, Texture *_texture, int _texturePosition);

    void draw(QGLShaderProgram *_program, GLenum _mode);
    void rotation(QMatrix4x4 _mat);
    void scaleTranslation(QMatrix4x4 _mat);

    void load(Object3D *_object3D, QString _mtlname);

    QVector<QVector3D> * vertices();
    QVector<QVector2D> * texCoords();
    QVector<QVector3D> * normals();

    QVector<QVector3D> * directions();
    QVector<QVector2D> * chests();
    QVector<QVector2D> * waists();
    QVector<QVector2D> * arms();
    QVector<QVector2D> * legs();

    QVector<GLfloat> * indexVertices();
    QVector<GLfloat> * indexTexCoords();
    QVector<GLfloat> * indexNormals();

    Material * material();

private:

    inline void split(const std::string& _string, std::vector<std::string>& _tokens, const std::string& _delim);

    void readFace(Object3D *_object3D, istringstream& _line);

    Material           m_material;

    QVector<QVector3D> m_vertices;
    QVector<QVector2D> m_texCoords;
    QVector<QVector3D> m_normals;

    QVector<QVector3D> m_directions;
    QVector<QVector2D> m_chests;
    QVector<QVector2D> m_waists;
    QVector<QVector2D> m_arms;
    QVector<QVector2D> m_legs;

    QVector<GLfloat>   m_indexVertices;
    QVector<GLfloat>   m_indexTexCoords;
    QVector<GLfloat>   m_indexNormals;

};

#endif // GROUP3D_H
