// LifeView.cpp : implementation of the CLifeView class
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
// CLifeView

IMPLEMENT_DYNCREATE(CLifeView, CView)

BEGIN_MESSAGE_MAP(CLifeView, CView)
	//{{AFX_MSG_MAP(CLifeView)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_OPTIONS_RUN, RunLife)
	ON_COMMAND(ID_OPTIONS_RANDOMWORLD, RandomLife)
	ON_COMMAND(ID_OPTIONS_STEPFORWARD, Step_Fwd)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLifeView construction/destruction

CLifeView::CLifeView() {
	
	isAnimating = false;

}

CLifeView::~CLifeView() {}

BOOL CLifeView::PreCreateWindow(CREATESTRUCT& cs) {
	cs.cx = NUM_CELLS*15+100;
	cs.cy = NUM_CELLS*15+36;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLifeView drawing

void CLifeView::OnDraw(CDC* pDC) {
	CLifeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	CDC memdc;
	CBitmap membmp;
	memdc.CreateCompatibleDC(pDC);
	membmp.CreateCompatibleBitmap(pDC,NUM_CELLS*BOARD_HEIGHT+BOARD_SIDE,NUM_CELLS*BOARD_HEIGHT);
	memdc.SelectObject(&membmp);

	COLORREF col = ::GetSysColor(COLOR_3DFACE);
	COLORREF top = ::GetSysColor(COLOR_3DLIGHT);
	COLORREF btm = ::GetSysColor(COLOR_3DSHADOW);

	memdc.FillSolidRect(0,0,NUM_CELLS*BOARD_HEIGHT+BOARD_SIDE,NUM_CELLS*BOARD_HEIGHT+1,col);

	/*Create the grid*/
	for (int i=0;i<NUM_CELLS;i++) {
		for (int j=0;j<NUM_CELLS;j++) {
			memdc.Draw3dRect(i*BOARD_HEIGHT,j*BOARD_HEIGHT,BOARD_HEIGHT,BOARD_HEIGHT,top,btm);
		}
	}

	memdc.Draw3dRect(NUM_CELLS*BOARD_HEIGHT+BOARD_BORDER,0,BOARD_TAKE,NUM_CELLS*BOARD_HEIGHT,top,btm);

	CDC p1dc, p2dc;
	p1dc.CreateCompatibleDC(&memdc);
	p2dc.CreateCompatibleDC(&memdc);
	CBitmap p1,p2;
	p1.LoadBitmap(IDB_ALIVE);
	p2.LoadBitmap(IDB_DEAD);

	p1dc.SelectObject(&p1);
	p2dc.SelectObject(&p2);
	

	for (i=0;i<13;i++) {
		for (int j=0;j<13;j++) {
			if (p1dc.GetPixel(i,j) == RGB(255,0,255))
				p1dc.SetPixel(i,j,col);
			if (p2dc.GetPixel(i,j) == RGB(255,0,255))
				p2dc.SetPixel(i,j,col);
		}
	}

	/* Either animate the cells or just paint them*/
	if (!isAnimating){

		// Draw the cells
		for (i=0;i<NUM_CELLS;i++) {
			for (int j=0;j<NUM_CELLS;j++) {
				char state = pDoc->my_Board.stateAt(i,j);

				if (state == 0) continue;
	
				CDC *bdc = (state == '*') ? &p1dc : &p2dc;
				memdc.BitBlt(i*BOARD_HEIGHT,j*BOARD_HEIGHT,13,13,bdc,0,0,SRCCOPY);
			}
		}
		pDC->BitBlt(0,0,NUM_CELLS*BOARD_HEIGHT + BOARD_SIDE,NUM_CELLS*BOARD_HEIGHT,&memdc,0,0,SRCCOPY);
	}
	else{
		/* Animate the cells for 100 steps at a time*/
		for(int gen=0; gen<100; gen++){
			pDoc->my_Board.setWorld();
			for (i=0;i<NUM_CELLS;i++) {
				for (int j=0;j<NUM_CELLS;j++) {

				char state = pDoc->my_Board.stateAt(i,j);

				if (state == 0) continue;

				CDC *bdc = (state == '*') ? &p1dc : &p2dc;
				memdc.BitBlt(i*BOARD_HEIGHT,j*BOARD_HEIGHT,13,13,bdc,0,0,SRCCOPY);
				}
			}
		pDC->BitBlt(0,0,NUM_CELLS*BOARD_HEIGHT + BOARD_SIDE,NUM_CELLS*BOARD_HEIGHT,&memdc,0,0,SRCCOPY);
		}

		isAnimating = false;  //reset this, b/c we're done
	}




}

/////////////////////////////////////////////////////////////////////////////
// CLifeView diagnostics

#ifdef _DEBUG
void CLifeView::AssertValid() const
{
	CView::AssertValid();
}

void CLifeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLifeDoc* CLifeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLifeDoc)));
	return (CLifeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLifeView message handlers

void CLifeView::OnLButtonUp(UINT nFlags, CPoint point) {


	//GetDocument()->m_cBoard.ToggleAt(int(point.x/BOARD_HEIGHT), int(point.y/BOARD_HEIGHT));
	GetDocument()->my_Board.ToggleAt(int(point.x/BOARD_HEIGHT), int(point.y/BOARD_HEIGHT));

	Invalidate(false);
	CView::OnLButtonUp(nFlags, point);
}

void CLifeView::OnInitialUpdate() {

	CView::OnInitialUpdate();
}


void CLifeView::GameOver(int winresult) {

}

void CLifeView::OnFileNew() {

	GetDocument()->my_Board.RestartGame();
	//GetDocument()->OnNewDocument();
	
    Invalidate(false);
	
}

void CLifeView::RandomLife(){

	GetDocument()->my_Board.initializeWorld();

    Invalidate(false);
}

//Advance the world one step
void CLifeView::Step_Fwd(){

	GetDocument()->my_Board.setWorld();
	Invalidate(false);
}


void CLifeView::RunLife(){

    isAnimating = true;

	Invalidate(false);
}
