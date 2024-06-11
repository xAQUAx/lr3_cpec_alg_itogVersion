
// lr3_cpec_algDoc.h: интерфейс класса Clr3cpecalgDoc 
//


#pragma once
#include "Rectangle.h"
#include "Ball.h"

class Clr3cpecalgDoc : public CDocument
{
protected: // создать только из сериализации
	Clr3cpecalgDoc() noexcept;
	DECLARE_DYNCREATE(Clr3cpecalgDoc)

// Атрибуты
public:
	CArray<Rectangles> m_rectangles;
	CArray<Ball> m_balls;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~Clr3cpecalgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
};
