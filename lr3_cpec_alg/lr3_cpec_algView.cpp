
// lr3_cpec_algView.cpp: реализация класса Clr3cpecalgView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "lr3_cpec_alg.h"
#endif

#include "lr3_cpec_algDoc.h"
#include "lr3_cpec_algView.h"

#include "Rectangle.h"
#include "Ball.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clr3cpecalgView

IMPLEMENT_DYNCREATE(Clr3cpecalgView, CView)

BEGIN_MESSAGE_MAP(Clr3cpecalgView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// Создание или уничтожение Clr3cpecalgView

Clr3cpecalgView::Clr3cpecalgView() noexcept
{
	// TODO: добавьте код создания

}

Clr3cpecalgView::~Clr3cpecalgView()
{
}

BOOL Clr3cpecalgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование Clr3cpecalgView

void Clr3cpecalgView::OnDraw(CDC* pDC)
{
	Clr3cpecalgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return; 

	// TODO: добавьте здесь код отрисовки для собственных данных
	for (int i = 0; i < pDoc->m_rectangles.GetCount(); i++)
	{
		CPen pen;
		CPen* oldPen = NULL;

		auto r = pDoc->m_rectangles.GetAt(i);

		if (i == m_selected && typeSelected == 1)
		{
			pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldPen = pDC->SelectObject(&pen);
		}

		pDC->Rectangle(r.x, r.y, r.x + r.width, r.y + r.height);

		if (oldPen)
		{
			pDC->SelectObject(oldPen);
			oldPen = NULL;
		}
	}

	for (int i = 0; i < pDoc->m_balls.GetCount(); i++)
	{
		CPen pen;
		CPen* oldPen = NULL;

		auto b = pDoc->m_balls.GetAt(i);

		if (i == m_selected && typeSelected == 2)
		{
			pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldPen = pDC->SelectObject(&pen);
		}

		pDC->Ellipse(b.x-b.r, b.y+b.r, b.x+b.r, b.y-b.r);

		if (oldPen)
		{
			pDC->SelectObject(oldPen);
			oldPen = NULL;
		}
	}

	if (m_bDrawInProgress)
	{
		pDC->Rectangle(rectInProgress.x, rectInProgress.y, rectInProgress.x + rectInProgress.width, rectInProgress.y + rectInProgress.height);
		pDC->Ellipse(ballInProgress.x - ballInProgress.r, ballInProgress.y + ballInProgress.r, ballInProgress.x + ballInProgress.r, ballInProgress.y - ballInProgress.r);
	}
}


// Диагностика Clr3cpecalgView

#ifdef _DEBUG
void Clr3cpecalgView::AssertValid() const
{
	CView::AssertValid();
}

void Clr3cpecalgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clr3cpecalgDoc* Clr3cpecalgView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clr3cpecalgDoc)));
	return (Clr3cpecalgDoc*)m_pDocument;
}
#endif //_DEBUG

int Clr3cpecalgView::findFigureRect(CPoint point)
{
	auto pDoc = GetDocument();
	for (int i = pDoc->m_rectangles.GetCount()-1; i >= 0; i--)
	{
		RECT r;
		r.left = pDoc->m_rectangles[i].x;
		r.right = pDoc->m_rectangles[i].x + pDoc->m_rectangles[i].width;
		r.top = pDoc->m_rectangles[i].y;
		r.bottom = pDoc->m_rectangles[i].y + pDoc->m_rectangles[i].height;

		if (r.left > r.right)
			std::swap(r.left, r.right);
		if (r.top > r.bottom)
			std::swap(r.top, r.bottom);
		if (PtInRect(&r, point))
		{
			return i;
		}
	}

	return -1;
}

int Clr3cpecalgView::findFigureBall(CPoint point)
{
	auto pDoc = GetDocument();
	for (int i = pDoc->m_balls.GetCount() - 1; i >= 0; i--)
	{
		RECT r;
		r.left = pDoc->m_balls[i].x - pDoc->m_balls[i].r;
		r.right = pDoc->m_balls[i].x + pDoc->m_balls[i].r;
		r.top = pDoc->m_balls[i].y + pDoc->m_balls[i].r;
		r.bottom = pDoc->m_balls[i].y - pDoc->m_balls[i].r;

		if (r.left > r.right)
			std::swap(r.left, r.right);
		if (r.top > r.bottom)
			std::swap(r.top, r.bottom);
		if (PtInRect(&r, point))
		{
			return i;
		}
	}
	return -1;
}

// Обработчики сообщений Clr3cpecalgView


void Clr3cpecalgView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	auto pDoc = GetDocument();

	int figRectNumber = findFigureRect(point);
	int figBallNumber = findFigureBall(point);

	if (figRectNumber > -1)
	{
		m_dragNumberRect = figRectNumber;
		rectInProgress.x = point.x;
		rectInProgress.y = point.y;
	}
	else
	{
		if (figBallNumber > -1)
		{
			m_dragNumberBall = figBallNumber;
			ballInProgress.x = point.x;
			ballInProgress.y = point.y;
		}
		else
		{
			if (typeFigure == 49)
			{
				rectInProgress.x = point.x;
				rectInProgress.y = point.y;
			}

			if (typeFigure == 50)
			{
				ballInProgress.x = point.x;
				ballInProgress.y = point.y;
			}
			m_bDrawInProgress = TRUE;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void Clr3cpecalgView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (m_dragNumberRect > -1)
	{
		m_dragNumberRect = -1;
	}

	if (m_dragNumberBall > -1)
	{
		m_dragNumberBall = -1;
	}

	if (m_bDrawInProgress)
	{
		if (typeFigure == 49)
		{
			rectInProgress.width = point.x - rectInProgress.x;
			rectInProgress.height = point.y - rectInProgress.y;

			auto pDoc = GetDocument();
			pDoc->m_rectangles.Add(rectInProgress);

			pDoc->SetModifiedFlag();
		}

		if (typeFigure == 50)
		{
			ballInProgress.r = pow((pow(point.x - ballInProgress.x, 2) + pow(point.y - ballInProgress.y, 2)), 0.5);

			auto pDoc = GetDocument();
			pDoc->m_balls.Add(ballInProgress);

			pDoc->SetModifiedFlag();
		}

		m_bDrawInProgress = FALSE;
	}
	InvalidateRect(NULL);
	CView::OnLButtonUp(nFlags, point);
}


void Clr3cpecalgView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (m_bDrawInProgress)
	{
		if (typeFigure == 49)
		{
			rectInProgress.width = point.x - rectInProgress.x;
			rectInProgress.height = point.y - rectInProgress.y;
		}

		if (typeFigure == 50)
		{
			ballInProgress.r = pow((pow(point.x - ballInProgress.x, 2) + pow(point.y - ballInProgress.y, 2)), 0.5);
		}

		InvalidateRect(NULL);
	}
	
	if (m_dragNumberRect > -1 )
	{
		int offsetX = point.x - rectInProgress.x;
		int offsetY = point.y - rectInProgress.y;
		rectInProgress.x = point.x;
		rectInProgress.y = point.y;

		auto pDoc = GetDocument();
		Rectangles r = pDoc->m_rectangles[m_dragNumberRect];
		r.x += offsetX;
		r.y += offsetY;
		pDoc->m_rectangles.SetAt(m_dragNumberRect, r);

		InvalidateRect(NULL);
	}

	if (m_dragNumberBall > -1)
	{
		int offsetBallX = point.x - ballInProgress.x;
		int offsetBallY = point.y - ballInProgress.y;
		ballInProgress.x = point.x;
		ballInProgress.y = point.y;

		auto pDoc = GetDocument();
		Ball b = pDoc->m_balls[m_dragNumberBall];
		b.x += offsetBallX;
		b.y += offsetBallY;
		pDoc->m_balls.SetAt(m_dragNumberBall, b);

		InvalidateRect(NULL);
	}

	CView::OnMouseMove(nFlags, point);
}


void Clr3cpecalgView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	auto pDoc = GetDocument();
	auto selectedRect = findFigureRect(point);
	auto selectedBall = findFigureBall(point);

	if (m_selected == selectedRect && m_selected == selectedBall)
		m_selected = -1;
	else
	{
		if (selectedRect > -1)
		{
			m_selected = selectedRect;
			typeSelected = 1; //флаг что мы выбрали прямоугольник
		}

		if (selectedBall > -1)
		{
			m_selected = selectedBall;
			typeSelected = 2; //флаг что мы выбрали круг
		}
	}

	InvalidateRect(NULL);
	CView::OnRButtonDown(nFlags, point);
}


void Clr3cpecalgView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if ((m_selected > -1) && (nChar == VK_DELETE))
	{
		auto pDoc = GetDocument();
		switch (typeSelected)
		{
		case 1:
			pDoc->m_rectangles.RemoveAt(m_selected);
			break;
		case 2:
			pDoc->m_balls.RemoveAt(m_selected);
			break;
		}

		pDoc->SetModifiedFlag();
		m_selected = -1;
		Invalidate();
	}

	if (nChar == 49)
	{
		typeFigure = 49;
	}
	
	if (nChar == 50)
	{
		typeFigure = 50;
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
