/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_SUBDMODIFIERWORLD_H__
#define __MayaDM_SUBDMODIFIERWORLD_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMSubdModifier.h"
namespace MayaDM
{
class SubdModifierWorld : public SubdModifier
{
public:
public:
	SubdModifierWorld(FILE* file,const std::string& name,const std::string& parent=""):SubdModifier(file, name, parent, "subdModifierWorld"){}
	virtual ~SubdModifierWorld(){}
	void setInputMatrix(const matrix& ix)
	{
		fprintf(mFile,"setAttr \".ix\" -type \"matrix\" ");
		ix.write(mFile);
		fprintf(mFile,";\n");

	}
	void setWorldSpace(bool ws)
	{
		if(ws == false) return;
		fprintf(mFile,"setAttr \".ws\" %i;\n", ws);

	}
	void setManipMatrix(const matrix& mp)
	{
		fprintf(mFile,"setAttr \".mp\" -type \"matrix\" ");
		mp.write(mFile);
		fprintf(mFile,";\n");

	}
	void getInputMatrix()
	{
		fprintf(mFile,"\"%s.ix\"",mName.c_str());

	}
	void getWorldSpace()
	{
		fprintf(mFile,"\"%s.ws\"",mName.c_str());

	}
	void getManipMatrix()
	{
		fprintf(mFile,"\"%s.mp\"",mName.c_str());

	}
protected:
	SubdModifierWorld(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):SubdModifier(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_SUBDMODIFIERWORLD_H__
