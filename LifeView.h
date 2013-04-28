
#ifndef _AFX_LIFE2VIEW_H_
#define _AFX_LIFE2VIEW_H_

#if _MSC_VER >= 1000
	#pragma once
#endif


class CLifeView : public CView {

protected:
	CLifeView();
	DECLARE_DYNCREATE(CLifeView)

public:

	CLifeDoc* GetDocument();

	//{{AFX_VIRTUAL(CLifeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

public:
	virtual ~CLifeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool	isAnimating;


protected:

	void GameOver(int);

	//{{AFX_MSG(CLifeView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void Step_Fwd();
	afx_msg void RunLife();	
	afx_msg void RandomLife();	
	afx_msg void OnFileNew();


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CLifeDoc* CLifeView::GetDocument()
   { return (CLifeDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}

#endif
