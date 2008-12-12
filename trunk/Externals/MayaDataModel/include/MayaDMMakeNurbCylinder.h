/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_MAKENURBCYLINDER_H__
#define __MayaDM_MAKENURBCYLINDER_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMRevolvedPrimitive.h"
namespace MayaDM
{
/*
Compute a cylinder given the center point (pivot) and the radius (radius).
 A partial cylinder can be computed by using startSweep and endSweep.
 <br/>
 <br/>
 The resolution of the cylinder in the sweep direction can be controlled
 by specifying the useTolerance (useTolerance) attribute and the
 tolerance (tolerance). Otherwise the number of sections (sections) will
 be used. Use spans to control the cylinder's resolution in the opposite direction.
 <br/>
 <br/>
 Control the orientation of the cylinder by specifying the axis of the cylinder.
 <br/>
 <br/>
 The degree of the resulting surface can be linear or cubic.
 <p/>
*/
class MakeNurbCylinder : public RevolvedPrimitive
{
public:
public:
	MakeNurbCylinder(FILE* file,const std::string& name,const std::string& parent=""):RevolvedPrimitive(file, name, parent, "makeNurbCylinder"){}
	virtual ~MakeNurbCylinder(){}
protected:
	MakeNurbCylinder(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):RevolvedPrimitive(file, name, parent, nodeType) {}
private:

};
}//namespace MayaDM
#endif//__MayaDM_MAKENURBCYLINDER_H__
