// LifeDoc.cpp : implementation of the CLifeDoc class
//

#include "stdafx.h"
#include "Life.h"

#include "LifeDoc.h"
#include "LifeView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLifeDoc

IMPLEMENT_DYNCREATE(CLifeDoc, CDocument)

BEGIN_MESSAGE_MAP(CLifeDoc, CDocument)
	//{{AFX_MSG_MAP(CLifeDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLifeDoc construction/destruction

CLifeDoc::CLifeDoc() {}

CLifeDoc::~CLifeDoc() {}

BOOL CLifeDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLifeDoc serialization

void CLifeDoc::Serialize(CArchive& ar) {
	POSITION pos = GetFirstViewPosition();
	CLifeView *view = (CLifeView *)(GetNextView(pos));

	ASSERT(view);
	
	if (ar.IsStoring()) {

	} else {

	}
}

/////////////////////////////////////////////////////////////////////////////
// CLifeDoc diagnostics

#ifdef _DEBUG
void CLifeDoc::AssertValid() const {
	CDocument::AssertValid();
}

void CLifeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLifeDoc commands

