#include <QDir>
#include <QDebug>

#include "MainWindow.h"

int const visibleSkinColorComboBoxIndex = 4;

const QString root = QString("Femme_Normale");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    loadPaths(root, 0, 0);
    initInterface();
    sldTaillesValueChanged();

    // m_glWidget.objects3D()->append(&m_squelette);
    // m_glWidget.objects3D()->append(&m_poitrine);
    // m_glWidget.objects3D()->append(&m_bassin);
    // m_glWidget.objects3D()->append(&m_bras);
    // m_glWidget.objects3D()->append(&m_jambes);


    m_glWidget.append(&m_corps);
    m_glWidget.append(&m_legging);

    m_glWidget.append(&m_jean);
    m_glWidget.append(&m_chemisier);
    m_glWidget.append(&m_robe);
    m_glWidget.append(&m_top);
    m_glWidget.append(&m_jupe);
    m_glWidget.append(&m_yeux);

    m_glWidget.append(&m_tete);
    m_glWidget.append(&m_cuir_chevelu);
    m_glWidget.append(&m_cheveux);


    m_additionalComboBoxes[0]->setEnabled(false);
    m_additionalComboBoxes[6]->setEnabled(false);


    m_additionalComboBoxes[4]->setCurrentIndex(2);
    m_additionalComboBoxes[2]->setCurrentIndex(2);
    m_additionalComboBoxes[1]->setCurrentIndex(2);
    m_additionalComboBoxes[5]->setCurrentIndex(4);
    m_additionalComboBoxes[6]->setCurrentIndex(0);
    m_additionalComboBoxes[7]->setCurrentIndex(0);

    loadObjects();


    // for(int i = 0; i < m_sldTailles.count(); i++)
    // m_sldTailles[i]->setEnabled(false);
}


void MainWindow::loadObjects()
{
    QMatrix4x4 scale;

    scale.scale(0.9245);

    if(m_cheveux.load(getPath(2), HAIR))
    {
        switch (m_haircut) {
        case 1:
            // m_cheveux.addGroup3D("Pin", &m_texHair, 0);
            m_cheveux.addGroup3D("material_0", &m_texHair, 0);
            break;

        case 2:
            m_cheveux.addGroup3D("material_2", &m_texHair, 2);
            m_cheveux.addGroup3D("material_3", &m_texHair, 4);
            m_cheveux.addGroup3D("material_0", &m_texHair, 0);
            m_cheveux.addGroup3D("material_1", &m_texHair, 1);
            break;

        case 3:
            m_cheveux.addGroup3D("material_0", &m_texHair, 1);
            break;

        case 4:
            m_cheveux.addGroup3D("material_0", &m_texHair, 1);
            break;

        case 5:
            m_cheveux.addGroup3D("material_0", &m_texHair, 1);
            break;

        case 6:
            m_cheveux.addGroup3D("material_0", &m_texHair, 0);
            break;

        case 7:
            m_cheveux.addGroup3D("material_0", &m_texHair, 0);
            break;

        case 8:
            m_cheveux.addGroup3D("material_0", &m_texHair, 1);
            break;

        case 9:
            m_cheveux.addGroup3D("material_2", &m_texHair, 2);
            m_cheveux.addGroup3D("material_1", &m_texHair, 1);
            m_cheveux.addGroup3D("material_0", &m_texHair, 0);
            m_cheveux.addGroup3D("material_3", &m_texHair, 3);
            m_cheveux.addGroup3D("material_4", &m_texHair, 4);
            break;
        }

        m_cheveux.scaleTranslation(scale);
    }

    if(m_cuir_chevelu.load(getPath(8), HAIR))
    {
        switch (m_haircut) {

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:

            m_cuir_chevelu.addGroup3D("material_0", &m_texHair, 0);
            break;

        case 1:
            m_cuir_chevelu.addGroup3D("material_0", &m_texHair, 1);
            break;

        case 2:
            m_cuir_chevelu.addGroup3D("material_0", &m_texHair, 3);
            break;

        case 9:
            m_cuir_chevelu.addGroup3D("material_0", &m_texHair, 5);
            break;
        }

        m_cuir_chevelu.scaleTranslation(scale);
    }

    QMatrix4x4 rotate;
    rotate.rotate(-90, 1, 0, 0);

    if(m_tete.load(getPath(0), SKIN))
    {
        m_tete.addGroup3D("Head_C01", &m_texHead);
        m_tete.addGroup3D("Torso_C01", &m_texTorso);
        m_tete.addGroup3D("Eyelashes", &m_texEyelashes);
        m_tete.rotation(rotate);
    }

    if(m_yeux.load(getPath(1), EYES))
    {
        m_yeux.addGroup3D("Irises_Blue", &m_texEyes);
        m_yeux.addGroup3D("Pupils", &m_texEyes);
        m_yeux.addGroup3D("Sclera", &m_texEyes);
        m_yeux.rotation(rotate);
    }

    if(m_corps.load(QString(root).append("/Corps/OBJ.obj"), SKIN))
    {
        m_corps.loadComplement(QString(root).append("/Corps/CMPL.cmpl"));
        m_corps.addGroup3D("Torso_C01", &m_texCorps);
        m_corps.addGroup3D("Limbs_C01", &m_texCorps);
    }

    if(m_legging.load(QString(root).append("/Corps/OBJ.obj"), SKIN))
    {
        m_legging.loadComplement(QString(root).append("/Corps/CMPL.cmpl"));
        m_legging.addGroup3D("Torso_C01", &m_texLegging);
        m_legging.addGroup3D("Limbs_C01", &m_texLegging);
    }

    if(m_jean.load(QString(root).append("/Pantalon/OBJ.obj"), OTHER))
    {
        m_jean.loadComplement(QString(root).append("/Pantalon/CMPL.cmpl"));
        m_jean.addGroup3D("Pantalon", &m_texPantalon);
    }

    if(m_chemisier.load(QString(root).append("/Chemisier/OBJ.obj"), OTHER))
    {
        m_chemisier.loadComplement(QString(root).append("/Chemisier/CMPL.cmpl"));
        m_chemisier.addGroup3D("Chemisier", &m_texChemisier);
    }

    if(m_robe.load(QString(root).append("/Robe/OBJ.obj"), OTHER))
    {
        m_robe.loadComplement(QString(root).append("/Robe/CMPL.cmpl"));
        m_robe.addGroup3D("Robe", &m_texRobe);
    }

    if(m_top.load(QString(root).append("/Debardeur/OBJ.obj"), OTHER))
    {
        m_top.loadComplement(QString(root).append("/Debardeur/CMPL.cmpl"));
        m_top.addGroup3D("Debardeur", &m_texDebardeur);
    }

    if(m_jupe.load(QString(root).append("/Jupe/OBJ.obj"), OTHER))
    {
        m_jupe.loadComplement(QString(root).append("/Jupe/CMPL.cmpl"));
        m_jupe.addGroup3D("Jupe", &m_texJupe);
    }

    // m_squelette.load("Squelette/Squelette.obj", OTHER);
    // m_squelette.addGroup3D("Panties", &m_texRobe);

    // if(m_bassin.fileName().compare(getPath(4)) != 0)
    // {
    // m_bassin.load(getPath(4), SKIN);
    // m_bassin.addGroup3D("Torso_C01", &m_texTorso);
    // m_bassin.transformation(transformation);
    // }
    // if(m_jambes.fileName().compare(getPath(6)) != 0)
    // {
    // m_jambes.load(getPath(6), SKIN);
    // m_jambes.addGroup3D("Torso_C01", &m_texBody);
    // m_jambes.addGroup3D("Limbs_C01", &m_texLimbs);
    // // m_jambes.transformation(transformation);
    // }
    // if(m_pants.fileName().compare(getPath(7)) != 0)
    // {
    // m_pants.load(getPath(7), SKIN);
    // m_pants.addGroup3D("Limbs_C01", &m_texLimbs);
    // m_pants.transformation(transformation);
    // }
}


void MainWindow::closeEvent(QCloseEvent *_event)
{
    Q_UNUSED(_event)
    exit(0);
}


void MainWindow::comboBoxesCurrentIndexChanged()
{
    setCursor(Qt::WaitCursor);
    QApplication::processEvents();

    if(isVisible())
        loadObjects();

    setCursor(Qt::ArrowCursor);
}


void MainWindow::additionalComboBoxesCurrentIndexChanged()
{
    setCursor(Qt::WaitCursor);
    QApplication::processEvents();

    m_skinColor = m_additionalComboBoxes[0]->currentIndex() + 1;
    m_eyesColor = m_additionalComboBoxes[3]->currentIndex() + 1;
    m_haircut   = m_additionalComboBoxes[4]->currentIndex() + 1;
    m_hairColor = m_additionalComboBoxes[5]->currentIndex() + 1;

    m_comboBoxes[0]->setCurrentIndex(m_additionalComboBoxes[1]->currentIndex() * 3 + m_additionalComboBoxes[2]->currentIndex());
    m_comboBoxes[2]->setCurrentIndex(m_additionalComboBoxes[4]->currentIndex());
    m_comboBoxes[3]->setCurrentIndex(m_additionalComboBoxes[6]->currentIndex());
    m_comboBoxes[5]->setCurrentIndex(m_additionalComboBoxes[7]->currentIndex());
    m_comboBoxes[6]->setCurrentIndex(m_additionalComboBoxes[8]->currentIndex());
    m_comboBoxes[7]->setCurrentIndex(m_additionalComboBoxes[9]->currentIndex());
    m_comboBoxes[8]->setCurrentIndex(m_additionalComboBoxes[4]->currentIndex());



    if(m_additionalComboBoxes[12]->currentIndex() == 0)
        m_texHead.setColorFileName           (QString(root).append("/Maps/Head/Head_C0").append(QString::number(m_skinColor)).append(".png"));

    else
        m_texHead.setColorFileName           (QString(root).append("/Maps/Head/Margot.png"));

    m_texHead.load();
    m_texHead.bind(&m_glWidget);

    m_robe.setVisible(m_additionalComboBoxes[10]->currentIndex() == 0);
    m_top.setVisible(m_additionalComboBoxes[10]->currentIndex() == 1);
    m_chemisier.setVisible(m_additionalComboBoxes[10]->currentIndex() == 2);

    m_jean.setVisible(m_additionalComboBoxes[11]->currentIndex() == 0 && m_additionalComboBoxes[10]->currentIndex() != 0);
    m_legging.setVisible(m_additionalComboBoxes[11]->currentIndex() == 1 && m_additionalComboBoxes[10]->currentIndex() != 0);
    m_jupe.setVisible(m_additionalComboBoxes[11]->currentIndex() == 2 && m_additionalComboBoxes[10]->currentIndex() != 0);

    m_corps.setVisible(m_additionalComboBoxes[11]->currentIndex() != 1 || m_additionalComboBoxes[10]->currentIndex() == 0);

    m_additionalComboBoxes[11]->setEnabled(m_additionalComboBoxes[10]->currentIndex() != 0);

    if(isVisible())
        loadObjects();

    initTextures();

    m_glWidget.update();






    setCursor(Qt::ArrowCursor);
}


void MainWindow::sldTaillesValueChanged()
{
    m_tourPoitrine = 0.8 * m_sldTailles[0]->value() / 100.0;
    m_tourHanches  = 0.3 * m_sldTailles[1]->value() / 100.0;
    m_tourVentre   = 0.7 * m_sldTailles[2]->value() / 100.0;
    m_tourCou      = 0.5 * m_sldTailles[3]->value() / 100.0;
    m_tourBras     = 0.5 * m_sldTailles[4]->value() / 100.0;
    m_tourJambes   = 0.5 * m_sldTailles[5]->value() / 100.0;
    m_longBras     = 1.0 * m_sldTailles[6]->value() / 100.0;
    m_longJambes   = 1.0 * m_sldTailles[7]->value() / 100.0;

    initTextures();

    m_glWidget.update();
}


void MainWindow::initTextures()
{
    m_glWidget.makeCurrent();

    m_texHair.setColorFileName(QString(root).append("/Maps/Cheveux/Hair0").append(QString::number(m_haircut)).append(".png"));
    if(m_hairColor > 0)
        m_texHair.setHairColor(m_hairColors[m_hairColor - 1]);

    switch (m_haircut) {

    case 1:
    case 6:
    case 7:

        m_texHair.setNbrTextureParts(1);
        break;

    case 3:
    case 4:
    case 8:

        m_texHair.setNbrTextureParts(2);
        break;

    case 5:

        m_texHair.setNbrTextureParts(3);
        break;

    case 2:

        m_texHair.setNbrTextureParts(5);
        break;

    case 9:

        m_texHair.setNbrTextureParts(6);
        break;

    }

    m_texEyelashes.setColorFileName      (QString(root).append("/Maps/Eyes/Eyelashes.png"));
    m_texEyelashes.load                  ();
    m_texEyelashes.bind                  (&m_glWidget);

    m_texEyes.setColorFileName           (QString(root).append("/Maps/Eyes/Eyes_C0").append(QString::number(m_eyesColor)).append(".png"));

    m_texHead.setColorFileName           (QString(root).append("/Maps/Head/Head_C0").append(QString::number(m_skinColor)).append(".png"));
    m_texHead.setTourCou                 (m_tourCou);

    m_texTorso.setColorFileName          (QString(root).append("/Maps/Torso/Torso_C0").append(QString::number(m_skinColor)).append(".png"));
    m_texTorso.setTourPoitrine           (m_tourPoitrine);
    m_texTorso.setTourVentre             (m_tourVentre);
    m_texTorso.setTourHanches            (m_tourHanches);
    m_texTorso.setTourCou                (m_tourCou);
    m_texTorso.setTourJambes             (m_tourJambes);

    // m_texBody.setColorFileName           (QString(root).append("/Body/Torso_C0").append(QString::number(m_skinColor)).append(".png"));





    m_texCorps.setColorFileName       (QString(root).append("/Corps/TEX.png"));
    m_texCorps.setTourCou             (m_tourCou);
    m_texCorps.setTourPoitrine        (m_tourPoitrine);
    m_texCorps.setTourVentre          (m_tourVentre);
    m_texCorps.setTourHanches         (m_tourHanches);
    m_texCorps.setTourBras            (m_tourBras);
    m_texCorps.setTourJambes          (m_tourJambes);
    m_texCorps.setLongBras            (m_longBras);
    m_texCorps.setLongJambes          (m_longJambes);

    m_texLegging.setColorFileName       (QString(root).append("/Legging/TEX.png"));
    m_texLegging.setTourCou             (m_tourCou);
    m_texLegging.setTourPoitrine        (m_tourPoitrine);
    m_texLegging.setTourVentre          (m_tourVentre);
    m_texLegging.setTourHanches         (m_tourHanches);
    m_texLegging.setTourBras            (m_tourBras);
    m_texLegging.setTourJambes          (m_tourJambes);
    m_texLegging.setLongBras            (m_longBras);
    m_texLegging.setLongJambes          (m_longJambes);

    m_texPantalon.setColorFileName      (QString(root).append("/Pantalon/TEX.png"));
    m_texPantalon.setTourCou            (m_tourCou);
    m_texPantalon.setTourPoitrine       (m_tourPoitrine);
    m_texPantalon.setTourVentre         (m_tourVentre);
    m_texPantalon.setTourHanches        (m_tourHanches);
    m_texPantalon.setTourBras           (m_tourBras);
    m_texPantalon.setTourJambes         (m_tourJambes);
    m_texPantalon.setLongBras           (m_longBras);
    m_texPantalon.setLongJambes         (m_longJambes);

    m_texChemisier.setColorFileName      (QString(root).append("/Chemisier/TEX.png"));
    m_texChemisier.setTourCou            (m_tourCou);
    m_texChemisier.setTourPoitrine       (m_tourPoitrine);
    m_texChemisier.setTourVentre         (m_tourVentre);
    m_texChemisier.setTourHanches        (m_tourHanches);
    m_texChemisier.setTourBras           (m_tourBras);
    m_texChemisier.setTourJambes         (m_tourJambes);
    m_texChemisier.setLongBras           (m_longBras);
    m_texChemisier.setLongJambes         (m_longJambes);

    m_texRobe.setColorFileName          (QString(root).append("/Robe/TEX.png"));
    m_texRobe.setTourCou                (m_tourCou);
    m_texRobe.setTourPoitrine           (m_tourPoitrine);
    m_texRobe.setTourVentre             (m_tourVentre);
    m_texRobe.setTourHanches            (m_tourHanches);
    m_texRobe.setTourBras               (m_tourBras);
    m_texRobe.setTourJambes             (m_tourJambes);
    m_texRobe.setLongBras               (m_longBras);
    m_texRobe.setLongJambes             (m_longJambes);

    m_texDebardeur.setColorFileName      (QString(root).append("/Debardeur/TEX.png"));
    m_texDebardeur.setTourCou            (m_tourCou);
    m_texDebardeur.setTourPoitrine       (m_tourPoitrine);
    m_texDebardeur.setTourVentre         (m_tourVentre);
    m_texDebardeur.setTourHanches        (m_tourHanches);
    m_texDebardeur.setTourBras           (m_tourBras);
    m_texDebardeur.setTourJambes         (m_tourJambes);
    m_texDebardeur.setLongBras           (m_longBras);
    m_texDebardeur.setLongJambes         (m_longJambes);

    m_texJupe.setColorFileName      (QString(root).append("/Jupe/TEX.png"));
    m_texJupe.setTourCou            (m_tourCou);
    m_texJupe.setTourPoitrine       (m_tourPoitrine);
    m_texJupe.setTourVentre         (m_tourVentre);
    m_texJupe.setTourHanches        (m_tourHanches);
    m_texJupe.setTourBras           (m_tourBras);
    m_texJupe.setTourJambes         (m_tourJambes);
    m_texJupe.setLongBras           (m_longBras);
    m_texJupe.setLongJambes         (m_longJambes);

    if(m_oldHaircut != m_haircut)
    {
        m_texHair.load();
        m_texHair.bind(&m_glWidget);

        m_oldHaircut = m_haircut;
    }

    if(m_oldEyesColor != m_eyesColor)
    {
        m_texEyes.load();
        m_texEyes.bind(&m_glWidget);

        m_oldEyesColor = m_eyesColor;
    }

    if(m_oldSkinColor != m_skinColor)
    {
        m_texHead.load();
        m_texHead.bind(&m_glWidget);

        m_texTorso.load();
        m_texTorso.bind(&m_glWidget);

        m_texCorps.load();
        m_texCorps.bind(&m_glWidget);

        m_texRobe.load();
        m_texRobe.bind(&m_glWidget);

        m_texCorps.load();
        m_texCorps.bind(&m_glWidget);

        m_texPantalon.load();
        m_texPantalon.bind(&m_glWidget);

        m_texDebardeur.load();
        m_texDebardeur.bind(&m_glWidget);

        m_texLegging.load();
        m_texLegging.bind(&m_glWidget);

        m_texJupe.load();
        m_texJupe.bind(&m_glWidget);

        m_texChemisier.load();
        m_texChemisier.bind(&m_glWidget);

        m_oldSkinColor = m_skinColor;
    }

}


QString MainWindow::getPath(int _index)
{
    QString str = QString(root).append("/").append(m_path0[_index]);

    int current = m_comboBoxes[_index]->currentIndex();

    if(m_path1[_index].count() > 0)
        str.append("/").append(m_path1[_index][current]);

    if(m_path2[_index][current].count() > 0)
        str.append("/").append(m_path2[_index][current][0]);

    return str;
}


void MainWindow::loadPaths(QString _path, int _parent, int _current)
{
    QStringList directories = QDir(_path).entryList();
    int i = 0;

    foreach(QString dir, directories)
        if(dir.compare("MAPS", Qt::CaseInsensitive) != 0
                && dir.right(4).compare(".MTL", Qt::CaseInsensitive) != 0
                && dir.length() > 2)
        {
            QString path = QString(_path).append("/").append(dir);
            int count = path.count("/");

            if(count == 1)
            {
                QList<QString> listPath1;
                QList<QList<QString> > listPath2;
                m_path0.append(dir);
                m_path1.append(listPath1);
                m_path2.append(listPath2);
            }

            else if(count == 2)
            {
                QList<QString> listPath2;
                m_path2[_current].append(listPath2);
                m_path1[_current].append(dir);
            }

            else if(count == 3)
                m_path2[_parent][_current].append(dir);

            loadPaths(path, _current, i);
            i++;
        }
}


void MainWindow::initInterface()
{
    resize(1000, 600);

    for(int i = 0; i < 8; i++)
    {
        m_sldTailles.append(new QSlider());
        m_sldTailles[i]->setOrientation(Qt::Horizontal);
        m_sldTailles[i]->setRange(0, 1000);
        connect(m_sldTailles[i], SIGNAL(valueChanged(int)), this, SLOT(sldTaillesValueChanged()));
    }

    for(int i = 0; i < 13; i++)
    {
        m_additionalComboBoxes.append(new QComboBox);
        connect(m_additionalComboBoxes[i], SIGNAL(currentIndexChanged(int)), this, SLOT(additionalComboBoxesCurrentIndexChanged()));
    }

    for(int i = 0; i < m_path0.count(); i++)
    {
        m_comboBoxes.append(new QComboBox());
        connect(m_comboBoxes[i], SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxesCurrentIndexChanged()));
    }

    addColorToComboBox("1", QColor(qRgb(202, 167, 143)), m_additionalComboBoxes[0]);
    addColorToComboBox("2", QColor(qRgb(189, 152, 120)), m_additionalComboBoxes[0]);
    addColorToComboBox("3", QColor(qRgb(174, 138, 104)), m_additionalComboBoxes[0]);
    addColorToComboBox("4", QColor(qRgb(149, 115,  86)), m_additionalComboBoxes[0]);
    addColorToComboBox("5", QColor(qRgb(137, 100,  74)), m_additionalComboBoxes[0]);
    addColorToComboBox("6", QColor(qRgb(125,  90,  64)), m_additionalComboBoxes[0]);
    addColorToComboBox("7", QColor(qRgb(102,  69,  45)), m_additionalComboBoxes[0]);
    addColorToComboBox("8", QColor(qRgb( 78,  54,  42)), m_additionalComboBoxes[0]);

    m_additionalComboBoxes[1]->addItem("ovale");
    m_additionalComboBoxes[1]->addItem("rectangulaire");
    m_additionalComboBoxes[1]->addItem("rond");
    m_additionalComboBoxes[1]->addItem("carre ");
    m_additionalComboBoxes[1]->addItem("triangulaire");

    m_additionalComboBoxes[2]->addItem("en amandes");
    m_additionalComboBoxes[2]->addItem("asiatiques");
    m_additionalComboBoxes[2]->addItem("ronds");

    addColorToComboBox("bleu",     QColor(qRgb( 84, 104, 167)), m_additionalComboBoxes[3]);
    addColorToComboBox("vert",     QColor(qRgb( 75, 170, 130)), m_additionalComboBoxes[3]);
    addColorToComboBox("noisette", QColor(qRgb(175, 176, 119)), m_additionalComboBoxes[3]);
    addColorToComboBox("marron",   QColor(qRgb(129, 107,  86)), m_additionalComboBoxes[3]);

    m_additionalComboBoxes[4]->addItem("1");
    m_additionalComboBoxes[4]->addItem("2");
    m_additionalComboBoxes[4]->addItem("3");
    m_additionalComboBoxes[4]->addItem("4");
    m_additionalComboBoxes[4]->addItem("5");
    m_additionalComboBoxes[4]->addItem("6");
    m_additionalComboBoxes[4]->addItem("7");
    m_additionalComboBoxes[4]->addItem("8");
    m_additionalComboBoxes[4]->addItem("9");

    m_hairColors.append(QColor(qRgb( 20,  20,  20)));
    m_hairColors.append(QColor(qRgb( 58,  40,  28)));
    m_hairColors.append(QColor(qRgb(111,  68,  30)));
    m_hairColors.append(QColor(qRgb(168,  98,  39)));
    m_hairColors.append(QColor(qRgb(198, 158, 109)));

    addColorToComboBox("noir",    m_hairColors[0], m_additionalComboBoxes[5]);
    addColorToComboBox("brun",    m_hairColors[1], m_additionalComboBoxes[5]);
    addColorToComboBox("chatain", m_hairColors[2], m_additionalComboBoxes[5]);
    addColorToComboBox("roux",    m_hairColors[3], m_additionalComboBoxes[5]);
    addColorToComboBox("blond",   m_hairColors[4], m_additionalComboBoxes[5]);

    m_additionalComboBoxes[6]->addItem("A");
    m_additionalComboBoxes[6]->addItem("B");
    m_additionalComboBoxes[6]->addItem("C");
    m_additionalComboBoxes[6]->addItem("D");
    m_additionalComboBoxes[6]->addItem("E");
    m_additionalComboBoxes[6]->addItem("F");

    m_additionalComboBoxes[7]->addItem("Long");
    m_additionalComboBoxes[7]->addItem("Court");

    m_additionalComboBoxes[8]->addItem("Long");
    m_additionalComboBoxes[8]->addItem("Court");

    m_additionalComboBoxes[9]->addItem("Plat");
    m_additionalComboBoxes[9]->addItem("Haut");

    m_additionalComboBoxes[10]->addItem("Robe");
    m_additionalComboBoxes[10]->addItem("Top");
    m_additionalComboBoxes[10]->addItem("Chemisier");

    m_additionalComboBoxes[11]->addItem("Jean");
    m_additionalComboBoxes[11]->addItem("Legging");
    m_additionalComboBoxes[11]->addItem("Jupe");

    m_additionalComboBoxes[12]->addItem("Modele");
    m_additionalComboBoxes[12]->addItem("Margot");

    int space = 20;

    m_sldLayout.addItem(new QSpacerItem(0, space));
    m_sldLayout.addRow("Couleur de peau", m_additionalComboBoxes[0]);

    m_sldLayout.addItem(new QSpacerItem(0, space));
    m_sldLayout.addRow("Texture du visage", m_additionalComboBoxes[12]);

    m_sldLayout.addItem(new QSpacerItem(0, space));
    m_sldLayout.addRow("Forme du visage", m_additionalComboBoxes[1]);

    m_sldLayout.addItem(new QSpacerItem(0, space));
    m_sldLayout.addRow("Forme des yeux", m_additionalComboBoxes[2]);
    m_sldLayout.addRow("Couleur des yeux", m_additionalComboBoxes[3]);

    m_sldLayout.addItem(new QSpacerItem(0, space));
    m_sldLayout.addRow("Coupe de cheveux", m_additionalComboBoxes[4]);
    m_sldLayout.addRow("Couleur des cheveux", m_additionalComboBoxes[5]);

    m_sldLayout.addItem(new QSpacerItem(0, space));
    // m_sldLayout.addRow("Tour du cou", m_sldTailles[3]);
    // m_sldLayout.addRow("Tour de poitrine", m_additionalComboBoxes[6]);

    m_sldLayout.addRow("Poitrine", m_sldTailles[0]);


    m_sldLayout.addRow("Tour de taille",   m_sldTailles[2]);
    m_sldLayout.addRow("Tour de hanches",  m_sldTailles[1]);

    m_sldLayout.addItem(new QSpacerItem(0, space));
    m_sldLayout.addRow("Tour de bras", m_sldTailles[4]);
    m_sldLayout.addRow("Longueur des bras", m_sldTailles[6]);

    // m_sldLayout.addRow("Longueur des bras", m_additionalComboBoxes[7]);

    m_sldLayout.addItem(new QSpacerItem(0, space));
    m_sldLayout.addRow("Tour de cuisse", m_sldTailles[5]);
    m_sldLayout.addRow("Longueur des jambes", m_sldTailles[7]);

    // m_sldLayout.addRow("Longueur des jambes", m_additionalComboBoxes[8]);

    m_sldLayout.addItem(new QSpacerItem(0, space));
    // m_sldLayout.addRow("Hauteur de talon", m_additionalComboBoxes[9]);

    m_sldLayout.addItem(new QSpacerItem(0, space));

    m_sldLayout.addRow("Haut", m_additionalComboBoxes[10]);
    m_sldLayout.addRow("Bas", m_additionalComboBoxes[11]);


    for(int i = 0; i < m_path0.count(); i++)
    {
        for(int j = 0; j < m_path1[i].count(); j++)
            if(m_path1[i][j].right(4).compare(".OBJ", Qt::CaseInsensitive) == 0)
                m_comboBoxes[i]->addItem(m_path1[i][j].left(m_path1[i][j].length() - 4));

        // m_sldLayout.addRow(m_path0[i], m_comboBoxes[i]);
    }


    m_mainLayout.addLayout(&m_sldLayout, 1);
    m_mainLayout.addWidget(&m_glWidget, 10);

    m_centralWidget.setLayout(&m_mainLayout);
    setCentralWidget(&m_centralWidget);
}


void MainWindow::addColorToComboBox(QString _text, QColor _color, QComboBox* _comboBox)
{
    int size = _comboBox->style()->pixelMetric(QStyle::PM_SmallIconSize);

    QPixmap pixmap(size, size);
    QPalette palette = _comboBox->palette();

    pixmap.fill(_color);
    palette.setColor(QPalette::HighlightedText, Qt::black);

    palette.setColor(QPalette::Highlight, Qt::transparent);

    _comboBox->addItem(_text);
    _comboBox->setItemData(_comboBox->count() - 1, pixmap, Qt::DecorationRole);
    _comboBox->setPalette(palette);
}

