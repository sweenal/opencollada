/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADAFramework.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADAFW_CONSTANTS_H__
#define __COLLADAFW_CONSTANTS_H__

#include "COLLADAFWPrerequisites.h"

namespace COLLADAFW
{

    /** Declares the storage for the graphical representation of an object. */
    class Constants
    {

    public:

        static const String EMPTY_STRING;

        static const String SEMANTIC_BINORMAL;
        static const String SEMANTIC_COLOR;
        static const String SEMANTIC_CONTINUITY;
        static const String SEMANTIC_IMAGE;
        static const String SEMANTIC_INPUT;
        static const String SEMANTIC_IN_TANGENT;
        static const String SEMANTIC_INTERPOLATION;
        static const String SEMANTIC_INV_BIND_MATRIX;
        static const String SEMANTIC_JOINT;
        static const String SEMANTIC_LINEAR_STEPS;
        static const String SEMANTIC_MORPH_TARGET;
        static const String SEMANTIC_MORPH_WEIGHT;
        static const String SEMANTIC_NORMAL;
        static const String SEMANTIC_OUTPUT;
        static const String SEMANTIC_OUT_TANGENT;
        static const String SEMANTIC_POSITION;
        static const String SEMANTIC_TANGENT;
        static const String SEMANTIC_TEXBINORMAL;
        static const String SEMANTIC_TEXCOORD;
        static const String SEMANTIC_TEXTANGENT;
        static const String SEMANTIC_UV;
        static const String SEMANTIC_VERTEX;
        static const String SEMANTIC_WEIGHT;

    };
}

#endif // __COLLADAFW_CONSTANTS_H__