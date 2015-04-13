/**
 * castresult.h
 * CastResults are encapsulations of the results of casting a ray into a scene.
 * They contain information such as the object hit, the t value of interaction,
 * where in space contact was made, and the normal of the surface contacted.
 *
 * This information is then used to calculate shading.
 */

#ifndef CASTRESULT_H
#define CASTRESULT_H

#include <QVector3D>
#include "scenegraphnode.h"

class SceneGraphNode;

class CastResult
{
public:
    CastResult();

    /** Reset the cast result to be used again */
    void reset();

    double t;

    SceneObject* subject;
    SceneObjectProperties* subjectProperties;
    QVector3D surfacePoint;
    QVector3D surfaceNormal;
};

#endif // CASTRESULT_H
