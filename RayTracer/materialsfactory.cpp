#include "materialsfactory.h"
#include <QDebug>

MaterialsFactory::MaterialsFactory()
{
    qDebug() << "MaterialsFactory: Creating Materials";
    this->materials = new SceneObjectProperties*[GREY_LIGHT_FLAT+1];
    this->materials[DEFAULT] =
        new SceneObjectProperties(
            QVector3D(0.2,0.2,0.2), //AMBIENT
            QVector3D(0.8,0.8,0.8), //DIFFUSE
            QVector3D(0.0, 0.0, 0.0), //SPECULAR
            0); //SHININESS

        //LIGHT_WHITE
    this->materials[LIGHT_WHITE] = new SceneObjectProperties(QVector3D(1.0, 1.0, 1.0)),

    this->materials[LIGHT_RED] = new SceneObjectProperties(QVector3D(1.0, 0, 0)),

    this->materials[LIGHT_BLUE] = new SceneObjectProperties(QVector3D(0, 0, 1)),

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
        //COPPER_POLISHED,
        //GOLD,
        //GOLD_POLISHED,
        //PEWTER,
        //SILVER,
        //SILVER_POLISHED,
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
