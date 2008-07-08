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


#ifndef __COLLADASTREAMWRITER_TECHNIQUE_H__
#define __COLLADASTREAMWRITER_TECHNIQUE_H__

#include "COLLADAPrerequisites.h"
#include "COLLADAElementWriter.h"
#include <map>

namespace COLLADA
{

    //---------------------------------------------------------------
    /** A class to add an Asset to the stream*/

    class Technique : public ElementWriter
    {

    private:

        /** Used to close the current @a \<technique\> tag */
        TagCloser mTechniqueCloser;

        /** Manages a map with the currently opened child elements */
        std::map<String, TagCloser*> mOpenChildElements;

    public:
        /** Constructor that sets the stream the asset should be written to*/
        Technique ( StreamWriter* streamWriter ) : ElementWriter ( streamWriter ) {}

        /** Opens the technique tag */
        void openTechnique ( const String &profile, const String &xmlns="" );

        /** Adds a parameter to the technique */
        void addParameter ( const String &paramName, const String &value="" );

        /** Adds a parameter to the technique */
        void addParameter ( const String &paramName, const int &value );

        /** Adds a parameter to the technique */
        void addParameter ( const String &paramName, const double &value );

        /** Adds a parameter to the technique */
        void addParameter ( const String &paramName, const bool &value );

        /** Adds a parameter to the technique */
        void addMatrixParameter ( const String &paramName, const double matrix[][4] ) const;

        /** Opens a tag with the given name and adds the TagCloser to the child element into a map */
        void addChildElement ( const String &childElementName );

        /** Closes the tag with the given name, if it is open */
        void closeChildElement ( const String &childElementName );

        /** Closes the technique tag */
        void closeTechnique();

    };

} //namespace COLLADA


#endif //__COLLADASTREAMWRITER_TECHNIQUE_H__
