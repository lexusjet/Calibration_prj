
// work_2.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы



// Cwork_2App:
// О реализации данного класса см. work_2.cpp
//

class Cwork_2App : public CWinApp
{
public:
	Cwork_2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Cwork_2App theApp;