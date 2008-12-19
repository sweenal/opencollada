/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_FILTEREULER_H__
#define __MayaDM_FILTEREULER_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMFilter.h"
namespace MayaDM
{
class FilterEuler : public Filter
{
public:
public:
	FilterEuler(FILE* file,const std::string& name,const std::string& parent=""):Filter(file, name, parent, "filterEuler"){}
	virtual ~FilterEuler(){}
	void setSmooth(unsigned int s)
	{
		if(s == 3) return;
		fprintf(mFile,"setAttr \".s\" %i;\n", s);

	}
	void setNearestTo(unsigned int nt)
	{
		if(nt == 2) return;
		fprintf(mFile,"setAttr \".nt\" %i;\n", nt);

	}
	void setWeight(const double3& w)
	{
		if(w == double3(1.0, 1.0, 1.0)) return;
		fprintf(mFile,"setAttr \".w\" -type \"double3\" ");
		w.write(mFile);
		fprintf(mFile,";\n");

	}
	void setWeightX(double wx)
	{
		if(wx == 1.0) return;
		fprintf(mFile,"setAttr \".w.wx\" %f;\n", wx);

	}
	void setWeightY(double wy)
	{
		if(wy == 1.0) return;
		fprintf(mFile,"setAttr \".w.wy\" %f;\n", wy);

	}
	void setWeightZ(double wz)
	{
		if(wz == 1.0) return;
		fprintf(mFile,"setAttr \".w.wz\" %f;\n", wz);

	}
	void setEnableInitialRotation(bool eir)
	{
		if(eir == false) return;
		fprintf(mFile,"setAttr \".eir\" %i;\n", eir);

	}
	void setInitialRotation(const double3& ir)
	{
		if(ir == double3(0., 0., 0.)) return;
		fprintf(mFile,"setAttr \".ir\" -type \"double3\" ");
		ir.write(mFile);
		fprintf(mFile,";\n");

	}
	void setInitialRotationX(double irx)
	{
		if(irx == 0) return;
		fprintf(mFile,"setAttr \".ir.irx\" %f;\n", irx);

	}
	void setInitialRotationY(double iry)
	{
		if(iry == 0) return;
		fprintf(mFile,"setAttr \".ir.iry\" %f;\n", iry);

	}
	void setInitialRotationZ(double irz)
	{
		if(irz == 0) return;
		fprintf(mFile,"setAttr \".ir.irz\" %f;\n", irz);

	}
	void setOutputUsageOpt(unsigned int use)
	{
		if(use == 0) return;
		fprintf(mFile,"setAttr \".use\" %i;\n", use);

	}
	void getSmooth()
	{
		fprintf(mFile,"\"%s.s\"",mName.c_str());

	}
	void getNearestTo()
	{
		fprintf(mFile,"\"%s.nt\"",mName.c_str());

	}
	void getWeight()
	{
		fprintf(mFile,"\"%s.w\"",mName.c_str());

	}
	void getWeightX()
	{
		fprintf(mFile,"\"%s.w.wx\"",mName.c_str());

	}
	void getWeightY()
	{
		fprintf(mFile,"\"%s.w.wy\"",mName.c_str());

	}
	void getWeightZ()
	{
		fprintf(mFile,"\"%s.w.wz\"",mName.c_str());

	}
	void getEnableInitialRotation()
	{
		fprintf(mFile,"\"%s.eir\"",mName.c_str());

	}
	void getInitialRotation()
	{
		fprintf(mFile,"\"%s.ir\"",mName.c_str());

	}
	void getInitialRotationX()
	{
		fprintf(mFile,"\"%s.ir.irx\"",mName.c_str());

	}
	void getInitialRotationY()
	{
		fprintf(mFile,"\"%s.ir.iry\"",mName.c_str());

	}
	void getInitialRotationZ()
	{
		fprintf(mFile,"\"%s.ir.irz\"",mName.c_str());

	}
	void getOutputUsageOpt()
	{
		fprintf(mFile,"\"%s.use\"",mName.c_str());

	}
protected:
	FilterEuler(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):Filter(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_FILTEREULER_H__
