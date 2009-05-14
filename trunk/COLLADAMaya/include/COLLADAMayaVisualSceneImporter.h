/*
    Copyright (c) 2008-2009 NetAllied Systems GmbH

	This file is part of COLLADAMaya.

    Portions of the code are:
    Copyright (c) 2005-2007 Feeling Software Inc.
    Copyright (c) 2005-2007 Sony Computer Entertainment America
    Copyright (c) 2004-2005 Alias Systems Corp.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADA_MAYA_VISUAL_SCENE_IMPORTER_H__
#define __COLLADA_MAYA_VISUAL_SCENE_IMPORTER_H__

#include "COLLADAMayaStableHeaders.h"
#include "COLLADAMayaBaseImporter.h"
#include "COLLADAMayaNode.h"
#include "COLLADAMayaAnimationImporter.h"
#include "COLLADAMayaTransformAnimation.h"

#include "MayaDMTransform.h"
#include "MayaDMJoint.h"

#include "COLLADAFWVisualScene.h"
#include "COLLADAFWLibraryNodes.h"
#include "COLLADAFWSkew.h"

#include "COLLADABUIDList.h"

#include "Math/COLLADABUMathUtils.h"
#include "Math/COLLADABUMathMatrix4.h"
#include "Math/COLLADABUMathQuaternion.h"

#include <map>
#include <set>


namespace COLLADAMaya
{

    /** Declares the importer implementation to import the visual scene nodes. */
    class VisualSceneImporter : public BaseImporter
    {

    private:

        /** The standard name for a transform node without name. */
        static const String TRANSFORM_NODE_NAME;

    private:

        /*
        *	Helper class, to handle the transformations.
        */
        class MayaTransformation
        {
        public:
            MayaTransformation () 
                : phase (0)
                , translate1 ( 0,0,0 ) 
                , translate1Vec (0)
                , numTranslate1 (0)
                , rotation ( 0,0,0 )
                , axisPhaseRotate1 ( 0,0,0 )
                , axisPhaseRotate2 ( 0,0,0 )
                , axisPhaseRotate3 ( 0,0,0 )
                , translate2 ( 0,0,0 ) 
                , translate2Vec (0)
                , numTranslate2 (0)
                , skew ( 0,0,0 )
                , scale ( 1,1,1 ) 
                , translate3 ( 0,0,0 ) 
                , translate3Vec (0)
                , numTranslate3 (0)
            {}
            virtual ~MayaTransformation () {}

            static const size_t PHASE_TRANS1            = 1;
            static const size_t PHASE_ROTATE_ORIENT1    = 2;
            static const size_t PHASE_ROTATE_ORIENT2    = 3;
            static const size_t PHASE_ROTATE_ORIENT3    = 4;
            static const size_t PHASE_ROTATE1           = 5;
            static const size_t PHASE_ROTATE2           = 6;
            static const size_t PHASE_ROTATE3           = 7;
            static const size_t PHASE_JOINT_ORIENT1     = 8;
            static const size_t PHASE_JOINT_ORIENT2     = 9;
            static const size_t PHASE_JOINT_ORIENT3     = 10;
            static const size_t PHASE_TRANS2            = 11;
            static const size_t PHASE_SCALE             = 12;
            static const size_t PHASE_TRANS3            = 13;
                                                        
            MVector translate1; // = 0,0,0
            std::vector<MVector> translate1Vec;
            size_t numTranslate1;

            MEulerRotation rotateOrient; // = 0,0,0
            COLLADABU::Math::Vector3 axisPhaseRotateOrient1, axisPhaseRotateOrient2, axisPhaseRotateOrient3;

            MEulerRotation rotation; // = 0,0,0
            COLLADABU::Math::Vector3 axisPhaseRotate1, axisPhaseRotate2, axisPhaseRotate3;

            MEulerRotation jointOrient; // = 0,0,0
            COLLADABU::Math::Vector3 axisPhaseJointOrient1, axisPhaseJointOrient2, axisPhaseJointOrient3;

            MVector translate2; // = 0,0,0
            std::vector<MVector> translate2Vec;
            size_t numTranslate2;

            MVector skew; // = 0,0,0
            MVector scale; // = 1,1,1

            MVector translate3; // = 0,0,0
            std::vector<MVector> translate3Vec;
            size_t numTranslate3;

            // 5 phases
            size_t phase;
        };

    private:

        /**
         * The list of the unique maya transform node names.
         */
        COLLADABU::IDList mTransformNodeIdList;

        /** 
        * The map holds the unique ids of the nodes to the full node pathes (contains the name). 
        */
        UniqueIdMayaNodesMap mMayaTransformNodesMap;

        /**
         * The map holds for every unique transform node id the maya data model transform object
         * of the transform node.
         */
        std::map< COLLADAFW::UniqueId, MayaDM::Transform > mMayaDMTransformMap;

        /**
         * The map holds for every transform node a list of all existing parent transform nodes
         * (this are the nodes, which hold an instance of the current transform node).
         */
        UniqueIdUniqueIdsMap mTransformInstancesMap;

        /**
         * The map holds for every unique id of a geometry a list of transform node unique ids.
         * We need it for the creation of the geometry, to set the parent transform nodes.
         */
        UniqueIdUniqueIdsMap mGeometryTransformIdsMap;

        /**
        * The map holds for every unique id of a camera a list of transform node unique ids.
        * We need it for the creation of the camera, to set the parent transform nodes.
        */
        UniqueIdUniqueIdsMap mCameraTransformIdsMap;

        /**
        * The map holds for every unique id of a light a list of transform node unique ids.
        * We need it for the creation of the light, to set the parent transform nodes.
        */
        UniqueIdUniqueIdsMap mLightTransformIdsMap;

        /**
        * The map holds for every unique id of a controller a list of transform node unique ids.
        * We need it for the creation of the controller, to set the parent transform nodes.
        */
        UniqueIdUniqueIdsMap mControllerTransformIdsMap;

        /**
         * Set the center of interest distance value in a map to the current transform node.
         */
        std::map<COLLADAFW::UniqueId, double> mCenterOfInterestDistances;

        /**
         * The map holds for every animationListId the unique id of corresponding node.
         */
        std::map <COLLADAFW::UniqueId, TransformAnimation> mTransformAnimationMap;

    public:

        /** Constructor. */
        VisualSceneImporter ( DocumentImporter* documentImporter );

        /** Destructor. */
        virtual ~VisualSceneImporter ();

        /** 
         * Import the current visual scene with all scene nodes and transforms. 
         */
        void importVisualScene ( const COLLADAFW::VisualScene* visualScene );

        /** 
        * Import the library nodes with all nodes. 
        */
        void importLibraryNodes ( const COLLADAFW::LibraryNodes* libraryNodes );

        /**
        * Write the parenting informations about node instances into the maya ascii file.
        */
        void writeNodeInstances ();

        /** 
        * The map holds the unique ids of the nodes to the full node pathes (contains the name). 
        */
        const MayaNodesList* findMayaTransformNode ( const COLLADAFW::UniqueId& transformId ) const;

        /** 
        * The map holds the unique ids of the nodes to the full node pathes (contains the name). 
        */
        MayaNodesList* findMayaTransformNode ( const COLLADAFW::UniqueId& transformId );

        /**
         * The map holds for every transform node a list of all existing parent transform nodes
         * (this are the nodes, which hold an instance of the current transform node).
         */
        const UniqueIdVec* findTransformInstances ( const COLLADAFW::UniqueId& transformId ) const;

        /*
        * The map holdes for every geometry (identified by it's unique id ) a list of all 
        * transform nodes (identified by their names, which are unique!).
        * We need it for the creation of the geometry, to set the parent transform nodes.
        */
        const UniqueIdVec* findGeometryTransformIds ( const COLLADAFW::UniqueId& geometryId ) const;

        /*
        * The map holdes for every camera (identified by it's unique id ) a list of all 
        * transform nodes (identified by their names, which are unique!).
        * We need it for the creation of the camera, to set the parent transform nodes.
        */
        const UniqueIdVec* findCameraTransformIds ( const COLLADAFW::UniqueId& cameraId ) const;

        /*
        * The map holdes for every light (identified by it's unique id ) a list of all 
        * transform nodes (identified by their names, which are unique!).
        * We need it for the creation of the light, to set the parent transform nodes.
        */
        const UniqueIdVec* findLightTransformIds ( const COLLADAFW::UniqueId& lightId ) const;

        /*
        * The map holdes for every controller (identified by it's unique id ) a list of all 
        * transform nodes (identified by their names, which are unique!).
        * We need it for the creation of the controller, to set the parent transform nodes.
        */
        const UniqueIdVec* findControllerTransformIds ( const COLLADAFW::UniqueId& controllerId ) const;

        /**
         * Determines the number of transform node instances.
         */
        size_t getNumTransformInstances ( 
            const COLLADAFW::UniqueId& transformId, 
            const bool recursive = false );

        /**
         * Returns a filled list of all existing pathes to all instances to the current node.
         */
        void getTransformPathes ( 
            std::vector<String>& transformPathes, 
            const COLLADAFW::UniqueId& transformId, 
            const String childSubPath = "" );

        /*
        * The center of interest distance value in a map to the current transform node.
        */
        const std::map<COLLADAFW::UniqueId, double>& getCenterOfInterestDistances () const { return mCenterOfInterestDistances; }

        /*
        * The center of interest distance value in a map to the current transform node.
        */
        bool findCenterOfInterestDistance ( 
            const COLLADAFW::UniqueId& transformId, 
            double& centerOfInterestDistance );

        /**
        * The map holds for every animationListId the unique id of corresponding node.
        */
        const TransformAnimation* findTransformAnimation ( const COLLADAFW::UniqueId& animationListId );

        /**
        * The map holds for every unique transform node id the maya data model transform object
        * of the transform node.
        */
        const MayaDM::Transform* findMayaDMTransform ( const COLLADAFW::UniqueId& transformId );

    private:

        /** Returns the tolerance value for double value comparison. */
        const double getTolerance () const 
        {
            return getDocumentImporter ()->getTolerance ();
        }

        /*
        * Imports the data of the current node.
        */
        void importNode ( 
            COLLADAFW::Node* rootNode, 
            COLLADAFW::Node* parentNode = NULL, 
            MayaNode* parentMayaNode = NULL, 
            const bool createNode = true );

        /**
         *	Save the transformation ids to the geometry ids.
         */
        bool readGeometryInstances ( const COLLADAFW::Node* node );

        /**
        *	Save the transformation ids to the camera ids.
        */
        bool readCameraInstances ( const COLLADAFW::Node* node );

        /**
        *	Save the transformation ids to the light ids.
        */
        bool readLightInstances ( const COLLADAFW::Node* node );

        /**
        *	Save the transformation ids to the controller ids.
        */
        bool readControllerInstances ( const COLLADAFW::Node* node );

        /**
         * Read the shading engines.
         */
        void readMaterialInstances ( 
            const COLLADAFW::UniqueId& transformNodeId, 
            const COLLADAFW::InstanceGeometry* instanceGeometry );

        /**
         * Handle the node instances. 
         */
        bool readNodeInstances ( const COLLADAFW::Node* node );

        /*
         *	Transform the input matrix and convert it in a double[4][4] matrix.
         */
        void convertMatrix4ToTransposedDouble4x4 ( 
            const COLLADABU::Math::Matrix4& inputMatrix, 
            double outputMatrix[][4], 
            const double tolerance );

        /** 
         * Imports the current transformations. 
         */
        bool importTransformations ( 
            const COLLADAFW::Node* node, 
            MayaDM::Transform* transformNode, 
            COLLADAFW::Node* parentNode = NULL );

        /**
         * Imports a camera lookat transformation.
         * @return Center of interest distance. We need it for creating the camera.
         */
        void importLookatTransform ( 
            const COLLADAFW::Node* node,
            const COLLADAFW::Transformation* transformation,
            MayaDM::Transform* transformNode );

        /**
         * Returns true, if the transform values from the framework is conform to the maya 
         * transformation and fills the maya transform values.
         */
        bool readMayaTransformations ( 
            const COLLADAFW::Node* node, 
            MayaTransformation& mayaTransform, 
            MayaDM::Transform* transformNode, 
            std::vector<TransformAnimation>& transformAnimations,
            bool& hasRotatePivot,
            bool& hasScalePivot,
            bool& isLookatTransform );

        void handleTranslateValues ( 
            MayaTransformation &mayaTransform, 
            const COLLADAFW::Transformation* transformation );

        bool checkPivotValues ( 
            MayaTransformation &mayaTransform,
            bool &hasScalePivot, 
            bool &hasRotatePivot );

        bool handleTransformRotateValues ( 
            MayaTransformation &mayaTransform, 
            const COLLADAFW::Transformation* transformation );

        bool handleJointRotateValues ( 
            MayaTransformation &mayaTransform, 
            const COLLADAFW::Transformation* transformation );

        /**
         * Set the transform values.
         */
        void importDecomposedNodeTransform ( 
            const MayaTransformation &mayaTransform, 
            MayaDM::Transform* transformNode, 
            const bool hasRotatePivot,
            const bool hasScalePivot );

        /**
        * Set the transform values.
        */
        void importDecomposedJointTransform ( 
            const MayaTransformation &mayaTransform, 
            MayaDM::Joint* jointNode );

        /** 
         * Returns the rotation order of the three vectors. 
         */
        MEulerRotation::RotationOrder getRotationOrder ( 
            const COLLADABU::Math::Vector3 axis1, 
            const COLLADABU::Math::Vector3 axis2, 
            const COLLADABU::Math::Vector3 axis3 );

        /**
         * Imports the transform values from a transform matrix.
         * Data loss: no animation possible!
         */
        void importMatrixJointTransform ( 
            const COLLADAFW::Node* node, 
            MayaDM::Transform* transformNode,
            COLLADAFW::Node* parentNode = NULL );

        /**
        * Imports the transform values from a transform matrix.
        * Data loss: no animation possible!
        */
        void importMatrixNodeTransform ( 
            const COLLADAFW::Node* node, 
            MayaDM::Transform* transformNode );

        /**
        * Imports the transform values from a transform matrix.
        * Data loss: no animation possible!
        */
        void importMatrixTransform ( 
            const COLLADABU::Math::Matrix4& transformMatrix,
            MayaDM::Transform* transformNode );

        /**
        * Creates a node or joint object.
        */
        MayaDM::Transform* createMayaNode ( 
            const COLLADAFW::Node* node, 
            const String& nodeName, 
            const String& parentNodeName );

        /**
        * Converts the skew into a matrix.
        */
        void skewValuesToMayaMatrix ( const COLLADAFW::Skew* skew, MMatrix& matrix );

    };
}

#endif // __COLLADA_MAYA_VISUAL_SCENE_IMPORTER_H__

