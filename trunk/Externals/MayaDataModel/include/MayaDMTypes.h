/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MAYA_DM_TYPES_H__
#define __MAYA_DM_TYPES_H__

#include <assert.h>
#include <string>
#include <vector>

namespace MayaDM
{

/**
Array of two short integers
Value Syntax 	short short
Value Meaning 	value1 value2
Example 		setAttr node.short2Attr -type short2 1 2;
*/
struct short2
{
	short values[2];
	short2(short s1, short s2)
	{
		values[0] = s1;
		values[2] = s2;
	}
	short operator[](size_t i) const
	{
		assert( i < 2 );
		return values[i];
	}
	short& operator[](size_t i)
	{
		assert( i < 2 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file, "%i %i", values[0], values[1]);
	}
};

inline bool operator==(const short2& d1, const short2& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	return true;
}

/**
Array of three short integers
Value Syntax 	short short short
Value Meaning 	value1 value2 value3
Example 		setAttr node.short3Attr -type short3 1 2 3;
*/
struct short3
{
	short values[3];
	short operator[](size_t i) const
	{
		assert( i < 3 );
		return values[i];
	}
	short& operator[](size_t i)
	{
		assert( i < 3 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file, "%i %i %i", values[0], values[1], values[2]);
	}
};

inline bool operator==(const short3& d1, const short3& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	if(d1[2] != d2[2])
		return false;
	return true;
}

/**
Array of two long integers
Value Syntax 	long long
Value Meaning 	value1 value2
Example 		setAttr node.long2Attr -type long2 1000000 2000000;
*/
struct long2
{
	long values[2];
	long2(long l1, long l2)
	{
		 values[0]=l1;
		 values[1]=l2;
	}
	long operator[](size_t i) const
	{
		assert( i < 2 );
		return values[i];
	}
	long& operator[](size_t i)
	{
		assert( i < 2 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file, "%i %i", values[0], values[1]);
	}
};

inline bool operator==(const long2& d1, const long2& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	return true;
}

/**
Array of three long integers
Value Syntax 	long long long
Value Meaning 	value1 value2 value3
Example		 	setAttr node.long3Attr -type long3 1000000 2000000 3000000;
*/
struct long3
{
	long values[3];
	long3(long v1,long v2,long v3)
	{
		values[0]=v1;
		values[1]=v2;
		values[2]=v3;
	}
	long operator[](size_t i) const
	{
		assert( i < 3 );
		return values[i];
	}
	long& operator[](size_t i)
	{
		assert( i < 3 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file, "%i %i %i", values[0], values[1], values[2]);
	}
};

inline bool operator==(const long3& d1, const long3& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	if(d1[2] != d2[2])
		return false;
	return true;
}

/**
Variable length array of long integers
*/
struct int32Array
{
	size_t size;
	int* values;

	int32Array(size_t s):size(s), values(new int[s]){}
	~int32Array(){delete [] values;}

	int operator[](size_t i) const
	{
		assert( i < size );
		return values[i];
	}
	int& operator[](size_t i)
	{
		assert( i < size );
		return values[i];
	}
	void write(FILE* file) const
	{
		for(size_t i=0; i<size; ++i)
		{
			fprintf_s(file, "%i", values[i]);
			if(i+1<size) fprintf_s(file, " ");
		}		
	}
};

typedef int32Array intArray;

/**
Array of two floats
Value Syntax 	float float
Value Meaning 	value1 value2
Example 		setAttr node.float2Attr -type float2 1.1 2.2;
*/
struct float2
{
	float values[2];
	float2(float v1, float v2)
	{
		values[0] = v1;
		values[1] = v2;
	}
	float operator[](size_t i) const
	{
		assert( i < 2 );
		return values[i];
	}
	float& operator[](size_t i)
	{
		assert( i < 2 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file, "%f %f", values[0], values[1]);
	}
};

inline bool operator==(const float2& d1, const float2& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	return true;
}

/**
Array of three floats
Value Syntax 	float float float
Value Meaning 	value1 value2 value3
Example 		setAttr node.float3Attr -type float3 1.1 2.2 3.3;
*/
struct float3
{
	float values[3];
	float3(float v1,float v2,float v3)
	{
		values[0]=v1;
		values[1]=v2;
		values[2]=v3;
	}
	float operator[](size_t i) const
	{
		assert( i < 3 );
		return values[i];
	}
	float& operator[](size_t i)
	{
		assert( i < 3 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file, "%f %f %f", values[0], values[1], values[2]);
	}
};

inline bool operator==(const float3& d1, const float3& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	if(d1[2] != d2[2])
		return false;
	return true;
}

/**
Array of two doubles
Value Syntax 	double double
Value Meaning 	value1 value2
Example 		setAttr node.double2Attr -type double2 1.1 2.2;
*/
struct double2
{
	double values[2];
	double2( double d1, double d2)
	{
		values[0]=d1;
		values[0]=d2;
	}
	double operator[](size_t i) const
	{
		assert( i < 2 );
		return values[i];
	}
	double& operator[](size_t i)
	{
		assert( i < 2 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file, "%f %f", values[0], values[1]);
	}
};

inline bool operator==(const double2& d1, const double2& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	return true;
}

/**
Array of three doubles
Value Syntax 	double double double
Value Meaning 	value1 value2 value3
Example 		setAttr node.double3Attr -type double3 1.1 2.2 3.3;
*/
struct double3
{
	double values[3];
	double3(double val1, double val2, double val3)
	{
		values[0] = val1;
		values[1] = val2;
		values[2] = val3;
	}
	double operator[](size_t i) const
	{
		assert( i < 3 );
		return values[i];
	}
	double& operator[](size_t i)
	{
		assert( i < 3 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file,"%f %f %f", values[0], values[1], values[2]);
	}
};

inline bool operator==(const double3& d1, const double3& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	if(d1[2] != d2[2])
		return false;
	return true;
}
inline bool operator==(const double3& d1, double d)
{
	if(d1[0] != d)
		return false;
	if(d1[1] != d)
		return false;
	if(d1[2] != d)
		return false;
	return true;
}

/**
Array of three doubles
Value Syntax 	double double double
Value Meaning 	value1 value2 value3
Example 		setAttr node.double3Attr -type double3 1.1 2.2 3.3;
*/
struct double4
{
	double values[4];
	double operator[](size_t i) const
	{
		assert( i < 4 );
		return values[i];
	}
	double& operator[](size_t i)
	{
		assert( i < 4 );
		return values[i];
	}
	void write(FILE* file) const
	{
		fprintf_s(file,"%f %f %f %f", values[0], values[1], values[2], values[3]);
	}
};

inline bool operator==(const double4& d1, const double4& d2)
{
	if(d1[0] != d2[0])
		return false;
	if(d1[1] != d2[1])
		return false;
	if(d1[2] != d2[2])
		return false;
	if(d1[3] != d2[3])
		return false;
	return true;
}

/**
Variable length array of doubles
Value Syntax 	int {double}
Value Meaning 	numberOfArrayValues {arrayValue}
Example 		setAttr node.doubleArrayAttr -type doubleArray 2 3.14159 2.782;
*/
struct doubleArray
{
	size_t size;
	double* values;

	doubleArray(size_t s):size(s), values(new double[s]){}
	~doubleArray(){delete [] values;}

	double operator[](size_t i) const
	{
		assert( i < size );
		return values[i];
	}
	double& operator[](size_t i)
	{
		assert( i < size );
		return values[i];
	}
	void write(FILE* file) const
	{
		for(size_t i=0; i<size; ++i)
		{
			fprintf_s(file,"%f", values[i]);
			if(i+1<size) fprintf_s(file," ");
		}		
	}
};

/**
4x4 matrix of doubles

Value Syntax
	double double double double
	double double double double
	double double double double
	double double double double

Value Meaning
	row1col1 row1col2 row1col3 row1col4
	row2col1 row2col2 row2col3 row2col4
	row3col1 row3col2 row3col3 row3col4
	row4col1 row4col2 row4col3 row4col4

Alternate Syntax
	string double double double
	double double double
	integer
	double double double
	double double double
	double double double
	double double double
	double double double
	double double double
	double double double double
	double double double double
	double double double
	boolean

Alternate Meaning
	"xform" scaleX scaleY scaleZ
	rotateX rotateY rotateZ
	rotationOrder (0=XYZ, 1=YZX, 2=ZXY, 3=XZY, 4=YXZ, 5=ZYX)
	translateX translateY translateZ
	shearXY shearXZ shearYZ
	scalePivotX scalePivotY scalePivotZ
	scaleTranslationX scaleTranslationY scaleTranslationZ
	rotatePivotX rotatePivotY rotatePivotZ
	rotateTranslationX rotateTranslationY rotateTranslationZ
	rotateOrientW rotateOrientX rotateOrientY rotateOrientZ
	jointOrientW jointOrientX jointOrientY jointOrientZ
	inverseParentScaleX inverseParentScaleY inverseParentScaleZ
	compensateForParentScale

Example
	setAttr node.matrixAttr -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 2 3 4 1;
	setAttr node.matrixAttr -type "matrix" "xform" 1 1 1 0 0 0 0 2 3 4 0 0 0
		0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 1 0 1 0 1 1 1 0 false;
*/
struct matrix
{
	double m[ 4 ][ 4 ];
	matrix(double m00, double m01, double m02, double m03,
		   double m10, double m11, double m12, double m13,
		   double m20, double m21, double m22, double m23,
		   double m30, double m31, double m32, double m33)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;
		
		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;

		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}

	// member access, allows use of construct mat[r][c]
	inline double* operator[] ( size_t iRow ) const
	{
		assert(iRow < 4);
		return ( double* ) m[ iRow ];
	}

	void write(FILE* file) const
	{
		fprintf_s(file,"%f %f %f %f ", m[0][0], m[0][1], m[0][2], m[0][3]);
		fprintf_s(file,"%f %f %f %f ", m[1][0], m[1][1], m[1][2], m[1][3]);
		fprintf_s(file,"%f %f %f %f ", m[2][0], m[2][1], m[2][2], m[2][3]);
		fprintf_s(file,"%f %f %f %f", m[3][0], m[3][1], m[3][2], m[3][3]);
	}
};

const matrix identity(1,0,0,0,
					  0,1,0,0,
					  0,0,1,0,
					  0,0,0,1);

inline bool operator==(const matrix& m1, const matrix& m2)
{
	for(size_t r=0; r<4; ++r)
	{
		for(size_t c=0; c<4; ++c)
		{
			if(m1[r][c] != m2[r][c])
				return false;
		}
	}
	return true;
}

/**
Variable length array of points
Value Syntax 	int {double double double double}
Value Meaning 	numberOfArrayValues {xValue yValue zValue wValue}
Example 		setAttr node.pointArrayAttr -type pointArray 2 1 1 1 1 2 2 2 1;
*/
struct point
{
	double x;
	double y;
	double z;
	double w;
	void write(FILE* file) const
	{
		fprintf_s(file,"%f %f %f %f", x, y, z, w);
	}
};
struct pointArray
{
	size_t size;
	point* values;
	pointArray(size_t s):size(s), values(new point[s]){}
	~pointArray(){delete [] values;}
	point operator[](size_t i) const
	{
		assert( i < size );
		return values[i];
	}
	point& operator[](size_t i)
	{
		assert( i < size );
		return values[i];
	}
	void write(FILE* file) const
	{
		for(size_t i=0; i<size; ++i)
		{
			values[i].write(file);
			if(i+1<size) fprintf_s(file," ");
		}		
	}
};

/**
Variable length array of vectors
Value Syntax 	int {double double double}
Value Meaning 	numberOfArrayValues {xValue yValue zValue}
Example 		setAttr node.vectorArrayAttr -type vectorArray 2 1 1 1 2 2 2;
*/
struct vector
{
	double x;
	double y;
	double z;
	void write(FILE* file) const
	{
		fprintf_s(file,"%f %f %f %f", x, y, z);
	}
};
struct vectorArray
{
	size_t size;
	vector* values;
	vectorArray(size_t s):size(s), values(new vector[s]){}
	~vectorArray(){delete [] values;}
	vector operator[](size_t i) const
	{
		assert( i < size );
		return values[i];
	}
	vector& operator[](size_t i)
	{
		assert( i < size );
		return values[i];
	}
	void write(FILE* file) const
	{
		for(size_t i=0; i<size; ++i)
		{
			values[i].write(file);
			if(i+1<size) fprintf_s(file," ");
		}		
	}
};

/**
Character string
Value Syntax 	string
Value Meaning 	characterStringValue
Example 		setAttr node.stringAttr -type "string" "blarg";
*/
struct string
{
	std::string str;
	string(){}
	string(const char* cstr): str(cstr){}
	string(const std::string& s): str(s){}

	string& operator=(const char* cstr)
	{
		str = cstr;
		return *this;
	}
	string& operator=(const std::string& s)
	{
		str = s;
		return *this;
	}	
	const char* c_str()
	{
		return str.c_str();
	}
	void write(FILE* file) const
	{
		fprintf_s(file, "\"%s\"", str.c_str());
	}
};

inline bool operator==(const string& s1, const string& s2)
{
	return s1.str == s2.str;
}

/**
Variable length array of strings
Value Syntax 	int {string}
Value Meaning 	numberOfArrayValues {arrayValue}
Example 		setAttr node.stringArrayAttr -type stringArray 3 "a" "b" "c";
*/
struct stringArray
{
	size_t size;
	string* values;
	stringArray(size_t s):size(s), values(new string[s]){}
	~stringArray(){delete [] values;}
	string operator[](size_t i) const
	{
		assert( i < size );
		return values[i];
	}
	string& operator[](size_t i)
	{
		assert( i < size );
		return values[i];
	}
	void write(FILE* file) const
	{
		for(size_t i=0; i<size; ++i)
		{
			values[i].write(file);
			if(i+1<size) fprintf_s(file," ");
		}		
	}
};

/**
Sphere data
Value Syntax 	double
Value Meaning 	sphereRadius
Example 		setAttr node.sphereAttr -type sphere 5.0;
*/
struct sphere
{
	double radius;
	void write(FILE* file) const
	{
		fprintf_s(file,"%f", radius);
	}
};

/**
Cone data
Value Syntax 	double double
Value Meaning 	coneAngle coneCap
Example 		setAttr node.coneAttr -type cone 45.0 5.0;
*/
struct cone
{
	double coneAngle;
	double coneCap;
	void write(FILE* file) const
	{
		fprintf_s(file, "%f %f", coneAngle, coneCap);
	}
};

/**
Reflectance data
Value Syntax 	double double double
Value Meaning 	redReflect greenReflect blueReflect
Example 		setAttr node.reflectanceRGBAttr -type reflectanceRGB 0.5 0.5 0.1;
*/
struct reflectanceRGB
{
	double redReflect;
	double greenReflect;
	double blueReflect;
	void write(FILE* file) const
	{
		fprintf_s(file, "%f %f %f", redReflect, greenReflect, blueReflect);
	}
};

/**
Spectrum data
Value Syntax 	double double double
Value Meaning 	redSpectrum greenSpectrum blueSpectrum
Example 		setAttr node.spectrumRGBAttr -type spectrumRGB 0.5 0.5 0.1;
*/
struct spectrumRGB
{
	double redSpectrum;
	double greenSpectrum;
	double blueSpectrum;
	void write(FILE* file) const
	{
		fprintf_s(file, "%f %f %f", redSpectrum, greenSpectrum, blueSpectrum);
	}
};

/**
Variable length array of components
Value Syntax 	int {string}
Value Meaning 	numberOfComponents {componentName}
Example 		setAttr node.componentListAttr -type componentList 3 cv[1] cv[12] cv[3];
*/
class componentList : public std::vector<string>
{
public:
	componentList(){}
	componentList(size_t s):std::vector<string>(s){}
	~componentList(){}
	void write(FILE* file) const
	{
		fprintf_s(file,"%i ", size());
		for(size_t i=0; i<size(); ++i)
		{
			at(i).write(file);
			if(i+1<size()) fprintf_s(file," ");
		}		
	}
};

/**
NURBS curve data
Value Syntax
	int int int bool int int {double}
	int {double double double}
Value Meaning
	degree spans form isRational dimension knotCount {knotValue}
	cvCount {xCVValue yCVValue [zCVValue] [wCVValue]}

Example
	setAttr node.curveAttr -type nurbsCurve 3 1 0 no 3
		6 0 0 0 1 1 1
		4 -2 3 0 -2 1 0 -2 -1 0 -2 -3 0;
*/
struct nurbsCurve
{
	/** degree is the degree of the curve(range 1-7) */
	int degree;
	/** spans is the number of spans*/
	int spans;
	/** form is open (0), closed (1), periodic (2)*/
	int form;
	/** isRational is true if the curve CVs contain a rational component*/
	bool isRational;
	/**  dimension is 2 or 3, depending on the dimension of the curve*/
	int dimension;
	/** knotCount is the size of the knot list*/
	int knotCount;
	/** knotValue is a single entry in the knot list*/
	double* knotValues;
	/** cvCount is the number of CVs in the curve*/
	int cvCount;
	/**
	xCVValue,yCVValue,[zCVValue] [wCVValue] is a single CV.
	zCVValue is only present when dimension is 3.
	wCVValue is only present when isRational is true.
	*/
	double* cvValues;
	
	void write(FILE* file) const
	{
		fprintf_s(file,"%i %i %i %i %i %i ", degree, spans, form, isRational, dimension, knotCount);
		for(int i=0; i<knotCount; ++i)
		{
			fprintf_s(file, "%f ", knotValues[i]);
		}
		fprintf_s(file, "%i ", cvCount);
		size_t numElements = 2;		
		if(dimension == 3) numElements++;
		if(isRational) 	numElements++;
		size_t size = cvCount * numElements;
		for(size_t i=0; i<size; ++i)
		{
			fprintf_s(file, "%f", cvValues[i]);
			if(i+1<size) fprintf_s(file," ");
		}
	}
};

/**
NURBS surface data
Value Syntax 	
	int int int int bool
	int {double}
	int {double}
	[string] int {double double double}
Value Meaning
	uDegree vDegree uForm vForm isRational
	uKnotCount {uKnotValue}
	vKnotCount {vKnotValue} 
	["TRIM"|"NOTRIM"] cvCount {xCVValue yCVValue zCVValue [wCVValue]}
Example
	setAttr node.surfaceAttr -type nurbsSurface 3 3 0 0 no
		6 0 0 0 1 1 1
		6 0 0 0 1 1 1
		16 -2 3 0 -2 1 0 -2 -1 0 -2 -3 0
		-1 3 0 -1 1 0 -1 -1 0 -1 -3 0
		1 3 0 1 1 0 1 -1 0 1 -3 0
		3 3 0 3 1 0 3 -1 0 3 -3 0;
*/
struct nurbsSurface
{
	enum trimOpt {TRIM, NOTRIM};
	/** uDegree is degree of the surface in U direction (range 1-7)*/
	int uDegree;
	/** vDegree is degree of the surface in V direction (range 1-7)*/
	int vDegree;
	/** uForm is open (0), closed (1), periodic (2) in U direction*/
	int uForm;
	/** vForm is open (0), closed (1), periodic (2) in V direction*/
	int vForm;
	/** isRational is true if the surface CVs contain a rational component*/
	bool isRational;
	/** uKnotCount is the size of the U knot list*/
	int	uKnotCount;
	/** uKnotValue is a single entry in the U knot list*/
	double* uKnotValues;
	/** vKnotCount is the size of the V knot list*/
	int vKnotCount;
	/** vKnotValue is a single entry in the V knot list*/
	double* vKnotValues;
	/** If "TRIM" is specified then additional trim information is expected
	If "NOTRIM" is specified then the surface is not trimmed*/
	trimOpt trim;
	/** cvCount is the number of CVs in the surface*/
	int cvCount;
	/**
	xCVValue,yCVValue,zCVValue [wCVValue]is a single CV.
	zCVValue is only present when dimension is 3.
	wCVValue is only present when isRational is true
	*/
	double* cvValues;

	void write(FILE* file) const
	{
		fprintf_s(file,"%i %i %i %i %i %i ", uDegree, vDegree, uForm, vForm, isRational, uKnotCount);
		for(int i=0; i<uKnotCount; ++i)
		{
			fprintf_s(file, "%f ", uKnotValues[i]);
		}
		fprintf_s(file,"%i ", vKnotCount);
		for(int i=0; i<uKnotCount; ++i)
		{
			fprintf_s(file, "%f ", uKnotValues[i]);
		}	
		if(trim == TRIM){
			fprintf_s(file, "\"%s\" ", "TRIM");
		} else
		{
			fprintf_s(file, "\"%s\" ", "NOTRIM");
		}
		fprintf_s(file, "%i ", cvCount);
		size_t numElements = 3;		
		if(isRational) 	numElements++;
		size_t size = cvCount * numElements;
		for(size_t i=0; i<size; ++i)
		{
			fprintf_s(file, "%f", cvValues[i]);
			if(i+1<size) fprintf_s(file," ");
		}
	}
};
/**
NURBS trim face data

Value Syntax
	bool int {int {int {int int int} int {int int}}}
Value Meaning
	flipNormal boundaryCount {boundaryType tedgeCountOnBoundary
	{splineCountOnEdge {edgeTolerance isEdgeReversed geometricContinuity}
	{splineCountOnPedge {isMonotone pedgeTolerance}}}
*/
struct nurbsTrimface
{
	/** flipNormal if true turns the surface inside out*/
	bool flipNormal;
	/** boundaryCount: number of boundaries*/
	int boundaryCount;
	
	struct boundary {
		int boundaryType;
		/** tedgeCountOnBoundary : number of edges in a boundary*/
		int tedgeCountOnBoundary;
		struct edge {
			/** splineCountOnEdge : number of splines in an edge in*/
			int splineCountOnEdge;
			struct splineOnEdge {
				/** edgeTolerance : tolerance used to build the 3d edge*/
				int edgeTolerance;
				/** isEdgeReversed : if true, the edge is backwards*/
				int isEdgeReversed;
				/** geometricContinuity : if true, the edge is tangent continuous*/
				int geometricContinuity;
				
				void write(FILE* file) const
				{
					fprintf_s(file, "%i %i %i", edgeTolerance, isEdgeReversed, geometricContinuity);
				}
			} *splinesOnEdge;
			
			/** splineCountOnPedge : number of splines in a 2d edge*/
			int	splineCountOnPedge;
			struct splineOnPedge {
				/** isMonotone : if true, curvature is monotone*/
				int isMonotone;
				/** pedgeTolerance : tolerance for the 2d edge*/
				int	pedgeTolerance;
			
				void write(FILE* file) const
				{
					fprintf_s(file, "%i %i", isMonotone, pedgeTolerance);
				}
			} *splinesOnPedge;

			void write(FILE* file) const
			{
				fprintf_s(file,"%i ", splineCountOnEdge);
				for(int i=0; i<splineCountOnEdge; ++i)
				{
					splinesOnEdge[i].write(file);
					if(i+1<splineCountOnEdge) fprintf_s(file, " ");
				}
				fprintf_s(file,"%i ", splineCountOnPedge);
				for(int i=0; i<splineCountOnPedge; ++i)
				{
					splinesOnPedge[i].write(file);
					if(i+1<splineCountOnPedge) fprintf_s(file, " ");
				}
			}
		} *edges;

		void write(FILE* file) const
		{
			fprintf_s(file,"%i %i ", boundaryType, tedgeCountOnBoundary);
			for(int i=0; i<tedgeCountOnBoundary; ++i)
			{
				edges[i].write(file);
				if(i+1<tedgeCountOnBoundary) fprintf_s(file, " ");
			}
		}
	} *boundaries;

	void write(FILE* file) const
	{
		fprintf_s(file,"%i %i ", flipNormal, boundaryCount);
		for(int i=0; i<boundaryCount; ++i)
		{
			boundaries[i].write(file);
			if(i+1<boundaryCount) fprintf_s(file, " ");
		}
	}
};

/**
Polygon face data

This data type (polyFace) is meant to be used in file I/O
after setAttrs have been written out for vertex position
arrays, edge connectivity arrays (with corresponding start
and end vertex descriptions), texture coordinate arrays and
color arrays. The reason is that this data type references
all of its data through ids created by the former types.

Value Syntax
	{"f" int {int}}
	{"h" int {int}}
	{"mf" int {int}}
	{"mh" int {int}}
	{"mu" int int {int}}
	{"fc" int {int}}

Value Meaning
	{"f" faceEdgeCount {edgeIdValue}}
	{"h" holeEdgeCount {edgeIdValue}}
	{"mf" faceUVCount {uvIdValue}}
	{"mh" holeUVCount {uvIdValue}}
	{"mu" uvSet faceUVCount {uvIdValue}}
	{"fc" faceColorCount {colorIndexValue}}

Example:
	setAttr node.polyFaceAttr -type polyFaces "f" 3 1 2 3 "fc" 3 4 4 6;
*/
struct polyFaces
{
	/**
	"f" specifies the ids of the edges making up a face -
	negative value if the edge is reversed in the face

	Format: {"f" faceEdgeCount {edgeIdValue}}
	*/
	struct F{
		int faceEdgeCount;
		int* edgeIdValue;

		void write(FILE* file) const
		{
			fprintf_s(file,"\"f\" %i ", faceEdgeCount);
			for(int i=0; i<faceEdgeCount; ++i)
			{
				fprintf_s(file,"%i", edgeIdValue[i]);
				if(i+1<faceEdgeCount) fprintf_s(file, " ");
			}
		}
	}f;

	/**
	"h" specifies the ids of the edges making up a hole -
	negative value if the edge is reversed in the face

	Format: {"h" holeEdgeCount {edgeIdValue}}
	*/
	struct H{
		int holeEdgeCount;
		int* edgeIdValue;

		void write(FILE* file) const
		{
			fprintf_s(file,"\"h\" %i ", holeEdgeCount);
			for(int i=0; i<holeEdgeCount; ++i)
			{
				fprintf_s(file,"%i", edgeIdValue[i]);
				if(i+1<holeEdgeCount) fprintf_s(file, " ");
			}
		}
	}h;

	/**
	"mf" specifies the ids of texture coordinates (uvs) for a face. 
	This data type is obsolete as of version 3.0. It is replaced by "mu".

	Format: {"mf" faceUVCount {uvIdValue}}
	*/
	struct MF{
		int faceUVCount;
		int* uvIdValue;

		void write(FILE* file) const
		{
			fprintf_s(file,"\"mf\" %i ", faceUVCount);
			for(int i=0; i<faceUVCount; ++i)
			{
				fprintf_s(file,"%i", uvIdValue[i]);
				if(i+1<faceUVCount) fprintf_s(file, " ");
			}
		}
	}mf;


	/**
	"mh" specifies the ids of texture coordinates (uvs) for a hole
	This data type is obsolete as of version 3.0. It is replaced by "mu".

	Format: {"mh" holeUVCount {uvIdValue}}
	*/
	struct MH{
		int holeUVCount;
		int* uvIdValue;

		void write(FILE* file) const
		{
			fprintf_s(file,"\"mh\" %i ", holeUVCount);
			for(int i=0; i<holeUVCount; ++i)
			{
				fprintf_s(file,"%i", uvIdValue[i]);
				if(i+1<holeUVCount) fprintf_s(file, " ");
			}
		}
	}mh;

	/**
	"mu" The first argument refers to the uv set. This is a zero-based
	integer number. The second argument refers to the number of vertices (n)
	on the face which have valid uv values. The last n values are the uv
	ids of the texture coordinates (uvs) for the face. These indices
	are what used to be represented by the "mf" and "mh" specification.
	There may be more than one "mu" specification, one for each unique uv set.

	Format: {"mu" uvSet faceUVCount {uvIdValue}}
	*/
	struct MU{
		int uvSet;
		int faceUVCount;
		int* uvIdValue;

		void write(FILE* file) const
		{
			fprintf_s(file,"\"mu\" %i ", uvSet);
			fprintf_s(file,"%i ", faceUVCount);
			for(int i=0; i<faceUVCount; ++i)
			{
				fprintf_s(file,"%i", uvIdValue[i]);
				if(i+1<faceUVCount) fprintf_s(file, " ");
			}
		}
	}mu;

	/**
	"fc" specifies the color index values for a face

	Format: {"fc" faceColorCount {colorIndexValue}}
	*/
	struct FC{
		int faceColorCount;
		int* colorIndexValue;
		
		void write(FILE* file) const
		{
			fprintf_s(file,"\"fc\" %i ", faceColorCount);
			for(int i=0; i<faceColorCount; ++i)
			{
				fprintf_s(file,"%i", colorIndexValue[i]);
				if(i+1<faceColorCount) fprintf_s(file, " ");
			}
		}
	}fc;

	polyFaces()
	{
		f.faceEdgeCount = 0;
		f.edgeIdValue = 0;
		h.holeEdgeCount = 0;
		h.edgeIdValue = 0;
		mf.faceUVCount = 0;
		mf.uvIdValue = 0;
		mh.holeUVCount = 0;
		mh.uvIdValue = 0;
		mu.faceUVCount = 0;
		mu.uvSet = 0;
		mu.uvIdValue = 0;
		fc.faceColorCount = 0;
		fc.colorIndexValue = 0;
	}
	~polyFaces()
	{
		
		delete [] f.edgeIdValue;
		delete [] h.edgeIdValue;
		delete [] mf.uvIdValue;
		delete [] mh.uvIdValue;
		delete [] mu.uvIdValue;
	}

	void write(FILE* file) const
	{
		if(f.faceEdgeCount)
		{
			f.write(file);			
		}
		if(h.holeEdgeCount)
		{
			fprintf_s(file, " ");
			h.write(file);
			
		}
		if(mf.faceUVCount)
		{
			fprintf_s(file, " ");
			mf.write(file);			
		}
		if(mh.holeUVCount)
		{
			fprintf_s(file, " ");
			mh.write(file);			
		}
		if(mu.faceUVCount)
		{
			fprintf_s(file, " ");
			mu.write(file);			
		}
		if(fc.faceColorCount)
		{
			fprintf_s(file, " ");
			fc.write(file);
		}		
	}
};

/**
Polygonal mesh

Value Syntax
	{string [int {double double double}]}
	{string [int {double double double}]}
	[{string [int {double double}]}]
	{string [int {double double string}]}

Value Meaning
	"v" [vertexCount {vertexX vertexY vertexZ}]
	"vn" [normalCount {normalX normalY normalZ}]
	["vt" [uvCount {uValue vValue}]]
	"e" [edgeCount {startVertex endVertex "smooth"|"hard"}]

Example
	setAttr node.meshAttr -type mesh "v" 3 0 0 0 0 1 0 0 0 1
		"vn" 3 1 0 0 1 0 0 1 0 0
		"vt" 3 0 0 0 1 1 0
		"e" 3 0 1 "hard" 1 2 "hard" 2 0 "hard";
*/
struct mesh 
{
	/** "v" specifies the vertices of the polygonal mesh*/
	struct 
	{
		int vertexCount;
		double* vertices;

		void write(FILE* file) const
		{
			fprintf_s(file,"\"v\" %i ", vertexCount);
			size_t size = vertexCount * 3;
			for(size_t i=0; i<size; ++i)
			{
				fprintf_s(file,"%f", vertices[i]);
				if(i+1<size) fprintf_s(file," ");
			}
		}
	}v;

	/** "vn" specifies the normal of each vertex*/
	struct  
	{
		int normalCount;
		double* normals;

		void write(FILE* file) const
		{
			fprintf_s(file,"\"vn\" %i ", normalCount);
			size_t size = normalCount * 3;
			for(size_t i=0; i<size; ++i)
			{
				fprintf_s(file,"%f", normals[i]);
				if(i+1<size) fprintf_s(file," ");
			}
		}
	}vn;

	/** "vt" is optional and specifies a U,V texture coordinate for each vertex*/
	struct  
	{
		int uvCount;
		double* uvValues;

		void write(FILE* file) const
		{
			fprintf_s(file,"\"vt\" %i ", uvCount);
			size_t size = uvCount * 2;
			for(size_t i=0; i<size; ++i)
			{
				fprintf_s(file,"%f", uvValues[i]);
				if(i+1<size) fprintf_s(file," ");
			}
		}
	}vt;

	/** "e" specifies the edge connectivity information between vertices*/
	struct 
	{
		int edgeCount;
		struct edge
		{
			enum edgeType
			{
				SMOOTH, HARD
			};
			double startVertex;
			double endVertex;
			edgeType type; 

			void write(FILE* file) const
			{
				fprintf_s(file, "%f %f ", startVertex, endVertex);
				if(type == HARD)
				{
					fprintf_s(file, "\"hard\"");	
				}else
				{
					fprintf_s(file, "\"smooth\"");	
				}
			}
		}*edges;
		
		void write(FILE* file) const
		{
			fprintf_s(file,"\"e\" %i ", edgeCount);
			for(int i=0; i<edgeCount; ++i)
			{
				edges[i].write(file);
				if(i+1<edgeCount) fprintf_s(file," ");
			}
		}
	}e;

	void write(FILE* file) const
	{
		if(v.vertexCount)
		{
			v.write(file);
			fprintf_s(file, " ");
		}
		if(vn.normalCount)
		{
			vn.write(file);
			fprintf_s(file, " ");
		}
		if(vt.uvCount)
		{
			vt.write(file);
			fprintf_s(file, " ");
		}
		if(e.edgeCount)
		{
			v.write(file);
			fprintf_s(file, " ");
		}
	}
};

/**
Lattice data

Value Syntax
	int int int int
	{double double double}

Value Meaning
	sDivisionCount tDivisionCount uDivisionCount pointCount
	{pointX pointY pointZ}

Example
	setAttr node.latticeAttr -type lattice 2 5 2 20
		-2 -2 -2 2 -2 -2 -2 -1 -2 2 -1 -2 -2 0 -2
		2 0 -2 -2 1 -2 2 1 -2 -2 2 -2 2 2 -2
		-2 -2 2 2 -2 2 -2 -1 2 2 -1 2 -2 0 2
		2 0 2 -2 1 2 2 1 2 -2 2 2 2 2 2;
*/
struct lattice
{
	/** sDivisionCount is the horizontal lattice division count*/
	int sDivisionCount;
	/** tDivisionCount is the vertical lattice division count*/
	int tDivisionCount;
	/** uDivisionCount is the depth lattice division count*/
	int uDivisionCount;
	/** pointCount is the total number of lattice points*/
	int	pointCount;
	/** pointX,pointY,pointZ is one lattice point. The list is
	specified varying first in S, then in T, last in U so the
	first two entries are (S=0,T=0,U=0) (s=1,T=0,U=0)
	*/
	double* points;

	void write(FILE* file) const
	{
		fprintf_s(file,"%i %i %i %i ", sDivisionCount, tDivisionCount, uDivisionCount, pointCount);
		size_t size = pointCount*3;
		for(size_t i; i<size; ++i)
		{
			fprintf_s(file, "%f", points[i]);
			if(i+1<size) fprintf_s(file, " ");
		}
	}
};

// Predefined variables
const bool on=true;
const bool off=false;
const bool yes=true;
const bool no=false;

}//namespace MayaDM
#endif // __MAYA_DM_TYPES_H__