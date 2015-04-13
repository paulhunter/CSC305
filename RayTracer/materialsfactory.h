/**
 * materialsfactory.h
 * The materials factory is a component which provides a number of well defined
 * materials that were either created by developers, or sourced from the
 * internet.
 *
 * For the moment there is no reason sceneobjects can't share instances of 
 * SceneObjectProperties, but in the future there may be a reason for this. 
 */

#ifndef MATERIALSFACTORY_H
#define MATERIALSFACTORY_H

#include "sceneobjectprops.h"

class MaterialsFactory
{

/* As one may also find, google often points to the link below when
 * searching for 'raytracing materials' 
 * http://globe3d.sourceforge.net/g3d_html/gl-materials__ads.htm
 */ 
enum MaterialType
{
	DEFAULT

	LIGHT_WHITE,

	RED_FLAT,
	ORANGE_FLAT,
	YELLOW_FLAT,
	GREEN_FLAT,
	INDIGO_FLAT,
	BLUE_FLAT,
	VIOLET_FLAT,
	WHITE_FLAT,
	BLACK_FLAT,
	GREY_FLAT,
	GREY_LIGHT_FLAT
	/* Real Materials, to add later.
	GLASS,
	BRASS,
	BRONZE,
	BRONZE_POLISHED,
	CHROME,
	COPPER,
	COPPER_POLISHED,
	GOLD,
	GOLD_POLISHED,
	PEWTER,
	SILVER,
	SILVER_POLISHED,
	EMERALD,
	JADE,
	OBSIDIAN,
	PEARL,
	RUBY,
	TURQUOISE,
	PLASTIC_BLACK,
	RUBBER_BLACK */
};

public:
	SceneObjectProperties* getMaterial(MaterialType type)
	{
		return materials[type];
	}
private:
	
	SceneObjectProperties* materials[] = new {
	//DEFAULT
	new SceneObjectProperties(
		QVector3D(0.2,0.2,0.2), //AMBIENT
		QVector3D(0.8,0.8,0.8), //DIFFUSE
		QVector3D(0.0, 0.0, 0.0), //SPECULAR
		0), //SHININESS

	//LIGHT_WHITE
	new SceneObjectProperties(QVector3D(1.0, 1.0, 1.0)),

	//RED_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(1.0,0,0), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//ORANGE_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.992157, 0.513726, 0.0), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//YELLOW_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.0, 1.0, 0.0), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//GREEN_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.0, 1.0, 0.0), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//INDIGO_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.0980392, 0.0, 0.458824), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//BLUE_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.0, 0.0, 1.0), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//VIOLET_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.635294, 0.0, 1.0), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//WHITE_FLAT
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.992157, 0.992157, 0.992157), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//BLACK_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.0, 0.0, 0.0), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//GREY_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.454902, 0.454902, 0.454902), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS
	//GREY_LIGHT_FLAT,
	new SceneObjectProperties(
		QVector3D(0,0,0), //AMBIENT
		QVector3D(0.682353, 0.682353, 0.682353), //DIFFUSE
		QVector3D(0.0225, 0.0225, 0.0225), //SPECULAR
		12.8), //SHININESS


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

	};

};


#endif