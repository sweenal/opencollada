/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_POLYMOVEFACE_H__
#define __MayaDM_POLYMOVEFACE_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMPolyMoveEdge.h"
namespace MayaDM
{
class PolyMoveFace : public PolyMoveEdge
{
public:
public:
	PolyMoveFace(FILE* file,const std::string& name,const std::string& parent=""):PolyMoveEdge(file, name, parent, "polyMoveFace"){}
	virtual ~PolyMoveFace(){}
	void setOffset(float off)
	{
		if(off == 0.0) return;
		fprintf(mFile,"setAttr \".off\" %f;\n", off);

	}
	void setWeight(double w)
	{
		if(w == 0.0) return;
		fprintf(mFile,"setAttr \".w\" %f;\n", w);

	}
	void setGravity(const double3& g)
	{
		if(g == double3(0.0, -1.0, 0.0)) return;
		fprintf(mFile,"setAttr \".g\" -type \"double3\" ");
		g.write(mFile);
		fprintf(mFile,";\n");

	}
	void setGravityX(double gx)
	{
		if(gx == 0) return;
		fprintf(mFile,"setAttr \".g.gx\" %f;\n", gx);

	}
	void setGravityY(double gy)
	{
		if(gy == 0) return;
		fprintf(mFile,"setAttr \".g.gy\" %f;\n", gy);

	}
	void setGravityZ(double gz)
	{
		if(gz == 0) return;
		fprintf(mFile,"setAttr \".g.gz\" %f;\n", gz);

	}
	void setAttraction(double att)
	{
		if(att == 0.0) return;
		fprintf(mFile,"setAttr \".att\" %f;\n", att);

	}
	void setMagnet(const double3& m)
	{
		if(m == double3(0.0, 0.0, 0.0)) return;
		fprintf(mFile,"setAttr \".m\" -type \"double3\" ");
		m.write(mFile);
		fprintf(mFile,";\n");

	}
	void setMagnX(double mx)
	{
		if(mx == 0) return;
		fprintf(mFile,"setAttr \".m.mx\" %f;\n", mx);

	}
	void setMagnY(double my)
	{
		if(my == 0) return;
		fprintf(mFile,"setAttr \".m.my\" %f;\n", my);

	}
	void setMagnZ(double mz)
	{
		if(mz == 0) return;
		fprintf(mFile,"setAttr \".m.mz\" %f;\n", mz);

	}
	void getOffset()
	{
		fprintf(mFile,"\"%s.off\"",mName.c_str());

	}
	void getWeight()
	{
		fprintf(mFile,"\"%s.w\"",mName.c_str());

	}
	void getGravity()
	{
		fprintf(mFile,"\"%s.g\"",mName.c_str());

	}
	void getGravityX()
	{
		fprintf(mFile,"\"%s.g.gx\"",mName.c_str());

	}
	void getGravityY()
	{
		fprintf(mFile,"\"%s.g.gy\"",mName.c_str());

	}
	void getGravityZ()
	{
		fprintf(mFile,"\"%s.g.gz\"",mName.c_str());

	}
	void getAttraction()
	{
		fprintf(mFile,"\"%s.att\"",mName.c_str());

	}
	void getMagnet()
	{
		fprintf(mFile,"\"%s.m\"",mName.c_str());

	}
	void getMagnX()
	{
		fprintf(mFile,"\"%s.m.mx\"",mName.c_str());

	}
	void getMagnY()
	{
		fprintf(mFile,"\"%s.m.my\"",mName.c_str());

	}
	void getMagnZ()
	{
		fprintf(mFile,"\"%s.m.mz\"",mName.c_str());

	}
protected:
	PolyMoveFace(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):PolyMoveEdge(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_POLYMOVEFACE_H__
