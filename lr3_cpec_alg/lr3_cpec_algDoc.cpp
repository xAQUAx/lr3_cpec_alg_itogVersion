
// lr3_cpec_algDoc.cpp: реализация класса Clr3cpecalgDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "lr3_cpec_alg.h"
#endif

#include "lr3_cpec_algDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Clr3cpecalgDoc

IMPLEMENT_DYNCREATE(Clr3cpecalgDoc, CDocument)

BEGIN_MESSAGE_MAP(Clr3cpecalgDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение Clr3cpecalgDoc

Clr3cpecalgDoc::Clr3cpecalgDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

Clr3cpecalgDoc::~Clr3cpecalgDoc()
{
}

BOOL Clr3cpecalgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация Clr3cpecalgDoc

void Clr3cpecalgDoc::Serialize(CArchive& ar)
{
	INT_PTR num[2] = {};
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
		num[0] = m_rectangles.GetCount();
		ar << num[0];
		for (int i = 0; i < num[0]; i++)
		{
			ar << m_rectangles[i].x;
			ar << m_rectangles[i].y;
			ar << m_rectangles[i].width;
			ar << m_rectangles[i].height;

		}

		num[1] = m_balls.GetCount();
		ar << num[1];
		for (int i = 0; i < num[1]; i++)
		{
			ar << m_balls[i].x;
			ar << m_balls[i].y;
			ar << m_balls[i].r;
		}
	}
	else
	{
		// TODO: добавьте код загрузки
		ar >> num[0];
		for (int i = 0; i < num[0]; i++)
		{
			Rectangles r;
			ar >> r.x;
			ar >> r.y;
			ar >> r.width;
			ar >> r.height;

			m_rectangles.Add(r);
		}

		ar >> num[1];
		for (int i = 0; i < num[1]; i++)
		{
			Ball b;
			ar >> b.x;
			ar >> b.y;
			ar >> b.r;

			m_balls.Add(b);
		}
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void Clr3cpecalgDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void Clr3cpecalgDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void Clr3cpecalgDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика Clr3cpecalgDoc

#ifdef _DEBUG
void Clr3cpecalgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Clr3cpecalgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды Clr3cpecalgDoc


void Clr3cpecalgDoc::DeleteContents()
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_rectangles.RemoveAll();
	m_balls.RemoveAll();
	CDocument::DeleteContents();
}
