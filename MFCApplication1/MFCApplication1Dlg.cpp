
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "Field_Descriptor.h"
#include "Dbf_header.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_filepath);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()


	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{	

	CFileDialog dlg(TRUE, NULL, NULL, OFN_READONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, _T("DBF Files(*dbf)|*.dbf|All Files (*.*)|*.*|"), this);

	CString strFileList;

	const int c_cMaxFiles = 400 /*선택할 파일 숫자*/;	// 메모리 부족현상으로 확장 안해주면 몇개 못씀
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (dlg.DoModal() == IDOK)
	{
	
		m_filepath.SetWindowTextW(dlg.GetPathName());
		CString filepath;
		m_filepath.GetWindowTextW(filepath);
		m_list.SetRedraw(FALSE);
		SetListData(filepath);
		m_list.SetRedraw(TRUE);
	}
}


void CMFCApplication1Dlg::SetListData(CString filepath)
{
	
	m_list.DeleteAllItems();
	FILE* fp;
	char ver;

	std::string filepathstring = CT2CA(filepath);

	if ((fp = fopen(filepathstring.c_str(), "rb")) == nullptr)
	{
		return;
	}

	fread(&ver, 1, 1, fp);

	if (ver != 3)
	{
		fclose(fp);
		return;
	}


	Dbf_header fHeader;
	fseek(fp, 0, SEEK_SET);
	fread(&fHeader, sizeof(Dbf_header), 1, fp);

	int nfield = (fHeader.header_length - sizeof(Dbf_header)) / sizeof(Field_Descriptor);

	Field_Descriptor* pField = new Field_Descriptor[nfield];
	
	fread(pField, sizeof(Field_Descriptor)*nfield, 1, fp);

	int offset = fHeader.header_length;
	fseek(fp, offset, SEEK_SET);
	char* record;

	for (int i = 0; i < nfield; i++)
	{
		unsigned char* name=pField[i].name;

		CString str;
		str.Format(L"%S", name);
		m_list.InsertColumn(i, str, 0, 100);
		
		
	}
	
	for (int j = 0; j < fHeader.recordn; j++)
	{
		fseek(fp, 1, SEEK_CUR);
		for (int i = 0; i < nfield; i++)
		{
	
			record = new char[pField[i].field_length + 1];
			fread(record, pField[i].field_length, 1, fp);
			record[pField[i].field_length] = '\0';
			removeSpace(record,pField[i].field_length);
			CString csTemp; 
			csTemp.Format(L"%S", record);
	
			if (i == 0)
			{
				m_list.InsertItem(j, csTemp);
			}
			else
			{
				m_list.SetItemText(j, i, csTemp);
			}
			delete[]record;
		}
	}
	fclose(fp);
}

void CMFCApplication1Dlg::removeSpace(char* rec, int length)
{
	for (short int i = length - 1; i > 0; i--)
	{
		if (rec[i] == ' ')
		{
			rec[i] = 0;
		}
		else
			break;
	}
}