// War3Key.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWar3KeyApp:
// �йش����ʵ�֣������ War3Key.cpp
//

class CWar3KeyApp : public CWinApp
{
public:
	CWar3KeyApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWar3KeyApp theApp;