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


#include "ColladaMaxStableHeaders.h"

#include "COLLADAMaxColladaExporter.h"
#include "COLLADAMaxDocumentExporter.h"

namespace COLLADAMax
{

    const Class_ID COLLADAExporter::COLLADAEXPORTER_CLASS_ID ( 0x7d656d57, 0x6f963848 );

    const String COLLADAExporter::EXTENSIONNAME = "dae";
    const String COLLADAExporter::LONGDESCRIPTION = "New COLLADA Document";
    const String COLLADAExporter::SHORTDESCRIPTION = "NEWCOLLADA";
    const String COLLADAExporter::AUTHORNAME = "netAllied";
    const String COLLADAExporter::COPYRIGHTMESSAGE = "Copyright 2008 netAllied. Copyright 2006 Feeling Software. Based on Autodesk' 3dsMax COLLADA Tools.";
    const String COLLADAExporter::OTHERMESSAGE1 = "";
    const String COLLADAExporter::OTHERMESSAGE2 = "";

    const String COLLADAExporter::PROGRESSSTART = "COLLADA export...";

    const String COLLADAExporter::FATALERROR = "Fatal Error: exception caught.";

    const unsigned int COLLADAExporter::PLUGINVERSION = 400;


    //---------------------------------------------------------------
    COLLADAExporter::COLLADAExporter()
    {}

    //---------------------------------------------------------------
    COLLADAExporter::~COLLADAExporter()
    {}

    //---------------------------------------------------------------
    int COLLADAExporter::ExtCount()
    {
        return 1;
    }

    //---------------------------------------------------------------
    const TCHAR* COLLADAExporter::Ext ( int )
    {
        return EXTENSIONNAME.c_str();
    }

    //---------------------------------------------------------------
    const TCHAR* COLLADAExporter::LongDesc()
    {
        return LONGDESCRIPTION.c_str();
    }

    //---------------------------------------------------------------
    const TCHAR* COLLADAExporter::ShortDesc()
    {
        return SHORTDESCRIPTION.c_str();
    }

    //---------------------------------------------------------------
    const TCHAR* COLLADAExporter::AuthorName()
    {
        return AUTHORNAME.c_str();
    }

    //---------------------------------------------------------------
    const TCHAR* COLLADAExporter::CopyrightMessage()
    {
        return COPYRIGHTMESSAGE.c_str();
    }

    //---------------------------------------------------------------
    const TCHAR* COLLADAExporter::OtherMessage1()
    {
        return OTHERMESSAGE1.c_str();
    }

    //---------------------------------------------------------------
    const TCHAR* COLLADAExporter::OtherMessage2()
    {
        return OTHERMESSAGE2.c_str();
    }

    //---------------------------------------------------------------
    unsigned int COLLADAExporter::Version()
    {
        return PLUGINVERSION;
    }

    //---------------------------------------------------------------
    void COLLADAExporter::ShowAbout ( HWND )
    {
        /// @todo add about dialog
    }

    //---------------------------------------------------------------
    BOOL COLLADAExporter::SupportsOptions ( int, DWORD )
    {
        // @TODO Decide which options to support.  Simply return
        // true for each option supported by each Extension
        // the exporter supports.

        return TRUE;
    }


    //---------------------------------------------------------------
    DWORD WINAPI fn ( LPVOID )
    {
        return 0;
    }

    //---------------------------------------------------------------
    int COLLADAExporter::DoExport ( const TCHAR* name, ExpInterface* UNUSED ( ei ), Interface* maxInterface, BOOL suppressPrompts, DWORD options )
    {
        bool success = true;
        maxInterface->ProgressStart ( ( char * ) PROGRESSSTART.c_str(), true, fn, 0 );

        try
        {
			DocumentExporter document ( maxInterface, name );
			if (document.ShowExportOptions(suppressPrompts) != false)
			{
				/// @todo handle errors here
				document.exportCurrentMaxScene();
			}
			else
			{
				// Set to TRUE although nothing happened in other to avoid the "generic failure" dialog.
				success = true; 
			}
        }

        catch ( ... )
        {
            // Add some check, here, for full UI-mode or batch-mode only.
            MessageBox ( 0, FATALERROR.c_str(), SHORTDESCRIPTION.c_str(), MB_OK );
        }

        maxInterface->ProgressEnd();

        return success;
    }


    ClassDesc2* getCOLLADAExporterDesc()
    {
        static ColladaExporterClassDesc description;
        return &description;
    }

}
