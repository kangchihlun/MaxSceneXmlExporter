/**********************************************************************
 *<
	FILE: Homework03.cpp

	DESCRIPTION:	Appwizard generated plugin

	CREATED BY: 

	HISTORY: 

 *>	Copyright (c) 2003, All Rights Reserved.
 **********************************************************************/

#include "Homework03.h"

#define Homework03_CLASS_ID	Class_ID(0xbed240e5, 0x773fc7e1)

#define VISUAL_EXPORT		 0x00000002
#define MODEL_EXPORT		 0x00000004
#define ANIMATION_EXPORT     0x00000008

unsigned int ExportMode = VISUAL_EXPORT|MODEL_EXPORT;


class Homework03 : public SceneExport {
	public:
		
		static HWND hParams;
		
		int				ExtCount();					// Number of extensions supported
		const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
		const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
		const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
		const TCHAR *	AuthorName();				// ASCII Author name
		const TCHAR *	CopyrightMessage();			// ASCII Copyright message
		const TCHAR *	OtherMessage1();			// Other message #1
		const TCHAR *	OtherMessage2();			// Other message #2
		unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
		void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
		BOOL			bSupressDialogBox;			// 新增的，壓制對話框不彈出
		
		TArray<INode*> ModelNodes ;
		BOOL SupportsOptions(int ext, DWORD options);

		Modifier* FindMaxSkinModifier( INode* nodePtr);
		int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);

		int				SaveFile(const TCHAR *filename, ExpInterface *ei, Interface *gi, Homework03 *exp);

		//// 新增的，輸出動態
		TArray<INode*>  SerialTree;
		void			CreateSerialTree(INode* inNode);
		TiXmlElement_Animation*			ExportAnimation();
		Matrix3 Uniform_Matrix(Matrix3 orig_cur_mat);
		Matrix3 Get_Relative_Matrix(INode *node, int t);

		void			ExportSkeleton(INode* pNode, int iTreeDepth ,TiXmlElement* pNextElement);
		TiXmlElement_Transform*	CreateNodeTMElement(INode* pNode, int iTreeDepth, TimeValue t =0);
		int DigestMaterial(INode *node,  INT matIndex,TCHAR * mapName,char* matName);	
		TiXmlElement_Model*		ExportModel(INode* pNode, TiXmlElement* pNextElement);
		//Constructor/Destructor
		Homework03();
		~Homework03();		

};



class Homework03ClassDesc : public ClassDesc2 {
	public:
	int 			IsPublic() { return TRUE; }
	void *			Create(BOOL loading = FALSE) { return new Homework03(); }
	const TCHAR *	ClassName() { return GetString(IDS_CLASS_NAME); }
	SClass_ID		SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	Class_ID		ClassID() { return Homework03_CLASS_ID; }
	const TCHAR* 	Category() { return GetString(IDS_CATEGORY); }

	const TCHAR*	InternalName() { return _T("Homework03"); }	// returns fixed parsable name (scripter-visible name)
	HINSTANCE		HInstance() { return hInstance; }					// returns owning module handle
	

};

static Homework03		   MyMaxExp;
static Homework03ClassDesc Homework03Desc;
ClassDesc2* GetHomework03Desc() { return &Homework03Desc; }




INT_PTR CALLBACK Homework03OptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static Homework03 *imp = NULL;
	int check;
	switch(message) {
		case WM_INITDIALOG:
				imp = (Homework03 *)lParam;
				CenterWindow(hWnd,GetParent(hWnd));
				CheckDlgButton(hWnd, IDC_MODEL, 1);
				CheckDlgButton(hWnd, IDC_VISUAL, 1);
				CheckDlgButton(hWnd, IDC_ANIMATION, 0);
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_MODEL:
					 ExportMode ^= MODEL_EXPORT;
					 check=(ExportMode&MODEL_EXPORT)!=0?1:0;
					 CheckDlgButton(hWnd, IDC_MODEL,check );
					 break;
 				case IDC_ANIMATION:
					 ExportMode ^= ANIMATION_EXPORT;
					 check=(ExportMode&ANIMATION_EXPORT)!=0?1:0;
					 CheckDlgButton(hWnd, IDC_ANIMATION, check);
					 break;
				case IDC_VISUAL:
					 ExportMode ^= VISUAL_EXPORT;
					 check=(ExportMode&VISUAL_EXPORT)!=0?1:0;
					 CheckDlgButton(hWnd, IDC_VISUAL, check);
					 break;
		        case IDC_CANCEL:
					 EndDialog(hWnd, 0);
					 return TRUE ;
					 break;
				case IDC_ExportModel:
					  EndDialog(hWnd, 1);
					  return TRUE;
					break;
					
			}	
				break;
		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
		
			
	}
	return 0;
}


//--- Homework03 -------------------------------------------------------
Homework03::Homework03()
{

}

Homework03::~Homework03() 
{

}

int Homework03::ExtCount()
{
	//TODO: Returns the number of file name extensions supported by the plug-in.
	return 1;
}

const TCHAR *Homework03::Ext(int n)
{		
	//TODO: Return the 'i-th' file name extension (i.e. "3DS").
	return _T("model");
}

const TCHAR *Homework03::LongDesc()
{
	//TODO: Return long ASCII description (i.e. "Targa 2.0 Image File")
	return _T("homework03 demo ");
}
	
const TCHAR *Homework03::ShortDesc() 
{			
	//TODO: Return short ASCII description (i.e. "Targa")
	return _T("homework03");
}

const TCHAR *Homework03::AuthorName()
{			
	//TODO: Return ASCII Author name
	return _T("KangChihLun");
}

const TCHAR *Homework03::CopyrightMessage() 
{	
	// Return ASCII Copyright message
	return _T("na");
}

const TCHAR *Homework03::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *Homework03::OtherMessage2() 
{		
	//TODO: Return other message #2 in any
	return _T("");
}

unsigned int Homework03::Version()
{				
	//TODO: Return Version number * 100 (i.e. v3.01 = 301)
	return 3;
}

void Homework03::ShowAbout(HWND hWnd)
{			
	// Optional
}

BOOL Homework03::SupportsOptions(int ext, DWORD options)
{
	// TODO Decide which options to support.  Simply return
	// true for each option supported by each Extension 
	// the exporter supports.

	return TRUE;
}


int	Homework03::DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{
   int status;
   float timePerFrame = (float) GetTicksPerFrame();
   status = SaveFile(name, ei, i, this);

   if (status == 0) {
      return 1;         // Dialog cancelled
   }
   else if (status < 0) {
      return 0;         // Real, honest-to-goodness error
   }
   else {
      return(status);
   }

}

int Homework03::SaveFile(const TCHAR *filename, ExpInterface *ei, Interface *gi, Homework03 *exp)
{
	if(!bSupressDialogBox)
	{
		BOOL beOK = DialogBox(hInstance, MAKEINTRESOURCE(IDD_PANEL), 0, Homework03OptionsDlgProc);
		if (!beOK) return (0);
	}
	{
		ModelNodes.Empty();
		/*
		StartWriting
		*/
		char drive[128], dir[128], name[128], path[128];
		_splitpath(filename, drive, dir, name, NULL);
		//拆出三種副檔名

		if(ExportMode & ANIMATION_EXPORT )
		{
			_makepath( path, drive, dir, name, "animation" );
			TiXmlDocument *g_Doc = new TiXmlDocument(); 
			if (NULL==g_Doc)  
			{  
				return false;  
			}
			TiXmlDeclaration *pDeclaration = new TiXmlDeclaration(_T("1.0"),_T(""),_T(""));  
			if (NULL==pDeclaration)  
			{  
				return false;  
			}  
			g_Doc->LinkEndChild(pDeclaration);
			TiXmlElement *pRootEle = new TiXmlElement(_T("Animation"));
			g_Doc->LinkEndChild(pRootEle);

			
			TiXmlElement_Animation* AnimStruct = ExportAnimation();
			for(int i = 0;i<AnimStruct->FrameTag.Num();i++)
			{
				pRootEle->LinkEndChild( AnimStruct->FrameTag[i] );
			}
			
			g_Doc->SaveFile(path); 
		}
		if(ExportMode & VISUAL_EXPORT )
		{
			_makepath( path, drive, dir, name, "visual" );
			TiXmlDocument *g_Doc = new TiXmlDocument(); 
			if (NULL==g_Doc)  
			{  
				return false;  
			}
			TiXmlDeclaration *pDeclaration = new TiXmlDeclaration(_T("1.0"),_T(""),_T(""));  
			if (NULL==pDeclaration)  
			{  
				return false;  
			}  
			g_Doc->LinkEndChild(pDeclaration);

			//寫入骨架資訊
			TiXmlElement *pRootEle = new TiXmlElement(_T("Skeleton"));
			g_Doc->LinkEndChild(pRootEle);
			INode* pRootNode = gi->GetRootNode();
			//Export tree.
			ExportSkeleton(pRootNode,0,pRootEle);
			g_Doc->SaveFile(path);  
		}
		if( ExportMode & MODEL_EXPORT )
		{
			_makepath( path, drive, dir, name, "model" );
			TiXmlDocument *g_Doc = new TiXmlDocument(); 
			if (NULL==g_Doc)  
			{  
				return false;  
			}
			TiXmlDeclaration *pDeclaration = new TiXmlDeclaration(_T("1.0"),_T(""),_T(""));  
			if (NULL==pDeclaration)  
			{  
				return false;  
			}  
			g_Doc->LinkEndChild(pDeclaration);

			//寫入模型資訊
			TiXmlElement *pModelEle = new TiXmlElement(_T("Model"));
			g_Doc->LinkEndChild(pModelEle);
			int ModelNum=ModelNodes.Num();
			for(int i = 0;i<ModelNodes.Num();i++)
			{
				TCHAR* fName = ModelNodes[i]->GetName();
				TiXmlElement_Model* ModelStruct = ExportModel(ModelNodes[i],pModelEle);
				ModelStruct->LinkElements();
				pModelEle->LinkEndChild(ModelStruct->pointsTag);
				pModelEle->LinkEndChild(ModelStruct->RefBonesTag);
				pModelEle->LinkEndChild(ModelStruct->FacesTag);
			}
			g_Doc->SaveFile(path);  
		}
		return TRUE; // We have successfully exported to our file!
	}	
	return (1);
}



void Homework03::ExportSkeleton(INode* pNode, int iTreeDepth ,TiXmlElement* pNextElement)
{
	TCHAR* pNodeName = pNode->GetName();
	int nChildren = pNode->NumberOfChildren();
	ObjectState os = pNode->EvalWorldState(0);
	bool bInSkeleton=FALSE;
	if (os.obj)
	{
		//判斷是不是模型，模型跳過
		Class_ID currentID = os.obj->ClassID();
		if( (currentID != EPOLYOBJ_CLASS_ID )&&
			(currentID != Class_ID(EDITTRIOBJ_CLASS_ID,0) )&&
			(currentID != Class_ID(POLYOBJ_CLASS_ID,0) )
		  )
		  bInSkeleton=TRUE;	
		else
		{
			//如果是 Editable_Poly ，卻是在階層內，一樣要輸出，不然會不正確
			INode* _parentNode = pNode->GetParentNode();
			if(
				(_parentNode == ::GetCOREInterface()->GetRootNode() ) &&
				(nChildren>0)
			  )
			  bInSkeleton=TRUE;
			else if(_parentNode != ::GetCOREInterface()->GetRootNode() )
			  bInSkeleton=TRUE;	
			else
				ModelNodes.AddItem(pNode);
		}
	}
	if((bInSkeleton) || (pNode == ::GetCOREInterface()->GetRootNode() ))
	{
		//確定不是模型，可輸出
		TiXmlElement *NodeElement = new TiXmlElement(pNodeName);  
		if (NULL==NodeElement)  
		{  
			return ;  
		}  
		pNextElement->LinkEndChild( NodeElement ); 
		iTreeDepth++;

		TiXmlElement_Transform *NodeTM = CreateNodeTMElement(pNode, iTreeDepth,0);
		NodeTM->LinkElements();
		NodeElement->LinkEndChild( NodeTM->TM ); 

		for (int i = 0; i < nChildren; i++)
		{
			ExportSkeleton(pNode->GetChildNode(i), iTreeDepth,NodeElement);
		}
	}
}


TiXmlElement_Transform* Homework03::CreateNodeTMElement(INode* pNode, int iTreeDepth, TimeValue t)
{
	// Export the nodes PRS at time t (0 by default)
	Matrix3 tmWorld = pNode->GetNodeTM(t);
	Matrix3 tmParent = pNode->GetParentTM(t);
	Matrix3 tmLocal = tmWorld * Inverse(tmParent);

    TiXmlElement *pTM = new TiXmlElement(_T("Transform"));  
	TiXmlElement *prow1 = new TiXmlElement(_T("Row1"));  
	TiXmlElement *prow2 = new TiXmlElement(_T("Row2"));  
	TiXmlElement *prow3 = new TiXmlElement(_T("Row3"));  
	TiXmlElement *prow4 = new TiXmlElement(_T("Row4")); 

	TiXmlElement_Transform* retElement = new TiXmlElement_Transform();
	retElement->SetElementsT(pTM,prow1,prow2,prow3,prow4);

	char str[100];
	float _x,_y,_z;
	_x = tmLocal.GetRow(0).x;
	_y = tmLocal.GetRow(0).y;
	_z = tmLocal.GetRow(0).z;
	sprintf(str, "Row1 %g %g %g ",_x,_y,_z);
	retElement->row1->SetValue(str);
	
	_x = tmLocal.GetRow(1).x;
	_y = tmLocal.GetRow(1).y;
	_z = tmLocal.GetRow(1).z;
	sprintf(str, "Row2 %g %g %g ",_x,_y,_z);
	retElement->row2->SetValue(str);
	
	_x = tmLocal.GetRow(2).x;
	_y = tmLocal.GetRow(2).y;
	_z = tmLocal.GetRow(2).z;
	sprintf(str, "Row3 %g %g %g ",_x,_y,_z);
	retElement->row3->SetValue(str);

	_x = tmLocal.GetRow(3).x;
	_y = tmLocal.GetRow(3).y;
	_z = tmLocal.GetRow(3).z;
	sprintf(str, "Row4 %g %g %g ",_x,_y,_z);
	retElement->row4->SetValue(str);
	return retElement;
}

TiXmlElement_Model* Homework03::ExportModel(INode* pNode, TiXmlElement* pNextElement)
{
	TCHAR* pNodeName = pNode->GetName();
	TiXmlElement_Model *ModelElement = new TiXmlElement_Model();  
	if (NULL==ModelElement)  
	{  
		return NULL;  
	}  

#pragma region Export Vertex
	//輸出頂點
	//先找出Node連結的三角面物體
	TriObject *tri;
	Object *obj = pNode->EvalWorldState(0).obj;
	Mesh* OurTriMesh;
	if(obj)
	{
		if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0))) 
		{
			tri=(TriObject *) obj->ConvertToType(0, 
				Class_ID(TRIOBJ_CLASS_ID, 0));
			if(tri)
			{
				OurTriMesh = &tri->mesh;
				Matrix3 SkinLocalTM = pNode->GetObjectTM(0);
				INT NumberVertices = OurTriMesh->getNumVerts();
				for (int i=0; i< NumberVertices ; i++)
				{
					// 導出每個頂點
					char vertStr[100];
					Point3 VxPos = OurTriMesh->getVert(i)*SkinLocalTM;
					sprintf(vertStr,"#Vert%i  %g %g %g ",i,VxPos.x,VxPos.y,VxPos.z);
					TiXmlElement *pP = new TiXmlElement(_T(""));
					pP->SetValue(vertStr);
					ModelElement->Points.AddItem(pP);

					//// 導出頂點法向量
					//char vertStrnNor[100];
					//Point3 NV;
					//NV = OurTriMesh->getNormal(i);
					//NV = NV*SkinLocalTM;
					//sprintf(vertStrnNor,"#Normal %i  %g %g %g ",i,NV.x,NV.y,NV.z);
					//TiXmlElement *nP = new TiXmlElement(_T(vertStrnNor));
					//ModelElement->Normal.AddItem(nP);
				}
			}
		}
	}
#pragma endregion Export Vertex 

#pragma region Export Vertex Weights

	Modifier* SkinMod = FindMaxSkinModifier(pNode);
	ISkin* MaxSkin = (ISkin*)SkinMod->GetInterface(I_SKIN);
	ISkinContextData* MaxSkinContext = MaxSkin->GetContextInterface(pNode);
	INT NumberVertices = MaxSkinContext->GetNumPoints();			
	INT TotalBones     = MaxSkin->GetNumBones(); // Total for skin.
	INT TotalFaces     = OurTriMesh->getNumFaces();
	for (int VertexIndex=0; VertexIndex< NumberVertices ; VertexIndex++) 
	{
		TArray <TiXmlElement*> RawInfluences;
		INT NumberBones = MaxSkinContext->GetNumAssignedBones( VertexIndex );
		TiXmlElement_BoneInfluence_PerVertex* vw = new TiXmlElement_BoneInfluence_PerVertex();
		if( NumberBones > 0 ) 
		{
			for (int BoneIndex=0; BoneIndex<NumberBones; BoneIndex++)
			{
				char str[60];
				float w = MaxSkinContext->GetBoneWeight( VertexIndex, BoneIndex );
				INT LocalBoneIndex  = MaxSkinContext->GetAssignedBone( VertexIndex, BoneIndex );
				sprintf(str, "bone: %i weight:%g",LocalBoneIndex,w);
				TiXmlElement* oneSetInfluence = new TiXmlElement(str);
				vw->InfluenceSet.AddItem(oneSetInfluence);
			}
		}
		ModelElement->RefBones.AddItem(vw);
	}

#pragma endregion Export Vertex Weights
	

#pragma region Export Faces
	OurTriMesh->buildNormals();
	Matrix3 Mesh2WorldTM = pNode->GetObjectTM(0);
	int NumFaces = OurTriMesh->getNumFaces();
	Mesh2WorldTM.NoScale();

	INT CountTexturedTris = 0;
	INT TotalTVNum = OurTriMesh->getNumTVerts();
	int Handedness = 0; //這個面的法向是否需要校正

	TArray<VVertex*> Wedges;
	for (int TriIndex = 0; TriIndex < NumFaces; TriIndex++)
	{
		Face*	TriFace			= &OurTriMesh->faces[TriIndex];
		TVFace*	TexturedTriFace	= &OurTriMesh->tvFace[TriIndex]; 
		
		//面結構創立
		TiXmlElement_Triangle* NewFace = new TiXmlElement_Triangle();


		////寫入平滑群組資訊
		char smgrpStr[50];
		int smgrp = (TriFace->getSmGroup());
		sprintf(smgrpStr,"#Smooth Group %i ",smgrp );
		TiXmlElement* TiSmGrp = new TiXmlElement(smgrpStr);
		NewFace->SmoothingGroups =TiSmGrp;



		////寫入TVerts & Face 資訊
		Point3 MaxNormal = OurTriMesh->getFaceNormal(TriIndex);	
		MaxNormal = VectorTransform( Mesh2WorldTM, MaxNormal );
		Point3 FaceNormal = Point3( MaxNormal.x, MaxNormal.y, MaxNormal.z);

		int PointIdx0 = TriFace->getVert(0);  // TriFace->v[0];
		int PointIdx1 = TriFace->getVert(1);
		int PointIdx2 = TriFace->getVert(2);


		//單一面的頂點編號
		char WedIdxStr[60];
		sprintf(WedIdxStr,"FaceIndice #%i #%i #%i",PointIdx0, PointIdx1, PointIdx2);
		TiXmlElement* TiWdIdx = new TiXmlElement(WedIdxStr);
		NewFace->WedgeIndex = TiWdIdx;

		
		Point3 WV0 = OurTriMesh->getVert(PointIdx0);
		Point3 WV1 = OurTriMesh->getVert(PointIdx1);
		Point3 WV2 = OurTriMesh->getVert(PointIdx2);

		Point3 OurNormal = (WV0 - WV1) ^ (WV2 - WV0);
		Handedness = ( ( OurNormal % FaceNormal ) < 0.0f);

		if( TotalTVNum > 0 ) 
		{
			//  TVertex indices
			DWORD UVidx0 = TexturedTriFace->getTVert(0);
			DWORD UVidx1 = TexturedTriFace->getTVert(1);
			DWORD UVidx2 = TexturedTriFace->getTVert(2);

			// TVertices
			UVVert UV0 = OurTriMesh->getTVert(UVidx0);
			UVVert UV1 = OurTriMesh->getTVert(UVidx1);
			UVVert UV2 = OurTriMesh->getTVert(UVidx2);


			char UVWStr[100];
			sprintf(UVWStr,"UV0.U %g UV0.V %g UV1.U %g UV1.V %g UV2.U %g UV2.V %g",	(UV0.x),(1.0f-UV0.y),(UV1.x),(1.0f-UV1.y),(UV2.x),(1.0f-UV2.y) );
			TiXmlElement* TiUVCoord = new TiXmlElement(UVWStr);
			NewFace->UVCoords=TiUVCoord;

			CountTexturedTris++;
		}

		//// 寫入material id 資訊
		int MaterialIndex = (int)TriFace->getMatID() /*& 255*/;
		char MatIdStr[20];
		sprintf( MatIdStr,"Material Id = %i" ,MaterialIndex);
		TiXmlElement* TiMatID = new TiXmlElement(MatIdStr);
		NewFace->MatIndex=TiMatID;


		//// 寫入material 資訊
		INT ThisMaterial = DigestMaterial( pNode,  MaterialIndex ,NewFace->mapName ,NewFace->materialName);
		ModelElement->Faces.AddItem(NewFace);
	}

#pragma endregion Export Faces
	return ModelElement;
}
int Homework03::DigestMaterial(INode *node,  INT matIndex, TCHAR * mapName,char* matName)
{
	Mtl* nodeMtl = node->GetMtl();

	if (!nodeMtl)
	{
		return -1; 
	}
	if (nodeMtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0)) 
	{
		StdMat* std_ = (StdMat*)nodeMtl;
		CStr matName = (CStr)nodeMtl->GetName();
		matName.printf(matName);
	}
	Mtl* ThisMtl;
	int NumSubs = nodeMtl->NumSubMtls();

	if (NumSubs > 0)
	{
		ThisMtl = nodeMtl->GetSubMtl(matIndex % NumSubs);
	}
	else
	{
		ThisMtl = nodeMtl;
	}
	if(ThisMtl)
	{
		CStr matName = (CStr)ThisMtl->GetName();
		matName.printf(matName);
		mapName = ((BitmapTex *) (ThisMtl->GetSubTexmap(ID_DI)))->GetMapName();
	}
	return matIndex;
}
Modifier* Homework03::FindMaxSkinModifier( INode* nodePtr)
{
	// Get object from node. Abort if no object.
	Object* ObjectPtr =nodePtr->GetObjectRef();
	
	if (!ObjectPtr) return NULL;

	// Is derived object ?
	if (ObjectPtr->SuperClassID() == GEN_DERIVOB_CLASS_ID) 
	{
		// Yes -> Cast.
		IDerivedObject* DerivedObjectPtr = static_cast<IDerivedObject*>(ObjectPtr);

		// Iterate over all entries of the modifier stack.
		int ModStackIndex = 0;
		while (ModStackIndex < DerivedObjectPtr->NumModifiers())
		{
			// Get current modifier.
			Modifier* ModifierPtr = DerivedObjectPtr->GetModifier(ModStackIndex);

			//DebugBox("Modifier Testing: %i \n",ModStackIndex);

			// Is this Physique ?
			if( ModifierPtr->ClassID() == Class_ID(SKIN_CLASSID) )
			{
				return ModifierPtr;
			}
			// Next modifier stack entry.
			ModStackIndex++;
		}
	}
	// Not found.
	return NULL;
}
void Homework03::CreateSerialTree(INode* inNode )
{
	ObjectState os = inNode->EvalWorldState(0);
	int nChildren = inNode->NumberOfChildren();
	bool bInSkeleton=FALSE;
	if (os.obj)
	{
		//判斷是不是模型，模型跳過
		Class_ID currentID = os.obj->ClassID();
		if( (currentID != EPOLYOBJ_CLASS_ID )&&
			(currentID != Class_ID(EDITTRIOBJ_CLASS_ID,0) )&&
			(currentID != Class_ID(POLYOBJ_CLASS_ID,0) )
		  )
		  bInSkeleton=TRUE;	
		else
		{
			//如果是 Editable_Poly ，卻是在階層內，一樣要輸出，不然會不正確
			INode* _parentNode = inNode->GetParentNode();
			if(
				(_parentNode == ::GetCOREInterface()->GetRootNode() ) &&
				(nChildren>0)
			  )
			  bInSkeleton=TRUE;
			else if(_parentNode != ::GetCOREInterface()->GetRootNode() )
			  bInSkeleton=TRUE;	

		}
	}
	else if(inNode == ::GetCOREInterface()->GetRootNode())
	  bInSkeleton=TRUE;
	if( bInSkeleton ) 
	{
		//確定不是模型
		SerialTree.AddItem(inNode);
		for (int i = 0; i < nChildren; i++)
		{
			CreateSerialTree(inNode->GetChildNode(i));
		}
	}
}
TiXmlElement_Animation* Homework03::ExportAnimation()
{
	SerialTree.Empty();
	CreateSerialTree(::GetCOREInterface()->GetRootNode() );
	TiXmlElement_Animation *AnimElement = new TiXmlElement_Animation(); 
	FLOAT StartFrame = ::GetCOREInterface()->GetAnimRange().Start();
	FLOAT EndFrame = ::GetCOREInterface()->GetAnimRange().End();
	INT FrameTicks = GetTicksPerFrame();
	INT TotalFrames = (EndFrame-StartFrame)/FrameTicks;
	for( INT t=0; t< TotalFrames; t++)
	{
		char Timestr[60];
		sprintf(Timestr, "#Frame %i",t);
		TiXmlElement *TimerXml = new TiXmlElement(Timestr); 

		TimeValue TimeNow = StartFrame + t * FrameTicks;
		for (int i = 0; i<SerialTree.Num(); i++)
		{
			Matrix3 parentTM, nodeTM, localTM;
			INode* ThisNode = SerialTree[i];
			INode* parent;

			nodeTM = ThisNode->GetNodeTM(TimeNow);
			nodeTM = Uniform_Matrix(nodeTM);
			if(i!=0)
			{
				parent = ThisNode->GetParentNode();
				parentTM = parent->GetNodeTM(TimeNow);
				parentTM = Uniform_Matrix(parentTM);
				localTM = nodeTM*Inverse(parentTM);
			}
			else
			{
				localTM = nodeTM;
			}
			char str[500];
			float r1_x = localTM.GetRow(0).x;
			float r1_y = localTM.GetRow(0).y;
			float r1_z = localTM.GetRow(0).z;

			float r2_x = localTM.GetRow(1).x;
			float r2_y = localTM.GetRow(1).y;
			float r2_z = localTM.GetRow(1).z;


			float r3_x = localTM.GetRow(2).x;
			float r3_y = localTM.GetRow(2).y;
			float r3_z = localTM.GetRow(2).z;


			float r4_x = localTM.GetRow(3).x;
			float r4_y = localTM.GetRow(3).y;
			float r4_z = localTM.GetRow(3).z;

			sprintf(str,"#%i %f,%f,%f  %f,%f,%f  %f,%f,%f  %f,%f,%f",i,r1_x,r1_y,r1_z,r2_x,r2_y,r2_z,r3_x,r3_y,r3_z,r4_x,r4_y,r4_z);
			TiXmlElement *TxmlTM = new TiXmlElement(str); 
			TimerXml->LinkEndChild(TxmlTM);
		}
		AnimElement->FrameTag.AddItem(TimerXml);
	}

	return AnimElement;
}
Matrix3 Homework03::Uniform_Matrix(Matrix3 orig_cur_mat)
{          
    AffineParts   parts;  
    Matrix3       mat;   
 	///Remove  scaling  from orig_cur_mat
	//1) Decompose original and get decomposition info
    decomp_affine(orig_cur_mat, &parts); 
 
	//2) construct 3x3 rotation from quaternion parts.q
    parts.q.MakeMatrix(mat);
 
	//3) construct position row from translation parts.t  
    mat.SetRow(3,  parts.t);
 
   return(mat);
}

// From the Biped sdk documentation ( BipExp.rtf )
Matrix3 Homework03::Get_Relative_Matrix(INode *node, int t)
{          
     /* Note: This function removes the non-uniform scaling 
     from MAX node transformations. before multiplying the 
     current node by  the inverse of its parent. The 
     removal  must be done on both nodes before the 
     multiplication and Inverse are applied. This is especially 
     useful for Biped export (which uses non-uniform scaling on 
     its body parts.) */
     
      INode *p_node  =    node->GetParentNode();
     
      Matrix3     orig_cur_mat;  // for current and parent 
      Matrix3     orig_par_mat;  // original matrices 
     
      Matrix3     cur_mat;       // for current and parent 
      Matrix3     par_mat;       // decomposed matrices 
                                                                         
      //Get transformation matrices
      orig_cur_mat   =      node->GetNodeTM(t);
      orig_par_mat   =    p_node->GetNodeTM(t); 
          
      //Decompose each matrix
      cur_mat =  Uniform_Matrix(orig_cur_mat);
      par_mat =  Uniform_Matrix(orig_par_mat);
     
      //then return relative matrix in coordinate space of parent
      return(cur_mat * Inverse( par_mat)); 
}

#pragma region Function Publishing 

#define H_FP_INTERFACE_ID Interface_ID(0x1d750ad9, 0x24d25aa8)  // Randomly chosen hex 32 bit id #s using GenCid.exe


class HMaxInterfaceFunctionPublish : public FPStaticInterface 
{
public:
	DECLARE_DESCRIPTOR(HMaxInterfaceFunctionPublish);
	enum OpID 
	{
		kyExportModel,//
		kyExportAnimation,//
	};
	BEGIN_FUNCTION_MAP
		FN_1(kyExportModel, TYPE_INT ,HExportModel,TYPE_STRING)
		FN_1(kyExportAnimation, TYPE_INT ,HExportAnimation,TYPE_STRING)
	END_FUNCTION_MAP
	/* 訊息映射用 fn */
	INT HExportModel(TCHAR* outputPath)
	{
		ExpInterface *ei=NULL;
		ExportMode = VISUAL_EXPORT|MODEL_EXPORT;
		MyMaxExp.bSupressDialogBox = TRUE;
		return(MyMaxExp.SaveFile(outputPath, ei, (::GetCOREInterface()), &MyMaxExp));
	}

	INT HExportAnimation(TCHAR* outputPath)
	{
		ExpInterface *ei=NULL;
		ExportMode = ANIMATION_EXPORT;
		MyMaxExp.bSupressDialogBox = TRUE;
		return(MyMaxExp.SaveFile(outputPath, ei, (::GetCOREInterface()), &MyMaxExp));

	}
};


static HMaxInterfaceFunctionPublish theHMaxInterfaceFunctionPublish(
H_FP_INTERFACE_ID, _T("HH"), -1, 0, FP_CORE,

HMaxInterfaceFunctionPublish::kyExportModel, _T("ExportModel"), -1, TYPE_INT,  0, 1,
	_T("Path"),-1,TYPE_STRING,

HMaxInterfaceFunctionPublish::kyExportAnimation, _T("ExportAnimation"), -1, TYPE_INT,  0, 1,
	_T("Path"),-1,TYPE_STRING,
end);

#pragma endregion


void TiXmlElement_Transform::SetElementsT(TiXmlElement* _tm ,TiXmlElement* r1,TiXmlElement* r2,TiXmlElement* r3,TiXmlElement* r4)
{
	TM = _tm;
	row1 = r1;
	row2 = r2;
	row3 = r3;
	row4 = r4;
}

void TiXmlElement_Transform::LinkElements()
{
	TM->LinkEndChild( row1);
	TM->LinkEndChild( row2);
	TM->LinkEndChild( row3);
	TM->LinkEndChild( row4);
}

void TiXmlElement_Model::LinkElements()
{
	int i,j;
	char str[60];
	pointsTag = new TiXmlElement(_T("Vertex")); 
	for(i=0;i<Points.Num();i++)
	{
		pointsTag->LinkEndChild( Points[i]);
		//pointsTag->LinkEndChild( Normal[i]);
	}

	RefBonesTag= new TiXmlElement(_T("BoneWeight"));
	for(i=0;i<RefBones.Num();i++)
	{
		sprintf(str, "#Vertex %i",i);
		TiXmlElement *VertexWeightTag = new TiXmlElement(_T(str));
		for (j=0;j<RefBones[i]->InfluenceSet.Num();j++)
		{
			VertexWeightTag->LinkEndChild(RefBones[i]->InfluenceSet[j]);
		}
		RefBonesTag->LinkEndChild(VertexWeightTag);
	}
	FacesTag = new TiXmlElement(_T("Facees"));
	for(i=0;i<Faces.Num();i++)
	{
		sprintf(str, "#Face %i",i);
		TiXmlElement *PerFaceTag = new TiXmlElement(_T(str));
		PerFaceTag->LinkEndChild(Faces[i]->WedgeIndex);
		PerFaceTag->LinkEndChild(Faces[i]->UVCoords);
		PerFaceTag->LinkEndChild(Faces[i]->MatIndex);
		PerFaceTag->LinkEndChild(Faces[i]->SmoothingGroups);
		FacesTag->LinkEndChild(PerFaceTag);
	}
}

void TiXmlElement_Animation::LinkElements()
{
	//int i,j;
	//char str[60];
	//for(i=0;i<Matrixs.Num();i++)
	//{
	//	sprintf(str, "#Frame %i",i);
	//	FrameTag = new TiXmlElement(_T(str));
	//	FrameTag->LinkEndChild(Matrixs[i]);
	//}
	
}


