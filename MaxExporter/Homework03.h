/**********************************************************************
 *<
	FILE: Homework03.h

	DESCRIPTION:	Includes for Plugins

	CREATED BY:

	HISTORY:

 *>	Copyright (c) 2003, All Rights Reserved.
 **********************************************************************/

#ifndef __Homework03__H
#define __Homework03__H

#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "decomp.h"
#include "stdmat.h"
#include "modstack.h"
#include "ISkin.h"    // Native skin modifier (since Max 4.2 )
#include "iFnPub.h" // Function publishing (script exposure.)

#include "..\tinyxml\\tinyxml.h"
#include "DynArray.h"
//SIMPLE TYPE



extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;



class TiXmlElement_Transform 
{
public:
	TiXmlElement* TM;
	TiXmlElement* row1;
	TiXmlElement* row2;
	TiXmlElement* row3;
	TiXmlElement* row4;
	
	TiXmlElement_Transform(){};
	~TiXmlElement_Transform(){};
	//TiXmlElement_Transform(TiXmlElement* _tm=NULL,TiXmlElement* r1=NULL,TiXmlElement* r2=NULL,TiXmlElement* r3=NULL,TiXmlElement* r4=NULL);
	void SetElementsT(TiXmlElement* _tm=NULL,TiXmlElement* r1=NULL,TiXmlElement* r2=NULL,TiXmlElement* r3=NULL,TiXmlElement* r4=NULL);
	void LinkElements();
};


class TiXmlElement_Triangle 
{
public:
	TiXmlElement*   WedgeIndex;//頂點編號
	TiXmlElement*	UVCoords;
	TiXmlElement*   MatIndex;
	TiXmlElement*   SmoothingGroups; 

	TCHAR* mapName;
	char  materialName[30];
	void SetElementsT(TiXmlElement* wedgeIndex=NULL,TiXmlElement* matIndex=NULL,TiXmlElement* SmGroups=NULL);
	void LinkElements();

};

struct VVertex //貼圖座標頂點
{
public:
	WORD	PointIndex;	
	FLOAT   U,V;         
};
class TiXmlElement_BoneInfluence_PerVertex
{
public:
	//TiXmlElement* weightTag;
	TArray<TiXmlElement*> InfluenceSet;
};



class TiXmlElement_Model
{
public:
	TiXmlElement* pointsTag;//包覆的標籤
	TiXmlElement* MaterialsTag;
	TiXmlElement* TextureTag;
	TiXmlElement* FacesTag;
	TiXmlElement* RefBonesTag;

	TArray<TiXmlElement*> Materials;//names only
	TArray<TiXmlElement*> Textures;
	TArray<TiXmlElement*> Points;
	//TArray<TiXmlElement*> Normal;
	TArray<TiXmlElement_Triangle*> Faces;
	TArray<TiXmlElement_BoneInfluence_PerVertex*> RefBones;

	TiXmlElement_Model(){};
	~TiXmlElement_Model(){};
	//void SetElementsT(TiXmlElement_Triangle* faces=NULL,TiXmlElement_BoneInfluence* RefBones=NULL);
	void LinkElements();
};


class TiXmlElement_Animation
{
public:
	TArray<TiXmlElement*> FrameTag;//包覆的標籤

	TiXmlElement_Animation(){};
	~TiXmlElement_Animation(){};
	void LinkElements();
};

#endif
