/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_CURVERANGE_H__
#define __MayaDM_CURVERANGE_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMAbstractBaseCreate.h"
namespace MayaDM
{
class CurveRange : public AbstractBaseCreate
{
public:
	CurveRange():AbstractBaseCreate(){}
	CurveRange(FILE* file,const std::string& name,const std::string& parent=""):AbstractBaseCreate(file, name, parent, "curveRange"){}
	virtual ~CurveRange(){}
protected:
	CurveRange(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType)
		:AbstractBaseCreate(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_CURVERANGE_H__
