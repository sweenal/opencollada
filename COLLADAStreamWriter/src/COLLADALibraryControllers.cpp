/*
    Copyright (c) 2008 NetAllied Systems GmbH
	
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include "COLLADAStreamWriter.h"
#include "COLLADALibraryControllers.h"
#include "COLLADASWC.h"
#include "COLLADAUtils.h"

namespace COLLADA
{

    const String LibraryControllers::SKIN_CONTROLLER_ID_SUFFIX = "-skin";
    const String LibraryControllers::MORPH_CONTROLLER_ID_SUFFIX = "-morph";
    const String LibraryControllers::ARRAY_ID_SUFFIX = "-array";
    const String LibraryControllers::JOINTS_SOURCE_ID_SUFFIX = "-joints";
    const String LibraryControllers::BIND_POSES_SOURCE_ID_SUFFIX = "-bind_poses";
    const String LibraryControllers::WEIGHTS_SOURCE_ID_SUFFIX = "-weights";
    

    //---------------------------------------------------------------
    LibraryControllers::LibraryControllers ( COLLADA::StreamWriter *streamWriter )
            : Library ( streamWriter, CSWC::COLLADA_ELEMENT_LIBRARY_CONTROLLERS )
    {}

    //---------------------------------------------------------------
    void LibraryControllers::openSkin ( 
        const String &controllerId, const String &controllerName, const String &skinTarget )
    {
        openController ( controllerId, controllerName );

        mSkinCloser = mSW->openElement ( CSWC::COLLADA_ELEMENT_SKIN );

        mSW->appendAttribute ( CSWC::COLLADA_ATTRIBUTE_SOURCE, skinTarget );
    }

    //---------------------------------------------------------------
    void LibraryControllers::closeSkin()
    {
        mSkinCloser.close();
    }

    //---------------------------------------------------------------
    void LibraryControllers::openController ( const String &controllerId, const String &controllerName )
    {
        openLibrary();

        mControllerCloser = mSW->openElement ( CSWC::COLLADA_ELEMENT_CONTROLLER );

        if ( !controllerId.empty() )
            mSW->appendAttribute ( CSWC::COLLADA_ATTRIBUTE_ID, controllerId );

        if ( !controllerName.empty() )
            mSW->appendAttribute ( CSWC::COLLADA_ATTRIBUTE_NAME, controllerName );
    }

    //---------------------------------------------------------------
    void LibraryControllers::closeController()
    {
        mControllerCloser.close();
    }

    //---------------------------------------------------------------
    void LibraryControllers::addBindShapeTransform ( const double matrix[][4] ) const
    {
        mSW->openElement ( CSWC::COLLADA_ELEMENT_BIND_SHAPE_MATRIX );

        mSW->appendValues ( matrix );

        mSW->closeElement();
    }


} //namespace COLLADA
