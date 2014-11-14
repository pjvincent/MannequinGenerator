#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtOpenGL/qgl.h>
#include <QVector3D>
#include <QVector2D>
#include <sstream>

#define PROGRAM_VERTEX_ATTRIBUTE          0
#define PROGRAM_TEXCOORD_ATTRIBUTE        1
#define PROGRAM_NORMAL_ATTRIBUTE          2

#define PROGRAM_DIRECTION_ATTRIBUTE       3
#define PROGRAM_CHEST_ATTRIBUTE           4
#define PROGRAM_WAIST_ATTRIBUTE           5
#define PROGRAM_ARMS_ATTRIBUTE            6
#define PROGRAM_LEGS_ATTRIBUTE            7

#define PROGRAM_INDEX_VERTEX_ATTRIBUTE    8
#define PROGRAM_INDEX_TEXCOORD_ATTRIBUTE  9
#define PROGRAM_INDEX_NORMAL_ATTRIBUTE   10

static bool DEBUG = false;

struct GLvector
{
    GLfloat fX;
    GLfloat fY;
    GLfloat fZ;
};

using namespace std;

class Global
{
public:

    Global();

    static GLvector readGLvector2(istringstream& _line);
    static GLvector readGLvector3(istringstream& _line);

    static QVector3D readQVector3D(istringstream& _line);
    static QVector2D readQVector2D(istringstream& _line);

    static GLvector qVector3DToGLvector(QVector3D _vector);
    static GLvector qVector2DToGLvector(QVector2D _vector);

    static QVector3D gLvectorToQVector3D(GLvector _vector);
    static QVector2D gLvectorToQVector2D(GLvector _vector);

    static QString readQString(istringstream& _line);
    static QString pathFromFileName(QString _fileName);
};

#endif // GLOBAL_H
