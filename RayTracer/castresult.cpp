#include "castresult.h"

CastResult::CastResult()
{
    this->t = -1; //No hit.
    this->subject = NULL;
    this->subjectProperties = NULL;
    this->surfaceNormal = QVector3D(0,0,0);
}

void CastResult::reset()
{
    this->t = -1; //No hit.
    this->subject = NULL;
    this->subjectProperties = NULL;
    this->surfaceNormal = QVector3D(0,0,0);
}
