
// lr3_cpec_algView.h: интерфейс класса Clr3cpecalgView
//

#pragma once


class Clr3cpecalgView : public CView
{
protected: // создать только из сериализации
	Clr3cpecalgView() noexcept;
	DECLARE_DYNCREATE(Clr3cpecalgView)

// Атрибуты
public:
	Clr3cpecalgDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~Clr3cpecalgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	Rectangles rectInProgress;
	BOOL m_bDrawInProgress = FALSE;
	int m_dragNumberRect = -1;
	int m_dragNumberBall = -1;
	int m_selected = -1;
	int m_selectedBall = -1;
	int typeSelected;

	Ball ballInProgress;
	int typeFigure = 49;

	int findFigureRect(CPoint point);
	int findFigureBall(CPoint point);
// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // версия отладки в lr3_cpec_algView.cpp
inline Clr3cpecalgDoc* Clr3cpecalgView::GetDocument() const
   { return reinterpret_cast<Clr3cpecalgDoc*>(m_pDocument); }
#endif

