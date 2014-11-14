#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QSlider>
#include "GLWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);

public slots:

    void sldTaillesValueChanged();
    void comboBoxesCurrentIndexChanged();
    void additionalComboBoxesCurrentIndexChanged();

protected:

    void closeEvent(QCloseEvent *_event);

private:

    void initInterface();
    void loadPaths(QString _path, int _parent, int _current);
    void initTextures();
    void addColorToComboBox(QString _text, QColor _color, QComboBox* _comboBox);
    void loadObjects();

    QString getPath(int _index);

    QList<QString>                 m_path0;
    QList<QList<QString> >         m_path1;
    QList<QList<QList<QString> > > m_path2;

    QList<QComboBox*> m_comboBoxes;
    QList<QComboBox*> m_additionalComboBoxes;
    QList<QSlider*>   m_sldTailles;

    QList<QColor> m_hairColors;

    QFormLayout m_sldLayout;
    QHBoxLayout m_mainLayout;

    QWidget  m_centralWidget;
    GLWidget m_glWidget;

    Object3D m_cuir_chevelu;
    Object3D m_cheveux;
    Object3D m_yeux;
    Object3D m_tete;
    Object3D m_top;
    Object3D m_robe;
    Object3D m_legging;
    Object3D m_jupe;
    Object3D m_jean;
    Object3D m_chemisier;

    Object3D m_squelette;

    Object3D m_corps;
    Object3D m_tShirt;
    Object3D m_veste;

    Texture m_texHair;
    Texture m_texEyes;
    Texture m_texHead;
    Texture m_texTorso;
    Texture m_texRobe;
    Texture m_texEyelashes;
    Texture m_texCorps;
    Texture m_texPantalon;
    Texture m_texDebardeur;
    Texture m_texJupe;
    Texture m_texChemisier;

    Texture m_texLegging;



    int m_skinColor;
    int m_eyesColor;
    int m_hairColor;
    int m_haircut;
    int m_oldSkinColor;
    int m_oldEyesColor;
    int m_oldHaircut;

    float m_tourPoitrine;
    float m_tourHanches;
    float m_tourVentre;
    float m_tourCou;
    float m_tourBras;
    float m_tourJambes;
    float m_longBras;
    float m_longJambes;

};

#endif // MAINWINDOW_H
