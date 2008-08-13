/*
    Copyright (c) 2008 NetAllied Systems GmbH

	This file is part of COLLADAMax.

    Portions of the code are:
    Copyright (c) 2005-2007 Feeling Software Inc.
    Copyright (c) 2005-2007 Sony Computer Entertainment America
    
    Based on the 3dsMax COLLADA Tools:
    Copyright (c) 2005-2006 Autodesk Media Entertainment
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/


#ifndef __COLLADAMAX_STABLE_HEADERS_H__
#define __COLLADAMAX_STABLE_HEADERS_H__


#ifdef MAX_9
#pragma message ("Compling for Max9")
#elif MAX_2008
#pragma message ("Compling for Max2008")
#elif MAX_2009
#pragma message ("Compling for Max2009")
#endif

#include <Max.h>
#include <istdplug.h>
#include <iparamb2.h>	// for IparamBlock2
#include <iparamm2.h>    // for IparamBlock2
#include <bitmap.h>    //for bitmap info
#include <triobj.h>
#include <MeshNormalSpec.h>
#include <modstack.h>   // for IDerivedObject
#include <cs/bipexp.h>   // for BipIface
#include <matrix3.h>
#include <stdmat.h>       // for standard material
#include <shaders.h>   // for shaders
#include <decomp.h>    // for decomposition of transformations
#include <simpobj.h>   //for SimpleObject2
#include <imtl.h>      // for UVGen
#include <custcont.h>  //for dialog


#include <IDxMaterial.h>  // for IDxMaterial

//STL
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>


#endif //__COLLADAMAX_STABLE_HEADERS_H__
