/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_SHELLTESSELLATE_H__
#define __MayaDM_SHELLTESSELLATE_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMParentTessellate.h"
namespace MayaDM
{
class ShellTessellate : public ParentTessellate
{
public:
public:
	ShellTessellate(FILE* file,const std::string& name,const std::string& parent=""):ParentTessellate(file, name, parent, "shellTessellate"){}
	virtual ~ShellTessellate(){}
	void getInputShell()
	{
		fprintf(mFile,"\"%s.is\"",mName.c_str());

	}
protected:
	ShellTessellate(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):ParentTessellate(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_SHELLTESSELLATE_H__
