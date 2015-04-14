#include "materialsfactory.h"
#include <QDebug>

MaterialsFactory::MaterialsFactory()
{
    qDebug() << "MaterialsFactory: Creating Materials";
    this->materials = new SceneObjectProperties*[MAT_LAST+1];
    this->materials[DEFAULT] =
        new SceneObjectProperties(
            QVector3D(0.2,0.2,0.2), //AMBIENT
            QVector3D(0.8,0.8,0.8), //DIFFUSE
            QVector3D(0.0, 0.0, 0.0), //SPECULAR
            0); //SHININESS

        //LIGHT_WHITE
    this->materials[LIGHT_WHITE] = new SceneObjectProperties(QVector3D(0.2, 0.2, 0.2)),
    this->materials[LIGHT_WHITE_SCENE] = new SceneObjectProperties(QVector3D(0.1, 0.1, 0.1)),

    /* For BlinnPhong
    this->materials[LIGHT_WHITE] = new SceneObjectProperties(QVector3D(0.02, 0.02, 0.02)),
    this->materials[LIGHT_WHITE_SCENE] = new SceneObjectProperties(QVector3D(0.05, 0.05, 0.05)),
    */

    this->materials[LIGHT_RED] = new SceneObjectProperties(QVector3D(0.3, 0, 0)),

    this->materials[LIGHT_BLUE] = new SceneObjectProperties(QVector3D(0, 0, 0.3)),

        //RED_FLAT,
    this->materials[RED_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(1.0,0,0), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8);

    this->materials[ORANGE_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.992157, 0.513726, 0.0), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8);

    this->materials[YELLOW_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.0, 1.0, 0.0), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8), //SHININESS

        //GREEN_FLAT,
    this->materials[GREEN_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.0, 1.0, 0.0), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8); //SHININESS
        //INDIGO_FLAT,
    this->materials[INDIGO_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.0980392, 0.0, 0.458824), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8); //SHININESS

        //BLUE_FLAT,
    this->materials[BLUE_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.0, 0.0, 1.0), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8); //SHININESS

   this->materials[VIOLET_FLAT] =
        new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.635294, 0.0, 1.0), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8); //SHININESS

    this->materials[WHITE_FLAT] =
        new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.992157, 0.992157, 0.992157), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8); //SHININESS
        //BLACK_FLAT,
    this->materials[BLACK_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.0, 0.0, 0.0), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8); //SHININESS

    this->materials[GREY_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.454902, 0.454902, 0.454902), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8);  //SHININESS

    this->materials[GREY_LIGHT_FLAT] = new SceneObjectProperties(
            QVector3D(0,0,0), //AMBIENT
            QVector3D(0.682353, 0.682353, 0.682353), //DIFFUSE
            QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
            12.8); //SHININESS

        //GLASS,
        //BRASS,
        //BRONZE,
        //BRONZE_POLISHED,
        //CHROME,
        //COPPER,
    this->materials[COPPER_POLISHED] = new SceneObjectProperties(
            QVector3D(0.2295, 0.08825, 0.0275), //AMBIENT
            QVector3D(0.5508, 0.2118, 0.066), //DIFFUSE
            QVector3D(0.580594, 0.223257, 0.0695701), //SPECULAR
            51.2, 0.3); //SHININESS

    //GOLD,
        //GOLD_POLISHED,
        //PEWTER,
        //SILVER,
     this->materials[SILVER_POLISHED] =new SceneObjectProperties(
                QVector3D(0.23125, 0.23125, 0.23125), //AMBIENT
                QVector3D(0.2775, 0.2775, 0.2775), //DIFFUSE
                QVector3D(0.773911, 0.773911, 0.773911), //SPECULAR
                89.6, 0.85), //SHININESS, MIRROR

        //EMERALD,
        //JADE,
        //OBSIDIAN,
        //PEARL,
        //RUBY,
        //TURQUOISE,
        //PLASTIC_BLACK,
        //RUBBER_BLACK

    qDebug() << "MaterialsFactory: Finished making materials";
}
