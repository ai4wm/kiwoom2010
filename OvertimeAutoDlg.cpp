// OvertimeAutoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "OvertimeAutoDlg.h"
#include "afxdialogex.h"


// COvertimeAutoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COvertimeAutoDlg, CDialog)

COvertimeAutoDlg::COvertimeAutoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COvertimeAutoDlg::IDD, pParent)
{

}

COvertimeAutoDlg::~COvertimeAutoDlg()
{
}

void COvertimeAutoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COvertimeAutoDlg, CDialog)
END_MESSAGE_MAP()

//*******************************************************************/
//! Function Name : OnInitDialog
//! Function      : 대화 초기 처리
//! Param         : void
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : CKwanSimDlg 메시지 처리기
//******************************************************************/
BOOL COvertimeAutoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 다이얼로그를 화면에 표시합니다.
	ShowWindow(SW_SHOW);

	return TRUE;
}
