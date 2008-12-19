/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_CONSTRAINT_H__
#define __MayaDM_CONSTRAINT_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMTransform.h"
namespace MayaDM
{
class Constraint : public Transform
{
public:
public:
	Constraint(FILE* file,const std::string& name,const std::string& parent=""):Transform(file, name, parent, "constraint"){}
	virtual ~Constraint(){}
	void setEnableRestPosition(bool erp)
	{
		if(erp == false) return;
		fprintf(mFile,"setAttr \".erp\" %i;\n", erp);

	}
	void setLockOutput(bool lo)
	{
		if(lo == false) return;
		fprintf(mFile,"setAttr \".lo\" %i;\n", lo);

	}
	void getEnableRestPosition()
	{
		fprintf(mFile,"\"%s.erp\"",mName.c_str());

	}
	void getLockOutput()
	{
		fprintf(mFile,"\"%s.lo\"",mName.c_str());

	}
protected:
	Constraint(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):Transform(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_CONSTRAINT_H__
