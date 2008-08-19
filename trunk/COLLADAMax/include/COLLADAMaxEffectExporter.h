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


#ifndef __COLLADAMAX_EFFECTEXPORTER_H__
#define __COLLADAMAX_EFFECTEXPORTER_H__

#include "COLLADAMaxPrerequisites.h"

#include "ColladaMaxStableHeaders.h"
#include "COLLADAStreamWriter.h"
#include "COLLADALibraryEffects.h"
#include "COLLADAIDList.h"

#include "COLLADAMaxExportSceneGraph.h"
#include "COLLADAMaxMaterialExporter.h"
#include "COLLADAMaxTypes.h"

class Mtl;

class StdMat2;

namespace COLLADAMax
{

    /** Class to export all used materials in a max scene to the library effect in COLLADA*/

    class EffectExporter : public COLLADA::LibraryEffects
    {

    private:
        /** Holds information about an already exported effect.*/

        class ExportedEffect
        {
            Mtl * mMaterial; // The max material, that was use to export the effect
            DWORD mColor;  // The color that was used to export the effect
        };

        /** A texture channel.
        Used by standard effects to assign textures to channels.
        Multi-texturing is done by assigning more than one texture per slot.
        Defaults to diffuse texture slot. */
        enum Channel
        {
            AMBIENT = 0,      /**< The texels will be modulated with the ambient light colors. */
            BUMP,      /**< The texels will re-orient the geometric normals. */
            DIFFUSE,      /**< The texels will be modulated with the non-ambient light colors. */
            DISPLACEMENT,      /**< The texels will displace the pixel positions. */
            EMISSION,      /**< The texels will be added to the final color directly. */
            FILTER,      /**< Max-specific. */
            REFLECTION,      /**< The texels will modify the pixel reflection factor. */
            REFRACTION,      /**< The texels will modify the pixel refraction factor. */
            SHININESS,      /**< The texels will modify the specular shininess of the pixel. */
            SPECULAR,      /**< The texels will be modulated with the specular light colors. */
            SPECULAR_LEVEL,      /**< The texels will be modulated with the specular light colors. */
            TRANSPARENt,      /**< The texels will be modify the final color alpha. */
            COUNT,      /**< The number of texture channels. */
            UNKNOWN,      /**< An unknown texture channel. */
            DEFAULT = DIFFUSE
        };


        enum ShaderClassID
        {
            STD2_PHONG_CLASS_ID = 0x00000037,
            STD2_BLINN_SHADER_CLASS_ID = 0x00000038,
            STD2_METAL_SHADER_CLASS_ID = 0x00000039,
            STD2_ANISOTROPIC_SHADER_CLASS_ID = 0x2857f460,
            STD2_MULTI_LAYER_SHADER_CLASS_ID = 0x2857f470,
            STD2_OREN_NAYER_BLINN_CLASS_ID = 0x2857f421
        };

	public:
		class MaterialChannelPair
		{
		public:
			MaterialChannelPair():mMaterial(0), mChannel(0){};
			MaterialChannelPair(Mtl* material, int channel):mMaterial(material), mChannel(channel){};
			bool operator<(const MaterialChannelPair & rhs) const;
		private:
			Mtl* mMaterial;
			int mChannel;
		};

		typedef std::map<MaterialChannelPair, IParamBlock*> MaterialChannelPairParamBlockMap;

	public:
        static const String COLOR_EFFECT_ID_PREFIX;

        static const String TEXCOORD_BASE;


    private:

        static const String DAE_AMBIENT_TEXTURE_CHANNEL;
        static const String DAE_BUMP_TEXTURE_CHANNEL;
        static const String DAE_DIFFUSE_TEXTURE_CHANNEL;
        static const String DAE_DISPLACEMENT_TEXTURE_CHANNEL;
        static const String DAE_EMISSION_TEXTURE_CHANNEL;
        static const String DAE_FILTER_TEXTURE_CHANNEL;
        static const String DAE_OPACITY_TEXTURE_CHANNEL;
        static const String DAE_REFLECTION_TEXTURE_CHANNEL;
        static const String DAE_REFRACTION_TEXTURE_CHANNEL;
        static const String DAE_SHININESS_TEXTURE_CHANNEL;
        static const String DAE_SPECULAR_TEXTURE_CHANNEL;
        static const String DAE_SPECULARLEVEL_TEXTURE_CHANNEL;
        static const String DAE_TRANSPARENT_TEXTURE_CHANNEL;

        static const String EMPTY_STRING;

        ExportSceneGraph * mExportSceneGraph;

        /** Maps already exported wire frame colors to the corresponding COLLADA effect id.*/
        WireFrameColorEffectList mWireFrameColorEffectList;

        DocumentExporter * mDocumentExporter;

        /** List of ids of the already exported materials that are used in the COLLADA file.*/
        ExportedEffectIdList * mExportedEffectIdList;

        /** Maps already exported effect (material in max) to the corresponding COLLADA effect id.*/
        EffectMap mEffectMap;

        /** Maps already exported image file names to the corresponding image id.*/
        ExportedImageMap mExportedImageMap;

        /** List of unique base effect ids.*/
        COLLADA::IDList mEffectIdList;

		/** Maps material and channels to the IParamBlock of the corresponding StdUVGen*/
		MaterialChannelPairParamBlockMap mMaterialChannelPairParamBlockMap;

    public:
        /** Constructor
        @param streamWriter The stream the animation should be written to
        @param exportSceneGraph The scene graph to export
        @param documentExporter The documentexporter this exporter belongs to
        */
        EffectExporter ( COLLADA::StreamWriter * streamWriter, ExportSceneGraph * exportSceneGraph, DocumentExporter * documentExporter );

        void doExport();

        /** Generates the unique id for an effect with color @a color.*/
        static String EffectExporter::getEffectId ( DWORD color );

        /** Returns the WireFrameColorEffectList of the effect exporter.*/
        const WireFrameColorEffectList & getWireFrameColorEffectMap() const
        {
            return mWireFrameColorEffectList;
        }

        /** Returns the EffectMap of the effect exporter.*/
        const EffectMap & getEffectMap() const
        {
            return mEffectMap;
        }

        /** Returns the ExportedImageMapp of the effect exporter.*/
        const ExportedImageMap & getExportedImageMap() const
        {
            return mExportedImageMap;
        }

		/** Returns the MaterialChannelPairParamBlockMap used by the effect exporter*/
		const MaterialChannelPairParamBlockMap & getMaterialChannelPairParamBlockMap() const
		{
			return mMaterialChannelPairParamBlockMap;
		}

    private:
        EffectExporter ( const EffectExporter & effectExporter );
        EffectExporter & operator= ( const EffectExporter & effectExporter );

        /** Exports all the effects of node @a exportNode and all its child nodes.*/
        void exportEffect ( ExportNode* exportNode );

        /** Exports all the effects of  @a material and all its sub materials.*/
        void exportEffect ( ExportNode* exportNode, Mtl* material );

        /** Exports the max standard material @a material.*/
        void exportStandardEffect ( COLLADA::EffectProfile & effectProfile, ExportNode* exportNode, StdMat2* material, const String & effectId, float weight, bool inited );

        /** Exports the max standard material @a material.*/
        void exportUnknownEffect ( COLLADA::EffectProfile & effectProfile, ExportNode* exportNode, Mtl* material, const String & effectId );

        /** Exports am common COLLADA effect created from  @a material.*/
        void exportCommonEffect ( COLLADA::EffectProfile & effectProfile, ExportNode* exportNode, Mtl* material, const String & effectId, float weight = 1.0, bool inited = false );

        /** Exports the material @a material.*/
        void exportSimpleEffect ( ExportNode* exportNode, Mtl* material );

        /** Exports a color effect with color @a color.*/
        void exportColorEffect ( ExportNode* exportNode, DWORD color );

        /** Converts a max color to a CommonColorOrTextureType.*/
        static COLLADA::ColorOrTexture maxColor2ColorOrTexture ( const Color & color, double scale = 1.0 );

        /** Retrieves the effect channel.
        @param mtl The max material
        @param id The id*/
        static EffectExporter::Channel maxIdToEffectChannel ( StdMat2* mtl, int id );

        /** Sets the appropriate opacity.*/
        static COLLADA::EffectProfile::Opaque getOpacity ( Texmap *tmap );


        /** Determines shader type from max shader.*/
        COLLADA::EffectProfile::ShaderTypes maxShaderToShaderType ( Class_ID id );


        static EffectExporter::Channel channelFromString ( const String & value );


        /**Exports the map @a texMap.*/
        void exportMap ( Mtl * material, unsigned int index, Texmap* texMap, COLLADA::EffectProfile & profile, float weight );

        /** Exports the image represented by @a map.*/
        String EffectExporter::exportImage ( Texmap* map, String& fullFileName );

        /** Exports the image represented by @a bitmapInfo.*/
        String EffectExporter::exportImage ( BitmapInfo& bitmapInfo, String& fullFileName );


        /** Blends the color on colorOrTexture with blendColor an amount @a amount.*/
        void EffectExporter::blendColor ( COLLADA::ColorOrTexture & colorOrTexture, Color blendColor, double amount );


    };

}

#endif //__COLLADAMAX_EFFECTEXPORTER_H__