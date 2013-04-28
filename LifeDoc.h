
#ifndef AFX_LifeAI2DOC_H_
#define AFX_LifeAI2DOC_H_

#include "LifeBoard.h"


#if _MSC_VER >= 1000
#pragma once
#endif


#define	BOARD_HEIGHT	14
#define BOARD_BORDER	25
#define BOARD_TAKE		41
#define BOARD_SIDE		BOARD_BORDER + BOARD_TAKE

class CLifeDoc : public CDocument {
protected:
	CLifeDoc();
	DECLARE_DYNCREATE(CLifeDoc)

public:

	//{{AFX_VIRTUAL(CLifeAIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:

	LifeBoard   my_Board;
	
	virtual ~CLifeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_bPlayer1First;
	//{{AFX_MSG(CLifeAIDoc)
	afx_msg void OnGameStatistics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
