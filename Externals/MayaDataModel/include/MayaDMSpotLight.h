/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_SPOTLIGHT_H__
#define __MayaDM_SPOTLIGHT_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMNonExtendedLightShapeNode.h"
namespace MayaDM
{
class SpotLight : public NonExtendedLightShapeNode
{
public:
	struct MentalRayControls{
		bool miExportMrLight;
		bool emitPhotons;
		float3 energy;
		float photonIntensity;
		float exponent;
		int causticPhotons;
		int globIllPhotons;
		bool shadowMap;
		int smapResolution;
		short smapSamples;
		float smapSoftness;
		float smapBias;
		string smapFilename;
		bool smapLightName;
		bool smapSceneName;
		bool smapFrameExt;
		bool smapDetail;
		short smapDetailSamples;
		float smapDetailAccuracy;
		bool smapDetailAlpha;
		bool areaLight;
		unsigned int areaType;
		float3 areaNormal;
		float3 areaEdge;
		float areaRadius;
		short2 areaSampling;
		short areaLowLevel;
		short2 areaLowSampling;
		bool areaVisible;
		void write(FILE* file) const
		{
			fprintf(file,"%i ", miExportMrLight);
			fprintf(file,"%i ", emitPhotons);
			energy.write(file);
			fprintf(file, " ");
			fprintf(file,"%f ", photonIntensity);
			fprintf(file,"%f ", exponent);
			fprintf(file,"%i ", causticPhotons);
			fprintf(file,"%i ", globIllPhotons);
			fprintf(file,"%i ", shadowMap);
			fprintf(file,"%i ", smapResolution);
			fprintf(file,"%i ", smapSamples);
			fprintf(file,"%f ", smapSoftness);
			fprintf(file,"%f ", smapBias);
			smapFilename.write(file);
			fprintf(file, " ");
			fprintf(file,"%i ", smapLightName);
			fprintf(file,"%i ", smapSceneName);
			fprintf(file,"%i ", smapFrameExt);
			fprintf(file,"%i ", smapDetail);
			fprintf(file,"%i ", smapDetailSamples);
			fprintf(file,"%f ", smapDetailAccuracy);
			fprintf(file,"%i ", smapDetailAlpha);
			fprintf(file,"%i ", areaLight);
			fprintf(file,"%i ", areaType);
			areaNormal.write(file);
			fprintf(file, " ");
			areaEdge.write(file);
			fprintf(file, " ");
			fprintf(file,"%f ", areaRadius);
			areaSampling.write(file);
			fprintf(file, " ");
			fprintf(file,"%i ", areaLowLevel);
			areaLowSampling.write(file);
			fprintf(file, " ");
			fprintf(file,"%i", areaVisible);
		}
	};
public:
	SpotLight(FILE* file,const std::string& name,const std::string& parent=""):NonExtendedLightShapeNode(file, name, parent, "spotLight"){}
	virtual ~SpotLight(){}
	void setConeAngle(double ca)
	{
		if(ca == 4) return;
		fprintf(mFile,"setAttr \".ca\" %f;\n", ca);

	}
	void setPenumbraAngle(double pa)
	{
		if(pa == 0) return;
		fprintf(mFile,"setAttr \".pa\" %f;\n", pa);

	}
	void setDropoff(double dro)
	{
		if(dro == 0.0) return;
		fprintf(mFile,"setAttr \".dro\" %f;\n", dro);

	}
	void setBarnDoors(bool bd)
	{
		if(bd == false) return;
		fprintf(mFile,"setAttr \".bd\" %i;\n", bd);

	}
	void setLeftBarnDoor(double lbd)
	{
		if(lbd == 2) return;
		fprintf(mFile,"setAttr \".lbd\" %f;\n", lbd);

	}
	void setRightBarnDoor(double rbd)
	{
		if(rbd == 2) return;
		fprintf(mFile,"setAttr \".rbd\" %f;\n", rbd);

	}
	void setTopBarnDoor(double tbd)
	{
		if(tbd == 2) return;
		fprintf(mFile,"setAttr \".tbd\" %f;\n", tbd);

	}
	void setBottomBarnDoor(double bbd)
	{
		if(bbd == 2) return;
		fprintf(mFile,"setAttr \".bbd\" %f;\n", bbd);

	}
	void setUseDecayRegions(bool udr)
	{
		if(udr == false) return;
		fprintf(mFile,"setAttr \".udr\" %i;\n", udr);

	}
	void setStartDistance1(float sd1)
	{
		if(sd1 == 1) return;
		fprintf(mFile,"setAttr \".sd1\" %f;\n", sd1);

	}
	void setEndDistance1(float ed1)
	{
		if(ed1 == 2) return;
		fprintf(mFile,"setAttr \".ed1\" %f;\n", ed1);

	}
	void setStartDistance2(float sd2)
	{
		if(sd2 == 3) return;
		fprintf(mFile,"setAttr \".sd2\" %f;\n", sd2);

	}
	void setEndDistance2(float ed2)
	{
		if(ed2 == 6) return;
		fprintf(mFile,"setAttr \".ed2\" %f;\n", ed2);

	}
	void setStartDistance3(float sd3)
	{
		if(sd3 == 8) return;
		fprintf(mFile,"setAttr \".sd3\" %f;\n", sd3);

	}
	void setEndDistance3(float ed3)
	{
		if(ed3 == 1) return;
		fprintf(mFile,"setAttr \".ed3\" %f;\n", ed3);

	}
	void setFogSpread(float fsp)
	{
		if(fsp == 1.0) return;
		fprintf(mFile,"setAttr \".fsp\" %f;\n", fsp);

	}
	void setFogIntensity(float fin)
	{
		if(fin == 1.0) return;
		fprintf(mFile,"setAttr \".fin\" %f;\n", fin);

	}
	void setObjectType(char ot)
	{
		if(ot == 1) return;
		fprintf(mFile,"setAttr \".ot\" %;\n", ot);

	}
	void setPointWorld(const float3& pw)
	{
		if(pw == float3(1.0f,1.0f,1.0f)) return;
		fprintf(mFile,"setAttr \".pw\" -type \"float3\" ");
		pw.write(mFile);
		fprintf(mFile,";\n");

	}
	void setPointWorldX(float tx)
	{
		if(tx == 0.0) return;
		fprintf(mFile,"setAttr \".pw.tx\" %f;\n", tx);

	}
	void setPointWorldY(float ty)
	{
		if(ty == 0.0) return;
		fprintf(mFile,"setAttr \".pw.ty\" %f;\n", ty);

	}
	void setPointWorldZ(float tz)
	{
		if(tz == 0.0) return;
		fprintf(mFile,"setAttr \".pw.tz\" %f;\n", tz);

	}
	void setFarPointWorld(const float3& fw)
	{
		if(fw == float3(1.0f,1.0f,1.0f)) return;
		fprintf(mFile,"setAttr \".fw\" -type \"float3\" ");
		fw.write(mFile);
		fprintf(mFile,";\n");

	}
	void setFarPointWorldX(float fx)
	{
		if(fx == 0.0) return;
		fprintf(mFile,"setAttr \".fw.fx\" %f;\n", fx);

	}
	void setFarPointWorldY(float fy)
	{
		if(fy == 0.0) return;
		fprintf(mFile,"setAttr \".fw.fy\" %f;\n", fy);

	}
	void setFarPointWorldZ(float fz)
	{
		if(fz == 0.0) return;
		fprintf(mFile,"setAttr \".fw.fz\" %f;\n", fz);

	}
	void setPsIllumSamples(short pis)
	{
		if(pis == 1) return;
		fprintf(mFile,"setAttr \".pis\" %i;\n", pis);

	}
	void setMentalRayControls(const MentalRayControls& mrc)
	{
		fprintf(mFile,"setAttr \".mrc\" ");
		mrc.write(mFile);
		fprintf(mFile,";\n");

	}
	void setMiExportMrLight(bool milt)
	{
		if(milt == false) return;
		fprintf(mFile,"setAttr \".mrc.milt\" %i;\n", milt);

	}
	void setEmitPhotons(bool phot)
	{
		if(phot == false) return;
		fprintf(mFile,"setAttr \".mrc.phot\" %i;\n", phot);

	}
	void setEnergy(const float3& eng)
	{
		fprintf(mFile,"setAttr \".mrc.eng\" -type \"float3\" ");
		eng.write(mFile);
		fprintf(mFile,";\n");

	}
	void setEnergyR(float engr)
	{
		if(engr == 8000) return;
		fprintf(mFile,"setAttr \".mrc.eng.engr\" %f;\n", engr);

	}
	void setEnergyG(float engg)
	{
		if(engg == 8000) return;
		fprintf(mFile,"setAttr \".mrc.eng.engg\" %f;\n", engg);

	}
	void setEnergyB(float engb)
	{
		if(engb == 8000) return;
		fprintf(mFile,"setAttr \".mrc.eng.engb\" %f;\n", engb);

	}
	void setPhotonIntensity(float phi)
	{
		if(phi == 1) return;
		fprintf(mFile,"setAttr \".mrc.phi\" %f;\n", phi);

	}
	void setExponent(float exp)
	{
		if(exp == 2) return;
		fprintf(mFile,"setAttr \".mrc.exp\" %f;\n", exp);

	}
	void setCausticPhotons(int cph)
	{
		if(cph == 10000) return;
		fprintf(mFile,"setAttr \".mrc.cph\" %i;\n", cph);

	}
	void setGlobIllPhotons(int gph)
	{
		if(gph == 10000) return;
		fprintf(mFile,"setAttr \".mrc.gph\" %i;\n", gph);

	}
	void setShadowMap(bool usm)
	{
		if(usm == false) return;
		fprintf(mFile,"setAttr \".mrc.usm\" %i;\n", usm);

	}
	void setSmapResolution(int smr)
	{
		if(smr == 256) return;
		fprintf(mFile,"setAttr \".mrc.smr\" %i;\n", smr);

	}
	void setSmapSamples(short smsa)
	{
		if(smsa == 1) return;
		fprintf(mFile,"setAttr \".mrc.smsa\" %i;\n", smsa);

	}
	void setSmapSoftness(float smso)
	{
		if(smso == 0) return;
		fprintf(mFile,"setAttr \".mrc.smso\" %f;\n", smso);

	}
	void setSmapBias(float smb)
	{
		if(smb == 0) return;
		fprintf(mFile,"setAttr \".mrc.smb\" %f;\n", smb);

	}
	void setSmapFilename(const string& smf)
	{
		if(smf == "NULL") return;
		fprintf(mFile,"setAttr \".mrc.smf\" -type \"string\" ");
		smf.write(mFile);
		fprintf(mFile,";\n");

	}
	void setSmapLightName(bool smln)
	{
		if(smln == 0) return;
		fprintf(mFile,"setAttr \".mrc.smln\" %i;\n", smln);

	}
	void setSmapSceneName(bool smsn)
	{
		if(smsn == 0) return;
		fprintf(mFile,"setAttr \".mrc.smsn\" %i;\n", smsn);

	}
	void setSmapFrameExt(bool smfe)
	{
		if(smfe == 0) return;
		fprintf(mFile,"setAttr \".mrc.smfe\" %i;\n", smfe);

	}
	void setSmapDetail(bool smd)
	{
		if(smd == 0) return;
		fprintf(mFile,"setAttr \".mrc.smd\" %i;\n", smd);

	}
	void setSmapDetailSamples(short sds)
	{
		if(sds == 0) return;
		fprintf(mFile,"setAttr \".mrc.sds\" %i;\n", sds);

	}
	void setSmapDetailAccuracy(float sdac)
	{
		if(sdac == 0) return;
		fprintf(mFile,"setAttr \".mrc.sdac\" %f;\n", sdac);

	}
	void setSmapDetailAlpha(bool sdal)
	{
		if(sdal == 0) return;
		fprintf(mFile,"setAttr \".mrc.sdal\" %i;\n", sdal);

	}
	void setAreaLight(bool algt)
	{
		if(algt == false) return;
		fprintf(mFile,"setAttr \".mrc.algt\" %i;\n", algt);

	}
	void setAreaType(unsigned int atyp)
	{
		if(atyp == 0) return;
		fprintf(mFile,"setAttr \".mrc.atyp\" %i;\n", atyp);

	}
	void setAreaNormal(const float3& ano)
	{
		fprintf(mFile,"setAttr \".mrc.ano\" -type \"float3\" ");
		ano.write(mFile);
		fprintf(mFile,";\n");

	}
	void setAreaNormalX(float anox)
	{
		if(anox == 0) return;
		fprintf(mFile,"setAttr \".mrc.ano.anox\" %f;\n", anox);

	}
	void setAreaNormalY(float anoy)
	{
		if(anoy == 2) return;
		fprintf(mFile,"setAttr \".mrc.ano.anoy\" %f;\n", anoy);

	}
	void setAreaNormalZ(float anoz)
	{
		if(anoz == 0) return;
		fprintf(mFile,"setAttr \".mrc.ano.anoz\" %f;\n", anoz);

	}
	void setAreaEdge(const float3& aed)
	{
		fprintf(mFile,"setAttr \".mrc.aed\" -type \"float3\" ");
		aed.write(mFile);
		fprintf(mFile,";\n");

	}
	void setAreaEdgeX(float aedx)
	{
		if(aedx == 2) return;
		fprintf(mFile,"setAttr \".mrc.aed.aedx\" %f;\n", aedx);

	}
	void setAreaEdgeY(float aedy)
	{
		if(aedy == 0) return;
		fprintf(mFile,"setAttr \".mrc.aed.aedy\" %f;\n", aedy);

	}
	void setAreaEdgeZ(float aedz)
	{
		if(aedz == 0) return;
		fprintf(mFile,"setAttr \".mrc.aed.aedz\" %f;\n", aedz);

	}
	void setAreaRadius(float arad)
	{
		if(arad == 2) return;
		fprintf(mFile,"setAttr \".mrc.arad\" %f;\n", arad);

	}
	void setAreaSampling(const short2& asa)
	{
		fprintf(mFile,"setAttr \".mrc.asa\" -type \"short2\" ");
		asa.write(mFile);
		fprintf(mFile,";\n");

	}
	void setAreaSamplingU(short asau)
	{
		if(asau == 3) return;
		fprintf(mFile,"setAttr \".mrc.asa.asau\" %i;\n", asau);

	}
	void setAreaSamplingV(short asav)
	{
		if(asav == 3) return;
		fprintf(mFile,"setAttr \".mrc.asa.asav\" %i;\n", asav);

	}
	void setAreaLowLevel(short alev)
	{
		if(alev == 0) return;
		fprintf(mFile,"setAttr \".mrc.alev\" %i;\n", alev);

	}
	void setAreaLowSampling(const short2& alo)
	{
		fprintf(mFile,"setAttr \".mrc.alo\" -type \"short2\" ");
		alo.write(mFile);
		fprintf(mFile,";\n");

	}
	void setAreaLowSamplingU(short alou)
	{
		if(alou == 2) return;
		fprintf(mFile,"setAttr \".mrc.alo.alou\" %i;\n", alou);

	}
	void setAreaLowSamplingV(short alov)
	{
		if(alov == 2) return;
		fprintf(mFile,"setAttr \".mrc.alo.alov\" %i;\n", alov);

	}
	void setAreaVisible(bool avis)
	{
		if(avis == false) return;
		fprintf(mFile,"setAttr \".mrc.avis\" %i;\n", avis);

	}
	void getConeAngle()
	{
		fprintf(mFile,"\"%s.ca\"",mName.c_str());

	}
	void getPenumbraAngle()
	{
		fprintf(mFile,"\"%s.pa\"",mName.c_str());

	}
	void getDropoff()
	{
		fprintf(mFile,"\"%s.dro\"",mName.c_str());

	}
	void getBarnDoors()
	{
		fprintf(mFile,"\"%s.bd\"",mName.c_str());

	}
	void getLeftBarnDoor()
	{
		fprintf(mFile,"\"%s.lbd\"",mName.c_str());

	}
	void getRightBarnDoor()
	{
		fprintf(mFile,"\"%s.rbd\"",mName.c_str());

	}
	void getTopBarnDoor()
	{
		fprintf(mFile,"\"%s.tbd\"",mName.c_str());

	}
	void getBottomBarnDoor()
	{
		fprintf(mFile,"\"%s.bbd\"",mName.c_str());

	}
	void getUseDecayRegions()
	{
		fprintf(mFile,"\"%s.udr\"",mName.c_str());

	}
	void getStartDistance1()
	{
		fprintf(mFile,"\"%s.sd1\"",mName.c_str());

	}
	void getEndDistance1()
	{
		fprintf(mFile,"\"%s.ed1\"",mName.c_str());

	}
	void getStartDistance2()
	{
		fprintf(mFile,"\"%s.sd2\"",mName.c_str());

	}
	void getEndDistance2()
	{
		fprintf(mFile,"\"%s.ed2\"",mName.c_str());

	}
	void getStartDistance3()
	{
		fprintf(mFile,"\"%s.sd3\"",mName.c_str());

	}
	void getEndDistance3()
	{
		fprintf(mFile,"\"%s.ed3\"",mName.c_str());

	}
	void getFogSpread()
	{
		fprintf(mFile,"\"%s.fsp\"",mName.c_str());

	}
	void getFogIntensity()
	{
		fprintf(mFile,"\"%s.fin\"",mName.c_str());

	}
	void getFogGeometry()
	{
		fprintf(mFile,"\"%s.fg\"",mName.c_str());

	}
	void getLightGlow()
	{
		fprintf(mFile,"\"%s.lg\"",mName.c_str());

	}
	void getPsIllumSamples()
	{
		fprintf(mFile,"\"%s.pis\"",mName.c_str());

	}
	void getMentalRayControls()
	{
		fprintf(mFile,"\"%s.mrc\"",mName.c_str());

	}
	void getMiExportMrLight()
	{
		fprintf(mFile,"\"%s.mrc.milt\"",mName.c_str());

	}
	void getMiLightShader()
	{
		fprintf(mFile,"\"%s.mrc.mils\"",mName.c_str());

	}
	void getMiPhotonEmitter()
	{
		fprintf(mFile,"\"%s.mrc.mipe\"",mName.c_str());

	}
	void getEmitPhotons()
	{
		fprintf(mFile,"\"%s.mrc.phot\"",mName.c_str());

	}
	void getEnergy()
	{
		fprintf(mFile,"\"%s.mrc.eng\"",mName.c_str());

	}
	void getEnergyR()
	{
		fprintf(mFile,"\"%s.mrc.eng.engr\"",mName.c_str());

	}
	void getEnergyG()
	{
		fprintf(mFile,"\"%s.mrc.eng.engg\"",mName.c_str());

	}
	void getEnergyB()
	{
		fprintf(mFile,"\"%s.mrc.eng.engb\"",mName.c_str());

	}
	void getPhotonIntensity()
	{
		fprintf(mFile,"\"%s.mrc.phi\"",mName.c_str());

	}
	void getExponent()
	{
		fprintf(mFile,"\"%s.mrc.exp\"",mName.c_str());

	}
	void getCausticPhotons()
	{
		fprintf(mFile,"\"%s.mrc.cph\"",mName.c_str());

	}
	void getGlobIllPhotons()
	{
		fprintf(mFile,"\"%s.mrc.gph\"",mName.c_str());

	}
	void getShadowMap()
	{
		fprintf(mFile,"\"%s.mrc.usm\"",mName.c_str());

	}
	void getSmapResolution()
	{
		fprintf(mFile,"\"%s.mrc.smr\"",mName.c_str());

	}
	void getSmapSamples()
	{
		fprintf(mFile,"\"%s.mrc.smsa\"",mName.c_str());

	}
	void getSmapSoftness()
	{
		fprintf(mFile,"\"%s.mrc.smso\"",mName.c_str());

	}
	void getSmapBias()
	{
		fprintf(mFile,"\"%s.mrc.smb\"",mName.c_str());

	}
	void getSmapCamera()
	{
		fprintf(mFile,"\"%s.mrc.smc\"",mName.c_str());

	}
	void getSmapFilename()
	{
		fprintf(mFile,"\"%s.mrc.smf\"",mName.c_str());

	}
	void getSmapLightName()
	{
		fprintf(mFile,"\"%s.mrc.smln\"",mName.c_str());

	}
	void getSmapSceneName()
	{
		fprintf(mFile,"\"%s.mrc.smsn\"",mName.c_str());

	}
	void getSmapFrameExt()
	{
		fprintf(mFile,"\"%s.mrc.smfe\"",mName.c_str());

	}
	void getSmapDetail()
	{
		fprintf(mFile,"\"%s.mrc.smd\"",mName.c_str());

	}
	void getSmapDetailSamples()
	{
		fprintf(mFile,"\"%s.mrc.sds\"",mName.c_str());

	}
	void getSmapDetailAccuracy()
	{
		fprintf(mFile,"\"%s.mrc.sdac\"",mName.c_str());

	}
	void getSmapDetailAlpha()
	{
		fprintf(mFile,"\"%s.mrc.sdal\"",mName.c_str());

	}
	void getAreaLight()
	{
		fprintf(mFile,"\"%s.mrc.algt\"",mName.c_str());

	}
	void getAreaType()
	{
		fprintf(mFile,"\"%s.mrc.atyp\"",mName.c_str());

	}
	void getAreaNormal()
	{
		fprintf(mFile,"\"%s.mrc.ano\"",mName.c_str());

	}
	void getAreaNormalX()
	{
		fprintf(mFile,"\"%s.mrc.ano.anox\"",mName.c_str());

	}
	void getAreaNormalY()
	{
		fprintf(mFile,"\"%s.mrc.ano.anoy\"",mName.c_str());

	}
	void getAreaNormalZ()
	{
		fprintf(mFile,"\"%s.mrc.ano.anoz\"",mName.c_str());

	}
	void getAreaEdge()
	{
		fprintf(mFile,"\"%s.mrc.aed\"",mName.c_str());

	}
	void getAreaEdgeX()
	{
		fprintf(mFile,"\"%s.mrc.aed.aedx\"",mName.c_str());

	}
	void getAreaEdgeY()
	{
		fprintf(mFile,"\"%s.mrc.aed.aedy\"",mName.c_str());

	}
	void getAreaEdgeZ()
	{
		fprintf(mFile,"\"%s.mrc.aed.aedz\"",mName.c_str());

	}
	void getAreaRadius()
	{
		fprintf(mFile,"\"%s.mrc.arad\"",mName.c_str());

	}
	void getAreaSampling()
	{
		fprintf(mFile,"\"%s.mrc.asa\"",mName.c_str());

	}
	void getAreaSamplingU()
	{
		fprintf(mFile,"\"%s.mrc.asa.asau\"",mName.c_str());

	}
	void getAreaSamplingV()
	{
		fprintf(mFile,"\"%s.mrc.asa.asav\"",mName.c_str());

	}
	void getAreaLowLevel()
	{
		fprintf(mFile,"\"%s.mrc.alev\"",mName.c_str());

	}
	void getAreaLowSampling()
	{
		fprintf(mFile,"\"%s.mrc.alo\"",mName.c_str());

	}
	void getAreaLowSamplingU()
	{
		fprintf(mFile,"\"%s.mrc.alo.alou\"",mName.c_str());

	}
	void getAreaLowSamplingV()
	{
		fprintf(mFile,"\"%s.mrc.alo.alov\"",mName.c_str());

	}
	void getAreaVisible()
	{
		fprintf(mFile,"\"%s.mrc.avis\"",mName.c_str());

	}
protected:
	SpotLight(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):NonExtendedLightShapeNode(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_SPOTLIGHT_H__
