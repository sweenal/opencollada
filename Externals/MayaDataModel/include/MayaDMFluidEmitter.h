/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_FLUIDEMITTER_H__
#define __MayaDM_FLUIDEMITTER_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMPointEmitter.h"
namespace MayaDM
{
class FluidEmitter : public PointEmitter
{
public:
public:
	FluidEmitter(FILE* file,const std::string& name,const std::string& parent=""):PointEmitter(file, name, parent, "fluidEmitter"){}
	virtual ~FluidEmitter(){}
	void setFluidDropoff(double fdo)
	{
		if(fdo == 2) return;
		fprintf(mFile,"setAttr \".fdo\" %f;\n", fdo);

	}
	void setTurbulenceType(unsigned int trt)
	{
		if(trt == 0) return;
		fprintf(mFile,"setAttr \".trt\" %i;\n", trt);

	}
	void setFluidJitter(bool fjt)
	{
		if(fjt == true) return;
		fprintf(mFile,"setAttr \".fjt\" %i;\n", fjt);

	}
	void setTurbulence(double trb)
	{
		if(trb == 0.0) return;
		fprintf(mFile,"setAttr \".trb\" %f;\n", trb);

	}
	void setTurbulenceSpeed(double trs)
	{
		if(trs == 0.2) return;
		fprintf(mFile,"setAttr \".trs\" %f;\n", trs);

	}
	void setTurbulenceFrequency(const double3& tf)
	{
		fprintf(mFile,"setAttr \".tf\" -type \"double3\" ");
		tf.write(mFile);
		fprintf(mFile,";\n");

	}
	void setTurbulenceFrequencyX(double tfx)
	{
		if(tfx == 1.0) return;
		fprintf(mFile,"setAttr \".tf.tfx\" %f;\n", tfx);

	}
	void setTurbulenceFrequencyY(double tfy)
	{
		if(tfy == 1.0) return;
		fprintf(mFile,"setAttr \".tf.tfy\" %f;\n", tfy);

	}
	void setTurbulenceFrequencyZ(double tfz)
	{
		if(tfz == 1.0) return;
		fprintf(mFile,"setAttr \".tf.tfz\" %f;\n", tfz);

	}
	void setTurbulenceOffset(const double3& to)
	{
		fprintf(mFile,"setAttr \".to\" -type \"double3\" ");
		to.write(mFile);
		fprintf(mFile,";\n");

	}
	void setTurbulenceOffsetX(double tox)
	{
		if(tox == 0.0) return;
		fprintf(mFile,"setAttr \".to.tox\" %f;\n", tox);

	}
	void setTurbulenceOffsetY(double toy)
	{
		if(toy == 0.0) return;
		fprintf(mFile,"setAttr \".to.toy\" %f;\n", toy);

	}
	void setTurbulenceOffsetZ(double toz)
	{
		if(toz == 0.0) return;
		fprintf(mFile,"setAttr \".to.toz\" %f;\n", toz);

	}
	void setDetailTurbulence(double dtr)
	{
		if(dtr == 0.0) return;
		fprintf(mFile,"setAttr \".dtr\" %f;\n", dtr);

	}
	void setFluidDensityEmission(double fde)
	{
		if(fde == 1.0) return;
		fprintf(mFile,"setAttr \".fde\" %f;\n", fde);

	}
	void setFluidHeatEmission(double fhe)
	{
		if(fhe == 0.0) return;
		fprintf(mFile,"setAttr \".fhe\" %f;\n", fhe);

	}
	void setFluidFuelEmission(double ffe)
	{
		if(ffe == 0.0) return;
		fprintf(mFile,"setAttr \".ffe\" %f;\n", ffe);

	}
	void setEmitFluidColor(bool efc)
	{
		if(efc == false) return;
		fprintf(mFile,"setAttr \".efc\" %i;\n", efc);

	}
	void getFluidDropoff()
	{
		fprintf(mFile,"\"%s.fdo\"",mName.c_str());

	}
	void getTurbulenceType()
	{
		fprintf(mFile,"\"%s.trt\"",mName.c_str());

	}
	void getFluidJitter()
	{
		fprintf(mFile,"\"%s.fjt\"",mName.c_str());

	}
	void getTurbulence()
	{
		fprintf(mFile,"\"%s.trb\"",mName.c_str());

	}
	void getTurbulenceSpeed()
	{
		fprintf(mFile,"\"%s.trs\"",mName.c_str());

	}
	void getTurbulenceFrequency()
	{
		fprintf(mFile,"\"%s.tf\"",mName.c_str());

	}
	void getTurbulenceFrequencyX()
	{
		fprintf(mFile,"\"%s.tf.tfx\"",mName.c_str());

	}
	void getTurbulenceFrequencyY()
	{
		fprintf(mFile,"\"%s.tf.tfy\"",mName.c_str());

	}
	void getTurbulenceFrequencyZ()
	{
		fprintf(mFile,"\"%s.tf.tfz\"",mName.c_str());

	}
	void getTurbulenceOffset()
	{
		fprintf(mFile,"\"%s.to\"",mName.c_str());

	}
	void getTurbulenceOffsetX()
	{
		fprintf(mFile,"\"%s.to.tox\"",mName.c_str());

	}
	void getTurbulenceOffsetY()
	{
		fprintf(mFile,"\"%s.to.toy\"",mName.c_str());

	}
	void getTurbulenceOffsetZ()
	{
		fprintf(mFile,"\"%s.to.toz\"",mName.c_str());

	}
	void getDetailTurbulence()
	{
		fprintf(mFile,"\"%s.dtr\"",mName.c_str());

	}
	void getFluidDensityEmission()
	{
		fprintf(mFile,"\"%s.fde\"",mName.c_str());

	}
	void getFluidHeatEmission()
	{
		fprintf(mFile,"\"%s.fhe\"",mName.c_str());

	}
	void getFluidFuelEmission()
	{
		fprintf(mFile,"\"%s.ffe\"",mName.c_str());

	}
	void getEmitFluidColor()
	{
		fprintf(mFile,"\"%s.efc\"",mName.c_str());

	}
	void getEmissionFunction()
	{
		fprintf(mFile,"\"%s.ef\"",mName.c_str());

	}
protected:
	FluidEmitter(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):PointEmitter(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_FLUIDEMITTER_H__
