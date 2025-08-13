#pragma once


// COvertimeAutoDlg 대화 상자입니다.

class COvertimeAutoDlg : public CDialog
{
	DECLARE_DYNAMIC(COvertimeAutoDlg)

public:
	COvertimeAutoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COvertimeAutoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OVERTIMEAUTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:
	CWnd*		m_pParent;
	CString		m_strScrNo;
	CString		m_strJongCode;

// 생성합니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
