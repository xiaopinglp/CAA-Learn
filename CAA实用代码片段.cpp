/*常见编译错误： 
fatal error C1189: #error :WINDOWS.H already included.	
解决方法：最顶端定义预编译的宏*/
#ifdef _WINDOWS_
#undef _WINDOWS_     #include <afx.h>
#endif

CAA常用代码构件
#include<afxwin.h>
AfcMessageBox(_T("hello!Point Command"));

//变量和表达式转换成字符串
//使用字符串运算符来实现转换输出定义
#define PR(x) cout<<#x"="<<x<<"\n";

//一、弹出对话框
//1、CATDlgNotify
	CATDlgNotify _OpenNotify;
	CATUnicodeString NotifyText;
	//NotifyText.BuildFromNum(iInputAllocatedSize);
	_OpenNotify = new CATDlgNotify(this, "TEST", CATDlgNfyWarning|CATDlgNfyOK);
	_OpenNotify->SetText(NotifyText);
	_OpenNotify->SetVisibility(CATDlgShow);

//2、MessageBox CATUnicodeString -->LPSTR 利用CString  afxstr;
	CATUnicodeString InstanceName;
	spProduct->GetPrdInstanceName(InstanceName);
	CString name=InstanceName.ConvertToChar();
	MessageBox(NULL,name,L"OK",MB_OK | MB_SYSTEMMODAL);
	MessageBox(NULL,L"Hello World!",L"成功",MB_OK | MB_SYSTEMMODAL);

//二、获取CATIA环境变量：
    CATUnicodeString oPreviewFileName,TmpDir,File;
         char *slash_tmp = NULL;
         if (CATGetEnvValue("CATInstallPath", &slash_tmp) == CATLibSuccess)
            oPreviewFileName = slash_tmp;
         if (slash_tmp) free(slash_tmp); slash_tmp=NULL;
#ifndef _WINDOWS_SOURCE
         oPreviewFileName.Append("\\");
#else
         oPreviewFileName.Append("/");
#endif
         oPreviewFileName.Append("CAAxPDMPreview.jpg");

// get System environment variable
char *pathvar;
pathvar = getenv("PATH");
cout << pathvar << endl
	 
/*CATIA CAA 32位和64位编译
	修改环境变量：
	_MkmkOS_BitMode  =  32   // Win32位编译
	_MkmkOS_BitMode  =  64   // Win64位编译
 */

//三、元素隐藏与显示
/**
* 隐藏元素
* @param ipListElemObj
* 元素列表
*/
void HideElements(CATLISTV(CATISpecObject_var) ipListElemObj)
{
	for(int i=1;i<ipListElemobj.Size();i++;)
	{
		CATIVisProperties* pPropONElem = NULL;
		HRESULT rc = ipListElemobj[i]->QueryInterface(IID_CATIVisProperties,(void**) &pPropONElem );
		if (NULL != pPropONElem) 
		{
			CATIVisPropertiesValues PropValue;
			CATIVisPropertyType PropTypeOnPtObj = CATVPShow;
			CATVisGeomType GeomTypeOnPtObj = CATVPGlobalType;
			PropValue.SetShowAttr(CATNOShowAttr);
			rc = pPropONElem -> SetPropertiesAttr(PropValue,
												  PropTypeOnPtObj,
												  GeomTypeOnPtObj);
			pPropONElem ->Release();
			pPropONElem = NULL;
		}
	}
}

/**
* 检测元素显示状态
*/
bool CheckIsShow(CATIVisProperties_var spPropOnTreeNode)
{
	// 5/18  add
	bool IsShow = false;

	CATShowAttribut oShow ;
	if ( NULL_var != spPropOnTreeNode )
	{
		if ( SUCCEEDED(GetShow(spPropOnTreeNode,oShow,2)))
		{
			// model show flag
			if (oShow == CATShowAttr)
			{
				IsShow = true;
			}
		}
	}//--- 5/18 add

	return IsShow;
}

/**
* 取得元素显示标识 Show Flag
*/
HRESULT GetShow(CATIVisProperties_var spProp, CATShowAttribut &oShow ,int Mode )
{
	if ( spProp == NULL_var)
		return E_FAIL;
	CATVisPropertiesValues  MyPropertyOnFace;
	CATVisPropertyType PropTypeOnFace = CATVPShow;
	CATVisGeomType GeomTypeOnFace;
	if ( Mode == 1 )
		GeomTypeOnFace     = CATVPMesh;
	else
		GeomTypeOnFace     = CATVPGlobalType ;
	HRESULT rc = spProp->GetPropertiesAtt(MyPropertyOnFace,PropTypeOnFace,GeomTypeOnFace);
	if ( SUCCEEDED(rc) )
	{
		HRESULT HR = MyPropertyOnFace.GetShowAttr(oShow);
		if ( FAILED(HR))
			return E_FAIL;
	}
	return S_OK;
}

//四、元素隐藏与显示
/**
* 高亮特征
* @param spSpec
* 高亮特征
*/
HRESULT HighLightSpecObject (CATISpecObject_var spSpec, CATBoolean boolClearHistory)
{
	HRESULT rc = E_FAIL;
	CATFrmEditor * pEditor = CATFrmEditor::GetCurrentEditor();
	if(NULL == pEditor )
		return rc;
	CATHSO * pHSO = pEditor->GetHSO();
	if(NULL == pHSO )
		return rc;	
	
	//为1时，清楚所有已有的高亮
	if(boolClearHistory)
		pHSO->Empty();
	CATPathElement pContext = pEditor->GetUIActiveObject();
	CATIBuildPath * piBuildPath = NULL;
	rc =spSpec->QueryInterface(IID_CATIBuildPath, (void **)&piBuildPath);
	if(SUCCEEDED(rc) && piBuildPath != NULL)
	{
		CATPathElement * pPathElement = NULL;
		rc = piBuildPath->ExtractPathElement(&pContext, &pPathElement);
		if (pPathElement != NULL)
		{
			pHSO->AddElement(pPathElement);
			pPathElement->Release();
			pPathElement = NULL;
		}
		piBuildPath->Release();
		piBuildPath = NULL;
	}
	return S_OK;
}

//五、属性获取   
    CATIAttributesDescription *piAttrDesc = NULL;
    rc = spRootProduct->QueryInterface(IID_CATIAttributesDescription, (void **) &piAttrDesc);
    if (FAILED(rc) || (NULL == piAttrDesc))
    {
        cout << "QueryInterface CATIAttributesDescription error" << endl;
        return 4;
    }
    CATIInstance *piInstance = NULL;
    rc = spRootProduct->QueryInterface(IID_CATIInstance, (void **) &piInstance);
    if (FAILED(rc) || (NULL == piInstance))
    {
        cout << "QueryInterface CATIInstance error" << endl;
        return 4;
    }
    CATListValCATAttributeInfos attrInfoList; 
    piAttrDesc->List(&attrInfoList);
    for (int i = 1; i <= attrInfoList.Size(); i++)
    {
        CATAttributeInfos attrInfo = attrInfoList[i];
        const CATUnicodeString& propertyName = attrInfo.Name(); //属性名
        const CATUnicodeString& valueType = attrInfo.Type()->Name(); //属性类型
        CATIValue *pValue = piInstance->GetValue(propertyName); //获得对应属性名的属性值
        CATUnicodeString value = "";
        pValue->AsString(value);
        cout << propertyName << "-" << valueType << "-" << value << endl;
        if (pValue)
        {
            pValue->Release();
            pValue = NULL;
        }
    }

//六、CATSystemInfo 主机信息获取
/*全局方法CATGetSystemInfo，获得一个CATSystemInfo结构体，包含主机名字、主机系统名字、系统版本等主机信息。*/
CATSystemInfo host;
::CATGetSystemInfo(&host);

cout << "HostName:" << host.HostName << endl;
cout << "OSName:" << host.OSName << endl;
cout << "OSVersion:" << host.OSVersion << endl;
cout << "OSType:" << host.OSType << endl;
cout << "MinorVersion:" << host.MinorVersion << endl;
cout << "MajorVersion:" << host.MajorVersion << endl;


CATTime 
CATTime timeNow = CATTime::GetCurrentLocalTime();
CATUnicodeString timeStr = timeNow.ConvertToString("%Y/%m/%d-%H:%M:%S");
std::cout << "Current Time:" << timeStr.ConvertToChar() << std::endl;

//七、C＃ C++ 字符集转换  字节流
	string  str="客服端是用c#写的，服务端是c++";
	send(str);
	public void send(msg)
	{
		string hexstr=StringToHexString(str)
		char[] chars= hexstr.ToCharArray();
		byte[] byteData = Encoding.Default.GetBytes(chars);  
		socket.write(byteData ,0,byteData.length);
	}
	//字符串转为16进制
	public string StringToHexString(string message)
	{
		//按照指定编码将string编程字节数组
		byte[] b = Encoding.UTF8.GetBytes(message);
		string result = string.Empty;
		for (int i = 0; i < b.Length; i++)
		{
			result += Convert.ToString(b[i], 16);
		}
		return result.ToUpper();
	}


//八、调用exe文件
ShellExecute(0,(LPCWSTR)L"open",(LPCWSTR)L"D:\\Bin_x64\\SuperMapDemo.exe",(LPCWSTR)L"",(LPCWSTR)L"",SW_SHOWNORMAL);
SHELLEXECUTEINFO ShellInfo;
	memset(&ShellInfo,0,sizeof(ShellInfo));
	ShellInfo.cbSize=sizeof(ShellInfo);
	ShellInfo.hwnd=NULL;
	ShellInfo.lpVerb=_T("open");
	//ShellInfo.lpFile=_T("..\\..\\..\\SuperMapDemo\\SuperMapDemo.exe");
	ShellInfo.lpFile=_T("E:\\supermap\\Bin_x64\\SuperMapDemo.exe");
	ShellInfo.lpParameters= name;
	ShellInfo.nShow=SW_HIDE;//SW_SHOWNORMAL
	ShellInfo.fMask=SEE_MASK_NOCLOSEPROCESS;
	BOOL bResult=ShellExecuteEx(&ShellInfo);
	if (!bResult)
	{
		return false;
	}

	行号 参数 含义  
	1 SW_HIDE 隐藏这个窗体，并激活其他窗体。 
	2 SW_MAXIMIZE 最大化指定的窗体。  
	3 SW_MINIMIZE 最小化指定的窗体，并按顺序激活最上层的窗体。  
	4 SW_RESTORE 激活并显示窗体。如果窗体为最小化或者最大化，窗体恢复到原始大小和位置。应用程序当恢复一个最小化的窗体时将指定标记。 
	5 SW_SHOW 以当前的大小和位置激活并显示窗体。 
	6 SW_SHOWDEFAULT   
	7 SW_SHOWMAXIMIZED 激活并最大化显示窗体。
	8 SW_SHOWMINIMIZED 激活并最小化现实窗体。 
	9 SW_SHOWMINNOACTIVE 最小化窗体，保持其激活状态。 
	10 SW_SHOWNA 以当前状态显示窗体，保持其激活状态。  
	11 SW_SHOWNOACTIVATE 以当前的大小和位置显示窗体，并保持其激活状态。 
	12 SW_SHOWNORMAL 激活并显示一个窗体。如果窗体为最大化或者最小化，窗体恢复到原始的大小和位置。当窗体第一次显示的时候，应用程序记录标记。


//九、批处理模式获得文件的rootProduct
HRESULT GetCurrentDoc_TopProduct( CATIProduct_var & spTopProd)
{
//--------------------------------------------------------------------
// 1. Prologue 
//--------------------------------------------------------------------
  cout << endl << flush;
  cout << endl << flush;
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;

  // --- Creating the Session:  A session must always be created in a batch
  char *sessionName = "CAA_EhiFilter_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(sessionName,pSession);
  if ((SUCCEEDED(rc)) && (NULL != pSession))
  {
    cout << "> session created : " << sessionName <<endl << flush;
  }
  else
  {
    cout << "ERROR in creating session" << sessionName << endl << flush;
    return 1;
  }
  
  // --- Opening an existing document 
  //     The input parameter to this sample program must contain 
  //     the entire path and name of the document that is to be opened.  
  
  CATDocument *pDoc = NULL;  // pDoc is a pointer to the document 

  cout << "> open document :"<< argv[1] << argv[2] << endl << flush;
  rc = CATDocumentServices::OpenDocument(CATUnicodeString(argv[1])+CATUnicodeString(argv[2]), pDoc);
  
  CATLockDocument(*pDoc);

  if (SUCCEEDED(rc) && (NULL != pDoc))
  {
    cout << "> document opened " << endl << flush;
  }
  else
  {
    cout << "ERROR in opening document" << endl << flush;
    return 2;
  }
  
  // --- Retrieving root product of the opened document 
  CATIProduct* piRootProduct = NULL; // piRootProduct is a handle to document root product  
  //  
  CATIDocRoots * piDocRoots = NULL;
  rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &piDocRoots);
  if ( FAILED(rc) || (NULL==piDocRoots) ) 
  {
	cout << "ERROR : Failed to query CATIDocRoots" << endl;
	return 3;
  }
  CATListValCATBaseUnknown_var* pListRootProduct = piDocRoots->GiveDocRoots();
  piDocRoots->Release();
  piDocRoots=NULL;
  
  if ( pListRootProduct && pListRootProduct->Size() )
  {  
    CATBaseUnknown_var hUnk = (*pListRootProduct)[1];

    if (NULL_var != hUnk) 
		rc = hUnk->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
    if (pListRootProduct) 
		delete pListRootProduct;
		pListRootProduct = NULL;
    //
    if  (SUCCEEDED(rc) && (NULL != piRootProduct))
    {
		cout << "> root product found in document " << endl << flush;
		spTopProd = piProductOnRoot;
		CATUnicodeString partNumber = piProductOnRoot->GetPartNumber();
		cout << "Working with '" << partNumber.ConvertToChar() << "'" << endl;
		return S_OK;
	}
    else
    {
      cout << "ERROR : Root product not found in document " << endl << flush;
      return 3;
    }
  }
  
//--------------------------------------------------------------------
	//创建草图
	CATInit *piInitOnDoc = NULL;
	rc = pDoc -> QueryInterface (IID_CATInit,(void**) &piInitOnDoc);
	if(SUCCEEDED(rc) && NULL != piInitOnDoc)
	{
		//获取Container
		const CATIdent idCATIContainer = "CATIPrtContainer";
		CATIPrtContainer *piRootContainer = NULL;
		piRootContainer = (CATIPrtContainer*)
			piInitOnDoc -> GetRootContainer(idCATIContainer);
		if(NULL != piRootContainer)
		{
			CATIPrtPart_var spPart = piRootContainer->GetPart();
			CATIBasicTool_var spTool= spPart->GetCurrentTool();

			CATIDescendants_var spDesTool = spPart;
			CATListValCATISpecObject_var  oLst ;
			spDesTool->GetAllChildren("CATIMechanicalTool",oLst);
			CATISpecObject_var spMainBody = oLst[1];
			CATIAlias_var spAlias = spMainBody;
			cout << spAlias->GetAlias() << endl << flush;

			CATISketchFactory_var spSketchFactory(piRootContainer);
			if(NULL_var != spSketchFactory)
			{
				CATISpecObject_var spSketchSpec=spSketchFactory->CreateSketch();
				CATISketch_var spSketch=spSketchSpec;
				if(NULL_var != spSketch)
				{
					spSketch->OpenEdition();
					CATI2DWFFactory_var sketch2DFactory(spSketch);
					if(NULL_var != sketch2DFactory)
					{
						double Origin[2]={0.,0.};
						double Radius=10;
						CATISpecObject_var spSpecCircle=
							sketch2DFactory->CreateCircle(Origin,Radius);
						if(NULL_var != spSpecCircle)
						{
							cout<<"草图中创建圆成功！"<<endl;	
						}
						spSketch->CloseEdition();

						spPart->SetCurrentFeature(spMainBody);


						//创建凸台
						CATIPrtFactory * piPrtFact=NULL;
						rc=piRootContainer->QueryInterface(IID_CATIPrtFactory,
							(void **)&piPrtFact);
						if(SUCCEEDED(rc) && NULL != piPrtFact)
						{
							CATISpecObject_var spPad=piPrtFact->CreatePad(spSketch);
							if(NULL_var != spPad)
							{
								CATIPad_var spPadPad=spPad;
								if(NULL_var != spPadPad)
								{
									spPadPad->ModifyEndType(catOffsetLimit);
									spPadPad->ModifyEndOffset(20.);
								}

								spPad->Update();
								cout<<"创建凸台成功！"<<endl;
							}
							piPrtFact->Release();
							piPrtFact=NULL;

							CATISpecObject_var spPart = piRootContainer->GetPart();
							spPart->Update();
						}
					}
				}
			}

			CATISpecObject_var spParentForTool = spMainBody;
			CATIMechanicalRootFactory_var spMechRoot = piRootContainer;
			CATISpecObject_var spSpecGS1 = NULL_var;
			rc = spMechRoot -> CreateGeometricalSet("新增几何图形集1",spParentForTool,spSpecGS1);
		}

		piInitOnDoc->Release();
		piInitOnDoc=NULL;
	}
