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

public:
/* As one may also find, google often points to the link below when
 * searching for 'raytracing materials' 
 * http://globe3d.sourceforge.net/g3d_html/gl-materials__ads.htm
 */ 
enum MaterialType
{
    DEFAULT,

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


    SceneObjectProperties ** materials;

    MaterialsFactory();

    static MaterialsFactory& getInstance()
    {
        static MaterialsFactory instance;
        return instance;
    }

    static SceneObjectProperties* getMaterial(MaterialType type)
    {
        return MaterialsFactory::getInstance().materials[type];
    }



};


#endif
