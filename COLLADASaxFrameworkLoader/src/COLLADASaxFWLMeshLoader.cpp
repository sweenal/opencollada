/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADASaxFrameworkLoader.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASaxFWLStableHeaders.h"
#include "COLLADASaxFWLMeshLoader.h"

#include "COLLADAFWTriangles.h"
#include "COLLADAFWTristrips.h"
#include "COLLADAFWTrifans.h"
#include "COLLADAFWPolygons.h"

#include "COLLADAFWIWriter.h"

#include <fstream>


namespace COLLADASaxFWL
{

	MeshLoader::MeshLoader( IFilePartLoader* callingFilePartLoader, const String& geometryId, const String& geometryName )
		: SourceArrayLoader (callingFilePartLoader )
		, mMesh ( new COLLADAFW::Mesh(getUniqueId('#' + geometryId, COLLADAFW::Geometry::ID()).getObjectId()) )
		, mCurrentMeshPrimitive(0)
		, mCurrentVertexInput(0)
		, mMeshPrimitiveInputs(mVerticesInputs)
		, mCurrentMeshPrimitiveInput(0)
		, mCurrentOffset(0)
		, mCurrentMaxOffset(0)
		, mCurrentVertexCount(0)
		, mCurrentLastPrimitiveVertexCount(0)
		, mCurrentPhHasEmptyP(true)
		, mCurrentExpectedVertexCount(0)
		, mCurrentFaceCount(0)
		, mPositionsOffset (0)
		, mPositionsIndexOffset(0)
		, mUsePositions ( true )
		, mNormalsOffset (0)
		, mNormalsIndexOffset(0)
		, mUseNormals ( false )
		, mColorsOffset (0)
		, mColorsIndexOffset(0)
		, mUseColors (false)
		, mUVCoordsOffset (0)
		, mUVCoordsIndexOffset(0)
		, mUseUVCoords ( false )
	{
		mMesh->setName(geometryName);
	}


    //------------------------------
    const InputUnshared* MeshLoader::getVertexInputBySemantic ( const InputSemantic::Semantic& semantic ) const 
    {
        // Search the vertex input elements for the semantic element.
        return getVertices().getInputBySemantic ( semantic );
    }

    //------------------------------
    const SourceBase* MeshLoader::getSourceByInputSemanticFromVertices ( const InputSemantic::Semantic& semantic ) const
    {
        // Check if the input element with the semantic is a vertex element.
        const InputUnshared* positionsInput = getVertexInputBySemantic ( semantic );
        if ( positionsInput == 0 ) return 0;

        // Get the source element with the uri of the input element.
        COLLADABU::URI positionsInputSource = positionsInput->getSource ();
        String sourceId = positionsInputSource.getFragment ();

        return getSourceById ( sourceId );
    }

    //------------------------------
    const SourceBase* MeshLoader::getPositionsSource () const
    {
        return getSourceByInputSemanticFromVertices ( InputSemantic::POSITION );
    }

 
    //------------------------------
    void MeshLoader::loadSourceElements ( const MeshPrimitiveInputList& polyBaseElement )
    {
        const InputSharedArray& inputArray = polyBaseElement.getInputArray ();
        size_t numInputElements = inputArray.getCount ();
        for ( size_t n=0; n<numInputElements; ++n )
        {
            // Get the input element and read the semantic.
            InputShared* input = inputArray [n];

            // Load the source element of the current input element into the framework mesh.
            loadSourceElement ( *input );
        }
    }

    //------------------------------
    bool MeshLoader::loadSourceElement ( const InputShared& input )
    {
        bool retValue = false;

        // Get the semantic of the current input element.
        InputSemantic::Semantic semantic = input.getSemantic ();
        switch ( semantic )
        {
        case InputSemantic::POSITION:
            retValue = loadPositionsSourceElement ( input );
            break;
        case InputSemantic::NORMAL:
            retValue = loadNormalsSourceElement ( input );
            break;
        case InputSemantic::COLOR:
            retValue = loadColorsSourceElement ( input );
            break;
        case InputSemantic::UV:
        case InputSemantic::TEXCOORD:
            retValue = loadUVCoordsSourceElement ( input );
            break;
        default:
            // Not implemented source
            std::cout << "Source with semantic " << semantic << "not implemented!" << std::endl;
            retValue = false;
        }

        return retValue;
    }

	//------------------------------
    bool MeshLoader::loadPositionsSourceElement ( const InputShared& input )
    {
        // Get the semantic of the current input element.
        InputSemantic::Semantic semantic = input.getSemantic ();
        if ( semantic != InputSemantic::POSITION )
        {
            std::cerr << "The current input element is not a POSITION element!" << std::endl;
            return false;
        }

        // Get the source element with the uri of the input element.
        COLLADABU::URI inputUrl = input.getSource ();
        String sourceId = inputUrl.getFragment ();
        SourceBase* sourceBase = getSourceById ( sourceId );

        // Check if the source element is already loaded.
        if ( sourceBase->getIsLoaded () ) 
			return false;

        // Get the source input array
        const SourceBase::DataType& dataType = sourceBase->getDataType ();
        switch ( dataType )
        {
        case SourceBase::DATA_TYPE_FLOAT:
            {
                // Get the values array from the source
                FloatSource* source = ( FloatSource* ) sourceBase;
                FloatArrayElement& arrayElement = source->getArrayElement ();
                COLLADAFW::ArrayPrimitiveType<float>& valuesArray = arrayElement.getValues ();

                // Check if there are already some values in the positions list.
                // If so, we have to store the last index to increment the following indexes.
                COLLADAFW::MeshPositions& positions = mMesh->getPositions ();
                const size_t initialIndex = positions.getPositionsCount ();
                sourceBase->setInitialIndex ( initialIndex );

                // Push the new positions into the list of positions.
                positions.setType ( COLLADAFW::MeshFloatDoubleInputs::DATA_TYPE_FLOAT );
                if ( initialIndex != 0 ) 
					positions.appendValues ( valuesArray );
                else 
					positions.setData ( valuesArray.getData (), valuesArray.getCount () );

                // Set the source base as loaded element.
                sourceBase->setIsLoaded ( true );

                break;
            }
        case SourceBase::DATA_TYPE_DOUBLE:
            {
                // Get the values array from the source
                DoubleSource* source = ( DoubleSource* ) sourceBase;
                DoubleArrayElement& arrayElement = source->getArrayElement ();
                COLLADAFW::ArrayPrimitiveType<double>& valuesArray = arrayElement.getValues ();

                // Check if there are already some values in the positions list.
                // If so, we have to store the last index to increment the following indexes.
                COLLADAFW::MeshPositions& positions = mMesh->getPositions ();
                const size_t initialIndex = positions.getPositionsCount ();
                sourceBase->setInitialIndex ( initialIndex );

                // Push the new positions into the list of positions.
                positions.setType ( COLLADAFW::MeshFloatDoubleInputs::DATA_TYPE_DOUBLE );
                if ( initialIndex != 0 ) positions.appendValues ( valuesArray );
                else positions.setData ( valuesArray.getData (), valuesArray.getCount () );
                
                // Set the source base as loaded element.
                sourceBase->setIsLoaded ( true );

                break;
            }
        default:
            std::cerr << "Position source has an other datatype as float or double! " << dataType << std::endl;
            return false;
        }

        return true;
    }

	//------------------------------
    bool MeshLoader::loadNormalsSourceElement ( const InputShared& input )
    {
        // Get the semantic of the current input element.
        InputSemantic::Semantic semantic = input.getSemantic ();
        if ( semantic != InputSemantic::NORMAL )
        {
            std::cerr << "The current input element is not a NORMAL element!" << std::endl;
            return false;
        }

        // Get the source element with the uri of the input element.
        COLLADABU::URI inputUrl = input.getSource ();
        String sourceId = inputUrl.getFragment ();
        SourceBase* sourceBase = getSourceById ( sourceId );

        // Check if the source element is already loaded.
        if ( sourceBase->getIsLoaded () ) return false;

        // Get the source input array
        const SourceBase::DataType& dataType = sourceBase->getDataType ();
        switch ( dataType )
        {
        case SourceBase::DATA_TYPE_FLOAT:
            {
                // Get the values array from the source
                FloatSource* source = ( FloatSource* ) sourceBase;
                FloatArrayElement& arrayElement = source->getArrayElement ();
                COLLADAFW::ArrayPrimitiveType<float>& valuesArray = arrayElement.getValues ();

                // Check if there are already some values in the positions list.
                // If so, we have to store the last index to increment the following indexes.
                COLLADAFW::MeshNormals& normals = mMesh->getNormals ();
                const size_t initialIndex = normals.getNormalsCount ();
                sourceBase->setInitialIndex ( initialIndex );

                // Push the new positions into the list of positions.
                normals.setType ( COLLADAFW::MeshFloatDoubleInputs::DATA_TYPE_FLOAT );
                if ( initialIndex != 0 ) normals.appendValues ( valuesArray );
                else normals.setData ( valuesArray.getData (), valuesArray.getCount () );

                // Set the source base as loaded element.
                sourceBase->setIsLoaded ( true );

                break;
            }
        case SourceBase::DATA_TYPE_DOUBLE:
            {
                // Get the values array from the source
                DoubleSource* source = ( DoubleSource* ) sourceBase;
                DoubleArrayElement& arrayElement = source->getArrayElement ();
                COLLADAFW::ArrayPrimitiveType<double>& valuesArray = arrayElement.getValues ();

                // Check if there are already some values in the positions list.
                // If so, we have to store the last index to increment the following indexes.
                COLLADAFW::MeshNormals& normals = mMesh->getNormals ();
                const size_t initialIndex = normals.getNormalsCount ();
                sourceBase->setInitialIndex ( initialIndex );

                // Push the new positions into the list of positions.
                normals.setType ( COLLADAFW::MeshFloatDoubleInputs::DATA_TYPE_DOUBLE );
                if ( initialIndex != 0 ) normals.appendValues ( valuesArray );
                else normals.setData ( valuesArray.getData (), valuesArray.getCount () );

                // Set the source base as loaded element.
                sourceBase->setIsLoaded ( true );

                break;
            }
        default:
            std::cerr << "Normals source has an other datatype as float or double! " << dataType << std::endl;
            return false;
        }

        return true;
    }
    //------------------------------
    bool MeshLoader::loadColorsSourceElement ( const InputShared& input )
    {
        // Get the semantic of the current input element.
        InputSemantic::Semantic semantic = input.getSemantic ();
        if ( semantic != InputSemantic::COLOR )
        {
            std::cerr << "The current input element is not a COLOR element!" << std::endl;
            return false;
        }

        // Get the source element with the uri of the input element.
        COLLADABU::URI inputUrl = input.getSource ();
        String sourceId = inputUrl.getFragment ();
        SourceBase* sourceBase = getSourceById ( sourceId );

        // Check if the source element is already loaded.
        if ( sourceBase->getIsLoaded () ) return false;

        // Get the source input array
        const SourceBase::DataType& dataType = sourceBase->getDataType ();
        switch ( dataType )
        {
        case SourceBase::DATA_TYPE_FLOAT:
            {
                // Get the values array from the source
                FloatSource* source = ( FloatSource* ) sourceBase;
                FloatArrayElement& arrayElement = source->getArrayElement ();
                COLLADAFW::ArrayPrimitiveType<float>& valuesArray = arrayElement.getValues ();

                // Check if there are already some values in the positions list.
                // If so, we have to store the last index to increment the following indexes.
                COLLADAFW::MeshColors& colors = mMesh->getColors ();
                const size_t initialIndex = colors.getColorsCount ();
                sourceBase->setInitialIndex ( initialIndex );

                // Push the new positions into the list of positions.
                colors.setType ( COLLADAFW::MeshFloatDoubleInputs::DATA_TYPE_FLOAT );
                if ( initialIndex != 0 ) colors.appendValues ( valuesArray );
                else colors.setData ( valuesArray.getData (), valuesArray.getCount () );
                colors.setStride ( source->getStride () );

                // Set the source base as loaded element.
                sourceBase->setIsLoaded ( true );

                break;
            }
        case SourceBase::DATA_TYPE_DOUBLE:
            {
                // Get the values array from the source
                DoubleSource* source = ( DoubleSource* ) sourceBase;
                DoubleArrayElement& arrayElement = source->getArrayElement ();
                COLLADAFW::ArrayPrimitiveType<double>& valuesArray = arrayElement.getValues ();

                // Check if there are already some values in the positions list.
                // If so, we have to store the last index to increment the following indexes.
                COLLADAFW::MeshColors& colors = mMesh->getColors ();
                const size_t initialIndex = colors.getColorsCount ();
                sourceBase->setInitialIndex ( initialIndex );

                // Push the new positions into the list of positions.
                colors.setType ( COLLADAFW::MeshFloatDoubleInputs::DATA_TYPE_DOUBLE );
                if ( initialIndex != 0 ) colors.appendValues ( valuesArray );
                else colors.setData ( valuesArray.getData (), valuesArray.getCount () );
                colors.setStride ( source->getStride () );

                // Set the source base as loaded element.
                sourceBase->setIsLoaded ( true );

                break;
            }
        default:
            std::cerr << "Color source has an other datatype as float or double! " << dataType << std::endl;
            return false;
        }

        return true;
    }

    //------------------------------
    bool MeshLoader::loadUVCoordsSourceElement ( const InputShared& input )
    {
        // Get the semantic of the current input element.
        InputSemantic::Semantic semantic = input.getSemantic ();
        if ( semantic != InputSemantic::UV && semantic != InputSemantic::TEXCOORD )
        {
            std::cerr << "The current input element is not a UV / TEXCOORD element!" << std::endl;
            return false;
        }

        // Get the source element with the uri of the input element.
        COLLADABU::URI inputUrl = input.getSource ();
        String sourceId = inputUrl.getFragment ();
        SourceBase* sourceBase = getSourceById ( sourceId );

        // Check if the source element is already loaded.
        if ( sourceBase->getIsLoaded () ) return false;

        // Get the source input array
        const SourceBase::DataType& dataType = sourceBase->getDataType ();
        switch ( dataType )
        {
        case SourceBase::DATA_TYPE_FLOAT:
            {
                // Get the values array from the source
                FloatSource* source = ( FloatSource* ) sourceBase;
                FloatArrayElement& arrayElement = source->getArrayElement ();
                COLLADAFW::ArrayPrimitiveType<float>& valuesArray = arrayElement.getValues ();

                // Check if there are already some values in the positions list.
                // If so, we have to store the last index to increment the following indexes.
                COLLADAFW::MeshUVCoords& uvCoords = mMesh->getUVCoords ();
                const size_t initialIndex = uvCoords.getUVCoordsCount ();
                sourceBase->setInitialIndex ( initialIndex );

                // Push the new positions into the list of positions.
                uvCoords.setType ( COLLADAFW::MeshFloatDoubleInputs::DATA_TYPE_FLOAT );
                if ( initialIndex != 0 ) uvCoords.appendValues ( valuesArray );
                else uvCoords.setData ( valuesArray.getData (), valuesArray.getCount () );
                uvCoords.setStride ( source->getStride () );

                // Set the source base as loaded element.
                sourceBase->setIsLoaded ( true );

                break;  
            }
        case SourceBase::DATA_TYPE_DOUBLE:
            {
                // Get the values array from the source
                DoubleSource* source = ( DoubleSource* ) sourceBase;
                DoubleArrayElement& arrayElement = source->getArrayElement ();
                COLLADAFW::ArrayPrimitiveType<double>& valuesArray = arrayElement.getValues ();

                // Check if there are already some values in the positions list.
                // If so, we have to store the last index to increment the following indexes.
                COLLADAFW::MeshUVCoords& uvCoords = mMesh->getUVCoords ();
                const size_t initialIndex = uvCoords.getUVCoordsCount ();
                sourceBase->setInitialIndex ( initialIndex );

                // Push the new positions into the list of positions.
                uvCoords.setType ( COLLADAFW::MeshFloatDoubleInputs::DATA_TYPE_DOUBLE );
                if ( initialIndex != 0 ) uvCoords.appendValues ( valuesArray );
                else uvCoords.setData ( valuesArray.getData (), valuesArray.getCount () );
                uvCoords.setStride ( source->getStride () );

                // Set the source base as loaded element.
                sourceBase->setIsLoaded ( true );

                break;
            }
        default:
            std::cerr << "UV coordinates source has an other datatype as float or double! " << dataType << std::endl;
            return false;
        }

        return true;
    }


	bool MeshLoader::writePrimitiveIndices ( const unsigned long long* data, size_t length )
	{
		// Write the index values in the index lists.
		for ( size_t i=0; i<length; ++i )
		{
			// Get the current index value.
			unsigned int index = (unsigned int)data [i];

			// Write the indices
			if ( mUsePositions && mCurrentOffset == mPositionsOffset )
			{
				COLLADAFW::UIntValuesArray& positionIndices = mCurrentMeshPrimitive->getPositionIndices ();
				positionIndices.append ( index + mPositionsIndexOffset );
			}
			if ( mUseNormals && mCurrentOffset == mNormalsOffset )
			{
				COLLADAFW::UIntValuesArray& normalIndices = mCurrentMeshPrimitive->getNormalIndices ();
				normalIndices.append ( index + mNormalsIndexOffset );
			}
			if ( mUseColors && mCurrentOffset == mColorsOffset )
			{
				COLLADAFW::UIntValuesArray& colorIndices = mCurrentMeshPrimitive->getColorIndices ();
				colorIndices.append ( index + mColorsIndexOffset );
			}
			if ( mUseUVCoords && mCurrentOffset == mUVCoordsOffset )
			{
				COLLADAFW::UIntValuesArray& uvCoordIndices = mCurrentMeshPrimitive->getUVCoordIndices ();
				uvCoordIndices.append ( index + mUVCoordsIndexOffset );
			}

			// Reset the offset if we went through all offset values
			if ( mCurrentOffset == mCurrentMaxOffset )
			{
				// Reset the current offset value
				mCurrentOffset = 0;
				++mCurrentVertexCount;
			}
			else
			{
				// Increment the current offset value
				++mCurrentOffset;
			}
		}
		return true;
	}


#if 0
	//------------------------------
    bool MeshLoader::initializeIndexLists ( 
        COLLADAFW::MeshPrimitive* primitiveElement, 
        const InputList* polyBaseElement )
    {
        // Get the index lists.
        COLLADAFW::UIntValuesArray& positionIndices = primitiveElement->getPositionIndices ();
        COLLADAFW::UIntValuesArray& normalIndices = primitiveElement->getNormalIndices ();
        COLLADAFW::UIntValuesArray& colorIndices = primitiveElement->getColorIndices ();
        COLLADAFW::UIntValuesArray& uvCoordIndices = primitiveElement->getUVCoordIndices ();

        // We need the maximum offset value of the input elements to calculate the 
        // number of indices for each index list.
        const size_t maxOffset = polyBaseElement->getInputArrayMaxOffset ();

        // Get the number of all indices in all p elements in the current primitive element.
//        size_t numPIndices = polyBaseElement->getIndexCount ();
  //      if ( numPIndices == 0 ) numPIndices = getNumOfPrimitiveIndices ( polyBaseElement );
		assert(false);

        // Get the number of index elements in the index list for each input element.
        size_t numElements = numPIndices / maxOffset;

        // The offset values of the input elements.
        const InputShared* input = polyBaseElement->getPositionInput ();
        if ( input == 0 ) 
        {
            throw new ColladaSaxFrameworkLoaderException ( "No positions input element!" );
            return false;
        }
        // Get the offset value, the initial index values and alloc the memory.
        mPositionsOffset = input->getOffset ();
        COLLADABU::URI inputUrl = input->getSource ();
        String sourceId = inputUrl.getFragment ();
        const SourceBase* sourceBase = getSourceById ( sourceId );
        if ( sourceBase == 0 ) 
        {   
            // TODO error handling!
            return false;
        }
        positionIndices.reallocMemory ( numElements );

        // Check for using normals
        input = polyBaseElement->getNormalInput ();
        if ( input != 0 ) 
        {
            // Get the offset value, the initial index values and alloc the memory.
            mNormalsOffset = input->getOffset ();
            sourceBase = getSourceById ( input->getSource ().getFragment () );
            normalIndices.reallocMemory ( numElements );
            mUseNormals = true;
        }

        // Check for using colors
        input = polyBaseElement->getColorInput ();
        if ( input != 0 ) 
        {
            // Get the offset value and alloc the memory.
            mColorsOffset = input->getOffset ();
            colorIndices.reallocMemory ( numElements );
            mUseColors = true;
        }

        // Check for using uv coordinates 
        input = polyBaseElement->getUVCoordInput ();
        if ( input != 0 ) 
        {
            // Get the offset value and alloc the memory.
            mUVCoordsOffset = input->getOffset ();
            uvCoordIndices.reallocMemory ( numElements );
            mUseUVCoords = true;
        }

        return true;
    }
#endif

	//------------------------------
	bool MeshLoader::initializeOffsets()
	{
		// We need the maximum offset value of the input elements to calculate the 
		// number of indices for each index list.
		mCurrentMaxOffset = (size_t)mMeshPrimitiveInputs.getInputArrayMaxOffset ();


		// The offset values of the input elements.
		const InputShared* positionInput = mMeshPrimitiveInputs.getPositionInput ();
		if ( positionInput == 0 ) 
		{
			throw new ColladaSaxFrameworkLoaderException ( "No positions input element!" );
			return false;
		}
		// Get the offset value, the initial index values and alloc the memory.
		mPositionsOffset = positionInput->getOffset ();
		COLLADABU::URI inputUrl = positionInput->getSource ();
		String sourceId = inputUrl.getFragment ();
		const SourceBase* sourceBase = getSourceById ( sourceId );
		if ( sourceBase == 0 ) 
		{   
			// TODO error handling!
			return false;
		}
		mPositionsIndexOffset = (unsigned int)sourceBase->getInitialIndex();

		// Check for using normals
		const InputShared* normalInput = mMeshPrimitiveInputs.getNormalInput ();
		if ( normalInput != 0 ) 
		{
			// Get the offset value, the initial index values and alloc the memory.
			mNormalsOffset = normalInput->getOffset ();
			sourceBase = getSourceById ( normalInput->getSource ().getFragment () );
			unsigned long long stride = sourceBase->getStride();
			// only stride 3 makes sense for normals
			if ( stride == 3 )
			{
				mNormalsIndexOffset = (unsigned int)(sourceBase->getInitialIndex() / stride);
				mUseNormals = true;
			}
			else
			{
				mNormalsIndexOffset = 0;
				mUseNormals = false;
			}
		}
		else
		{
			mNormalsIndexOffset = 0;
			mUseNormals = false;
		}

		// Check for using colors
		const InputShared* colorInput = mMeshPrimitiveInputs.getColorInput ();
		if ( colorInput != 0 ) 
		{
			// Get the offset value and alloc the memory.
			mColorsOffset = colorInput->getOffset ();
			sourceBase = getSourceById ( colorInput->getSource ().getFragment () );
			unsigned long long stride = sourceBase->getStride();
			// only stride 3 or 4 makes sense for colors
			if ( (stride == 3) || (stride == 4) )
			{
				mColorsIndexOffset = (unsigned int)(sourceBase->getInitialIndex()/stride );
				mUseColors = true;
			}
			else
			{
				mColorsIndexOffset = 0;
				mUseColors = false;
			}

		}
		else
		{
			mColorsIndexOffset = 0;
			mUseColors = false;
		}

		// Check for using uv coordinates 
		const InputShared* uVCoordInput = mMeshPrimitiveInputs.getUVCoordInput ();
		if ( uVCoordInput != 0 ) 
		{
			// Get the offset value and alloc the memory.
			mUVCoordsOffset = uVCoordInput->getOffset ();
			sourceBase = getSourceById ( uVCoordInput->getSource ().getFragment () );
			unsigned long long stride = sourceBase->getStride();
			// only stride 1, 2, 3 or 4 makes sense for uv coords
			if ( (stride >= 1) || (stride <= 4) )
			{
				mUVCoordsIndexOffset = (unsigned int)(sourceBase->getInitialIndex()/stride);
				mUseUVCoords = true;
			}
			else
			{
				mUVCoordsIndexOffset = 0;
				mUseUVCoords = false;
			}
		}
		else
		{
			mUVCoordsIndexOffset = 0;
			mUseUVCoords = false;
		}

		return true;
	}

#if 0
    //------------------------------
    void MeshLoader::loadFaceVertexCountArray ( 
        COLLADAFW::MeshPrimitive* primitiveElement, 
        const PolyBase* polyBaseElement )
    {
        // TODO Not all types implemented!
        COLLADAFW::MeshPrimitive::PrimitiveType primitiveType = polyBaseElement->getPrimitiveType ();

        switch ( primitiveType )
        {
        case COLLADAFW::MeshPrimitive::POLYGONS:
            {
                // Calculate to get the polygonal face vertex counts 
                // and push them in the face vertex count list.

                // Allocate the necessary memory
                COLLADAFW::UIntValuesArray& faceVertexCountArray = primitiveElement->getFaceVertexCountArray ();
                faceVertexCountArray.allocMemory ( polyBaseElement->getFaceCount () );

                // Write the number of vertices for every face in the list of face vertex counts.
                Polygons* polygons = ( Polygons* ) polyBaseElement;

                // The current index in the face vertex count array.
                size_t index = 0;

                // TODO What's about the order of the elements? 
                const PArray& pArray = polyBaseElement->getPArray ();
                size_t numPElements = pArray.getCount ();
                for ( size_t j=0; j<numPElements; ++j )
                {
                    // Count the number of p elements.
                    PElement* pElement = pArray [j];
                    faceVertexCountArray [ index++ ] = pElement->getCount();
                }
                // Every ph element has exact one p element.
                Polygons* polygonsElement = ( Polygons* ) polyBaseElement;
                const PHArray& phArray = polygonsElement->getPHArray ();
                size_t numPHElements = phArray.getCount ();
                for ( size_t j=0; j<numPHElements; ++j )
                {
                    // Count the number of p elements.
                    const PHElement* phElement = phArray [j];
                    const PElement& pElement = phElement->getPElement ();
                    faceVertexCountArray [ index++ ] = pElement.getCount();
                }

                break;
            }
        case COLLADAFW::MeshPrimitive::POLYLIST:
            {
                // A POLYLIST element should already has set the face vertex count array. 
                Polylist* polylist = ( Polylist* ) polyBaseElement;
                COLLADAFW::UIntValuesArray& vCountArray = polylist->getVCountArray ();

                COLLADAFW::UIntValuesArray& faceVertexCountArray = primitiveElement->getFaceVertexCountArray ();
                faceVertexCountArray.setData ( vCountArray.getData (), vCountArray.getCount (), vCountArray.getCapacity () );
                break;
            }
        case COLLADAFW::MeshPrimitive::TRIANGLES:
            // TODO Always three, we don't need to store!?
            break;
        default:
            std::cerr << "Type not implemented! " << std::endl;
            return;
        }
    }
#endif 

#if 0
    //------------------------------
    void MeshLoader::loadIndexLists ( 
        COLLADAFW::MeshPrimitive* primitiveElement, 
        const PolyBase* polyBaseElement )
    {
        // TODO Not all types implemented!
        COLLADAFW::MeshPrimitive::PrimitiveType primitiveType = polyBaseElement->getPrimitiveType ();

        switch ( primitiveType )
        {
        case COLLADAFW::MeshPrimitive::POLYGONS:
        case COLLADAFW::MeshPrimitive::POLYLIST:
        case COLLADAFW::MeshPrimitive::TRIANGLES:
            {
                // Initialize the size of the index lists, check for used source elements and get 
                // the offset values of the index lists.
                if ( initializeIndexLists ( primitiveElement, polyBaseElement) == false ) return;

                // TODO Iterate over all existing p elements and get the index values.
                // (not about triangles and polylists, but about the polygons)

                // Get the maximum offset value in the input list.
                const size_t maxOffset = polyBaseElement->getInputArrayMaxOffset ();

                // Write the indexes of p elements of the p array.
                const PArray& pArray = polyBaseElement->getPArray ();
                size_t numPElements = pArray.getCount ();
                for ( size_t j=0; j<numPElements; ++j )
                {
                    const PElement* pElement = pArray [j];
                    writePElementIndices( pElement, primitiveElement, maxOffset );
                }

                if ( primitiveType == COLLADAFW::MeshPrimitive::POLYGONS )
                {
                    // Write the indexes of the p elements of each ph element in the the ph array.
                    Polygons* polygonsElement = ( Polygons* ) polyBaseElement;
                    const PHArray& phArray = polygonsElement->getPHArray ();
                    size_t numPHElements = phArray.getCount ();
                    for ( size_t j=0; j<numPHElements; ++j )
                    {
                        // Count the number of p elements.
                        const PHElement* phElement = phArray [j];
                        const PElement& pElement = phElement->getPElement ();
                        writePElementIndices( &pElement, primitiveElement, maxOffset );
                    }
                }

                // Output
                std::ofstream outFile;
                outFile.open ( "C:\\Temp\\DebugLog.txt", std::ios_base::out );

                // Get the index lists.
                COLLADAFW::UIntValuesArray& positionIndices = primitiveElement->getPositionIndices ();
                COLLADAFW::UIntValuesArray& normalIndices = primitiveElement->getNormalIndices ();
                COLLADAFW::UIntValuesArray& colorIndices = primitiveElement->getColorIndices ();
                COLLADAFW::UIntValuesArray& uvCoordIndices = primitiveElement->getUVCoordIndices ();

                outFile << "position indices = ";
                for ( size_t p=0; p<positionIndices.getCount (); ++p )
                    outFile << positionIndices[p] << ", ";
                outFile << std::endl;

                outFile << "normal indices = ";
                for ( size_t p=0; p<normalIndices.getCount (); ++p )
                    outFile << normalIndices[p] << ", ";
                outFile << std::endl;

                outFile << "color indices = ";
                for ( size_t p=0; p<colorIndices.getCount (); ++p )
                    outFile << colorIndices[p] << ", ";
                outFile << std::endl;

                outFile << "uv coord indices = ";
                for ( size_t p=0; p<uvCoordIndices.getCount (); ++p )
                    outFile << uvCoordIndices[p] << ", ";
                outFile << std::endl;

                break;
            }
        default:
            // No more implementations.
            std::cerr << "Primitive type " << primitiveType << " not implemented!";
            return;
        }
    }
#endif


	//------------------------------
	void MeshLoader::initCurrentValues()
	{
		mCurrentVertexCount = 0;
		mCurrentLastPrimitiveVertexCount = 0;
		mCurrentExpectedVertexCount = 0;
		mCurrentMeshPrimitive = 0;
		mCurrentFaceCount = 0;
		mCurrentPhHasEmptyP = true;
	}


	//------------------------------
	bool MeshLoader::end__mesh() 
	{
		bool success = writer()->writeGeometry(mMesh);
		delete mMesh;
		finish();
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__mesh__source( const mesh__source__AttributeData& attributes )
	{
		return beginSource(attributes);
	}

	//------------------------------
	bool MeshLoader::end__mesh__source(  )
	{
		return endSource();
	}

	//------------------------------
	bool MeshLoader::begin__mesh__vertices( const mesh__vertices__AttributeData& attributeData )
	{
		if ( attributeData.id )
			mVerticesInputs.setId( (const char*)attributeData.id );
		if ( attributeData.name )
			mVerticesInputs.setName( (const char*)attributeData.name );
		return true;
	}

	//------------------------------
	bool MeshLoader::end__mesh__vertices()
	{
		//we don't need to do anything here
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__vertices__input( const vertices__input__AttributeData& attributeData )
	{
		mCurrentVertexInput = new InputUnshared((const char*)attributeData.semantic, (const char*)attributeData.source);
		return true;
	}

	//------------------------------
	bool MeshLoader::end__vertices__input()
	{
		mVerticesInputs.getInputArray().append(mCurrentVertexInput);
		mCurrentVertexInput = 0;
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__mesh__triangles( const mesh__triangles__AttributeData& attributeData )
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::end__mesh__triangles()
	{
		mMeshPrimitiveInputs.clearInputs();
		return true;
	}


	//------------------------------
	bool MeshLoader::begin__triangles__input( const triangles__input__AttributeData& attributeData )
	{
		return beginInput(attributeData);
	}

	//------------------------------
	bool MeshLoader::end__triangles__input()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::beginInput( const triangles__input__AttributeData& attributeData )
	{
		mMeshPrimitiveInputs.appendInputElement(new InputShared((const char*)attributeData.semantic, 
			(const char*)attributeData.source, 
			attributeData.offset,
			attributeData.set));
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__triangles__p()
	{
		loadSourceElements(mMeshPrimitiveInputs);
		initializeOffsets();
		mCurrentMeshPrimitive = new COLLADAFW::Triangles();
		return true;
	}

	//------------------------------
	bool MeshLoader::end__triangles__p()
	{
		size_t trianglesCount = mCurrentVertexCount/3;
		// check if the triangles really contains triangles. If not, we will discard it
		if ( trianglesCount > 0 )
		{
			mCurrentMeshPrimitive->setFaceCount(trianglesCount);
			mMesh->appendPrimitive(mCurrentMeshPrimitive);
		}
		else
		{
			delete mCurrentMeshPrimitive;
		}
		initCurrentValues();
		return true;
	}

	//------------------------------
	bool MeshLoader::data__triangles__p( const unsigned long long* data, size_t length )
	{
		return writePrimitiveIndices(data, length);
	}

	//------------------------------
	bool MeshLoader::begin__mesh__polylist( const mesh__polylist__AttributeData& attributeData )
	{
		COLLADAFW::Polygons* polygons = new COLLADAFW::Polygons();
		polygons->getGroupedVerticesVertexCountArray().allocMemory((size_t)attributeData.count);
		mCurrentMeshPrimitive = polygons;
		return true;
	}

	//------------------------------
	bool MeshLoader::end__mesh__polylist()
	{
		// check if there are enough vertices as expected by the vcount and that there exist at least
		// one polygon. If not, we will discard it
		if ( mCurrentVertexCount >= mCurrentExpectedVertexCount && mCurrentVertexCount > 0 )
		{
			COLLADAFW::Polygons* polygons = (COLLADAFW::Polygons*) mCurrentMeshPrimitive;
			COLLADAFW::Polygons::VertexCountArray& vertexCountArray = polygons->getGroupedVerticesVertexCountArray();

			mCurrentMeshPrimitive->setFaceCount(vertexCountArray.getCount());
			mMesh->appendPrimitive(mCurrentMeshPrimitive);
		}
		else
		{
			delete mCurrentMeshPrimitive;
		}
		initCurrentValues();
		mMeshPrimitiveInputs.clearInputs();
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__polylist__input( const polylist__input__AttributeData& attributeData )
	{
		return beginInput( *((triangles__input__AttributeData*)&attributeData) );
	}

	//------------------------------
	bool MeshLoader::end__polylist__input()
	{
		loadSourceElements(mMeshPrimitiveInputs);
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__polylist__vcount()
	{
		initializeOffsets();
		return true;
	}

	//------------------------------
	bool MeshLoader::end__polylist__vcount()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::data__polylist__vcount( const unsigned long long* data, size_t length )
	{
		COLLADAFW::Polygons* polygons = (COLLADAFW::Polygons*) mCurrentMeshPrimitive;
		COLLADAFW::Polygons::VertexCountArray& vertexCountArray = polygons->getGroupedVerticesVertexCountArray();
		size_t count = vertexCountArray.getCount();
		vertexCountArray.reallocMemory( count + length);
		for ( size_t i = 0; i < length; ++i)
		{
			unsigned long long vcount = data[i];
			vertexCountArray.append((unsigned int)vcount);
			mCurrentExpectedVertexCount += (size_t)vcount;
		}
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__polylist__p()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::end__polylist__p()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::data__polylist__p( const unsigned long long* data, size_t length )
	{
		return writePrimitiveIndices(data, length);
	}

	//------------------------------
	bool MeshLoader::begin__mesh__polygons( const mesh__polygons__AttributeData& attributeData )
	{
		COLLADAFW::Polygons* polygons = new COLLADAFW::Polygons();
		// The actual size might be bigger, but its a lower bound
		polygons->getGroupedVerticesVertexCountArray().allocMemory((size_t)attributeData.count);
		mCurrentMeshPrimitive = polygons;
		return true;
	}

	//------------------------------
	bool MeshLoader::end__mesh__polygons()
	{
		// check if there is at least one polygon. If not, we will discard it.
		if ( mCurrentFaceCount > 0 )
		{
			mCurrentMeshPrimitive->setFaceCount(mCurrentFaceCount);
			mMesh->appendPrimitive(mCurrentMeshPrimitive);
		}
		else
		{
			delete mCurrentMeshPrimitive;
		}
		initCurrentValues();
		mMeshPrimitiveInputs.clearInputs();
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__polygons__input( const polygons__input__AttributeData& attributeData )
	{
		return beginInput( *((triangles__input__AttributeData*)&attributeData) );
	}

	//------------------------------
	bool MeshLoader::end__polygons__input()
	{
		loadSourceElements(mMeshPrimitiveInputs);
		initializeOffsets();
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__polygons__p()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::end__polygons__p()
	{
		int currentFaceVertexCount = (int)mCurrentVertexCount - (int)mCurrentLastPrimitiveVertexCount;
		if ( currentFaceVertexCount > 0 )
		{
			COLLADAFW::Polygons* polygons = (COLLADAFW::Polygons*) mCurrentMeshPrimitive;
			COLLADAFW::Polygons::VertexCountArray& vertexCountArray = polygons->getGroupedVerticesVertexCountArray();
			vertexCountArray.append(currentFaceVertexCount);
			mCurrentLastPrimitiveVertexCount = mCurrentVertexCount;
			mCurrentFaceCount++;
		}

		return true;
	}

	//------------------------------
	bool MeshLoader::data__polygons__p( const unsigned long long* data, size_t length )
	{
		return writePrimitiveIndices(data, length);
	}

	//------------------------------
	bool MeshLoader::begin__ph()
	{
		mCurrentPhHasEmptyP = true;
		return true;
	}

	//------------------------------
	bool MeshLoader::end__ph()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__ph__p()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::end__ph__p()
	{
		int currentPolygonVertexCount = (int)mCurrentVertexCount - (int)mCurrentLastPrimitiveVertexCount;
		if ( currentPolygonVertexCount > 0 )
		{
			COLLADAFW::Polygons* polygons = (COLLADAFW::Polygons*) mCurrentMeshPrimitive;
			COLLADAFW::Polygons::VertexCountArray& vertexCountArray = polygons->getGroupedVerticesVertexCountArray();
			vertexCountArray.append(currentPolygonVertexCount);
			mCurrentLastPrimitiveVertexCount = mCurrentVertexCount;
			mCurrentFaceCount++;
			mCurrentPhHasEmptyP = false;
		}
		else
		{
			mCurrentPhHasEmptyP = true;
		}
		return true;
	}

	//------------------------------
	bool MeshLoader::data__ph__p( const unsigned long long* data, size_t length )
	{
		return writePrimitiveIndices(data, length);
	}

	//------------------------------
	bool MeshLoader::begin__h()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::end__h()
	{
		int currentFaceVertexCount = (int)mCurrentVertexCount - (int)mCurrentLastPrimitiveVertexCount;
		if ( currentFaceVertexCount > 0 )
		{
			COLLADAFW::Polygons* polygons = (COLLADAFW::Polygons*) mCurrentMeshPrimitive;
			COLLADAFW::Polygons::VertexCountArray& vertexCountArray = polygons->getGroupedVerticesVertexCountArray();
			vertexCountArray.append(-currentFaceVertexCount);
			mCurrentLastPrimitiveVertexCount = mCurrentVertexCount;
		}
		return true;
	}

	//------------------------------
	bool MeshLoader::data__h( const unsigned long long* data, size_t length )
	{
		// If the p element of the parent ph is empty, we don't need to read the h element
		if ( mCurrentPhHasEmptyP )
			return true;
		return writePrimitiveIndices(data, length);
	}

	//------------------------------
	bool MeshLoader::begin__mesh__tristrips( const mesh__tristrips__AttributeData& attributeData )
	{
		COLLADAFW::Tristrips* tristrips = new COLLADAFW::Tristrips();
		// The actual size might be bigger, but its a lower bound
		tristrips->getGroupedVerticesVertexCountArray().allocMemory((size_t)attributeData.count);
		mCurrentMeshPrimitive = tristrips;
		return true;
	}

	//------------------------------
	bool MeshLoader::end__mesh__tristrips()
	{
		// check if there is at least one tristrip. If not, we will discard it.
		if ( mCurrentFaceCount > 0 )
		{
			mCurrentMeshPrimitive->setFaceCount(mCurrentFaceCount);
			mMesh->appendPrimitive(mCurrentMeshPrimitive);
		}
		else
		{
			delete mCurrentMeshPrimitive;
		}
		initCurrentValues();
		mMeshPrimitiveInputs.clearInputs();
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__tristrips__input( const tristrips__input__AttributeData& attributeData )
	{
		return beginInput( *((triangles__input__AttributeData*)&attributeData) );
	}

	//------------------------------
	bool MeshLoader::end__tristrips__input()
	{
		loadSourceElements(mMeshPrimitiveInputs);
		initializeOffsets();
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__tristrips__p()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::end__tristrips__p()
	{
		int currentTristripVertexCount = (int)mCurrentVertexCount - (int)mCurrentLastPrimitiveVertexCount;
		if ( currentTristripVertexCount > 0 )
		{
			COLLADAFW::Tristrips* tristrips = (COLLADAFW::Tristrips*) mCurrentMeshPrimitive;
			if ( currentTristripVertexCount >= 3 )
			{
				COLLADAFW::Tristrips::VertexCountArray& vertexCountArray = tristrips->getGroupedVerticesVertexCountArray();
				vertexCountArray.append(currentTristripVertexCount);
				tristrips->setTristripCount(tristrips->getTristripCount() + 1);
				mCurrentFaceCount += (currentTristripVertexCount - 2);
			}
			else
			{
				tristrips->getPositionIndices().erase(currentTristripVertexCount);
				tristrips->getNormalIndices().erase(currentTristripVertexCount);
				tristrips->getColorIndices().erase(currentTristripVertexCount);
				tristrips->getUVCoordIndices().erase(currentTristripVertexCount);
			}
			mCurrentLastPrimitiveVertexCount = mCurrentVertexCount;
		}
		return true;
	}

	//------------------------------
	bool MeshLoader::data__tristrips__p( const unsigned long long* data, size_t length )
	{
		return writePrimitiveIndices(data, length);
	}



	//------------------------------
	bool MeshLoader::begin__mesh__trifans( const mesh__trifans__AttributeData& attributeData )
	{
		COLLADAFW::Trifans* trifans = new COLLADAFW::Trifans();
		// The actual size might be bigger, but its a lower bound
		trifans->getGroupedVerticesVertexCountArray().allocMemory((size_t)attributeData.count);
		mCurrentMeshPrimitive = trifans;
		return true;
	}

	//------------------------------
	bool MeshLoader::end__mesh__trifans()
	{
		// check if there is at least one trifan. If not, we will discard it.
		if ( mCurrentFaceCount > 0 )
		{
			mCurrentMeshPrimitive->setFaceCount(mCurrentFaceCount);
			mMesh->appendPrimitive(mCurrentMeshPrimitive);
		}
		else
		{
			delete mCurrentMeshPrimitive;
		}
		initCurrentValues();
		mMeshPrimitiveInputs.clearInputs();
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__trifans__input( const trifans__input__AttributeData& attributeData )
	{
		return beginInput( *((triangles__input__AttributeData*)&attributeData) );
	}

	//------------------------------
	bool MeshLoader::end__trifans__input()
	{
		loadSourceElements(mMeshPrimitiveInputs);
		initializeOffsets();
		return true;
	}

	//------------------------------
	bool MeshLoader::begin__trifans__p()
	{
		return true;
	}

	//------------------------------
	bool MeshLoader::end__trifans__p()
	{
		int currentTrifanVertexCount = (int)mCurrentVertexCount - (int)mCurrentLastPrimitiveVertexCount;
		if ( currentTrifanVertexCount > 0 )
		{
			COLLADAFW::Trifans* trifans = (COLLADAFW::Trifans*) mCurrentMeshPrimitive;
			if ( currentTrifanVertexCount >= 3 )
			{
				COLLADAFW::Trifans::VertexCountArray& vertexCountArray = trifans->getGroupedVerticesVertexCountArray();
				vertexCountArray.append(currentTrifanVertexCount);
				trifans->setTrifanCount(trifans->getTrifanCount() + 1);
				mCurrentFaceCount += (currentTrifanVertexCount - 2);
			}
			else
			{
				trifans->getPositionIndices().erase(currentTrifanVertexCount);
				trifans->getNormalIndices().erase(currentTrifanVertexCount);
				trifans->getColorIndices().erase(currentTrifanVertexCount);
				trifans->getUVCoordIndices().erase(currentTrifanVertexCount);
			}
			mCurrentLastPrimitiveVertexCount = mCurrentVertexCount;
		}
		return true;
	}

	//------------------------------
	bool MeshLoader::data__trifans__p( const unsigned long long* data, size_t length )
	{
		return writePrimitiveIndices(data, length);
	}

} // namespace COLLADASaxFWL
