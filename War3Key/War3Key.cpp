// War3Key.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "War3Key.h"
#include "War3KeyDlg.h"
#include "xmlParser.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWar3KeyApp

BEGIN_MESSAGE_MAP(CWar3KeyApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWar3KeyApp ����

CWar3KeyApp::CWar3KeyApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CWar3KeyApp ����

CWar3KeyApp theApp;


// CWar3KeyApp ��ʼ��

BOOL CWar3KeyApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	HANDLE hMapping;
	hMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS,true,_T("War3KeyMappingShared"));
	if (!hMapping)
		hMapping = CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,sizeof(KeyMappingInformation),_T("War3KeyMappingShared"));
	KeyMappingInformation *lpMapping = (KeyMappingInformation*)MapViewOfFile(hMapping,FILE_MAP_WRITE,0,0,0);
	if(!lpMapping) {
		MessageBox(0,_T("OpenFileMapping failed"),_T("Error"),0);
		return FALSE;
	}
	memset(lpMapping,0,sizeof(KeyMappingInformation));

    
	int i;
	XMLNode xMainNode;
	FILE *f;
	CWar3KeyDlg dlg;

	f = fopen("config.xml","rt");
	if(f==NULL) {
		f = fopen("config.xml","wt");
		fwrite("<?War3 KeyMapper Configuration?>",strlen("<?War3 KeyMapper Configuration?>"),1,f);
	}
	fclose(f);
	xMainNode = XMLNode::openFileHelper(_T("config.xml"));
		
	InitializeCriticalSection(&(lpMapping->CriticalSection));

	for (int i=0;i<xMainNode.nChildNode();i++) {
	
		lpMapping->OriginalKey[i] = _wtoi(xMainNode.getChildNode(i).getAttribute(_T("OriginalKey")));
		lpMapping->MappedKey[i] = _wtoi(xMainNode.getChildNode(i).getAttribute(_T("MappedKey")));
		lpMapping->nMappingCount++;
	}
	
	m_pMainWnd = &dlg;
	dlg.lpMapping = lpMapping;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	Unhook();

    xMainNode=XMLNode::createXMLTopNode(_T("War3 KeyMapper Configuration"),TRUE);
	XMLNode xNode;
	wchar_t txt[256];
	for (i=0;i<lpMapping->nMappingCount;i++) {
		_itow(i,txt,10);
		xNode=xMainNode.addChild(txt);

		_itow(lpMapping->OriginalKey[i],txt,10);
		xNode.addAttribute(_T("OriginalKey"),txt);
		_itow(lpMapping->MappedKey[i],txt,10);
		xNode.addAttribute(_T("MappedKey"),txt);
	}

    wchar_t *t=xMainNode.createXMLString(TRUE);
    size_t converted,origsize = wcslen(t) + 1;
    char* buffer = (char *)malloc(origsize);
    wcstombs_s(&converted,buffer, origsize, t, _TRUNCATE);

	f = fopen("config.xml","wt");
	fwrite(buffer,converted-1,1,f);
	fclose(f);
	free(buffer);
    free(t);

	DeleteCriticalSection(&(lpMapping->CriticalSection));
	UnmapViewOfFile(lpMapping);
	CloseHandle(hMapping);

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
