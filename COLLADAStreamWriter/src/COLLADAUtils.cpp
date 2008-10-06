/*
    Copyright (c) 2008 NetAllied Systems GmbH

	This file is part of COLLADAStreamWriter.
	
    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#include "COLLADAUtils.h"


namespace COLLADA
{

    const String Utils::FILE_PROTOCOL = "file:///";
    const String Utils::FILE_DELIMITER = "/";
    const char Utils::FILE_DELIMITER_CHAR = '/';

	const String Utils::EMPTY_STRING = String();

    // defines
#define MAX_FILENAME_LEN 512

    // The number of characters at the start of an absolute filename.  e.g. in DOS,
    // absolute filenames start with "X:\" so this value should be 3, in UNIX they start
    // with "\" so this value should be 1. A slash must set to '\\' for DOS or '/' for UNIX.

#if defined( __WIN32__ ) || defined( _WIN32 )
    #define ABSOLUTE_NAME_START 3
    #define SLASH '\\'
#elif defined( __APPLE_CC__)
    #define ABSOLUTE_NAME_START 1 // TODO Ist das so?
    #define SLASH '/' // TODO Ist das so?
#else
    #define ABSOLUTE_NAME_START 1
    #define SLASH '/'
#endif



    //---------------------------------
    String Utils::checkNCName ( const String &ncName )
    {
        String result;
        result.reserve ( ncName.length() );

        // check if first character is an alpha character
        char firstCharacter = ncName[0];

        if ( isAsciiAlphaChar ( firstCharacter )  )
            result.append ( 1, firstCharacter );
        else
            result.append ( 1, '_' );

        //replace all spaces and colons by underlines
        for ( size_t i = 1; i<ncName.length(); ++i )
        {
            char character = ncName[i];

            if ( isIDChar ( character ) )
                result.append ( 1, character );
            else
                result.append ( 1, '_' );
        }

        return result;
    }

    //---------------------------------
    String Utils::checkID ( const String &id )
    {
        return checkNCName ( id );
    }

    //---------------------------------
    String Utils::translateToXML ( const String &srcString )
    {
        String returnString = ""; 

        for ( unsigned int i=0; i<srcString.length(); ++i )
        {
            switch ( srcString[i])
            {
            case '\r':  
                returnString += "&#13";
                break;
            case '<':  
                returnString += "&lt;";
                break;
            case '>': 
                returnString += "&gt;";
                break;
            case '&':  
                returnString += "&amp;";
                break;
            case '"':  
                returnString += "&quot;";
                break;
            case '\'':  
                returnString += "&apos;";
                break;
            default :   
                returnString += srcString[i];
            }
        }

        return returnString;
    }



    //---------------------------------
    String Utils::replaceDot ( const String &text )
    {
        std::stringstream stream;

        for ( size_t i = 0; i < text.length(); ++i )
        {
            if ( text[i] == '.' )
                stream << '_';
            else
                stream << text[i];
        }

        return stream.str();
    }

    //---------------------------------
    String Utils::getAbsolutePathFromFile( const String& absoluteFilename )
    {
        String absolutePath;

        size_t found = absoluteFilename.rfind( Utils::FILE_DELIMITER );
        if (found != String::npos)
            absolutePath = absoluteFilename.substr( 0, found+1 );
        else
            absolutePath = absoluteFilename;
        
        return absolutePath;
    }

    //---------------------------------
    String Utils::getFileNameFromFile( const String& absoluteFilename )
    {
        String absolutePath;

        size_t found = absoluteFilename.rfind( Utils::FILE_DELIMITER );
        if (found != String::npos)
            absolutePath = absoluteFilename.substr( found+1 );
        else
            absolutePath = absoluteFilename;

        return absolutePath;
    }

    //---------------------------------
    String Utils::getRelativeFilename(const String currentDirectory, const String absoluteFilename)
    {
        // Given the absolute current directory and an absolute file 
        // name, returns a relative file name.
        // For example, if the current directory is C:\foo\bar and the 
        // filename C:\foo\whee\text.txt is given,
        // getRelativeFilename will return ..\whee\text.txt.

        // declarations - put here so this should work in a C compiler
        int afMarker = 0, rfMarker = 0;
        size_t cdLen = 0, afLen = 0;
        unsigned int i = 0;
        unsigned int levels = 0;
        String relativeFilename;

        cdLen = currentDirectory.length();
        afLen = absoluteFilename.length();

        // make sure the names are not too long or too short
        if ( cdLen > MAX_FILENAME_LEN || cdLen < ABSOLUTE_NAME_START+1 ||
             afLen > MAX_FILENAME_LEN || afLen < ABSOLUTE_NAME_START+1 )
        {
            return NULL;
        }

        // Handle DOS names that are on different drives:
        if ( currentDirectory[0] != absoluteFilename[0] )
        {
            // not on the same drive, so only absolute filename will do
            relativeFilename = absoluteFilename;
            return relativeFilename;
        }

        // they are on the same drive, find out how much of the current directory
        // is in the absolute filename
        i = ABSOLUTE_NAME_START;
        while ( i<afLen && i<cdLen && currentDirectory[i] == absoluteFilename[i] )
        {
            i++;
        }

        if ( i==cdLen && (absoluteFilename[i]==FILE_DELIMITER_CHAR || absoluteFilename[i-1]==FILE_DELIMITER_CHAR))
        {
            // the whole current directory name is in the file name,
            // so we just trim off the current directory name to get the
            // current file name.
            if ( absoluteFilename[i] == FILE_DELIMITER_CHAR )
            {
                // a directory name might have a trailing slash but a relative
                // file name should not have a leading one...
                i++;
            }

            String filename = &absoluteFilename[i];
            relativeFilename = filename;

            return relativeFilename;
        }


        // The file is not in a child directory of the current directory, so we
        // need to step back the appropriate number of parent directories by
        // using "..\"s.  First find out how many levels deeper we are than the
        // common directory
        afMarker = i;
        levels = 1;

        // count the number of directory levels we have to go up to get to the
        // common directory
        while ( i < cdLen )
        {
            i++;
            if ( currentDirectory[i] == FILE_DELIMITER_CHAR )
            {
                // make sure it's not a trailing slash
                i++;
                if ( currentDirectory[i] != FILE_DELIMITER_CHAR )
                {
                    levels++;
                }
            }
        }

        // move the absolute filename marker back to the start of the directory name
        // that it has stopped in.
        while ( afMarker > 0 && absoluteFilename[afMarker-1] != FILE_DELIMITER_CHAR )
        {
            afMarker--;
        }

        // check that the result will not be too long
        if (levels * 3 + afLen - afMarker > MAX_FILENAME_LEN)
        {
            return NULL;
        }
        
        // add the appropriate number of "..\"s.
        rfMarker = 0;
        for (i = 0; i < levels; i++)
        {
            if ( i == 0 )
            {
                relativeFilename += ".";
                relativeFilename += FILE_DELIMITER;
            }
            else
            {
                relativeFilename += "..";
                relativeFilename += FILE_DELIMITER;
            }
        }

        // copy the rest of the filename into the result string
        relativeFilename += &absoluteFilename[afMarker];

        return relativeFilename;
    }

    //---------------------------------
    bool Utils::copyFile( const String& src, const String& dest )
    {
        std::ifstream in;
        in.open( src.c_str(), std::ios_base::in | std::ios_base::binary );
        std::ofstream out;
        out.open( dest.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        bool success = copyFile( in, out );
        out.close();
        in.close();
        return success;
    }

    //---------------------------------
    bool Utils::copyFile( std::ifstream& src, std::ofstream& dest )
    {
        if ( src.is_open() && dest.is_open() )
        {
            dest << src.rdbuf();
            dest.flush();
            return true;
        }

        return false;
    }

    //---------------------------------
    void Utils::stringFindAndReplace ( String &source, const String searchString, const String replaceString )
    {
        size_t found = source.find ( searchString );
        if ( found != String::npos ) 
        {
            size_t searchStrLength = searchString.length();
            size_t replaceStrLength = replaceString.length();
            do
            {
                source.replace ( found, searchStrLength, replaceString );
                found = source.find (searchString, found + replaceStrLength );
            } while ( found != String::npos );
        }

    }

    //---------------------------------
    bool Utils::equals ( const String &str1, const String &str2 )
    {
        return ( strcmp ( str1.c_str(), str2.c_str() ) == 0 );
    }

    //--------------------------------
    bool Utils::equalsIgnoreCase ( const String& s1, const String& s2 ) 
    {
        String::const_iterator it1=s1.begin();
        String::const_iterator it2=s2.begin();

        // has the end of at least one of the strings been reached?
        while ( (it1!=s1.end()) && (it2!=s2.end()) ) 
        { 
            if(::toupper(*it1) != ::toupper(*it2)) //letters differ?
                // return -1 to indicate 'smaller than', 1 otherwise
                return false; 
            // proceed to the next character in each string
            ++it1;
            ++it2;
        }
        size_t size1=s1.size(), size2=s2.size();// cache lengths
        //return -1,0 or 1 according to strings' lengths
        if (size1==size2) 
            return true;
        return false;
    }

    //--------------------------------
	Utils::SystemType Utils::getSystemType()
	{
#ifdef WIN32
		return WINDOWS;
#else
		return POSIX;
#endif
	}

}