//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2015 (��)�ѱ��Ҹ���ġ                /
//******************************************************************/
//! File Name     : RealAddDlg.cpp
//! Function      : ������ ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2015/04/01
//! Update        : 
//! Comment       : 
//******************************************************************/
// RealAddDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "RealAddDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FIDLIST	_T("9001;302;10;25;12;61;71;292;295;21")

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPTSBFID[] = 
{
	{"�����ڵ�",					"9001",	    -1,	0,	DT_NONE,		FALSE,	DT_LEFT,	"",	""}, 
	{"�����",						"302",		-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	"",	""}, 
	{"���簡",						"10",		-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"���ϴ���ȣ",				"25",		-1,	3,	DT_SIGN,		TRUE,	DT_CENTER,	"",	""}, 
	{"�����",						"12",		-1,	4,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
	{"�ŵ��ܷ�",					"61",		-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""},
	{"�ż��ܷ�",					"71",		-1,	6,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""},
	{"����ü�ᷮ",					"292",		-1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""},
	{"��������",					"295",		-1,	8,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"},
//	{"�ŷ���",						"13",		-1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_LEFT,	"",	""},
//	{"����ü�ᰡ",					"23",		-1,	10,	DT_ZERO_NUMBER,	FALSE,	DT_LEFT,	"",	""},
//	{"���Ϻ�",					    "30",		-1,	11,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"%"},
	{"��Ͻð�",					"21",		-1,	9,	DT_TIME,	    FALSE,	DT_RIGHT,	"",	""},
};

// CRealAddDlg ��ȭ ����
//*******************************************************************/
//! Function Name : CRealAddDlg::CRealAddDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CRealAddDlg::IDD, pParent)
//! Function      : ���� �ʱ� ó��
//! Param         : HANDLE hBitmap, int bits
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
CRealAddDlg::CRealAddDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRealAddDlg::IDD, pParent)
	, m_chk1(FALSE)
	, m_price(0)
	, m_start(false)
	, m_Jgubu(_T(""))
	, m_jumuntime(false)
{
	m_pParent = pParent;
	m_strScrNo = "9999";
	m_cellSelect.row = 0;
	m_cellSelect.col = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strPreConditionName = "";
	m_nPreConditionIndex = -1;
	m_strConditionName = "";
	m_nConditionIndex = -1;
	m_start = true;
	m_jumuntime = false;
	m_jumuntime2 = false;
	//bool jumun = false;
	//bool jumun2 = false;
	//bool jumun3 = false;
	//bool jumun4 = false;
}

//*******************************************************************/
// Function Name : DoDataExchange
// Function      : DDX/DDV�� ���� �� �Լ� ȣ��
// Param         : CDataExchange*	pDX
// Return        : void
// Create        : , 2015/04/01
// Comment       : DDX - ��Ʈ�Ѱ� ����������̿� ������ ��ȯ�ϴ� ����
//				 : DDV - ��������� ���� �� ���� ��ȿ�� üũ
//				 : UapdateData()�Լ��� ���� ȣ�� �� �� ����
//*******************************************************************/
void CRealAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRealAddDlg)
	DDX_Control(pDX, IDC_GRD_REALADD,		m_grdRealAdd);
	DDX_Control(pDX, IDC_CMB_CON,			m_cmbCon);
	DDX_Control(pDX, IDC_COMBO_ACCLIST,		m_strAcctList);
	DDX_Control(pDX, IDC_LIST_INSERT,		m_listCtl_Insert);
	DDX_Control(pDX, IDC_LIST_DELETE,		m_listCtl_Delete);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK1, m_chk1);
	DDX_Control(pDX, IDC_LIST1, m_listCtl_mumber);
	DDX_Control(pDX, IDC_COMBO_ACCLIST, m_strAcctList);
	DDX_Control(pDX, IDC_LIST2, m_listCtl_jumun);
}

//*******************************************************************/
// BEGIN_MESSAGE_MAP
//*******************************************************************/
BEGIN_MESSAGE_MAP(CRealAddDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEARCH,				OnBtnSearch)
	ON_BN_CLICKED(IDC_BTN_CLOSE,					OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_ALLCANCEL,			OnBnClickedBtnAllcancel)
	ON_BN_CLICKED(IDC_BTN_CONDI, &CRealAddDlg::OnBnClickedBtnCondi)
	ON_BN_CLICKED(IDC_BUTTON1, &CRealAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRealAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &CRealAddDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON3, &CRealAddDlg::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO_ACCLIST, &CRealAddDlg::OnCbnSelchangeComboAcclist)
	ON_BN_CLICKED(IDC_BUTTON4, &CRealAddDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CRealAddDlg::OnBnClickedButton5)
END_MESSAGE_MAP()

//*******************************************************************/
//! Function Name : OnInitDialog
//! Function      : ���� �ʱ� ó��
//! Param         : void
//! Return        : BOOL
//! Create        : , 2015/04/01
//! Comment       : CRealAddDlg �޽��� ó����
//******************************************************************/
BOOL CRealAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	InitRealAddGrid();					// �׸��� �ʱ� ó��

	((CEdit *) GetDlgItem(IDC_EDIT1))->SetLimitText(10); //�ݾ� �������� 99,999,999��
	/*CString str = theApp.m_khOpenApi.GetMasterLastPrice("066430");
	AfxMessageBox(str);*/
	//CString   strAcctList = theApp.m_khOpenApi.GetLoginInfo("ACCLIST");
	//AfxMessageBox(strAcctList);
	CString   resToken;
	int curPos = 0;

	CString strAcctList = theApp.m_khOpenApi.GetLoginInfo("ACCLIST");
	//CString check_date = _T("2010-02-11");
	TCHAR split_type[] = _T(";");

	TCHAR *p_next_token = NULL;
	TCHAR *p_token = _tcstok_s( (TCHAR *)(const TCHAR *)strAcctList, split_type, &p_next_token );

	m_strAcctList.ResetContent();
	int knum = 0;
	while( p_token != NULL ){
		//AfxMessageBox(p_token);
		m_strAcctList.AddString(p_token);
		p_token = _tcstok_s( NULL, split_type, &p_next_token );
		knum++;
	}

	m_strAcctList.SetCurSel(knum-1);
	m_strAcctList.GetLBText(m_strAcctList.GetCurSel(), m_strAcct);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

//*******************************************************************/
//! Function Name : OnPaint
//! Function      : �׸��� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//!               : �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//!               : �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
//******************************************************************/
void CRealAddDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//*******************************************************************/
//! Function Name : OnClose
//! Function      : �ı���
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnClose()
{
	// ȭ�� ���� �� �θ������쿡�� �뺸(ȭ�� ���� ����)
	if (m_pParent)
	{
		//�ü� �ǽð� ����
		theApp.m_khOpenApi.SetRealRemove(m_strScrNo, _T("ALL"));

		if (m_strConditionName != "" && m_nConditionIndex > -1)
		{
			theApp.m_khOpenApi.SendConditionStop(m_strScrNo, m_strConditionName, m_nConditionIndex);
		}
		int nLen = m_strScrNo.GetLength();
		char *cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);
	}

	CDialogEx::OnClose();
}

//*******************************************************************/
//! Function Name : OnQueryDragIcon
//! Function      : �巡�� ������ ó��
//! Param         : void
//! Return        : HCURSOR
//! Create        : , 2015/04/01
//! Comment       : ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ��� 
//!               : �� �Լ��� ȣ���մϴ�.
//******************************************************************/
HCURSOR CRealAddDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*******************************************************************/
//! Function Name : OnBtnSearch
//! Function      : �ü� �ǽð����
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnBtnSearch()
{
	//�ü� �ǽð���� �Լ� ȣ��
	//���� ���� ���簡, ���, �����, �ŷ���� ���� �ǽð��� �ޱ� ���� �ݵ�� ȣ���ؾ���.
	int nCount = m_grdRealAdd.GetRowCount();
	CString strCodeList;
	
	for (int i = 1; i < nCount; i++)
	{
		strCodeList += m_grdRealAdd.GetItemText(i, 0) + ";";
	}

	long lRet = theApp.m_khOpenApi.SetRealReg(m_strScrNo, strCodeList, FIDLIST, "1");
}

//*******************************************************************/
//! Function Name : OnBtnClose
//! Function      : �ǽð� ����.
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnBtnClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	theApp.m_khOpenApi.SetRealRemove(m_strScrNo, _T("ALL"));
}

//*******************************************************************/
//! Function Name : InitRealAddGrid
//! Function      : ȣ�� �׸��� �ʱ� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::InitRealAddGrid()
{
	m_grdRealAdd.SetEditable(false);				//cell�� ����Ʈ ���ϰ� ��.
	m_grdRealAdd.EnableScrollBars(SB_BOTH, TRUE);

	COLORREF clr = RGB(215, 227, 241);

	// ���� ��/�� ����
	m_grdRealAdd.SetFixedRowCount(1);

	// ��/�� ���� ����
	m_grdRealAdd.SetRowCount(1);
	m_grdRealAdd.SetColumnCount(10);

	// ���� ���� ����
	int i, nWidth[] = {70, 100, 80, 30, 70, 80 , 80 , 80, 70, 80};//{70, 100, 80, 30, 70, 90 , 90 , 80, 70, 90, 80, 90, 80}{50, 80, 60, 20, 50, 70 , 70 , 60, 50, 70, 60, 70, 60}
	CString strHeader[] = {"�ڵ�", "�����", "���簡", "��", "�����", "�ŵ��ܷ�", "�ż��ܷ�", "��ü�ᷮ", "�����", "��Ͻð�"};
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nCnt; i++)
	{
		m_grdRealAdd.SetColumnWidth(i, nWidth[i]);//nWidth[i] (0,LVSCW_AUTOSIZE_USEHEADER);
		m_grdRealAdd.SetItemFormat(0, i, DT_CENTER);
		m_grdRealAdd.SetItemText(0, i, strHeader[i]);
		m_grdRealAdd.SetItemBkColour(0, i, clr);	// ������ ���� ���� ����
	}

	// ���� ���� ����
	m_grdRealAdd.SetRowHeight(0, 24);//LVSCW_AUTOSIZE_USEHEADER 24

	m_grdRealAdd.Invalidate();
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	return;
}

//*******************************************************************/
//! Function Name : OnReceiveMsgKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg
//! Return        : void//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : �ǽð� ó��
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	CString strIndex;
	//AfxMessageBox("kkkkkkkkkkkkkkkkkkkkkkkkk");
	if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
	{
		return;
	}

	CString strData;
	CStringArray arrData;
	
	CString strRQName = _T("�ֽ��ֹ�");
	long lRet;
	lRet = OP_ERR_ORD_OVERFLOW;

	arrData.Add(sJongmokCode);
	int i, nFieldCnt = sizeof(lstOPTSBFID) / sizeof(*lstOPTSBFID);		// ��üũ�� / ����ũ�� = ���Ұ���
	int jnum = m_grdRealAdd.GetColumnCount();
	/*CString str2;
	str2.Format("%d", nFieldCnt);
	SetDlgItemText(IDC_STATIC1,str2);*/

	for (i = 1; i < nFieldCnt; i++)
	{		
		if (atoi(lstOPTSBFID[i].strRealKey) < 0)
		{
			arrData.Add("");
			continue;
		}
		strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPTSBFID[i].strRealKey));	strData.Trim();
		
		if(IsDlgButtonChecked(IDC_CHECK1)) {
			/*CString strRQName = _T("���簡/��������");
			CString strTRCode = TR_OPT10001;
			theApp.m_khOpenApi.SetInputValue("�����ڵ�", sJongmokCode);
			long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
			CString		strErr;
			if (!theApp.IsError(lRet))
			{
				strErr.Format(_T("�ֽı⺻������û ���� [%s][%d]"), strTRCode, lRet);
				OutputDebugString(strErr);
			}*/

			
			if(i == 7) { //����ü�ᷮ
				if (_ttoi(strData) > 0) {
					if(m_Jgubu2.Find(sJongmokCode) < 0) {
						m_Jgubu2 += sJongmokCode;
						m_Jgubu2 += "|";
					}
				} else if (_ttoi(strData) == 0){
					if(m_Jgubu.Find(sJongmokCode) >= 0) {
						m_Jgubu2.Delete( m_Jgubu2.Find(sJongmokCode), 7 );//vi�ߵ�����
					}
				}
				//AfxMessageBox(sJongmokCode);
			}
			if(i == 8) { //��������
				//USES_CONVERSION;
				//strData = A2CT(sJongmokCode);
				//strData = sJongmokCode;
				
				if(31 > _ttoi(strData) && _ttoi(strData) > 10) {//�������� vi(������ ��ȭ��ġ) �ߵ�
					/*CString str2;
					str2.Format("%d", atoi(strData));
					AfxMessageBox(str2+"######");
					AfxMessageBox(sJongmokCode)*/;
					//CommRqData( "RQName"	,  "opt10001"	,  "0"	,  "ȭ���ȣ");
					CString str = theApp.m_khOpenApi.GetMasterLastPrice(sJongmokCode);
					//int qty;// �ֹ����� quantity
					//qty = m_price/(atoi(str)*1.3);
					CString Margin = theApp.m_khOpenApi.GetMasterStockState(sJongmokCode);
					double besu = 1;
					if(IsDlgButtonChecked(IDC_CHECK2)) {
						besu = 1;
					} else if(Margin.Find("100%") >= 0) {
						besu = 1;
					} else if(Margin.Find("40%") >= 0) {
						besu = 3.3;//3.3 2.5
						//m_price = m_price + m_price + m_price/2;
					} else if(Margin.Find("50%") >= 0) {
						besu = 2.5;//2.5 2
						//m_price = m_price + m_price;
					} else if(Margin.Find("60%") >= 0) {
						besu = 2;//2 1.6
						//m_price = m_price + m_price + m_price + m_price + m_price;
					} else if(Margin.Find("30%") >= 0) {
						besu = 5;// 5 3.3
						//m_price = m_price + m_price + m_price/3;
					} else if(Margin.Find("20%") >= 0) {
						besu = 5;
						//m_price = m_price + m_price + m_price + m_price + m_price;
					} 
					int qty;// �ֹ����� quantity
					int qty2;// �ֹ����� quantity
					int qty3;// �ֹ����� quantity
					qty2 = m_price/(atoi(str)*1.3);
					qty = m_price*besu/(atoi(str)*1.3);
					qty3 = qty - qty2;
					
					if(qty > 0 && m_Jgubu.Find(sJongmokCode) < 0) {
						lRet = theApp.m_khOpenApi.SendOrder(strRQName, "0101", m_strAcct, 1/*�ֹ�����*/, sJongmokCode, qty, 0, "03", "");//5031295011 1129984611
						CString str2;
					    str2.Format("%d", qty3);
						CString jongname = theApp.m_khOpenApi.GetMasterCodeName(sJongmokCode);						
					    m_listCtl_mumber.InsertString(0, jongname+" : "+str2);
						if(m_Jgubu.Find(sJongmokCode) < 0) {
							m_Jgubu += sJongmokCode;
							m_Jgubu += "|";
							m_jumuntime = true;
						}
						//((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(0);  
						PlaySound("C:\\sound10.wav" , NULL, SND_ASYNC | SND_LOOP);// http://xxxr.cafe24.com/gongsi.php?code=  https://finance.naver.com/item/main.nhn?code=
						CString data1 = _T("http://xxxr.cafe24.com/gongsi.php?code=");// http://board.moneta.co.kr/cgi-bin/paxBulletin/bulList.cgi?code=078940&boardid= 
						CString data2 = _T("https://finance.naver.com/item/news.nhn?code=");
					//	CString data2 = sJongmokCode; https://finance.naver.com/item/news.nhn?code=038880
						
					//	ShellExecute(NULL, "open", data1 + sJongmokCode , NULL, NULL,SW_SHOW);
					//	ShellExecute(NULL, "open", "iexplore", data1 + sJongmokCode , NULL, SW_SHOW);
						ShellExecute(NULL, "open", data2 + sJongmokCode , NULL, NULL,SW_SHOW);
					//	m_listCtl_jumun.InsertString(0, jongname+" : "+"�ֹ��� ����Ǿ����ϴ�!");
					//	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText("�ֹ��� ����Ǿ����ϴ�! Ȯ���غ�����");
					//	AfxMessageBox("�ֹ��� ����Ǿ����ϴ�! Ȯ���غ�����");
					} 
				} 
				if(_ttoi(strData) == 0 && strData == "0.00" && m_Jgubu2.Find(sJongmokCode) < 0) {
					if(m_Jgubu.Find(sJongmokCode) >= 0) {
						m_Jgubu.Delete( m_Jgubu.Find(sJongmokCode), 7 );
						m_jumuntime2 = true;//vi�ߵ� ����
						//AfxMessageBox(m_Jgubu+"+"+sJongmokCode);
					}
				}
				// �ֹ� ��ȣ
				//AfxMessageBox(m_Jgubu);
		        //CString jumunno = theApp.m_khOpenApi.GetCommData(sJongmokCode, strRQName, 0, _T("�ֹ���ȣ"));	jumunno.Trim();
				//AfxMessageBox(jumunno + "##");
				//theApp.m_khOpenApi.SendOrder(strRQName, "0101", "8070735711", 3/*�ֹ�����*/, sJongmokCode, 10, 0, "0", jumunno);
			}
			
		} else {  // ����ü�ᰡ ����� �ź�
			if(i == 8) {
				if(_ttoi(strData) != 100 && _ttoi(strData) != 0) {
					if(m_Jgubu.Find(sJongmokCode) < 0) {
						m_Jgubu += sJongmokCode;
						m_Jgubu += "|";
						CString jongname = theApp.m_khOpenApi.GetMasterCodeName(sJongmokCode);						
					    m_listCtl_mumber.AddString(jongname+" : ");
						PlaySound("C:\\sound11.wav" , NULL, SND_ASYNC);
					}
				}
			}
		}
		
		if(i == 9) {
			if(m_jumuntime) m_jumuntime = false;
			else if(m_jumuntime2) {
				m_jumuntime2 = false;
				strData = "-";//vi�ߵ� ����
				m_listCtl_jumun.InsertString(0, "---------------------------------------------");
			}
			else strData = "";
		}
		arrData.Add(strData);
	}
	SetDataRealAddGrid(arrData, sRealType);
}

//*******************************************************************/
//! Function Name : OnReceiveRealCondition
//! Function      : ���ǰ˻� �ǽð� ���� ����/��Ż
//! Param         : LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	CString strName, strMsg, strIndex, sType, sCode;
	sType = strType;	//���� ����, ��Ż ����
	sCode = strCode;	//�����ڵ�
	m_cmbCon.GetLBText(m_cmbCon.GetCurSel(), strName);	//���� ���õ� ���Ǹ�

	if (strName == strConditionName)	//���� ���õ� ���Ǹ�� �ǽð����� ���� ���Ǹ��� ������ ��.
	{
		if (sType == "I")	//���� ����
		{
			m_grdRealAdd.InsertRow(sCode, 1);

			// �����/
			CString strCodeName;
			strCodeName = theApp.m_khOpenApi.GetMasterCodeName(sCode);
			m_grdRealAdd.SetItemText(1, 1, strCodeName);

			//�ϴ� �޼��� ���̱�
			//�޼��� 5�ٸ� ������ Ŭ�����ϱ�.
			if (m_listCtl_Insert.GetCount() > 5)
			{
				m_listCtl_Insert.ResetContent();
			}

			strMsg.Format(_T("[%s] ������ ���ԵǾ����ϴ�."), sCode);
			m_listCtl_Insert.AddString(strMsg);

			//������ȸ�� ������ �ü��� ������ �ִ� ��Ȳ���� �߰��� ���Ե� ������ �ü��� �����ٶ� 
			// ������ �Ķ���Ϳ� "1"�� �־��־�� ���� ����� �Բ� ���Ե� ������ �ü��� ���´�.
			// ���� "1" �̿��� "0"�� �־��ָ� ������ ����� ����鿡 ���� �ü��� ��������.
			//�ǽð���� �Լ� ȣ��
			long lRet = theApp.m_khOpenApi.SetRealReg(m_strScrNo, strCode, FIDLIST, "1");
		} 
		else if (sType == "D")	//���� ��Ż
		{
			//������ �ִ� �������� Ȯ��.
			if (!m_mapJongCode.Lookup(sCode, strIndex))
			{
				return;
			}

			//��Ż ���� ����.
			m_grdRealAdd.DeleteRow(_ttoi(strIndex));

			//��Ż�� ������ �ü��� ���� �������� ����Ѵ�.
			theApp.m_khOpenApi.SetRealRemove(m_strScrNo, sCode);

			//�ϴ� �޼��� ���̱�
			//�޼��� 5�ٸ� ������ Ŭ�����ϱ�.
			if (m_listCtl_Delete.GetCount() > 5)
			{
				m_listCtl_Delete.ResetContent();
			}

			strMsg.Format(_T("[%s] ������ ��Ż�Ǿ����ϴ�."), sCode);
			m_listCtl_Delete.AddString(strMsg);
		}

		m_grdRealAdd.Invalidate();

 		m_mapJongCode.RemoveAll();

		int nCount = m_grdRealAdd.GetRowCount();
		for (int i = 1; i < nCount; i++)
		{
			sCode = m_grdRealAdd.GetItemText(i, 0);
			strIndex.Format("%d", i);
			m_mapJongCode.SetAt(sCode, strIndex);
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveTrCondition
//! Function			: ���ǰ˻� ���񸮽�Ʈ ��ȸ����
//! Param				: LPCTSTR sScrNo					- ȭ���ȣ
//!						: PCTSTR strCodeList				- ���񸮽�Ʈ
//!						: LPCTSTR strConditionName	- ���Ǹ�
//!						: int nIndex								- ���Ǹ� �ε�����ȣ
//!						: int nNext								- ������ȸ(2:������ȸ, 0:������ȸ����)
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnReceiveTrCondition(LPCTSTR sScrNo,PCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	CString strCndName, sConditionName;
	m_cmbCon.GetLBText(m_cmbCon.GetCurSel(), strCndName);	//���õ� ���Ǹ�

	if (strConditionName == strCndName)	//���� ���Ǹ�� ��ȸ�������� ���� ���Ǹ��� �������� ó��.
	{
		if (strCodeList != "")
		{
			int nIndex(0);
			CString strConditionCode;
			m_mapJongCode.RemoveAll();		// �����ڵ� �ʱ�ȭ
			m_grdRealAdd.SetRowCount(1);

			while ( AfxExtractSubString( strConditionCode, strCodeList, nIndex++, _T(';')) )
			{
			}

			m_grdRealAdd.SetRowCount(nIndex-1);

			nIndex = 0;
			CString strIndex;
			while ( AfxExtractSubString( strConditionCode, strCodeList, nIndex++, _T(';')) )
			{
				if (strConditionCode != "")
				{
					m_grdRealAdd.SetRowHeight(nIndex, 20);		// ���� ���� ����20
					m_grdRealAdd.SetItemText(nIndex, 0, strConditionCode);

					// �����
					CString strCodeName;
					strCodeName = theApp.m_khOpenApi.GetMasterCodeName(strConditionCode);
					m_grdRealAdd.SetItemText(nIndex, 1, strCodeName);

					strIndex.Format("%d", nIndex);
					m_mapJongCode.SetAt(strConditionCode, strIndex);
				}
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveConditionVer
//! Function			: ����� ���ǽ� ��ȸ����
//! Param				: BOOL bRet							- ����(TRUE), ����(FALSE)
//!						: LPCTSTR sMsg					- �޼���(reserved)
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	CString strMsg(sMsg);
	if (lRet == 1)
	{
		//���ǰ˻��� ����Ʈ�� �ҷ��´�.
		CString strCondition, strConditionName, strIndex;
		CString strConditionNameList = theApp.m_khOpenApi.GetConditionNameList();

		//�޾ƿ� ���ǰ˻����� �޺��� �ִ´�.
		m_cmbCon.ResetContent();

		int i(0);

		while( AfxExtractSubString( strCondition, strConditionNameList, i++, _T(';')) )
		{
			if (strCondition != _T(""))
			{
				strCondition.Trim();
				int nPos = strCondition.Find("^");
				int nConditionNo = atoi(strCondition.Left(nPos));
				strConditionName = strCondition.Mid(nPos+1, strCondition.GetLength());
				strIndex.Format(_T("%d"), nConditionNo);
				m_mapNameList.SetAt(strConditionName, strIndex);
				m_cmbCon.InsertString(i-1, strConditionName);
			}
		}

		m_cmbCon.SetCurSel(0);
		BOOL bRet = theApp.m_khOpenApi.SendCondition(m_strScrNo, "�����Ǹ�1", 0, 1);
	}
	else
	{
		CString		strErr;
		strErr.Format(_T("����� �����б� ���� \r\n\r\n[%s]"), strMsg);
		AfxMessageBox(strErr);
	}
}

//*******************************************************************/
//! Function Name : SetDataRealAddGrid
//! Function      : �׸��� ����Ÿ ����(������������ ����)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::SetDataRealAddGrid(CStringArray &arrData, CString strRealType/* = ""*/)
{
	// �����ڵ忡 �´� �� ã��
	CString strData, strTemp;
	strData = arrData.GetAt(0);
	if (!m_mapJongCode.Lookup(strData, strTemp))
	{
		return;
	}

	int i, nRow = atol(strTemp), nCnt = arrData.GetSize();

	// ����Ÿ ����
	CString strTempData;
	for (i = 1; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		/////////////////////////////////////////////
		// ���� �� ������ ���� ó������������
		if (strRealType != "" && (i == 2 || i == 4 || i == 5))
		{
			strTempData = strData;
			strTempData.Replace("+", "");	strTempData.Replace("-", "");	strTempData.Replace(".", "");

			strTemp = m_grdRealAdd.GetItemText(nRow, lstOPTSBFID[i].nCol);
			strTemp.Replace("%", "");	strTemp.Replace("+", "");	strTemp.Replace("-", "");
			strTemp.Replace(",", "");	strTemp.Replace(".", "");
			if (strTempData != strTemp)
			{
				m_cellSelect.col = lstOPTSBFID[i].nCol;
				m_grdRealAdd.SetFocusCell(m_cellSelect);
				m_grdRealAdd.SetSelectedRange(nRow, m_cellSelect.col, nRow, m_cellSelect.col);
				m_grdRealAdd.Invalidate();
			}
		}
		// ���� �� ������ ���� ó������������
		/////////////////////////////////////////////
		if (lstOPTSBFID[i].bTextColor)
		{
			strTemp = arrData.GetAt(3);
			if (strTemp == "1" || strTemp == "2")	// ��ȣ�� ���� ���󺯰�
			{
				strTemp = "1";
			}
			else if (strTemp == "4" || strTemp == "5")	// ��ȣ�� ���� ���󺯰�
			{
				strTemp = "-1";
			}
			else
			{
				strTemp = "0";
			}
			theApp.SetDataFgColour(&m_grdRealAdd, nRow, lstOPTSBFID[i].nCol, strTemp);
		}
		if (lstOPTSBFID[i].nDataType == DT_SIGN)
		{
			if (strData.IsEmpty())
			{
				continue;
			}
			theApp.SetSignData(&m_grdRealAdd, nRow, lstOPTSBFID[i].nCol, strData);
		}
		else
		{
			if (strData.IsEmpty())
			{
				continue;
			}
			int nCol = lstOPTSBFID[i].nCol;
			m_grdRealAdd.SetItemText(nRow, lstOPTSBFID[i].nCol, theApp.ConvDataFormat(lstOPTSBFID[i].nDataType, strData, lstOPTSBFID[i].strBeforeData, lstOPTSBFID[i].strAfterData));
		}
	}
	m_grdRealAdd.Invalidate();
}

//*******************************************************************/
//! Function Name : OnBtnClose
//! Function      : ��ȭ�� �ǽð� ��� ����
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnBnClickedBtnAllcancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	theApp.m_khOpenApi.SetRealRemove(_T("ALL"), _T("ALL"));
}

//*******************************************************************/
//! Function Name : OnBnClickedBtnCondi
//! Function      : ���Ǹ� ����Ʈ�� �ҷ��ͼ� �޺��� ����.
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/22
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnBnClickedBtnCondi()
{
	CString strConditionName = _T(""), strConditionNameList = _T(""), strCondition = _T(""), strIndex = _T("");

	//���ǰ˻��� ����Ʈ�� �ҷ��´�.
	strConditionNameList = theApp.m_khOpenApi.GetConditionNameList();

	//�޾ƿ� ���ǰ˻����� �޺��� �ִ´�.
	m_cmbCon.ResetContent();

	int i(0);

	while( AfxExtractSubString( strCondition, strConditionNameList, i++, _T(';')) )
	{
		if (strCondition != _T(""))
		{
			strCondition.Trim();
			int nPos = strCondition.Find("^");
			int nConditionNo = atoi(strCondition.Left(nPos));
			strConditionName = strCondition.Mid(nPos+1, strCondition.GetLength());
			strIndex.Format(_T("%d"), nConditionNo);
			m_mapNameList.SetAt(strConditionName, strIndex);
			m_cmbCon.InsertString(i-1, strConditionName);
		}
	}

	if(m_cmbCon.GetCount() > 0)
		m_cmbCon.SetCurSel(0);
}

//���� �˻� �ǽð� ��ȸ
void CRealAddDlg::OnBnClickedButton1()
{
	CString strConditionCodeList = _T(""), strIndex;

	//������ ���Ǹ��� �˻��� ���񸮽�Ʈ�� �ҷ��´�.
	m_cmbCon.GetLBText(m_cmbCon.GetCurSel(), m_strConditionName);
	m_mapNameList.Lookup(m_strConditionName, strIndex);
	m_nConditionIndex = _ttoi(strIndex);

	m_strPreConditionName = m_strConditionName;
	m_nPreConditionIndex = m_nConditionIndex;

	//��������, ��Ż �α� ����
	m_listCtl_Insert.ResetContent();
	m_listCtl_Delete.ResetContent();

	//���˰˻� �ǽð� ��ȸ
	//���񸮽�Ʈ�� OnReceiveTrCondition()�� ���Ͽ� ���´�.
	//�ǽð� ���� �˻��� �ϰ� ������ ������ �Ķ���Ϳ� 1�� �ش�.
	BOOL bRet = theApp.m_khOpenApi.SendCondition(m_strScrNo, m_strConditionName, m_nConditionIndex, 1);

	if (bRet == FALSE)
	{
		//����
		return;
	}
}


void CRealAddDlg::OnBnClickedButton2()
{
	//��������
	m_strPreConditionName = "";
 	CString strConditionName, strIndex;
 	m_cmbCon.GetLBText(m_cmbCon.GetCurSel(), strConditionName);
	m_mapNameList.Lookup(m_strConditionName, strIndex);
	int nConditionIndex = _ttoi(strIndex);
 	theApp.m_khOpenApi.SendConditionStop(m_strScrNo, strConditionName, nConditionIndex);
}


void CRealAddDlg::OnBnClickedCheck1()
{
	CString strPrice;
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(strPrice);
	if(strPrice == "") {
		strPrice = "10000";
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(strPrice);
	}
	m_price = _ttoi(strPrice);
	PlaySound(NULL, AfxGetInstanceHandle(),  NULL);  //�Ҹ� �ߴ�
	/*strPrice.Format("%d", m_price);
	AfxMessageBox(strPrice)*/;
}


void CRealAddDlg::OnBnClickedButton3()
{
	m_Jgubu = _T("");
//	AfxMessageBox(m_Jgubu);
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : ü���ܰ� �ǽð� ó��
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CRealAddDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}
	sjumunnumber = theApp.m_khOpenApi.GetChejanData(9203);
	m_listCtl_jumun.InsertString(0, sjumunnumber);
	//AfxMessageBox(strAcctList);
}

void CRealAddDlg::OnCbnSelchangeComboAcclist()
{
	m_strAcctList.GetLBText(m_strAcctList.GetCurSel(), m_strAcct);
	//AfxMessageBox(m_strAcct);
}

#define Pointer ((CRealAddDlg*)pParam)
UINT ThreadStart1(void * pParam)
{
	AfxMessageBox("######################################");
	while(Pointer->m_start) {
		/*Sleep(1000);
		Pointer->OnBnClickedButton2();
		Sleep(100);
		Pointer->OnBnClickedButton1();		*/
	}
	return 0;
}


void CRealAddDlg::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	long lRet;
	lRet = OP_ERR_ORD_OVERFLOW;
	lRet = theApp.m_khOpenApi.SendOrder("�ֽ��ֹ�", "0101", m_strAcct, 1/*�ֹ�����*/, "005930", 3, 46400, "00", "");//5031295011 1129984611
	//m_listCtl_jumun.InsertString(0, m_strAcct);
}


void CRealAddDlg::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	long lRet;
	lRet = OP_ERR_ORD_OVERFLOW;
//	lRet = theApp.m_khOpenApi.SendOrder("�ֽ��ֹ�", "0101", m_strAcct, 3/*�ֹ�����*/, "005930", 0, 0, "00", sjumunnumber);//5031295011 1129984611 �ż�
	lRet = theApp.m_khOpenApi.SendOrder("�ֽ��ֹ�", "0101", m_strAcct, 2/*�ֹ�����*/, "005930", 1, 0, "03", "");//5031295011 1129984611  sjumunnumber �ŵ�
}
