/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_NURBSTESSELLATE_H__
#define __MayaDM_NURBSTESSELLATE_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMParentTessellate.h"
namespace MayaDM
{
class NurbsTessellate : public ParentTessellate
{
public:
public:
	NurbsTessellate(FILE* file,const std::string& name,const std::string& parent=""):ParentTessellate(file, name, parent, "nurbsTessellate"){}
	virtual ~NurbsTessellate(){}
	void setSmoothEdge(bool ues)
	{
		if(ues == false) return;
		fprintf(mFile,"setAttr \".ues\" %i;\n", ues);

	}
	void setSmoothEdgeRatio(double esr)
	{
		if(esr == 0.99) return;
		fprintf(mFile,"setAttr \".esr\" %f;\n", esr);

	}
	void setExplicitTessellationAttributes(bool eta)
	{
		if(eta == true) return;
		fprintf(mFile,"setAttr \".eta\" %i;\n", eta);

	}
	void setUDivisionsFactor(double nuf)
	{
		if(nuf == 1.5) return;
		fprintf(mFile,"setAttr \".nuf\" %f;\n", nuf);

	}
	void setVDivisionsFactor(double nvf)
	{
		if(nvf == 1.5) return;
		fprintf(mFile,"setAttr \".nvf\" %f;\n", nvf);

	}
	void setCurvatureTolerance(unsigned int cvt)
	{
		if(cvt == 2) return;
		fprintf(mFile,"setAttr \".cvt\" %i;\n", cvt);

	}
	void getInputSurface()
	{
		fprintf(mFile,"\"%s.is\"",mName.c_str());

	}
	void getSmoothEdge()
	{
		fprintf(mFile,"\"%s.ues\"",mName.c_str());

	}
	void getSmoothEdgeRatio()
	{
		fprintf(mFile,"\"%s.esr\"",mName.c_str());

	}
	void getExplicitTessellationAttributes()
	{
		fprintf(mFile,"\"%s.eta\"",mName.c_str());

	}
	void getUDivisionsFactor()
	{
		fprintf(mFile,"\"%s.nuf\"",mName.c_str());

	}
	void getVDivisionsFactor()
	{
		fprintf(mFile,"\"%s.nvf\"",mName.c_str());

	}
	void getCurvatureTolerance()
	{
		fprintf(mFile,"\"%s.cvt\"",mName.c_str());

	}
protected:
	NurbsTessellate(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):ParentTessellate(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_NURBSTESSELLATE_H__
