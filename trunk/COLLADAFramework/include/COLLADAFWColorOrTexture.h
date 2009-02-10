/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADAStreamWriter.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADAFRAMEWORK_COLOR_OR_TEXTURE_H__
#define __COLLADAFRAMEWORK_COLOR_OR_TEXTURE_H__

#include "COLLADAFWPrerequisites.h"
#include "COLLADAFWColor.h"
//#include "COLLADAFWTexture.h"
#include <vector>
#include <map>


namespace COLLADAFW
{

    /** Class that either represents a color or a texture*/
    class ColorOrTexture
    {

    public:

        enum Type
        {
            UNSPECIFIED,
            COLOR,
            TEXTURE
        };

	private:
        Type mType;
		Color mColor;
        //Texture mTexture;
        String mSid;

    public:
        /** Constructor to create a ColorOrTexture object that represents a color.
        @param color The color that should be represented.
        */
        ColorOrTexture ( Color color, const String& sid = "" )
        : mColor ( color )
        , mType ( COLOR )
        , mSid ( sid )
        {};

        /** Constructor to create a ColorOrTexture object that represents a color.
        @param texture The color that should be represented.
        */
/*        ColorOrTexture ( Texture texture, const String& sid = "" )
        : mTexture ( texture )
        , mType ( TEXTURE )
        , mSid ( sid )
        {};
*/
        /** Creates an invalid CommonColorOrTextureType*/
        ColorOrTexture() : mType ( UNSPECIFIED ) {};

        /** Copy-Constructor */
        ColorOrTexture ( const ColorOrTexture& cot )
        {
            mColor = cot.mColor;
//            mTexture = cot.mTexture;
            mType = cot.mType;
            mSid = cot.mSid;
        }

		/** Returns the type of the color or texture.*/
		Type getType() const { return mType; }

		/** Returns the type of the color or texture.*/
		void setType(Type type) { mType = type; }

        /** Returns the sid. */
        const String& getSid () const
        {
            return mSid;
        }

        /** Return true if the CommonColorOrTextureType is a valid color, false otherwise*/
        bool isColor() const
        {
            return ( mType == COLOR ) && ( mColor.isValid() );
        }

        /** Return true if the CommonColorOrTextureType is a valid Texture, false otherwise.*/
 /*       bool isTexture() const
        {
            return ( mType == TEXTURE ) && ( mTexture.isValid() );
        }
*/
        /** Return true if the CommonColorOrTextureType is a valid Texture, false otherwise.*/
        bool isValid() const
        {
            return ( mType != UNSPECIFIED ) /*&& ( isTexture() || isColor() ) */;
        }


        /** Returns the color */
        const Color& getColor() const
        {
            return mColor;
        }

        /** Returns the color */
        Color& getColor()
        {
            return mColor;
        }

        /** Returns the texture */
/*        const Texture& getTexture() const
        {
            return mTexture;
        }*/

        /** Returns the texture */
/*        Texture& getTexture()
        {
            return mTexture;
        }
		*/

    };

} //namespace COLLADAFW


#endif //__COLLADAFRAMEWORK_COLOR_OR_TEXTURE_H__
