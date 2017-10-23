常见编译错误：
fatal error C1189: #error :WINDOWS.H already included.

解决方法：最顶端定义预编译的宏
#ifdef _WINDOWS_
#undef _WINDOWS_     #include <afx.h>
#endif


CAA常用代码构件
#include<afxwin.h>
AfcMessageBox(_T("hello!Point Command"));

//变量和表达式转换成字符串
//使用字符串运算符来实现转换输出定义
#define PR(x) cout<<#x"="<<x<<"\n";
1、CATDlgNotify
	CATUnicodeString NotifyText;
	//NotifyText.BuildFromNum(iInputAllocatedSize);
	_OpenNotify = new CATDlgNotify(this, "TEST", CATDlgNfyWarning|CATDlgNfyOK);
	_OpenNotify->SetText(NotifyText);
	_OpenNotify->SetVisibility(CATDlgShow);

2、CATUnicodeString -->LPSTR 利用CString  afxstr;
	CATUnicodeString InstanceName;
	spProduct->GetPrdInstanceName(InstanceName);
	CString name=InstanceName.ConvertToChar();
	MessageBox(NULL,name,L"OK",MB_OK | MB_SYSTEMMODAL);
	MessageBox(NULL,L"Hello World!",L"成功",MB_OK | MB_SYSTEMMODAL);

	CString str;  
    str.Format(_T("%d"),len); //CString类的一个成员函数,它通过格式操作使任意类型的数据转换成一个字符串
//获取CATIA环境变量：
CATGetEnvValue("CATTemp", &slash_tmp) == CATLibSuccess)
// get System environment variable
char *pathvar;
pathvar = getenv("PATH");
cout << pathvar << endl



3、元素隐藏与显示

/**
* 隐藏元素
* @param ipListElemObj
* 元素列表
*/
void BasicGlobalFunc::HideElements(CATLISTV(CATISpecObject_var) ipListElemObj)
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

/**
* 高亮特征
* @param spSpec
*   高亮特征
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
	if(boolClearHistory)//为1时，清楚所有已有的高亮
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


3、C＃ C++ 字符集转换  字节流
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


4、调用exe文件
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



5、批处理模式获得文件的rootProduct
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

//-------------------------------------------------------------------------
// Callback on DiaOK of _BITCreateAssemSndDlg
//-------------------------------------------------------------------------
#include"iostream.h"
#include"fstream.h"
#include "CATNotification.h"
void BITCreateAssemSndDlg::OnBITCreateAssemSndDlgDiaOKNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{	
	_OpenNotify = new CATDlgNotify(this, "", CATDlgNfyOKCancel);//弹出询问消息框
	_OpenNotify->SetText("导出信息？");
	_OpenNotify->SetVisibility(CATDlgShow);

	pDlgFile = new CATDlgFile(this,"导出",CATDlgFileSave);//弹出文件选择框
	pDlgFile->SetVisibility(CATDlgShow);	
	CATUnicodeString nameExtension = CATUnicodeString("txt files");//设置文件格式为txt
	CATString filterExtension = CATString("*.txt");
	pDlgFile->SetFilterStrings(&nameExtension, &filterExtension, 1);
	pDlgFile->SetFileName("信息记录");//设置文件默认名称为信息记录
	int iTypeOfInput = 0;
	//添加文件选择框确定按钮事件回调函数 ActOnOK
	AddAnalyseNotificationCB (pDlgFile, 
		pDlgFile->GetDiaOKNotification(),
		(CATCommandMethod)&BITCreateAssemSndDlg::ActOnOK,
		&iTypeOfInput);
}

//事件回调函数 ActOnOK的实现
void BITCreateAssemSndDlg::ActOnOK(CATCommand * cmd, CATNotification* evt , CATCommandClientData data)
{
	CATUnicodeString fileName;
	pDlgFile->GetSelection(fileName);//获取选择的路径
	_OpenNotify = new CATDlgNotify(this, "", CATDlgNfyOK);//选择的路径提示框
	_OpenNotify->SetText("文件将被保存到:"+fileName);
	_OpenNotify->SetVisibility(CATDlgShow);

	fileName=fileName+".txt";
	const char *filepath=fileName.ConvertToChar();
	ofstream outfile(filepath,ios::out|ios::trunc);//用c++的输出文件
	if(!outfile)	 
	{
		_OpenNotify = new CATDlgNotify(this, "", CATDlgNfyError);
		_OpenNotify->SetText("打开出错！");
		_OpenNotify->SetVisibility(CATDlgShow);
	}
	outfile<<"姓名  "<<"性别  "<<"年龄  "<<"喜欢学科	  "<<endl;
	CATUnicodeString	 name,gender,age,subject;
	int ColumnNum=_MultiListInformation->GetLineCount();
	for(int i=0;i<ColumnNum;i++)
	{
		//获取MultiListInformation中的信息
		_MultiListInformation->GetColumnItem(0, name,i);
		_MultiListInformation->GetColumnItem(1, gender,i);
		_MultiListInformation->GetColumnItem(3, age,i);
		_MultiListInformation->GetColumnItem(2, subject,i);
		//此处需要调整字符串的输出方式，使得txt格式整齐
		name.Resize(6,' ',0);
		gender.Resize(4,' ',0);
		age.Resize(4,' ',0);
		outfile<<name<<" "<<gender<<" "<<age<<" "<<subject<<" "<<endl;
	}
	pDlgFile->RequestDelayedDestruction();
	pDlgFile=NULL;
}



void BITCreateAssemSndDlg::OnMultiListInformationListSelectNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	int selectLine[1];
	int selectNumb = _MultiListInformation->GetSelect(selectLine,1);
	CATUnicodeString	 name,gender,age,subject;
	_MultiListInformation->GetColumnItem(0, name,selectLine[0]);
	_MultiListInformation->GetColumnItem(1, gender,selectLine[0]);
	_MultiListInformation->GetColumnItem(3, age,selectLine[0]);
	_MultiListInformation->GetColumnItem(2, subject,selectLine[0]);
	_EditorName->SetText(name);//Editor值设置
	if(gender=="男") {_RadioButtonMale->SetState(CATDlgCheck);_RadioButtonFemale->SetState(CATDlgUncheck);}//RadioButton状态设置
	if(gender=="女") {_RadioButtonMale->SetState(CATDlgUncheck);_RadioButtonFemale->SetState(CATDlgCheck);}
	int ageNumb;
	age.ConvertToNum(&ageNumb,"%d");//字符串转化为整数
	_ComboAge->SetSelect(ageNumb-20);
	if(-1==subject.SearchSubString("知识工程"))//字符串搜索
		_CheckButtonKnowledge->SetState(CATDlgUncheck);//CheckButton状态设置
	else _CheckButtonKnowledge->SetState(CATDlgCheck);
	if(-1==subject.SearchSubString("设计制造集成"))
		_CheckButtonDesign->SetState(CATDlgUncheck);
	else _CheckButtonDesign->SetState(CATDlgCheck);
	if(-1==subject.SearchSubString("三维工艺设计"))
		_CheckButton3D->SetState(CATDlgUncheck);
	else _CheckButton3D->SetState(CATDlgCheck);
}
