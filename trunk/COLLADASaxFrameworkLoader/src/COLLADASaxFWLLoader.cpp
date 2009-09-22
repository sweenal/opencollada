/*
Copyright (c) 2008-2009 NetAllied Systems GmbH

This file is part of COLLADASaxFrameworkLoader.

Licensed under the MIT Open Source License,
for details please see LICENSE file or the website
http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASaxFWLStableHeaders.h"
#include "COLLADASaxFWLLoader.h"
#include "COLLADASaxFWLFileLoader.h"
#include "COLLADASaxFWLPostProcessor.h"
#include "COLLADASaxFWLSaxParserErrorHandler.h"
#include "COLLADASaxFWLUtils.h"

#include "COLLADABUURI.h"

#include "COLLADAFWVisualScene.h"
#include "COLLADAFWLibraryNodes.h"
#include "COLLADAFWIWriter.h"
#include "COLLADAFWEffect.h"
#include "COLLADAFWLight.h"
#include "COLLADAFWCamera.h"
#include "COLLADAFWAnimationList.h"
#include "COLLADAFWConstants.h"

#include <sys/types.h>
#include <sys/timeb.h>
#include <fstream>

namespace COLLADASaxFWL
{

	Loader::Loader( IErrorHandler* errorHandler )
		: mNextFileId(0)
		, mCurrentFileId(0)
		, mErrorHandler(errorHandler)
		, mNextTextureMapId(0)
		, mObjectFlags( Loader::ALL_OBJECTS_MASK )
		, mParsedObjectFlags( Loader::NO_FLAG )
		, mSidTreeRoot( new SidTreeNode("", 0) )
	{
	}


	//---------------------------------
	Loader::~Loader()
	{
		delete mSidTreeRoot;

		// delete visual scenes
		deleteVectorFW(mVisualScenes);

		// delete library nodes
		deleteVectorFW(mLibraryNodes);

		// delete effects
		deleteVectorFW(mEffects);

		// delete lights
		deleteVectorFW(mLights);

		// delete cameras
		deleteVectorFW(mCameras);

		// We do not delete formulas here. They are deleted by the Formulas class

		// delete animation lists
		Loader::UniqueIdAnimationListMap::const_iterator it = mUniqueIdAnimationListMap.begin();
		for ( ; it != mUniqueIdAnimationListMap.end(); ++it )
		{
			COLLADAFW::AnimationList* animationList = it->second;
			FW_DELETE animationList;
		}
	}

    //---------------------------------
	const COLLADAFW::UniqueId& Loader::getUniqueId( const COLLADABU::URI& uri, COLLADAFW::ClassId classId )
	{
		URIUniqueIdMap::iterator it = mURIUniqueIdMap.find(uri);
		if ( it == mURIUniqueIdMap.end() )
		{
			return mURIUniqueIdMap[uri] = COLLADAFW::UniqueId(classId, mLoaderUtil.getLowestObjectIdFor(classId), getFileId(uri));
		}
		else
		{
			return it.second();
		}
	}

	//---------------------------------
	const COLLADAFW::UniqueId& Loader::getUniqueId( const COLLADABU::URI& uri)
	{
		URIUniqueIdMap::iterator it = mURIUniqueIdMap.find(uri);
		if ( it == mURIUniqueIdMap.end() )
		{
			return COLLADAFW::UniqueId::INVALID;
		}
		else
		{
			return it.second();
		}
	}

	//---------------------------------
	COLLADAFW::UniqueId Loader::getUniqueId( COLLADAFW::ClassId classId )
	{
		return COLLADAFW::UniqueId(classId, mLoaderUtil.getLowestObjectIdFor(classId), mCurrentFileId);
	}

	//---------------------------------
	COLLADAFW::FileId Loader::getFileId( const COLLADABU::URI& uri )
	{
		// check if the uri is relative
		bool isRelative = uri.getScheme().empty() && 
			              uri.getAuthority().empty() && 
						  uri.getPath().empty() && 
						  uri.getQuery().empty();
		if ( isRelative )
		{
			// its a relative uri. The file id is that of the current file
			return mCurrentFileId;
		}

		// the uri is not relative. We need to find the correct file id
		const COLLADABU::URI* usedUri = 0;

		COLLADABU::URI uriWithoutFragment;
		
		if ( uri.getFragment().empty() )
		{
			// the passed uri has no fragment, we can use it without modification
			usedUri = &uri;
		}
		else
		{
			// the passed uri has a fragment, we need to make a copy without fragment
			uriWithoutFragment.set( uri.getScheme(), uri.getAuthority(), uri.getPath(), uri.getQuery(), COLLADAFW::Constants::EMPTY_STRING);
			usedUri = &uriWithoutFragment;
		}

		URIFileIdMap::iterator it = mURIFileIdMap.find( *usedUri );

		if ( it == mURIFileIdMap.end() )
		{
			COLLADAFW::FileId fileId = mNextFileId++;
			addFileIdUriPair( fileId, *usedUri );
			return fileId;
		}
		else
		{
			return it.second();
		}
	}

	//---------------------------------
	const COLLADABU::URI& Loader::getFileUri( COLLADAFW::FileId fileId )
	{
		FileIdURIMap::const_iterator it = mFileIdURIMap.find( fileId );

		if ( it == mFileIdURIMap.end() )
		{
			return COLLADABU::URI::INVALID;
		}
		else
		{
			return it->second;
		}
	}

	//---------------------------------
	void Loader::addFileIdUriPair( COLLADAFW::FileId fileId, const COLLADABU::URI& uri )
	{
		mURIFileIdMap[uri] = fileId;
		mFileIdURIMap[fileId] = uri;
	}

	//---------------------------------
	bool Loader::loadDocument( const String& fileName, COLLADAFW::IWriter* writer )
	{
		if ( !writer )
			return false;
		mWriter = writer;

		SaxParserErrorHandler saxParserErrorHandler(mErrorHandler);

		COLLADABU::URI rootFileUri(COLLADABU::URI::nativePathToUri(fileName));
		
		// the root file has always file id 0
		addFileIdUriPair( mNextFileId++, rootFileUri );

		while ( mCurrentFileId < mNextFileId )
		{
			FileLoader fileLoader(this, 
								  getFileUri( mCurrentFileId ),
								  &saxParserErrorHandler, 
								  mObjectFlags,
								  mParsedObjectFlags);
			fileLoader.load();

			mCurrentFileId++;
		}

		PostProcessor postProcessor(this, 
				                    &saxParserErrorHandler, 
				                    mObjectFlags,
				                    mParsedObjectFlags);
		postProcessor.postProcess();

		mParsedObjectFlags |= mObjectFlags;

		return true;
	}

	//---------------------------------
	GeometryMaterialIdInfo& Loader::getMeshMaterialIdInfo( const COLLADAFW::UniqueId& uniqueId )
	{
		return mGeometryMeshMaterialIdInfoMapMap[uniqueId];
	}

	//---------------------------------
	COLLADAFW::TextureMapId Loader::getTextureMapIdBySematic( const String& semantic )
	{
		StringTextureMapIdMap::iterator it = mTextureMapSemanticTextureMapIdMap.find(semantic);
		if ( it == mTextureMapSemanticTextureMapIdMap.end() )
		{
			return mTextureMapSemanticTextureMapIdMap[semantic] = mNextTextureMapId++;
		}
		else
		{
			return it->second;
		}
	}

} // namespace COLLADA
