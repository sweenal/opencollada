/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_HWRENDERGLOBALS_H__
#define __MayaDM_HWRENDERGLOBALS_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMDependNode.h"
namespace MayaDM
{
class HwRenderGlobals : public DependNode
{
public:
public:
	HwRenderGlobals(FILE* file,const std::string& name,const std::string& parent=""):DependNode(file, name, parent, "hwRenderGlobals"){}
	virtual ~HwRenderGlobals(){}
	void setRenderPasses(unsigned int rp)
	{
		if(rp == 0) return;
		fprintf(mFile,"setAttr \".rp\" %i;\n", rp);

	}
	void setCameraIcons(bool cai)
	{
		if(cai == false) return;
		fprintf(mFile,"setAttr \".cai\" %i;\n", cai);

	}
	void setCollisionIcons(bool coi)
	{
		if(coi == false) return;
		fprintf(mFile,"setAttr \".coi\" %i;\n", coi);

	}
	void setBackgroundColor(const float3& bc)
	{
		if(bc == float3(0.0f,0.0f,0.0f)) return;
		fprintf(mFile,"setAttr \".bc\" -type \"float3\" ");
		bc.write(mFile);
		fprintf(mFile,";\n");

	}
	void setBackgroundColorR(float bcr)
	{
		if(bcr == 0.0) return;
		fprintf(mFile,"setAttr \".bc.bcr\" %f;\n", bcr);

	}
	void setBackgroundColorG(float bcg)
	{
		if(bcg == 0.0) return;
		fprintf(mFile,"setAttr \".bc.bcg\" %f;\n", bcg);

	}
	void setBackgroundColorB(float bcb)
	{
		if(bcb == 0.0) return;
		fprintf(mFile,"setAttr \".bc.bcb\" %f;\n", bcb);

	}
	void setEmitterIcons(bool ei)
	{
		if(ei == false) return;
		fprintf(mFile,"setAttr \".ei\" %i;\n", ei);

	}
	void setExtension(unsigned int ex)
	{
		if(ex == 3) return;
		fprintf(mFile,"setAttr \".ex\" %i;\n", ex);

	}
	void setEdgeSmoothing(float es)
	{
		if(es == 1.0) return;
		fprintf(mFile,"setAttr \".es\" %f;\n", es);

	}
	void setEndFrame(int ef)
	{
		if(ef == 10) return;
		fprintf(mFile,"setAttr \".ef\" %i;\n", ef);

	}
	void setByFrame(int bf)
	{
		if(bf == 1) return;
		fprintf(mFile,"setAttr \".bf\" %i;\n", bf);

	}
	void setFieldIcons(bool fii)
	{
		if(fii == false) return;
		fprintf(mFile,"setAttr \".fii\" %i;\n", fii);

	}
	void setStartFrame(int sf)
	{
		if(sf == 1) return;
		fprintf(mFile,"setAttr \".sf\" %i;\n", sf);

	}
	void setGrid(bool gr)
	{
		if(gr == false) return;
		fprintf(mFile,"setAttr \".gr\" %i;\n", gr);

	}
	void setLightIcons(bool li)
	{
		if(li == false) return;
		fprintf(mFile,"setAttr \".li\" %i;\n", li);

	}
	void setLineSmoothing(bool ls)
	{
		if(ls == false) return;
		fprintf(mFile,"setAttr \".ls\" %i;\n", ls);

	}
	void setMotionBlur(float mb)
	{
		if(mb == 0.0) return;
		fprintf(mFile,"setAttr \".mb\" %f;\n", mb);

	}
	void setTransformIcons(bool ti)
	{
		if(ti == false) return;
		fprintf(mFile,"setAttr \".ti\" %i;\n", ti);

	}
	void setTexturing(bool txt)
	{
		if(txt == true) return;
		fprintf(mFile,"setAttr \".txt\" %i;\n", txt);

	}
	void setMultiPassRendering(bool mpr)
	{
		if(mpr == false) return;
		fprintf(mFile,"setAttr \".mpr\" %i;\n", mpr);

	}
	void setWriteZDepth(bool wzd)
	{
		if(wzd == false) return;
		fprintf(mFile,"setAttr \".wzd\" %i;\n", wzd);

	}
	void setFilename(const string& fn)
	{
		if(fn == "NULL") return;
		fprintf(mFile,"setAttr \".fn\" -type \"string\" ");
		fn.write(mFile);
		fprintf(mFile,";\n");

	}
	void setImageFormat(unsigned int if_)
	{
		if(if_ == 0) return;
		fprintf(mFile,"setAttr \".if\" %i;\n", if_);

	}
	void setResolution(const string& res)
	{
		if(res == "NULL") return;
		fprintf(mFile,"setAttr \".res\" -type \"string\" ");
		res.write(mFile);
		fprintf(mFile,";\n");

	}
	void setAlphaSource(unsigned int as)
	{
		if(as == 0) return;
		fprintf(mFile,"setAttr \".as\" %i;\n", as);

	}
	void setDrawStyle(unsigned int ds)
	{
		if(ds == 3) return;
		fprintf(mFile,"setAttr \".ds\" %i;\n", ds);

	}
	void setLightingMode(unsigned int lm)
	{
		if(lm == 0) return;
		fprintf(mFile,"setAttr \".lm\" %i;\n", lm);

	}
	void setFullImageResolution(bool fir)
	{
		if(fir == false) return;
		fprintf(mFile,"setAttr \".fir\" %i;\n", fir);

	}
	void setAntiAliasPolygons(bool aap)
	{
		if(aap == false) return;
		fprintf(mFile,"setAttr \".aap\" %i;\n", aap);

	}
	void setGeometryMask(bool gh)
	{
		if(gh == false) return;
		fprintf(mFile,"setAttr \".gh\" %i;\n", gh);

	}
	void setDisplayShadows(bool sd)
	{
		if(sd == false) return;
		fprintf(mFile,"setAttr \".sd\" %i;\n", sd);

	}
	void getRenderPasses()
	{
		fprintf(mFile,"\"%s.rp\"",mName.c_str());

	}
	void getCameraIcons()
	{
		fprintf(mFile,"\"%s.cai\"",mName.c_str());

	}
	void getCollisionIcons()
	{
		fprintf(mFile,"\"%s.coi\"",mName.c_str());

	}
	void getBackgroundColor()
	{
		fprintf(mFile,"\"%s.bc\"",mName.c_str());

	}
	void getBackgroundColorR()
	{
		fprintf(mFile,"\"%s.bc.bcr\"",mName.c_str());

	}
	void getBackgroundColorG()
	{
		fprintf(mFile,"\"%s.bc.bcg\"",mName.c_str());

	}
	void getBackgroundColorB()
	{
		fprintf(mFile,"\"%s.bc.bcb\"",mName.c_str());

	}
	void getEmitterIcons()
	{
		fprintf(mFile,"\"%s.ei\"",mName.c_str());

	}
	void getExtension()
	{
		fprintf(mFile,"\"%s.ex\"",mName.c_str());

	}
	void getEdgeSmoothing()
	{
		fprintf(mFile,"\"%s.es\"",mName.c_str());

	}
	void getEndFrame()
	{
		fprintf(mFile,"\"%s.ef\"",mName.c_str());

	}
	void getByFrame()
	{
		fprintf(mFile,"\"%s.bf\"",mName.c_str());

	}
	void getFieldIcons()
	{
		fprintf(mFile,"\"%s.fii\"",mName.c_str());

	}
	void getStartFrame()
	{
		fprintf(mFile,"\"%s.sf\"",mName.c_str());

	}
	void getGrid()
	{
		fprintf(mFile,"\"%s.gr\"",mName.c_str());

	}
	void getLightIcons()
	{
		fprintf(mFile,"\"%s.li\"",mName.c_str());

	}
	void getLineSmoothing()
	{
		fprintf(mFile,"\"%s.ls\"",mName.c_str());

	}
	void getMotionBlur()
	{
		fprintf(mFile,"\"%s.mb\"",mName.c_str());

	}
	void getTransformIcons()
	{
		fprintf(mFile,"\"%s.ti\"",mName.c_str());

	}
	void getTexturing()
	{
		fprintf(mFile,"\"%s.txt\"",mName.c_str());

	}
	void getMultiPassRendering()
	{
		fprintf(mFile,"\"%s.mpr\"",mName.c_str());

	}
	void getWriteZDepth()
	{
		fprintf(mFile,"\"%s.wzd\"",mName.c_str());

	}
	void getFilename()
	{
		fprintf(mFile,"\"%s.fn\"",mName.c_str());

	}
	void getImageFormat()
	{
		fprintf(mFile,"\"%s.if\"",mName.c_str());

	}
	void getResolution()
	{
		fprintf(mFile,"\"%s.res\"",mName.c_str());

	}
	void getAlphaSource()
	{
		fprintf(mFile,"\"%s.as\"",mName.c_str());

	}
	void getDrawStyle()
	{
		fprintf(mFile,"\"%s.ds\"",mName.c_str());

	}
	void getLightingMode()
	{
		fprintf(mFile,"\"%s.lm\"",mName.c_str());

	}
	void getFullImageResolution()
	{
		fprintf(mFile,"\"%s.fir\"",mName.c_str());

	}
	void getAntiAliasPolygons()
	{
		fprintf(mFile,"\"%s.aap\"",mName.c_str());

	}
	void getGeometryMask()
	{
		fprintf(mFile,"\"%s.gh\"",mName.c_str());

	}
	void getDisplayShadows()
	{
		fprintf(mFile,"\"%s.sd\"",mName.c_str());

	}
protected:
	HwRenderGlobals(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):DependNode(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_HWRENDERGLOBALS_H__
