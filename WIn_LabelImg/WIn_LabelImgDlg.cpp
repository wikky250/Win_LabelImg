
// WIn_LabelImgDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "WIn_LabelImg.h"
#include "WIn_LabelImgDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
// ʵ��
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
// CWIn_LabelImgDlg �Ի���
CString CWIn_LabelImgDlg::GetCurrentAppPath()
{
	char str[MAX_PATH], drive[_MAX_DIR], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	CString AppPath;
	GetModuleFileName(NULL, str, sizeof(str));
	_splitpath_s(str, drive, dir, fname, ext);
	strcat_s(drive, dir);
	AppPath.Format("%s", drive);/**/
	return AppPath;
}
void CWIn_LabelImgDlg::InitClassList()
{
	CString m_strConfigPath = GetCurrentAppPath() + "LabelClass.ini";
	CString st;
	for (int i=0;i<9;i++)
	{
		char name[10];
		st.Format("%d", i);
		GetPrivateProfileString("LabelName", st, "δ����", name, 256, m_strConfigPath);
		m_cslClassName.AddTail(name);
		GetDlgItem(1010 + i)->SetWindowText(name);
	}
}
CWIn_LabelImgDlg::CWIn_LabelImgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WIN_LABELIMG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CWIn_LabelImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ClassName, m_editClassName);
	DDX_Control(pDX, IDC_STATIC_PIC, m_BitmapShow);
	DDX_Control(pDX, IDC_LIST_Target, m_ListTarget);
}
BEGIN_MESSAGE_MAP(CWIn_LabelImgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDOK, &CWIn_LabelImgDlg::OnIdok)
	ON_LBN_SELCHANGE(IDC_LIST_Target, &CWIn_LabelImgDlg::OnLbnSelchangeListTarget)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CWIn_LabelImgDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_CHECK1, &CWIn_LabelImgDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CWIn_LabelImgDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CWIn_LabelImgDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CWIn_LabelImgDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CWIn_LabelImgDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CWIn_LabelImgDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CWIn_LabelImgDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CWIn_LabelImgDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CWIn_LabelImgDlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_BUTTON_Save, &CWIn_LabelImgDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()
// CWIn_LabelImgDlg ��Ϣ�������
BOOL CWIn_LabelImgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_editClassName.SetWindowText(_T("���һ���ť�Զ�������"));
	InitClassList();
	m_iselectedLabel = -1;
	m_clickpos = CPoint(0, 0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CWIn_LabelImgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CWIn_LabelImgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWIn_LabelImgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
BOOL CWIn_LabelImgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam==VK_RETURN&&GetFocus()==GetDlgItem(IDC_EDIT_ClassName))
		{
			m_editClassName.EnableWindow(FALSE);
			m_editClassName.SetWindowText("���һ���ť�Զ�������");
		}
		if (pMsg->wParam>=VK_NUMPAD1&&pMsg->wParam<=VK_NUMPAD9)
		{
			for (int i=0;i<9;++i)
			{
				((CButton *)GetDlgItem(1010 + i))->SetCheck(FALSE);
			}
			((CButton *)GetDlgItem(1010 + pMsg->wParam - 0x61))->SetCheck(TRUE);
			m_iselectedLabel = pMsg->wParam - 0x61;
		}
	}
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (m_iselectedLabel!=-1)
		{
			m_editClassName.EnableWindow(FALSE);
			m_editClassName.SetWindowText(_T("���һ���ť�Զ�������"));
			m_clickpos = CPoint(0, 0);
		}
	}
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (m_iselectedLabel != -1 && m_clickpos.x != 0 && m_clickpos.y != 0)
		{
			CPoint mouseclick;
			GetCursorPos(&mouseclick);
			CRect re;
			GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(re);
			if (mouseclick.x > re.left&&mouseclick.x<re.right
				&&mouseclick.y>re.top&&mouseclick.y < re.bottom)
			{
				CPoint p1;
				p1.x = m_clickpos.x - re.left;
				p1.y = m_clickpos.y - re.top;
				CPoint p2;
				p2.x = mouseclick.x - re.left;
				p2.y = mouseclick.y - re.top;
				CRect tar = CRect(
					p1.x < p2.x ? p1.x : p2.x,
					p1.y<p2.y ? p1.y : p2.y,
					p2.x>p1.x ? p2.x : p1.x,
					p2.y>p1.y ? p2.y : p1.y);

				cv::Mat tempimg = m_oriimg.clone();
				//cv::cvtColor(m_oriimg,tempimg,CV_GRAY2BGR);
				m_RectCurrent = cv::Rect(tar.left*1.0/re.Width()*tempimg.cols,tar.top*1.0/re.Height()*tempimg.rows, tar.Width()*1.0 / re.Width()*tempimg.cols, tar.Height()*1.0 / re.Height()*tempimg.rows);
				cv::rectangle(tempimg, m_RectCurrent, cv::Scalar(0, 0, 255), 8, 8, 0);
				DrawMat(tempimg, IDC_STATIC_PIC);
			}
		}

	}
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		CPoint mouseclick;
		GetCursorPos(&mouseclick);
		CRect re;
		GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(re);
		if (mouseclick.x > re.left&&mouseclick.x<re.right
			&&mouseclick.y>re.top&&mouseclick.y < re.bottom)
		{
			m_clickpos = mouseclick;
		}
		else
		{
			m_clickpos = CPoint(0, 0);
		}
		m_editClassName.EnableWindow(FALSE);
		m_editClassName.SetWindowText(_T("���һ���ť�Զ�������"));
	}
	if (pMsg->message == WM_RBUTTONUP)
	{
		CPoint mouseclick;
		GetCursorPos(&mouseclick);
		CRect re;
		int i = 0;
		for (; i < 9; ++i)
		{
			GetDlgItem(1010 + i)->GetWindowRect(re);
			if (mouseclick.x>re.left&&mouseclick.x<re.right
				&&mouseclick.y>re.top&&mouseclick.y<re.bottom)
			{
				m_editClassName.EnableWindow(TRUE);
				m_editClassName.SetWindowText("123");
				UpdateData(FALSE);
				m_editClassName.SetFocus();
				break;
			}
		}
		if (m_RectCurrent.width!=0&& m_RectCurrent.height!=0)
		{
			GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(re);
			if (mouseclick.x > re.left&&mouseclick.x<re.right
				&&mouseclick.y>re.top&&mouseclick.y < re.bottom)
			{
				m_editClassName.EnableWindow(TRUE);
				m_editClassName.SetWindowText("123");
				CString str;
				str.Format("���ͣ�%d,x:%d,y:%d,w:%d,h:%d",m_iselectedLabel,m_RectCurrent.x,m_RectCurrent.y,m_RectCurrent.width,m_RectCurrent.height);
				m_ListTarget.AddString(str);
				m_RectCurrent = cv::Rect(0, 0, 0, 0);
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CWIn_LabelImgDlg::OnIdok()
{
	// TODO: �ڴ���������������
}
void CWIn_LabelImgDlg::OnLbnSelchangeListTarget()
{ 
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CWIn_LabelImgDlg::OnBnClickedButtonLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isOpen = TRUE;//�Ƿ��(TRUEΪ�򿪶Ի���FALSEΪ����Ի���)
	CString defaultDir = ""; //Ĭ�ϴ򿪵��ļ�·�� 
	CString filter = "ͼƬ(*.bmp)|*.bmp|��������(*.*)|*.*||"; //�ļ����ǵ����� 
	CFileDialog openFileDlg(isOpen, NULL, defaultDir, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();//�Ƿ�ѡ���ļ�����ȡ����ѡ��
	if (result == IDOK)
	{
		CString pathName, fileName, titleName, extName;
		pathName = openFileDlg.GetPathName();//�õ��������ļ���������Ŀ¼������չ���磺c:/test/test1.txt
											 // 		fileName = openFileDlg.GetFileName();//�õ��������ļ�����������չ���磺test1.txt
											 // 		titleName=openFileDlg.GetFileTitle();//�õ��������ļ�����������Ŀ¼������չ���磺test1
											 // 		extName = openFileDlg.GetFileExt();// �õ��������ļ���չ�����磺txt
		m_oriimg = imread(std::string(pathName.GetBuffer(0)));
		DrawMat(m_oriimg, IDC_STATIC_PIC);

		m_sImageLabel = openFileDlg.GetFolderPath() + openFileDlg.GetFileTitle() + ".txt";
		bool b = PathFileExists(m_sImageLabel);
		if (b)
		{
			m_ListTarget.ResetContent();
			std::ifstream in(m_sImageLabel.GetBuffer());
			std::string str;
			if (in.is_open())
			{
				while (getline(in, str))
				{
					m_ListTarget.AddString(str.c_str());
				}
			}
		}
		else
		{
			CFile file(m_sImageLabel, CFile::modeCreate);
			file.Close();
		}
	}
} 
void CWIn_LabelImgDlg::DrawMat(cv::Mat& img, UINT nID)
{
	cv::Mat imgTmp;
	CRect rect;
	GetDlgItem(nID)->GetClientRect(&rect);  // ��ȡ�ؼ���С
	cv::resize(img, imgTmp, cv::Size(rect.Width(), rect.Height()));// ����Mat������
																   // תһ�¸�ʽ,��ο��Է�����,
	switch (imgTmp.channels())
	{
	case 1:
		cv::cvtColor(imgTmp, imgTmp, CV_GRAY2BGRA); // GRAY��ͨ��
		break;
	case 3:
		cv::cvtColor(imgTmp, imgTmp, CV_BGR2BGRA);  // BGR��ͨ��
		break;
	default:
		break;
	}
	int pixelBytes = imgTmp.channels()*(imgTmp.depth() + 1); // ����һ�����ض��ٸ��ֽ�
															// ����bitmapinfo(����ͷ)
	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biBitCount = 8 * pixelBytes;
	bitInfo.bmiHeader.biWidth = imgTmp.cols;
	bitInfo.bmiHeader.biHeight = -imgTmp.rows;
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biClrImportant = 0;
	bitInfo.bmiHeader.biClrUsed = 0;
	bitInfo.bmiHeader.biSizeImage = 0;
	bitInfo.bmiHeader.biXPelsPerMeter = 0;
	bitInfo.bmiHeader.biYPelsPerMeter = 0;
	// Mat.data+ bitmap����ͷ -> MFC
	CDC *pDC = GetDlgItem(nID)->GetDC();
	::StretchDIBits(
		pDC->GetSafeHdc(),
		0, 0, rect.Width(), rect.Height(),
		0, 0, rect.Width(), rect.Height(),
		imgTmp.data,
		&bitInfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);
	ReleaseDC(pDC);
}

void CWIn_LabelImgDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 0;
}


void CWIn_LabelImgDlg::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 1;
}


void CWIn_LabelImgDlg::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 2;
}


void CWIn_LabelImgDlg::OnBnClickedCheck4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 3;
}


void CWIn_LabelImgDlg::OnBnClickedCheck5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 4;
}


void CWIn_LabelImgDlg::OnBnClickedCheck6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 5;
}


void CWIn_LabelImgDlg::OnBnClickedCheck7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 6;
}


void CWIn_LabelImgDlg::OnBnClickedCheck8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 7;
}


void CWIn_LabelImgDlg::OnBnClickedCheck9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iselectedLabel = 8;
}


void CWIn_LabelImgDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (PathFileExists(m_sImageLabel))
	{
		CFile file(m_sImageLabel, CFile::modeWrite);
		for (int i=0;i<m_ListTarget.GetCount();i++)
		{
			CString st;
			m_ListTarget.GetText(i, st);
			st += "\r\n";
			file.Write(st.GetBuffer(), st.GetLength());
		}


		file.Close();
	}
}
