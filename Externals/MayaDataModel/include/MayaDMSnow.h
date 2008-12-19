/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_SNOW_H__
#define __MayaDM_SNOW_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMTexture3d.h"
namespace MayaDM
{
class Snow : public Texture3d
{
public:
public:
	Snow(FILE* file,const std::string& name,const std::string& parent=""):Texture3d(file, name, parent, "snow"){}
	virtual ~Snow(){}
	void setSnowColor(const float3& sn)
	{
		if(sn == float3(1.0f,1.0f,1.0f)) return;
		fprintf(mFile,"setAttr \".sn\" -type \"float3\" ");
		sn.write(mFile);
		fprintf(mFile,";\n");

	}
	void setSnowColorR(float snr)
	{
		if(snr == 0.0) return;
		fprintf(mFile,"setAttr \".sn.snr\" %f;\n", snr);

	}
	void setSnowColorG(float sng)
	{
		if(sng == 0.0) return;
		fprintf(mFile,"setAttr \".sn.sng\" %f;\n", sng);

	}
	void setSnowColorB(float snb)
	{
		if(snb == 0.0) return;
		fprintf(mFile,"setAttr \".sn.snb\" %f;\n", snb);

	}
	void setSurfaceColor(const float3& su)
	{
		if(su == float3(0.5f,0.0f,0.0f)) return;
		fprintf(mFile,"setAttr \".su\" -type \"float3\" ");
		su.write(mFile);
		fprintf(mFile,";\n");

	}
	void setSurfaceColorR(float sur)
	{
		if(sur == 0.0) return;
		fprintf(mFile,"setAttr \".su.sur\" %f;\n", sur);

	}
	void setSurfaceColorG(float sug)
	{
		if(sug == 0.0) return;
		fprintf(mFile,"setAttr \".su.sug\" %f;\n", sug);

	}
	void setSurfaceColorB(float sub)
	{
		if(sub == 0.0) return;
		fprintf(mFile,"setAttr \".su.sub\" %f;\n", sub);

	}
	void setThreshold(float th)
	{
		if(th == 0.5) return;
		fprintf(mFile,"setAttr \".th\" %f;\n", th);

	}
	void setDepthDecay(float dd)
	{
		if(dd == 5.0) return;
		fprintf(mFile,"setAttr \".dd\" %f;\n", dd);

	}
	void setThickness(float tn)
	{
		if(tn == 1.0) return;
		fprintf(mFile,"setAttr \".tn\" %f;\n", tn);

	}
	void getNormalCamera()
	{
		fprintf(mFile,"\"%s.n\"",mName.c_str());

	}
	void getNormalCameraX()
	{
		fprintf(mFile,"\"%s.n.nx\"",mName.c_str());

	}
	void getNormalCameraY()
	{
		fprintf(mFile,"\"%s.n.ny\"",mName.c_str());

	}
	void getNormalCameraZ()
	{
		fprintf(mFile,"\"%s.n.nz\"",mName.c_str());

	}
	void getRefPointObj()
	{
		fprintf(mFile,"\"%s.rpo\"",mName.c_str());

	}
	void getRefPointObjX()
	{
		fprintf(mFile,"\"%s.rpo.rox\"",mName.c_str());

	}
	void getRefPointObjY()
	{
		fprintf(mFile,"\"%s.rpo.roy\"",mName.c_str());

	}
	void getRefPointObjZ()
	{
		fprintf(mFile,"\"%s.rpo.roz\"",mName.c_str());

	}
	void getRefPointCamera()
	{
		fprintf(mFile,"\"%s.rpc\"",mName.c_str());

	}
	void getRefPointCameraX()
	{
		fprintf(mFile,"\"%s.rpc.rcx\"",mName.c_str());

	}
	void getRefPointCameraY()
	{
		fprintf(mFile,"\"%s.rpc.rcy\"",mName.c_str());

	}
	void getRefPointCameraZ()
	{
		fprintf(mFile,"\"%s.rpc.rcz\"",mName.c_str());

	}
	void getEyeToTextureMatrix()
	{
		fprintf(mFile,"\"%s.e2t\"",mName.c_str());

	}
	void getSnowColor()
	{
		fprintf(mFile,"\"%s.sn\"",mName.c_str());

	}
	void getSnowColorR()
	{
		fprintf(mFile,"\"%s.sn.snr\"",mName.c_str());

	}
	void getSnowColorG()
	{
		fprintf(mFile,"\"%s.sn.sng\"",mName.c_str());

	}
	void getSnowColorB()
	{
		fprintf(mFile,"\"%s.sn.snb\"",mName.c_str());

	}
	void getSurfaceColor()
	{
		fprintf(mFile,"\"%s.su\"",mName.c_str());

	}
	void getSurfaceColorR()
	{
		fprintf(mFile,"\"%s.su.sur\"",mName.c_str());

	}
	void getSurfaceColorG()
	{
		fprintf(mFile,"\"%s.su.sug\"",mName.c_str());

	}
	void getSurfaceColorB()
	{
		fprintf(mFile,"\"%s.su.sub\"",mName.c_str());

	}
	void getThreshold()
	{
		fprintf(mFile,"\"%s.th\"",mName.c_str());

	}
	void getDepthDecay()
	{
		fprintf(mFile,"\"%s.dd\"",mName.c_str());

	}
	void getThickness()
	{
		fprintf(mFile,"\"%s.tn\"",mName.c_str());

	}
protected:
	Snow(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):Texture3d(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_SNOW_H__
