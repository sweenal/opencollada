/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_UVCHOOSER_H__
#define __MayaDM_UVCHOOSER_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMDependNode.h"
namespace MayaDM
{
class UvChooser : public DependNode
{
public:
public:
	UvChooser(FILE* file,const std::string& name,const std::string& parent=""):DependNode(file, name, parent, "uvChooser"){}
	virtual ~UvChooser(){}
	void setUvSets(size_t uvs_i,const string& uvs)
	{
		if(uvs == "NULL") return;
		fprintf(mFile,"setAttr \".uvs[%i]\" -type \"string\" ",uvs_i);
		uvs.write(mFile);
		fprintf(mFile,";\n");

	}
	void setVertexUvOne(const float2& vt1)
	{
		fprintf(mFile,"setAttr \".vt1\" -type \"float2\" ");
		vt1.write(mFile);
		fprintf(mFile,";\n");

	}
	void setVertexUvOneU(float t1u)
	{
		if(t1u == 0.0) return;
		fprintf(mFile,"setAttr \".vt1.t1u\" %f;\n", t1u);

	}
	void setVertexUvOneV(float t1v)
	{
		if(t1v == 0.0) return;
		fprintf(mFile,"setAttr \".vt1.t1v\" %f;\n", t1v);

	}
	void setVertexUvTwo(const float2& vt2)
	{
		fprintf(mFile,"setAttr \".vt2\" -type \"float2\" ");
		vt2.write(mFile);
		fprintf(mFile,";\n");

	}
	void setVertexUvTwoU(float t2u)
	{
		if(t2u == 0.0) return;
		fprintf(mFile,"setAttr \".vt2.t2u\" %f;\n", t2u);

	}
	void setVertexUvTwoV(float t2v)
	{
		if(t2v == 0.0) return;
		fprintf(mFile,"setAttr \".vt2.t2v\" %f;\n", t2v);

	}
	void setVertexUvThree(const float2& vt3)
	{
		fprintf(mFile,"setAttr \".vt3\" -type \"float2\" ");
		vt3.write(mFile);
		fprintf(mFile,";\n");

	}
	void setVertexUvThreeU(float t3u)
	{
		if(t3u == 0.0) return;
		fprintf(mFile,"setAttr \".vt3.t3u\" %f;\n", t3u);

	}
	void setVertexUvThreeV(float t3v)
	{
		if(t3v == 0.0) return;
		fprintf(mFile,"setAttr \".vt3.t3v\" %f;\n", t3v);

	}
	void setVertexCameraOne(const float3& vc1)
	{
		fprintf(mFile,"setAttr \".vc1\" -type \"float3\" ");
		vc1.write(mFile);
		fprintf(mFile,";\n");

	}
	void setVertexCameraOneX(float c1x)
	{
		if(c1x == 0.0) return;
		fprintf(mFile,"setAttr \".vc1.c1x\" %f;\n", c1x);

	}
	void setVertexCameraOneY(float c1y)
	{
		if(c1y == 0.0) return;
		fprintf(mFile,"setAttr \".vc1.c1y\" %f;\n", c1y);

	}
	void setVertexCameraOneZ(float c1z)
	{
		if(c1z == 0.0) return;
		fprintf(mFile,"setAttr \".vc1.c1z\" %f;\n", c1z);

	}
	void setOutVertexUvOne(const float2& ov1)
	{
		fprintf(mFile,"setAttr \".ov1\" -type \"float2\" ");
		ov1.write(mFile);
		fprintf(mFile,";\n");

	}
	void setOutVertexUvOneU(float o1u)
	{
		if(o1u == 0.0) return;
		fprintf(mFile,"setAttr \".ov1.o1u\" %f;\n", o1u);

	}
	void setOutVertexUvOneV(float o1v)
	{
		if(o1v == 0.0) return;
		fprintf(mFile,"setAttr \".ov1.o1v\" %f;\n", o1v);

	}
	void setOutVertexUvTwo(const float2& ov2)
	{
		fprintf(mFile,"setAttr \".ov2\" -type \"float2\" ");
		ov2.write(mFile);
		fprintf(mFile,";\n");

	}
	void setOutVertexUvTwoU(float o2u)
	{
		if(o2u == 0.0) return;
		fprintf(mFile,"setAttr \".ov2.o2u\" %f;\n", o2u);

	}
	void setOutVertexUvTwoV(float o2v)
	{
		if(o2v == 0.0) return;
		fprintf(mFile,"setAttr \".ov2.o2v\" %f;\n", o2v);

	}
	void setOutVertexUvThree(const float2& ov3)
	{
		fprintf(mFile,"setAttr \".ov3\" -type \"float2\" ");
		ov3.write(mFile);
		fprintf(mFile,";\n");

	}
	void setOutVertexUvThreeU(float o3u)
	{
		if(o3u == 0.0) return;
		fprintf(mFile,"setAttr \".ov3.o3u\" %f;\n", o3u);

	}
	void setOutVertexUvThreeV(float o3v)
	{
		if(o3v == 0.0) return;
		fprintf(mFile,"setAttr \".ov3.o3v\" %f;\n", o3v);

	}
	void setOutVertexCameraOne(const float3& oc1)
	{
		fprintf(mFile,"setAttr \".oc1\" -type \"float3\" ");
		oc1.write(mFile);
		fprintf(mFile,";\n");

	}
	void setOutVertexCameraOneX(float o1x)
	{
		if(o1x == 0.0) return;
		fprintf(mFile,"setAttr \".oc1.o1x\" %f;\n", o1x);

	}
	void setOutVertexCameraOneY(float o1y)
	{
		if(o1y == 0.0) return;
		fprintf(mFile,"setAttr \".oc1.o1y\" %f;\n", o1y);

	}
	void setOutVertexCameraOneZ(float o1z)
	{
		if(o1z == 0.0) return;
		fprintf(mFile,"setAttr \".oc1.o1z\" %f;\n", o1z);

	}
	void getUvSets(size_t uvs_i)
	{
		fprintf(mFile,"\"%s.uvs[%i]\"",mName.c_str(),uvs_i);

	}
	void getUvCoord()
	{
		fprintf(mFile,"\"%s.uv\"",mName.c_str());

	}
	void getUCoord()
	{
		fprintf(mFile,"\"%s.uv.u\"",mName.c_str());

	}
	void getVCoord()
	{
		fprintf(mFile,"\"%s.uv.v\"",mName.c_str());

	}
	void getVertexUvOne()
	{
		fprintf(mFile,"\"%s.vt1\"",mName.c_str());

	}
	void getVertexUvOneU()
	{
		fprintf(mFile,"\"%s.vt1.t1u\"",mName.c_str());

	}
	void getVertexUvOneV()
	{
		fprintf(mFile,"\"%s.vt1.t1v\"",mName.c_str());

	}
	void getVertexUvTwo()
	{
		fprintf(mFile,"\"%s.vt2\"",mName.c_str());

	}
	void getVertexUvTwoU()
	{
		fprintf(mFile,"\"%s.vt2.t2u\"",mName.c_str());

	}
	void getVertexUvTwoV()
	{
		fprintf(mFile,"\"%s.vt2.t2v\"",mName.c_str());

	}
	void getVertexUvThree()
	{
		fprintf(mFile,"\"%s.vt3\"",mName.c_str());

	}
	void getVertexUvThreeU()
	{
		fprintf(mFile,"\"%s.vt3.t3u\"",mName.c_str());

	}
	void getVertexUvThreeV()
	{
		fprintf(mFile,"\"%s.vt3.t3v\"",mName.c_str());

	}
	void getVertexCameraOne()
	{
		fprintf(mFile,"\"%s.vc1\"",mName.c_str());

	}
	void getVertexCameraOneX()
	{
		fprintf(mFile,"\"%s.vc1.c1x\"",mName.c_str());

	}
	void getVertexCameraOneY()
	{
		fprintf(mFile,"\"%s.vc1.c1y\"",mName.c_str());

	}
	void getVertexCameraOneZ()
	{
		fprintf(mFile,"\"%s.vc1.c1z\"",mName.c_str());

	}
	void getInfoBits()
	{
		fprintf(mFile,"\"%s.ib\"",mName.c_str());

	}
	void getOutUv()
	{
		fprintf(mFile,"\"%s.ouv\"",mName.c_str());

	}
	void getOutU()
	{
		fprintf(mFile,"\"%s.ouv.ou\"",mName.c_str());

	}
	void getOutV()
	{
		fprintf(mFile,"\"%s.ouv.ov\"",mName.c_str());

	}
	void getOutVertexUvOne()
	{
		fprintf(mFile,"\"%s.ov1\"",mName.c_str());

	}
	void getOutVertexUvOneU()
	{
		fprintf(mFile,"\"%s.ov1.o1u\"",mName.c_str());

	}
	void getOutVertexUvOneV()
	{
		fprintf(mFile,"\"%s.ov1.o1v\"",mName.c_str());

	}
	void getOutVertexUvTwo()
	{
		fprintf(mFile,"\"%s.ov2\"",mName.c_str());

	}
	void getOutVertexUvTwoU()
	{
		fprintf(mFile,"\"%s.ov2.o2u\"",mName.c_str());

	}
	void getOutVertexUvTwoV()
	{
		fprintf(mFile,"\"%s.ov2.o2v\"",mName.c_str());

	}
	void getOutVertexUvThree()
	{
		fprintf(mFile,"\"%s.ov3\"",mName.c_str());

	}
	void getOutVertexUvThreeU()
	{
		fprintf(mFile,"\"%s.ov3.o3u\"",mName.c_str());

	}
	void getOutVertexUvThreeV()
	{
		fprintf(mFile,"\"%s.ov3.o3v\"",mName.c_str());

	}
	void getOutVertexCameraOne()
	{
		fprintf(mFile,"\"%s.oc1\"",mName.c_str());

	}
	void getOutVertexCameraOneX()
	{
		fprintf(mFile,"\"%s.oc1.o1x\"",mName.c_str());

	}
	void getOutVertexCameraOneY()
	{
		fprintf(mFile,"\"%s.oc1.o1y\"",mName.c_str());

	}
	void getOutVertexCameraOneZ()
	{
		fprintf(mFile,"\"%s.oc1.o1z\"",mName.c_str());

	}
protected:
	UvChooser(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):DependNode(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_UVCHOOSER_H__
