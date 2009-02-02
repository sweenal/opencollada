/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_CHARACTER_H__
#define __MayaDM_CHARACTER_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMObjectSet.h"
namespace MayaDM
{
class Character : public ObjectSet
{
public:
	struct ClipEvaluate{
		struct ClipEvaluate_Inmap{
			short clipEvaluate_InmapTo;
			short clipEvaluate_InmapFrom;
			void write(FILE* file) const
			{
				fprintf(file,"%i ", clipEvaluate_InmapTo);
				fprintf(file,"%i", clipEvaluate_InmapFrom);
			}
		}* clipEvaluate_Inmap;
		struct ClipEvaluate_Outmap{
			short clipEvaluate_OutmapTo;
			short clipEvaluate_OutmapFrom;
			void write(FILE* file) const
			{
				fprintf(file,"%i ", clipEvaluate_OutmapTo);
				fprintf(file,"%i", clipEvaluate_OutmapFrom);
			}
		}* clipEvaluate_Outmap;
		void write(FILE* file) const
		{
			size_t size = sizeof(clipEvaluate_Inmap)/sizeof(ClipEvaluate_Inmap);
			for(size_t i=0; i<size; ++i)
			{
				clipEvaluate_Inmap[i].write(file);
				fprintf(file, " ");
				if(i+1<size) fprintf(file," ");
			}
			size = sizeof(clipEvaluate_Outmap)/sizeof(ClipEvaluate_Outmap);
			for(size_t i=0; i<size; ++i)
			{
				clipEvaluate_Outmap[i].write(file);
				if(i+1<size) fprintf(file," ");
			}
		}
	};
public:
	Character(FILE* file,const std::string& name,const std::string& parent=""):ObjectSet(file, name, parent, "character"){}
	virtual ~Character(){}
	void setClipEvaluate(const ClipEvaluate& ce)
	{
		fprintf(mFile,"setAttr \".ce\" ");
		ce.write(mFile);
		fprintf(mFile,";\n");

	}
	void setClipEvaluate_Inmap(size_t cei_i,const ClipEvaluate::ClipEvaluate_Inmap& cei)
	{
		fprintf(mFile,"setAttr \".ce.cei[%i]\" ",cei_i);
		cei.write(mFile);
		fprintf(mFile,";\n");

	}
	void setClipEvaluate_InmapTo(size_t cei_i,short ceit)
	{
		if(ceit == 0) return;
		fprintf(mFile,"setAttr \".ce.cei[%i].ceit\" %i;\n", cei_i,ceit);

	}
	void setClipEvaluate_InmapFrom(size_t cei_i,short ceif)
	{
		if(ceif == 0) return;
		fprintf(mFile,"setAttr \".ce.cei[%i].ceif\" %i;\n", cei_i,ceif);

	}
	void setClipEvaluate_Outmap(size_t ceo_i,const ClipEvaluate::ClipEvaluate_Outmap& ceo)
	{
		fprintf(mFile,"setAttr \".ce.ceo[%i]\" ",ceo_i);
		ceo.write(mFile);
		fprintf(mFile,";\n");

	}
	void setClipEvaluate_OutmapTo(size_t ceo_i,short ceot)
	{
		if(ceot == 0) return;
		fprintf(mFile,"setAttr \".ce.ceo[%i].ceot\" %i;\n", ceo_i,ceot);

	}
	void setClipEvaluate_OutmapFrom(size_t ceo_i,short ceof)
	{
		if(ceof == 0) return;
		fprintf(mFile,"setAttr \".ce.ceo[%i].ceof\" %i;\n", ceo_i,ceof);

	}
	void setUnitlessValues(size_t uv_i,double uv)
	{
		if(uv == 0.0) return;
		fprintf(mFile,"setAttr \".uv[%i]\" %f;\n", uv_i,uv);

	}
	void setUnitlessValues(size_t uv_start,size_t uv_end,double* uv)
	{
		fprintf(mFile,"setAttr \".uv[%i:%i]\" ", uv_start,uv_end);
		size_t size = (uv_end-uv_start)*1+1;
		for(size_t i=0;i<size;++i)
		{
			fprintf(mFile,"%f",uv[i]);
			if(i+1<size) fprintf(mFile," ");
		}
		fprintf(mFile,";\n");

	}
	void startUnitlessValues(size_t uv_start,size_t uv_end)
	{
		fprintf(mFile,"setAttr \".uv[%i:%i]\"",uv_start,uv_end);

	}
	void appendUnitlessValues(double uv)
	{
		fprintf(mFile," %f",uv);

	}
	void endUnitlessValues()
	{
		fprintf(mFile,";\n");

	}
	void setLinearValues(size_t lv_i,double lv)
	{
		if(lv == 0) return;
		fprintf(mFile,"setAttr \".lv[%i]\" %f;\n", lv_i,lv);

	}
	void setLinearValues(size_t lv_start,size_t lv_end,double* lv)
	{
		fprintf(mFile,"setAttr \".lv[%i:%i]\" ", lv_start,lv_end);
		size_t size = (lv_end-lv_start)*1+1;
		for(size_t i=0;i<size;++i)
		{
			fprintf(mFile,"%f",lv[i]);
			if(i+1<size) fprintf(mFile," ");
		}
		fprintf(mFile,";\n");

	}
	void startLinearValues(size_t lv_start,size_t lv_end)
	{
		fprintf(mFile,"setAttr \".lv[%i:%i]\"",lv_start,lv_end);

	}
	void appendLinearValues(double lv)
	{
		fprintf(mFile," %f",lv);

	}
	void endLinearValues()
	{
		fprintf(mFile,";\n");

	}
	void setAngularValues(size_t av_i,double av)
	{
		if(av == 0) return;
		fprintf(mFile,"setAttr \".av[%i]\" %f;\n", av_i,av);

	}
	void setAngularValues(size_t av_start,size_t av_end,double* av)
	{
		fprintf(mFile,"setAttr \".av[%i:%i]\" ", av_start,av_end);
		size_t size = (av_end-av_start)*1+1;
		for(size_t i=0;i<size;++i)
		{
			fprintf(mFile,"%f",av[i]);
			if(i+1<size) fprintf(mFile," ");
		}
		fprintf(mFile,";\n");

	}
	void startAngularValues(size_t av_start,size_t av_end)
	{
		fprintf(mFile,"setAttr \".av[%i:%i]\"",av_start,av_end);

	}
	void appendAngularValues(double av)
	{
		fprintf(mFile," %f",av);

	}
	void endAngularValues()
	{
		fprintf(mFile,";\n");

	}
	void setClipIndexMap(const intArray& cim)
	{
		if(cim.size == 0) return;
		fprintf(mFile,"setAttr \".cim\" -type \"intArray\" ");
		cim.write(mFile);
		fprintf(mFile,";\n");

	}
	void setActiveClipConnected(bool acc)
	{
		if(acc == 0) return;
		fprintf(mFile,"setAttr \".acc\" %i;\n", acc);

	}
	void getClipEvaluate()
	{
		fprintf(mFile,"\"%s.ce\"",mName.c_str());

	}
	void getClipEvaluate_Raw()
	{
		fprintf(mFile,"\"%s.ce.cer\"",mName.c_str());

	}
	void getClipEvaluate_Inmap(size_t cei_i)
	{
		fprintf(mFile,"\"%s.ce.cei[%i]\"",mName.c_str(),cei_i);

	}
	void getClipEvaluate_InmapTo(size_t cei_i)
	{
		fprintf(mFile,"\"%s.ce.cei[%i].ceit\"",mName.c_str(),cei_i);

	}
	void getClipEvaluate_InmapFrom(size_t cei_i)
	{
		fprintf(mFile,"\"%s.ce.cei[%i].ceif\"",mName.c_str(),cei_i);

	}
	void getClipEvaluate_Outmap(size_t ceo_i)
	{
		fprintf(mFile,"\"%s.ce.ceo[%i]\"",mName.c_str(),ceo_i);

	}
	void getClipEvaluate_OutmapTo(size_t ceo_i)
	{
		fprintf(mFile,"\"%s.ce.ceo[%i].ceot\"",mName.c_str(),ceo_i);

	}
	void getClipEvaluate_OutmapFrom(size_t ceo_i)
	{
		fprintf(mFile,"\"%s.ce.ceo[%i].ceof\"",mName.c_str(),ceo_i);

	}
	void getUnitlessValues(size_t uv_i)
	{
		fprintf(mFile,"\"%s.uv[%i]\"",mName.c_str(),uv_i);

	}
	void getLinearValues(size_t lv_i)
	{
		fprintf(mFile,"\"%s.lv[%i]\"",mName.c_str(),lv_i);

	}
	void getAngularValues(size_t av_i)
	{
		fprintf(mFile,"\"%s.av[%i]\"",mName.c_str(),av_i);

	}
	void getTimeValues(size_t tv_i)
	{
		fprintf(mFile,"\"%s.tv[%i]\"",mName.c_str(),tv_i);

	}
	void getAnimationMapping()
	{
		fprintf(mFile,"\"%s.am\"",mName.c_str());

	}
	void getReferenceMapping()
	{
		fprintf(mFile,"\"%s.rm\"",mName.c_str());

	}
	void getOffsetNode()
	{
		fprintf(mFile,"\"%s.ofn\"",mName.c_str());

	}
protected:
	Character(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):ObjectSet(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_CHARACTER_H__