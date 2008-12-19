/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_LAMBERT_H__
#define __MayaDM_LAMBERT_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMDependNode.h"
namespace MayaDM
{
class Lambert : public DependNode
{
public:
public:
	Lambert(FILE* file,const std::string& name,const std::string& parent=""):DependNode(file, name, parent, "lambert"){}
	virtual ~Lambert(){}
	void setRefractionLimit(short rdl)
	{
		if(rdl == 6) return;
		fprintf(mFile,"setAttr \".rdl\" %i;\n", rdl);

	}
	void setRefractiveIndex(float rfi)
	{
		if(rfi == 1.0) return;
		fprintf(mFile,"setAttr \".rfi\" %f;\n", rfi);

	}
	void setRefractions(bool rfc)
	{
		if(rfc == false) return;
		fprintf(mFile,"setAttr \".rfc\" %i;\n", rfc);

	}
	void setDiffuse(float dc)
	{
		if(dc == 0.8) return;
		fprintf(mFile,"setAttr \".dc\" %f;\n", dc);

	}
	void setColor(const float3& c)
	{
		fprintf(mFile,"setAttr \".c\" -type \"float3\" ");
		c.write(mFile);
		fprintf(mFile,";\n");

	}
	void setColorR(float cr)
	{
		if(cr == 0.5) return;
		fprintf(mFile,"setAttr \".c.cr\" %f;\n", cr);

	}
	void setColorG(float cg)
	{
		if(cg == 0.5) return;
		fprintf(mFile,"setAttr \".c.cg\" %f;\n", cg);

	}
	void setColorB(float cb)
	{
		if(cb == 0.5) return;
		fprintf(mFile,"setAttr \".c.cb\" %f;\n", cb);

	}
	void setTransparency(const float3& it)
	{
		fprintf(mFile,"setAttr \".it\" -type \"float3\" ");
		it.write(mFile);
		fprintf(mFile,";\n");

	}
	void setTransparencyR(float itr)
	{
		if(itr == 0.0) return;
		fprintf(mFile,"setAttr \".it.itr\" %f;\n", itr);

	}
	void setTransparencyG(float itg)
	{
		if(itg == 0.0) return;
		fprintf(mFile,"setAttr \".it.itg\" %f;\n", itg);

	}
	void setTransparencyB(float itb)
	{
		if(itb == 0.0) return;
		fprintf(mFile,"setAttr \".it.itb\" %f;\n", itb);

	}
	void setAmbientColor(const float3& ambc)
	{
		fprintf(mFile,"setAttr \".ambc\" -type \"float3\" ");
		ambc.write(mFile);
		fprintf(mFile,";\n");

	}
	void setAmbientColorR(float acr)
	{
		if(acr == 0.0) return;
		fprintf(mFile,"setAttr \".ambc.acr\" %f;\n", acr);

	}
	void setAmbientColorG(float acg)
	{
		if(acg == 0.0) return;
		fprintf(mFile,"setAttr \".ambc.acg\" %f;\n", acg);

	}
	void setAmbientColorB(float acb)
	{
		if(acb == 0.0) return;
		fprintf(mFile,"setAttr \".ambc.acb\" %f;\n", acb);

	}
	void setIncandescence(const float3& ic)
	{
		fprintf(mFile,"setAttr \".ic\" -type \"float3\" ");
		ic.write(mFile);
		fprintf(mFile,";\n");

	}
	void setIncandescenceR(float ir)
	{
		if(ir == 0.0) return;
		fprintf(mFile,"setAttr \".ic.ir\" %f;\n", ir);

	}
	void setIncandescenceG(float ig)
	{
		if(ig == 0.0) return;
		fprintf(mFile,"setAttr \".ic.ig\" %f;\n", ig);

	}
	void setIncandescenceB(float ib)
	{
		if(ib == 0.0) return;
		fprintf(mFile,"setAttr \".ic.ib\" %f;\n", ib);

	}
	void setTranslucence(float tc)
	{
		if(tc == 0.0) return;
		fprintf(mFile,"setAttr \".tc\" %f;\n", tc);

	}
	void setTranslucenceFocus(float tcf)
	{
		if(tcf == 0.5) return;
		fprintf(mFile,"setAttr \".tcf\" %f;\n", tcf);

	}
	void setTranslucenceDepth(float trsd)
	{
		if(trsd == 0.5) return;
		fprintf(mFile,"setAttr \".trsd\" %f;\n", trsd);

	}
	void setOpacityDepth(float opad)
	{
		if(opad == 0.0) return;
		fprintf(mFile,"setAttr \".opad\" %f;\n", opad);

	}
	void setGlowIntensity(float gi)
	{
		if(gi == 0.0) return;
		fprintf(mFile,"setAttr \".gi\" %f;\n", gi);

	}
	void setVrOverwriteDefaults(bool vrod)
	{
		if(vrod == 0) return;
		fprintf(mFile,"setAttr \".vrod\" %i;\n", vrod);

	}
	void setVrFillObject(unsigned int vrfo)
	{
		if(vrfo == 0) return;
		fprintf(mFile,"setAttr \".vrfo\" %i;\n", vrfo);

	}
	void setVrEdgeWeight(double vrew)
	{
		if(vrew == 0.0) return;
		fprintf(mFile,"setAttr \".vrew\" %f;\n", vrew);

	}
	void setVrEdgeColor(const float3& vrec)
	{
		fprintf(mFile,"setAttr \".vrec\" -type \"float3\" ");
		vrec.write(mFile);
		fprintf(mFile,";\n");

	}
	void setVrEdgeColorR(float vecr)
	{
		if(vecr == 0.5) return;
		fprintf(mFile,"setAttr \".vrec.vecr\" %f;\n", vecr);

	}
	void setVrEdgeColorG(float vecg)
	{
		if(vecg == 0.5) return;
		fprintf(mFile,"setAttr \".vrec.vecg\" %f;\n", vecg);

	}
	void setVrEdgeColorB(float vecb)
	{
		if(vecb == 0.5) return;
		fprintf(mFile,"setAttr \".vrec.vecb\" %f;\n", vecb);

	}
	void setVrEdgeStyle(unsigned int vres)
	{
		if(vres == 0) return;
		fprintf(mFile,"setAttr \".vres\" %i;\n", vres);

	}
	void setVrEdgePriority(int vrep)
	{
		if(vrep == 0) return;
		fprintf(mFile,"setAttr \".vrep\" %i;\n", vrep);

	}
	void setVrHiddenEdges(bool vrhe)
	{
		if(vrhe == 0) return;
		fprintf(mFile,"setAttr \".vrhe\" %i;\n", vrhe);

	}
	void setVrHiddenEdgesOnTransparent(bool vrht)
	{
		if(vrht == 0) return;
		fprintf(mFile,"setAttr \".vrht\" %i;\n", vrht);

	}
	void setVrOutlinesAtIntersections(bool vroi)
	{
		if(vroi == 1) return;
		fprintf(mFile,"setAttr \".vroi\" %i;\n", vroi);

	}
	void setMaterialAlphaGain(float maga)
	{
		if(maga == 1.0) return;
		fprintf(mFile,"setAttr \".maga\" %f;\n", maga);

	}
	void setHideSource(bool hs)
	{
		if(hs == false) return;
		fprintf(mFile,"setAttr \".hs\" %i;\n", hs);

	}
	void setSurfaceThickness(float thik)
	{
		if(thik == 0.0) return;
		fprintf(mFile,"setAttr \".thik\" %f;\n", thik);

	}
	void setShadowAttenuation(float fakc)
	{
		if(fakc == 0.5) return;
		fprintf(mFile,"setAttr \".fakc\" %f;\n", fakc);

	}
	void setTransparencyDepth(float trdp)
	{
		if(trdp == 0.0) return;
		fprintf(mFile,"setAttr \".trdp\" %f;\n", trdp);

	}
	void setLightAbsorbance(float absb)
	{
		if(absb == 0.0) return;
		fprintf(mFile,"setAttr \".absb\" %f;\n", absb);

	}
	void setChromaticAberration(bool crab)
	{
		if(crab == false) return;
		fprintf(mFile,"setAttr \".crab\" %i;\n", crab);

	}
	void setMatteOpacityMode(unsigned int mom)
	{
		if(mom == 2) return;
		fprintf(mFile,"setAttr \".mom\" %i;\n", mom);

	}
	void setMatteOpacity(float mog)
	{
		if(mog == 1.0) return;
		fprintf(mFile,"setAttr \".mog\" %f;\n", mog);

	}
	void setMiRefractionBlur(float mirfb)
	{
		if(mirfb == 0) return;
		fprintf(mFile,"setAttr \".mirfb\" %f;\n", mirfb);

	}
	void setMiRefractionRays(short mirfr)
	{
		if(mirfr == 1) return;
		fprintf(mFile,"setAttr \".mirfr\" %i;\n", mirfr);

	}
	void setMiIrradiance(const float3& mii)
	{
		fprintf(mFile,"setAttr \".mii\" -type \"float3\" ");
		mii.write(mFile);
		fprintf(mFile,";\n");

	}
	void setMiIrradianceR(float miir)
	{
		if(miir == 0) return;
		fprintf(mFile,"setAttr \".mii.miir\" %f;\n", miir);

	}
	void setMiIrradianceG(float miig)
	{
		if(miig == 0) return;
		fprintf(mFile,"setAttr \".mii.miig\" %f;\n", miig);

	}
	void setMiIrradianceB(float miib)
	{
		if(miib == 0) return;
		fprintf(mFile,"setAttr \".mii.miib\" %f;\n", miib);

	}
	void setMiIrradianceColor(const float3& miic)
	{
		fprintf(mFile,"setAttr \".miic\" -type \"float3\" ");
		miic.write(mFile);
		fprintf(mFile,";\n");

	}
	void setMiIrradianceColorR(float miicr)
	{
		if(miicr == 1) return;
		fprintf(mFile,"setAttr \".miic.miicr\" %f;\n", miicr);

	}
	void setMiIrradianceColorG(float miicg)
	{
		if(miicg == 1) return;
		fprintf(mFile,"setAttr \".miic.miicg\" %f;\n", miicg);

	}
	void setMiIrradianceColorB(float miicb)
	{
		if(miicb == 1) return;
		fprintf(mFile,"setAttr \".miic.miicb\" %f;\n", miicb);

	}
	void setMiDeriveFromMaya(bool mifm)
	{
		if(mifm == true) return;
		fprintf(mFile,"setAttr \".mifm\" %i;\n", mifm);

	}
	void setMiRefractiveIndex(float miri)
	{
		if(miri == 1) return;
		fprintf(mFile,"setAttr \".miri\" %f;\n", miri);

	}
	void setMiRefractions(bool mirc)
	{
		if(mirc == true) return;
		fprintf(mFile,"setAttr \".mirc\" %i;\n", mirc);

	}
	void setMiAbsorbs(bool miab)
	{
		if(miab == true) return;
		fprintf(mFile,"setAttr \".miab\" %i;\n", miab);

	}
	void setMiDiffuse(float midc)
	{
		if(midc == 0.8) return;
		fprintf(mFile,"setAttr \".midc\" %f;\n", midc);

	}
	void setMiColor(const float3& mic)
	{
		fprintf(mFile,"setAttr \".mic\" -type \"float3\" ");
		mic.write(mFile);
		fprintf(mFile,";\n");

	}
	void setMiColorR(float micr)
	{
		if(micr == 0.5) return;
		fprintf(mFile,"setAttr \".mic.micr\" %f;\n", micr);

	}
	void setMiColorG(float micg)
	{
		if(micg == 0.5) return;
		fprintf(mFile,"setAttr \".mic.micg\" %f;\n", micg);

	}
	void setMiColorB(float micb)
	{
		if(micb == 0.5) return;
		fprintf(mFile,"setAttr \".mic.micb\" %f;\n", micb);

	}
	void setMiTransparency(const float3& mit)
	{
		fprintf(mFile,"setAttr \".mit\" -type \"float3\" ");
		mit.write(mFile);
		fprintf(mFile,";\n");

	}
	void setMiTransparencyR(float mitr)
	{
		if(mitr == 0) return;
		fprintf(mFile,"setAttr \".mit.mitr\" %f;\n", mitr);

	}
	void setMiTransparencyG(float mitg)
	{
		if(mitg == 0) return;
		fprintf(mFile,"setAttr \".mit.mitg\" %f;\n", mitg);

	}
	void setMiTransparencyB(float mitb)
	{
		if(mitb == 0) return;
		fprintf(mFile,"setAttr \".mit.mitb\" %f;\n", mitb);

	}
	void setMiTranslucence(float mitc)
	{
		if(mitc == 0) return;
		fprintf(mFile,"setAttr \".mitc\" %f;\n", mitc);

	}
	void setMiTranslucenceFocus(float mitf)
	{
		if(mitf == 0.5) return;
		fprintf(mFile,"setAttr \".mitf\" %f;\n", mitf);

	}
	void setMiNormalCamera(const float3& minc)
	{
		fprintf(mFile,"setAttr \".minc\" -type \"float3\" ");
		minc.write(mFile);
		fprintf(mFile,";\n");

	}
	void setMiNormalCameraX(float mincx)
	{
		if(mincx == 0) return;
		fprintf(mFile,"setAttr \".minc.mincx\" %f;\n", mincx);

	}
	void setMiNormalCameraY(float mincy)
	{
		if(mincy == 0) return;
		fprintf(mFile,"setAttr \".minc.mincy\" %f;\n", mincy);

	}
	void setMiNormalCameraZ(float mincz)
	{
		if(mincz == 0) return;
		fprintf(mFile,"setAttr \".minc.mincz\" %f;\n", mincz);

	}
	void getRefractionLimit()
	{
		fprintf(mFile,"\"%s.rdl\"",mName.c_str());

	}
	void getRefractiveIndex()
	{
		fprintf(mFile,"\"%s.rfi\"",mName.c_str());

	}
	void getRefractions()
	{
		fprintf(mFile,"\"%s.rfc\"",mName.c_str());

	}
	void getDiffuse()
	{
		fprintf(mFile,"\"%s.dc\"",mName.c_str());

	}
	void getColor()
	{
		fprintf(mFile,"\"%s.c\"",mName.c_str());

	}
	void getColorR()
	{
		fprintf(mFile,"\"%s.c.cr\"",mName.c_str());

	}
	void getColorG()
	{
		fprintf(mFile,"\"%s.c.cg\"",mName.c_str());

	}
	void getColorB()
	{
		fprintf(mFile,"\"%s.c.cb\"",mName.c_str());

	}
	void getTransparency()
	{
		fprintf(mFile,"\"%s.it\"",mName.c_str());

	}
	void getTransparencyR()
	{
		fprintf(mFile,"\"%s.it.itr\"",mName.c_str());

	}
	void getTransparencyG()
	{
		fprintf(mFile,"\"%s.it.itg\"",mName.c_str());

	}
	void getTransparencyB()
	{
		fprintf(mFile,"\"%s.it.itb\"",mName.c_str());

	}
	void getAmbientColor()
	{
		fprintf(mFile,"\"%s.ambc\"",mName.c_str());

	}
	void getAmbientColorR()
	{
		fprintf(mFile,"\"%s.ambc.acr\"",mName.c_str());

	}
	void getAmbientColorG()
	{
		fprintf(mFile,"\"%s.ambc.acg\"",mName.c_str());

	}
	void getAmbientColorB()
	{
		fprintf(mFile,"\"%s.ambc.acb\"",mName.c_str());

	}
	void getIncandescence()
	{
		fprintf(mFile,"\"%s.ic\"",mName.c_str());

	}
	void getIncandescenceR()
	{
		fprintf(mFile,"\"%s.ic.ir\"",mName.c_str());

	}
	void getIncandescenceG()
	{
		fprintf(mFile,"\"%s.ic.ig\"",mName.c_str());

	}
	void getIncandescenceB()
	{
		fprintf(mFile,"\"%s.ic.ib\"",mName.c_str());

	}
	void getTranslucence()
	{
		fprintf(mFile,"\"%s.tc\"",mName.c_str());

	}
	void getTranslucenceFocus()
	{
		fprintf(mFile,"\"%s.tcf\"",mName.c_str());

	}
	void getTranslucenceDepth()
	{
		fprintf(mFile,"\"%s.trsd\"",mName.c_str());

	}
	void getOpacityDepth()
	{
		fprintf(mFile,"\"%s.opad\"",mName.c_str());

	}
	void getGlowIntensity()
	{
		fprintf(mFile,"\"%s.gi\"",mName.c_str());

	}
	void getVrOverwriteDefaults()
	{
		fprintf(mFile,"\"%s.vrod\"",mName.c_str());

	}
	void getVrFillObject()
	{
		fprintf(mFile,"\"%s.vrfo\"",mName.c_str());

	}
	void getVrEdgeWeight()
	{
		fprintf(mFile,"\"%s.vrew\"",mName.c_str());

	}
	void getVrEdgeColor()
	{
		fprintf(mFile,"\"%s.vrec\"",mName.c_str());

	}
	void getVrEdgeColorR()
	{
		fprintf(mFile,"\"%s.vrec.vecr\"",mName.c_str());

	}
	void getVrEdgeColorG()
	{
		fprintf(mFile,"\"%s.vrec.vecg\"",mName.c_str());

	}
	void getVrEdgeColorB()
	{
		fprintf(mFile,"\"%s.vrec.vecb\"",mName.c_str());

	}
	void getVrEdgeStyle()
	{
		fprintf(mFile,"\"%s.vres\"",mName.c_str());

	}
	void getVrEdgePriority()
	{
		fprintf(mFile,"\"%s.vrep\"",mName.c_str());

	}
	void getVrHiddenEdges()
	{
		fprintf(mFile,"\"%s.vrhe\"",mName.c_str());

	}
	void getVrHiddenEdgesOnTransparent()
	{
		fprintf(mFile,"\"%s.vrht\"",mName.c_str());

	}
	void getVrOutlinesAtIntersections()
	{
		fprintf(mFile,"\"%s.vroi\"",mName.c_str());

	}
	void getMaterialAlphaGain()
	{
		fprintf(mFile,"\"%s.maga\"",mName.c_str());

	}
	void getHideSource()
	{
		fprintf(mFile,"\"%s.hs\"",mName.c_str());

	}
	void getSurfaceThickness()
	{
		fprintf(mFile,"\"%s.thik\"",mName.c_str());

	}
	void getShadowAttenuation()
	{
		fprintf(mFile,"\"%s.fakc\"",mName.c_str());

	}
	void getTransparencyDepth()
	{
		fprintf(mFile,"\"%s.trdp\"",mName.c_str());

	}
	void getLightAbsorbance()
	{
		fprintf(mFile,"\"%s.absb\"",mName.c_str());

	}
	void getChromaticAberration()
	{
		fprintf(mFile,"\"%s.crab\"",mName.c_str());

	}
	void getOutColor()
	{
		fprintf(mFile,"\"%s.oc\"",mName.c_str());

	}
	void getOutColorR()
	{
		fprintf(mFile,"\"%s.oc.ocr\"",mName.c_str());

	}
	void getOutColorG()
	{
		fprintf(mFile,"\"%s.oc.ocg\"",mName.c_str());

	}
	void getOutColorB()
	{
		fprintf(mFile,"\"%s.oc.ocb\"",mName.c_str());

	}
	void getOutTransparency()
	{
		fprintf(mFile,"\"%s.ot\"",mName.c_str());

	}
	void getOutTransparencyR()
	{
		fprintf(mFile,"\"%s.ot.otr\"",mName.c_str());

	}
	void getOutTransparencyG()
	{
		fprintf(mFile,"\"%s.ot.otg\"",mName.c_str());

	}
	void getOutTransparencyB()
	{
		fprintf(mFile,"\"%s.ot.otb\"",mName.c_str());

	}
	void getOutGlowColor()
	{
		fprintf(mFile,"\"%s.ogc\"",mName.c_str());

	}
	void getOutGlowColorR()
	{
		fprintf(mFile,"\"%s.ogc.ogr\"",mName.c_str());

	}
	void getOutGlowColorG()
	{
		fprintf(mFile,"\"%s.ogc.ogg\"",mName.c_str());

	}
	void getOutGlowColorB()
	{
		fprintf(mFile,"\"%s.ogc.ogb\"",mName.c_str());

	}
	void getPointCamera()
	{
		fprintf(mFile,"\"%s.pc\"",mName.c_str());

	}
	void getPointCameraX()
	{
		fprintf(mFile,"\"%s.pc.px\"",mName.c_str());

	}
	void getPointCameraY()
	{
		fprintf(mFile,"\"%s.pc.py\"",mName.c_str());

	}
	void getPointCameraZ()
	{
		fprintf(mFile,"\"%s.pc.pz\"",mName.c_str());

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
	void getMatteOpacityMode()
	{
		fprintf(mFile,"\"%s.mom\"",mName.c_str());

	}
	void getMatteOpacity()
	{
		fprintf(mFile,"\"%s.mog\"",mName.c_str());

	}
	void getOutMatteOpacity()
	{
		fprintf(mFile,"\"%s.omo\"",mName.c_str());

	}
	void getOutMatteOpacityR()
	{
		fprintf(mFile,"\"%s.omo.omor\"",mName.c_str());

	}
	void getOutMatteOpacityG()
	{
		fprintf(mFile,"\"%s.omo.omog\"",mName.c_str());

	}
	void getOutMatteOpacityB()
	{
		fprintf(mFile,"\"%s.omo.omob\"",mName.c_str());

	}
	void getHardwareShader()
	{
		fprintf(mFile,"\"%s.hws\"",mName.c_str());

	}
	void getHardwareShaderR()
	{
		fprintf(mFile,"\"%s.hws.hwr\"",mName.c_str());

	}
	void getHardwareShaderG()
	{
		fprintf(mFile,"\"%s.hws.hwg\"",mName.c_str());

	}
	void getHardwareShaderB()
	{
		fprintf(mFile,"\"%s.hws.hwb\"",mName.c_str());

	}
	void getMiRefractionBlur()
	{
		fprintf(mFile,"\"%s.mirfb\"",mName.c_str());

	}
	void getMiRefractionRays()
	{
		fprintf(mFile,"\"%s.mirfr\"",mName.c_str());

	}
	void getMiIrradiance()
	{
		fprintf(mFile,"\"%s.mii\"",mName.c_str());

	}
	void getMiIrradianceR()
	{
		fprintf(mFile,"\"%s.mii.miir\"",mName.c_str());

	}
	void getMiIrradianceG()
	{
		fprintf(mFile,"\"%s.mii.miig\"",mName.c_str());

	}
	void getMiIrradianceB()
	{
		fprintf(mFile,"\"%s.mii.miib\"",mName.c_str());

	}
	void getMiIrradianceColor()
	{
		fprintf(mFile,"\"%s.miic\"",mName.c_str());

	}
	void getMiIrradianceColorR()
	{
		fprintf(mFile,"\"%s.miic.miicr\"",mName.c_str());

	}
	void getMiIrradianceColorG()
	{
		fprintf(mFile,"\"%s.miic.miicg\"",mName.c_str());

	}
	void getMiIrradianceColorB()
	{
		fprintf(mFile,"\"%s.miic.miicb\"",mName.c_str());

	}
	void getMiDeriveFromMaya()
	{
		fprintf(mFile,"\"%s.mifm\"",mName.c_str());

	}
	void getMiRefractiveIndex()
	{
		fprintf(mFile,"\"%s.miri\"",mName.c_str());

	}
	void getMiRefractions()
	{
		fprintf(mFile,"\"%s.mirc\"",mName.c_str());

	}
	void getMiAbsorbs()
	{
		fprintf(mFile,"\"%s.miab\"",mName.c_str());

	}
	void getMiDiffuse()
	{
		fprintf(mFile,"\"%s.midc\"",mName.c_str());

	}
	void getMiColor()
	{
		fprintf(mFile,"\"%s.mic\"",mName.c_str());

	}
	void getMiColorR()
	{
		fprintf(mFile,"\"%s.mic.micr\"",mName.c_str());

	}
	void getMiColorG()
	{
		fprintf(mFile,"\"%s.mic.micg\"",mName.c_str());

	}
	void getMiColorB()
	{
		fprintf(mFile,"\"%s.mic.micb\"",mName.c_str());

	}
	void getMiTransparency()
	{
		fprintf(mFile,"\"%s.mit\"",mName.c_str());

	}
	void getMiTransparencyR()
	{
		fprintf(mFile,"\"%s.mit.mitr\"",mName.c_str());

	}
	void getMiTransparencyG()
	{
		fprintf(mFile,"\"%s.mit.mitg\"",mName.c_str());

	}
	void getMiTransparencyB()
	{
		fprintf(mFile,"\"%s.mit.mitb\"",mName.c_str());

	}
	void getMiTranslucence()
	{
		fprintf(mFile,"\"%s.mitc\"",mName.c_str());

	}
	void getMiTranslucenceFocus()
	{
		fprintf(mFile,"\"%s.mitf\"",mName.c_str());

	}
	void getMiNormalCamera()
	{
		fprintf(mFile,"\"%s.minc\"",mName.c_str());

	}
	void getMiNormalCameraX()
	{
		fprintf(mFile,"\"%s.minc.mincx\"",mName.c_str());

	}
	void getMiNormalCameraY()
	{
		fprintf(mFile,"\"%s.minc.mincy\"",mName.c_str());

	}
	void getMiNormalCameraZ()
	{
		fprintf(mFile,"\"%s.minc.mincz\"",mName.c_str());

	}
protected:
	Lambert(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):DependNode(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_LAMBERT_H__
