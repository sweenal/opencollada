/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_POLYDELFACET_H__
#define __MayaDM_POLYDELFACET_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMPolyModifier.h"
namespace MayaDM
{
class PolyDelFacet : public PolyModifier
{
public:
	PolyDelFacet():PolyModifier(){}
	PolyDelFacet(FILE* file,const std::string& name,const std::string& parent=""):PolyModifier(file, name, parent, "polyDelFacet"){}
	virtual ~PolyDelFacet(){}
protected:
	PolyDelFacet(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType)
		:PolyModifier(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_POLYDELFACET_H__
