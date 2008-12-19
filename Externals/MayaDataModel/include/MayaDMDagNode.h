/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_DAGNODE_H__
#define __MayaDM_DAGNODE_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMEntity.h"
namespace MayaDM
{
class DagNode : public Entity
{
public:
	struct BoundingBox{
		void write(FILE* file) const
		{
		}
	};
	struct InstObjGroups{
		struct ObjectGroups{
			componentList objectGrpCompList;
			int objectGroupId;
			short objectGrpColor;
			void write(FILE* file) const
			{
				objectGrpCompList.write(file);
				fprintf(file, " ");
				fprintf(file,"%i ", objectGroupId);
				fprintf(file,"%i", objectGrpColor);
			}
		}* objectGroups;
		void write(FILE* file) const
		{
			size_t size = sizeof(objectGroups)/sizeof(ObjectGroups);
			for(size_t i=0; i<size; ++i)
			{
				objectGroups[i].write(file);
				if(i+1<size) fprintf(file," ");
			}
		}
	};
	struct DrawOverride{
		unsigned int overrideDisplayType;
		unsigned int overrideLevelOfDetail;
		bool overrideShading;
		bool overrideTexturing;
		bool overridePlayback;
		bool overrideEnabled;
		bool overrideVisibility;
		unsigned char overrideColor;
		void write(FILE* file) const
		{
			fprintf(file,"%i ", overrideDisplayType);
			fprintf(file,"%i ", overrideLevelOfDetail);
			fprintf(file,"%i ", overrideShading);
			fprintf(file,"%i ", overrideTexturing);
			fprintf(file,"%i ", overridePlayback);
			fprintf(file,"%i ", overrideEnabled);
			fprintf(file,"%i ", overrideVisibility);
			fprintf(file,"%i", overrideColor);
		}
	};
	struct RenderInfo{
		short identification;
		bool layerRenderable;
		unsigned char layerOverrideColor;
		void write(FILE* file) const
		{
			fprintf(file,"%i ", identification);
			fprintf(file,"%i ", layerRenderable);
			fprintf(file,"%i", layerOverrideColor);
		}
	};
	struct RenderLayerInfo{
		short renderLayerId;
		bool renderLayerRenderable;
		unsigned char renderLayerColor;
		void write(FILE* file) const
		{
			fprintf(file,"%i ", renderLayerId);
			fprintf(file,"%i ", renderLayerRenderable);
			fprintf(file,"%i", renderLayerColor);
		}
	};
	struct GhostCustomSteps{
		int ghostPreSteps;
		int ghostPostSteps;
		int ghostStepSize;
		void write(FILE* file) const
		{
			fprintf(file,"%i ", ghostPreSteps);
			fprintf(file,"%i ", ghostPostSteps);
			fprintf(file,"%i", ghostStepSize);
		}
	};
public:
	DagNode(FILE* file,const std::string& name,const std::string& parent=""):Entity(file, name, parent, "dagNode"){}
	virtual ~DagNode(){}
	void setVisibility(bool v)
	{
		if(v == true) return;
		fprintf(mFile,"setAttr \".v\" %i;\n", v);

	}
	void setIntermediateObject(bool io)
	{
		if(io == false) return;
		fprintf(mFile,"setAttr \".io\" %i;\n", io);

	}
	void setTemplate(bool tmp)
	{
		if(tmp == false) return;
		fprintf(mFile,"setAttr \".tmp\" %i;\n", tmp);

	}
	void setGhosting(bool gh)
	{
		if(gh == false) return;
		fprintf(mFile,"setAttr \".gh\" %i;\n", gh);

	}
	void setInstObjGroups(size_t iog_i,const InstObjGroups& iog)
	{
		fprintf(mFile,"setAttr \".iog[%i]\" ",iog_i);
		iog.write(mFile);
		fprintf(mFile,";\n");

	}
	void setObjectGroups(size_t iog_i,size_t og_i,const InstObjGroups::ObjectGroups& og)
	{
		fprintf(mFile,"setAttr \".iog[%i].og[%i]\" ",iog_i,og_i);
		og.write(mFile);
		fprintf(mFile,";\n");

	}
	void setObjectGrpCompList(size_t iog_i,size_t og_i,const componentList& gcl)
	{
		fprintf(mFile,"setAttr \".iog[%i].og[%i].gcl\" -type \"componentList\" ",iog_i,og_i);
		gcl.write(mFile);
		fprintf(mFile,";\n");

	}
	void setObjectGroupId(size_t iog_i,size_t og_i,int gid)
	{
		if(gid == 0) return;
		fprintf(mFile,"setAttr \".iog[%i].og[%i].gid\" %i;\n", iog_i,og_i,gid);

	}
	void setObjectGrpColor(size_t iog_i,size_t og_i,short gco)
	{
		if(gco == -1) return;
		fprintf(mFile,"setAttr \".iog[%i].og[%i].gco\" %i;\n", iog_i,og_i,gco);

	}
	void setUseObjectColor(bool uoc)
	{
		if(uoc == false) return;
		fprintf(mFile,"setAttr \".uoc\" %i;\n", uoc);

	}
	void setObjectColor(short oc)
	{
		if(oc == 0) return;
		fprintf(mFile,"setAttr \".oc\" %i;\n", oc);

	}
	void setDrawOverride(const DrawOverride& do_)
	{
		fprintf(mFile,"setAttr \".do\" ");
		do_.write(mFile);
		fprintf(mFile,";\n");

	}
	void setOverrideDisplayType(unsigned int ovdt)
	{
		if(ovdt == 0) return;
		fprintf(mFile,"setAttr \".do.ovdt\" %i;\n", ovdt);

	}
	void setOverrideLevelOfDetail(unsigned int ovlod)
	{
		if(ovlod == 0) return;
		fprintf(mFile,"setAttr \".do.ovlod\" %i;\n", ovlod);

	}
	void setOverrideShading(bool ovs)
	{
		if(ovs == true) return;
		fprintf(mFile,"setAttr \".do.ovs\" %i;\n", ovs);

	}
	void setOverrideTexturing(bool ovt)
	{
		if(ovt == true) return;
		fprintf(mFile,"setAttr \".do.ovt\" %i;\n", ovt);

	}
	void setOverridePlayback(bool ovp)
	{
		if(ovp == true) return;
		fprintf(mFile,"setAttr \".do.ovp\" %i;\n", ovp);

	}
	void setOverrideEnabled(bool ove)
	{
		if(ove == false) return;
		fprintf(mFile,"setAttr \".do.ove\" %i;\n", ove);

	}
	void setOverrideVisibility(bool ovv)
	{
		if(ovv == true) return;
		fprintf(mFile,"setAttr \".do.ovv\" %i;\n", ovv);

	}
	void setOverrideColor(unsigned char ovc)
	{
		if(ovc == 0) return;
		fprintf(mFile,"setAttr \".do.ovc\" %i;\n", ovc);

	}
	void setLodVisibility(bool lodv)
	{
		if(lodv == true) return;
		fprintf(mFile,"setAttr \".lodv\" %i;\n", lodv);

	}
	void setRenderInfo(const RenderInfo& ri)
	{
		fprintf(mFile,"setAttr \".ri\" ");
		ri.write(mFile);
		fprintf(mFile,";\n");

	}
	void setIdentification(short rlid)
	{
		if(rlid == 0) return;
		fprintf(mFile,"setAttr \".ri.rlid\" %i;\n", rlid);

	}
	void setLayerRenderable(bool rndr)
	{
		if(rndr == true) return;
		fprintf(mFile,"setAttr \".ri.rndr\" %i;\n", rndr);

	}
	void setLayerOverrideColor(unsigned char lovc)
	{
		if(lovc == 0) return;
		fprintf(mFile,"setAttr \".ri.lovc\" %i;\n", lovc);

	}
	void setRenderLayerInfo(size_t rlio_i,const RenderLayerInfo& rlio)
	{
		fprintf(mFile,"setAttr \".rlio[%i]\" ",rlio_i);
		rlio.write(mFile);
		fprintf(mFile,";\n");

	}
	void setRenderLayerId(size_t rlio_i,short rli)
	{
		if(rli == 0) return;
		fprintf(mFile,"setAttr \".rlio[%i].rli\" %i;\n", rlio_i,rli);

	}
	void setRenderLayerRenderable(size_t rlio_i,bool rlr)
	{
		if(rlr == true) return;
		fprintf(mFile,"setAttr \".rlio[%i].rlr\" %i;\n", rlio_i,rlr);

	}
	void setRenderLayerColor(size_t rlio_i,unsigned char rlc)
	{
		if(rlc == 0) return;
		fprintf(mFile,"setAttr \".rlio[%i].rlc\" %i;\n", rlio_i,rlc);

	}
	void setGhostingControl(unsigned int gc)
	{
		if(gc == 0) return;
		fprintf(mFile,"setAttr \".gc\" %i;\n", gc);

	}
	void setGhostCustomSteps(const GhostCustomSteps& gcs)
	{
		fprintf(mFile,"setAttr \".gcs\" ");
		gcs.write(mFile);
		fprintf(mFile,";\n");

	}
	void setGhostPreSteps(int gpr)
	{
		if(gpr == 3) return;
		fprintf(mFile,"setAttr \".gcs.gpr\" %i;\n", gpr);

	}
	void setGhostPostSteps(int gps)
	{
		if(gps == 3) return;
		fprintf(mFile,"setAttr \".gcs.gps\" %i;\n", gps);

	}
	void setGhostStepSize(int gss)
	{
		if(gss == 1) return;
		fprintf(mFile,"setAttr \".gcs.gss\" %i;\n", gss);

	}
	void setGhostFrames(const intArray& gf)
	{
		if(gf.size == 0) return;
		fprintf(mFile,"setAttr \".gf\" -type \"intArray\" ");
		gf.write(mFile);
		fprintf(mFile,";\n");

	}
	void getBoundingBox()
	{
		fprintf(mFile,"\"%s.bb\"",mName.c_str());

	}
	void getBoundingBoxMin()
	{
		fprintf(mFile,"\"%s.bb.bbmn\"",mName.c_str());

	}
	void getBoundingBoxMinX()
	{
		fprintf(mFile,"\"%s.bb.bbmn.bbnx\"",mName.c_str());

	}
	void getBoundingBoxMinY()
	{
		fprintf(mFile,"\"%s.bb.bbmn.bbny\"",mName.c_str());

	}
	void getBoundingBoxMinZ()
	{
		fprintf(mFile,"\"%s.bb.bbmn.bbnz\"",mName.c_str());

	}
	void getBoundingBoxMax()
	{
		fprintf(mFile,"\"%s.bb.bbmx\"",mName.c_str());

	}
	void getBoundingBoxMaxX()
	{
		fprintf(mFile,"\"%s.bb.bbmx.bbxx\"",mName.c_str());

	}
	void getBoundingBoxMaxY()
	{
		fprintf(mFile,"\"%s.bb.bbmx.bbxy\"",mName.c_str());

	}
	void getBoundingBoxMaxZ()
	{
		fprintf(mFile,"\"%s.bb.bbmx.bbxz\"",mName.c_str());

	}
	void getBoundingBoxSize()
	{
		fprintf(mFile,"\"%s.bb.bbsi\"",mName.c_str());

	}
	void getBoundingBoxSizeX()
	{
		fprintf(mFile,"\"%s.bb.bbsi.bbsx\"",mName.c_str());

	}
	void getBoundingBoxSizeY()
	{
		fprintf(mFile,"\"%s.bb.bbsi.bbsy\"",mName.c_str());

	}
	void getBoundingBoxSizeZ()
	{
		fprintf(mFile,"\"%s.bb.bbsi.bbsz\"",mName.c_str());

	}
	void getCenter()
	{
		fprintf(mFile,"\"%s.c\"",mName.c_str());

	}
	void getBoundingBoxCenterX()
	{
		fprintf(mFile,"\"%s.c.bcx\"",mName.c_str());

	}
	void getBoundingBoxCenterY()
	{
		fprintf(mFile,"\"%s.c.bcy\"",mName.c_str());

	}
	void getBoundingBoxCenterZ()
	{
		fprintf(mFile,"\"%s.c.bcz\"",mName.c_str());

	}
	void getMatrix()
	{
		fprintf(mFile,"\"%s.m\"",mName.c_str());

	}
	void getInverseMatrix()
	{
		fprintf(mFile,"\"%s.im\"",mName.c_str());

	}
	void getWorldMatrix(size_t wm_i)
	{
		fprintf(mFile,"\"%s.wm[%i]\"",mName.c_str(),wm_i);

	}
	void getWorldInverseMatrix(size_t wim_i)
	{
		fprintf(mFile,"\"%s.wim[%i]\"",mName.c_str(),wim_i);

	}
	void getParentMatrix(size_t pm_i)
	{
		fprintf(mFile,"\"%s.pm[%i]\"",mName.c_str(),pm_i);

	}
	void getParentInverseMatrix(size_t pim_i)
	{
		fprintf(mFile,"\"%s.pim[%i]\"",mName.c_str(),pim_i);

	}
	void getVisibility()
	{
		fprintf(mFile,"\"%s.v\"",mName.c_str());

	}
	void getIntermediateObject()
	{
		fprintf(mFile,"\"%s.io\"",mName.c_str());

	}
	void getTemplate()
	{
		fprintf(mFile,"\"%s.tmp\"",mName.c_str());

	}
	void getGhosting()
	{
		fprintf(mFile,"\"%s.gh\"",mName.c_str());

	}
	void getInstObjGroups(size_t iog_i)
	{
		fprintf(mFile,"\"%s.iog[%i]\"",mName.c_str(),iog_i);

	}
	void getObjectGroups(size_t iog_i,size_t og_i)
	{
		fprintf(mFile,"\"%s.iog[%i].og[%i]\"",mName.c_str(),iog_i,og_i);

	}
	void getObjectGroupId(size_t iog_i,size_t og_i)
	{
		fprintf(mFile,"\"%s.iog[%i].og[%i].gid\"",mName.c_str(),iog_i,og_i);

	}
	void getObjectGrpColor(size_t iog_i,size_t og_i)
	{
		fprintf(mFile,"\"%s.iog[%i].og[%i].gco\"",mName.c_str(),iog_i,og_i);

	}
	void getUseObjectColor()
	{
		fprintf(mFile,"\"%s.uoc\"",mName.c_str());

	}
	void getObjectColor()
	{
		fprintf(mFile,"\"%s.oc\"",mName.c_str());

	}
	void getDrawOverride()
	{
		fprintf(mFile,"\"%s.do\"",mName.c_str());

	}
	void getOverrideDisplayType()
	{
		fprintf(mFile,"\"%s.do.ovdt\"",mName.c_str());

	}
	void getOverrideLevelOfDetail()
	{
		fprintf(mFile,"\"%s.do.ovlod\"",mName.c_str());

	}
	void getOverrideShading()
	{
		fprintf(mFile,"\"%s.do.ovs\"",mName.c_str());

	}
	void getOverrideTexturing()
	{
		fprintf(mFile,"\"%s.do.ovt\"",mName.c_str());

	}
	void getOverridePlayback()
	{
		fprintf(mFile,"\"%s.do.ovp\"",mName.c_str());

	}
	void getOverrideEnabled()
	{
		fprintf(mFile,"\"%s.do.ove\"",mName.c_str());

	}
	void getOverrideVisibility()
	{
		fprintf(mFile,"\"%s.do.ovv\"",mName.c_str());

	}
	void getOverrideColor()
	{
		fprintf(mFile,"\"%s.do.ovc\"",mName.c_str());

	}
	void getLodVisibility()
	{
		fprintf(mFile,"\"%s.lodv\"",mName.c_str());

	}
	void getRenderInfo()
	{
		fprintf(mFile,"\"%s.ri\"",mName.c_str());

	}
	void getIdentification()
	{
		fprintf(mFile,"\"%s.ri.rlid\"",mName.c_str());

	}
	void getLayerRenderable()
	{
		fprintf(mFile,"\"%s.ri.rndr\"",mName.c_str());

	}
	void getLayerOverrideColor()
	{
		fprintf(mFile,"\"%s.ri.lovc\"",mName.c_str());

	}
	void getRenderLayerInfo(size_t rlio_i)
	{
		fprintf(mFile,"\"%s.rlio[%i]\"",mName.c_str(),rlio_i);

	}
	void getRenderLayerId(size_t rlio_i)
	{
		fprintf(mFile,"\"%s.rlio[%i].rli\"",mName.c_str(),rlio_i);

	}
	void getRenderLayerRenderable(size_t rlio_i)
	{
		fprintf(mFile,"\"%s.rlio[%i].rlr\"",mName.c_str(),rlio_i);

	}
	void getRenderLayerColor(size_t rlio_i)
	{
		fprintf(mFile,"\"%s.rlio[%i].rlc\"",mName.c_str(),rlio_i);

	}
	void getGhostingControl()
	{
		fprintf(mFile,"\"%s.gc\"",mName.c_str());

	}
	void getGhostCustomSteps()
	{
		fprintf(mFile,"\"%s.gcs\"",mName.c_str());

	}
	void getGhostPreSteps()
	{
		fprintf(mFile,"\"%s.gcs.gpr\"",mName.c_str());

	}
	void getGhostPostSteps()
	{
		fprintf(mFile,"\"%s.gcs.gps\"",mName.c_str());

	}
	void getGhostStepSize()
	{
		fprintf(mFile,"\"%s.gcs.gss\"",mName.c_str());

	}
	void getGhostFrames()
	{
		fprintf(mFile,"\"%s.gf\"",mName.c_str());

	}
	void getGhostRangeStart()
	{
		fprintf(mFile,"\"%s.grs\"",mName.c_str());

	}
	void getGhostRangeEnd()
	{
		fprintf(mFile,"\"%s.gre\"",mName.c_str());

	}
	void getGhostDriver()
	{
		fprintf(mFile,"\"%s.gdr\"",mName.c_str());

	}
protected:
	DagNode(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):Entity(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_DAGNODE_H__
