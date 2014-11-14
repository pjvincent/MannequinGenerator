#include <QApplication>
#include <QtOpenGL/QGLWidget>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    //    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // Anti-aliasing //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    QGLFormat glf = QGLFormat::defaultFormat();
    glf.setSampleBuffers(true);
    glf.setSamples(4);
    QGLFormat::setDefaultFormat(glf);
    // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    MainWindow window;
    window.showMaximized();


    return app.exec();
}
