
// work_2.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������



// Cwork_2App:
// � ���������� ������� ������ ��. work_2.cpp
//

class Cwork_2App : public CWinApp
{
public:
	Cwork_2App();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern Cwork_2App theApp;