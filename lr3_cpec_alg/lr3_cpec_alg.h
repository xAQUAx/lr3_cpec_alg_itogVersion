
// lr3_cpec_alg.h: основной файл заголовка для приложения lr3_cpec_alg
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// Clr3cpecalgApp:
// Сведения о реализации этого класса: lr3_cpec_alg.cpp
//

class Clr3cpecalgApp : public CWinApp
{
public:
	Clr3cpecalgApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Clr3cpecalgApp theApp;
