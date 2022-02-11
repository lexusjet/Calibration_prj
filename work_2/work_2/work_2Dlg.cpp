
// work_2Dlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "work_2.h"
#include "work_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// ���������� ���� Cwork_2Dlg








Cwork_2Dlg::Cwork_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cwork_2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  		memset(mass,0,sizeof(mass));
maxPok=0;
}

void Cwork_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC2, m_poleGrad);
	DDX_Control(pDX, IDC_BUTTON5, m_screen);
}

BEGIN_MESSAGE_MAP(Cwork_2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUTTON1, &Cwork_2Dlg::OnBnClickedButton1)
  ON_BN_CLICKED(IDC_BUTTON3, &Cwork_2Dlg::OnBnClickedButton3)
  ON_BN_CLICKED(IDC_BUTTON2, &Cwork_2Dlg::OnBnClickedButton2)
  ON_BN_CLICKED(IDOK, &Cwork_2Dlg::OnBnClickedOk)
  ON_BN_CLICKED(IDC_BUTTON4, &Cwork_2Dlg::OnBnClickedButton4)
  ON_BN_CLICKED(IDC_BUTTON6, &Cwork_2Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// ����������� ��������� Cwork_2Dlg

BOOL Cwork_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
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

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void Cwork_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void Cwork_2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR Cwork_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cwork_2Dlg::OnBnClickedButton1()
{
	CString path;						//	���� � ������������ �����
	CString angle;						//	���������� ����� ����
	CString format;						//	������ ����� ToT.txt
	CString txt;
	CString filename;					//	��� ����� ���������
	CString num;
	

  // ��� ������� ������


	CString sFilter = L"TXT ����� (*.txt)|*.txt|����� ����� (*.*)|*.*||";
	CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, (LPCTSTR) sFilter, this); // �������� ���������� ����
	if(IDCANCEL == dlgOpen.DoModal())
	return;							// ������������ ��������� �� ������
	txt = dlgOpen.GetPathName();		//�������� ���� � �����
	filename = dlgOpen.GetFileName();
	num = filename;
	num.Delete(0,1);

	if (num =="_Event.txt"){
		memset(mass, 0, sizeof(mass));
		memset(strmass, 0, sizeof(strmass)); // ��������� ������� ��������� 
		memset(showgr, 0, sizeof(showgr));   // ��������� ������
		Cwork_2Dlg::read_file(txt);
		//MessageBox(L"���", L"���������", MB_OK);
		for (int i = 0; i < 256; i++){
			for(int j = 0; j < 256; j++){
				strmass[i] += mass[j][i];
			}
		}
		showgr[0] = 1;
		m_screen.setIN( 256, showgr, strmass,  strmass1, strmass2, strmass3);
	}
	else{
		path =txt.Left(txt.GetLength()-filename.GetLength());
	
		if(filename.Find('_')== -1){		//�������� ������� �����
			MessageBox(L"��������� ���� ��������� �������", L"�������� ", MB_OK);
			return;
		};
		angle = filename.Left(filename.Find('_'));

		WIN32_FIND_DATA fileinfo;						// ���������, ���� ����������� ������ ��� �������� ����� �� �-�� finfirst
		HANDLE fileHndl;								// ���������� ���������� ����� (���� ��������� )

		//	�������� ����� �� ������� ����� ����������� �����	//

		CString mask;
		mask.Format(L"%s%s_*%s", path, angle, L"_ToT.txt");//�����: ����, ���� + ��������� + ����� � �������� ����� 

		// ����� ������� ����� //
		fileHndl = FindFirstFile( mask, &fileinfo);		// �������� ������ ���� �� �������� ����� (��� ������ HANDLE � �������� fileinfo ���������� �����)
		if(fileHndl != INVALID_HANDLE_VALUE){			// ��������� ������� �� ����� ����
			while(1){									// �������� ���� �������
				if(fileinfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // �������� �� ������ ������, ����� ��� ���������� ( �� �����������)
				;

				else{											// ���� �� ���������� ����� ������� ��� ��� ����
				  //MessageBox(fileinfo.cFileName, L"������ ���� :", MB_OK);   // ���������� ��� ���
					txt = path + fileinfo.cFileName;
				
					read_file(txt);
				}
				// ������ ������ ���� ��� ��������� ����
				if(FindNextFile(fileHndl, &fileinfo) == 0){  // ���� ������ ������ ��� ������ �� �����  
					FindClose(fileHndl);  // �� ������� ������� ��� ������
					MessageBox(L"���", L"���������", MB_OK);
					break;
				}
		  // �� � ���� ��������� ���� ���������
			}

		}
		for (int i = 0; i < 256; i++){
			for(int j = 0; j < 256; j++){
				strmass[i] += mass[j][i];
			}
		}
		showgr[0] = 1;
		m_screen.setIN( 256, showgr, strmass,  strmass1, strmass2, strmass3);	

	}
	
	//memset(strmass1, 0 , sizeof(strmass1));
	//memset(strmass2, 0 , sizeof(strmass2));
	//memset(strmass3, 0 , sizeof(strmass3));

	// ����������� ������� ��� �������� //
	

	//three_graph();
	

		// ���������� �������� � ������ min � max
    //m_poleGrad.setTemperature(maxPok, 0);
    //m_poleGrad.Invalidate();
    //m_screen.setIN(256, 256, (int*)mass, maxPok, &m_poleGrad);
	  //m_screen.Invalidate();
}

void Cwork_2Dlg::read_file(CString txt) //������ �� ����� � ������ � ����� ������
{	
	char buffer [1] ={0};
	string a;
	string b;
	int begin = 0;
	int end = 0;
	int len = 0;
	int j = 0;
	int n = 0;

	CFile f;

	if(!f.Open(txt , CFile::modeRead )){ //�������� �������� 
		MessageBox(txt, L"����  � ����� �������� �� ��������� :", MB_OK);
		return;
	}

	CMemFile mf;                      // ������� ����������� ����
	ULONGLONG lenF = f.SeekToEnd() ;  // ������� ����� ������ �����, ��������� ������� � ����� �����
	char *fbuf = new char[lenF];      // ������� ��� ��� ������
	f.SeekToBegin();                  // ���������� ��������� �� ������ �����
	f.Read(fbuf, lenF);               // ��������� ���� ���� � �����
	f.Close();                        // ������� ����
	mf.Write((void*)fbuf, lenF);      // ������� ���������� ������ � ����������� ����, ��������� ������� � ����� �����
	if(fbuf)                          // ��������� ������
		delete [] fbuf;
	mf.SeekToBegin();                 // ���������� ��������� � ������ ������������ �����





	while(1){							// ������ � ������ � ������
		if(mf.Read((void*)buffer,1) == 1){ //�������� ����� ���������
			a += buffer[0];
			if(buffer[0] =='\n'){
				parth(a,n);
				
				if (n > 2){
					int srrrr =5;
				}

				n++;					//	����� ������ �������
				a.clear();
			}
		}
		else{
			if(a.size() > 0){
				parth(a, n);
			}
			//MessageBox(L"����� �����", L"������ ���� :", MB_OK);
			break;
		}
	}
	mf.Close();
		
	
}

void Cwork_2Dlg::parth(string a, int n)
{
	int j = 0;
	for(int k = 0; k < a.size();k++){
		if(a[k]==' '){
			continue;
		}
		int num =atoi(a.data() + k);
		if(num){
			mass[n][j] += num;
      if(maxPok < mass[n][j])
        maxPok = mass[n][j];
		}
		k = a.find(' ', k);
		if(k ==a.npos){
			break;
		}
		j++;
	}
}

// ������ ���������� ������ ����������� 
void Cwork_2Dlg::OnBnClickedButton3()
{
	// ����� ��������������� �����//
	if(showgr[1] == 1){
		showgr[1] = 0;
		m_screen.setin_dif(0, dmass);

	}
	else{
		showgr[1] = 1;
		for(int i = 0; i < 255; i++){
		dmass[i] = strmass[1 + i] - strmass[i];

		}
		int dmax = abs(dmass[0]);
		int max = 0;
		for(int i = 1; i < 255; i++){
			if(dmax < abs(dmass[i])){
				dmax = abs(dmass[i]);
				max = i;
			}
		}
		m_screen.setin_dif(max, dmass);
	}

}

// ������ ���������� ������ ����� 
void Cwork_2Dlg::OnBnClickedButton4()
{		
	if(showgr[3] == 1){
		showgr[3] = 0;
		m_screen.set_mline(sec1, sec2, 0 , 0);
	
	}
	else{
		showgr[3] = 1;
		thik = detach();
		if(thik > 10){
			MessageBox(L"������ ����������",L"���������", MB_OK);
			showgr[3] = 0;
		}
		else{
			CString rex;
			linelength = findposled();
			cutline();
			linelength = sec2[1] -sec2[0];
			rex.Format(L"������ ������� ����� = %d", linelength);
			MessageBox(rex, L"���������", MB_OK);
			m_screen.set_mline(sec1,sec2, separ1 ,separ2);
		}

	}

}

// ���������� ����� ����� 
int Cwork_2Dlg::findposled(void)
{
	int j = 0;
	int n = 0;
	int i = 50;
	int fl1 ;
	int fl2 ;
	int posar [2][2] = {0};
	int negar [3][2] = {0};
	memset( negar, 0, sizeof(negar));
	// ������� ����� ������� ������������� ������� 
	while(i < 180){
		if(dmass[i] > 0){
			fl1 = (dmass[i] > 0) & ( i < 180);
			posar[j][0] = i;
			while(fl1){
				i++;
				fl1 = (dmass[i] > 0) & ( i < 180);
			}
			posar[j][1] = i;
			j++;
			if(j == 2){
				int len1 = posar[0][1] - posar[0][0];
				int len2 = posar[1][1] -posar[1][0];
				if(len1 < len2){
					posar[0][0] =posar[1][0];
					posar[0][1] =posar[1][1];
				}
				j = 1;
			}
		}
		else{
			i++;
		}
	}
	sec1[0] = posar[0][0];
	sec1[1] = posar[0][1];
	j = 0;
	i = posar[0][1] - 1;
	while(i < 150){
		if(dmass[i] < 0){
			negar[j][0] = i;
			fl2 = (dmass[i] < 0) & ( i < 200);
			while(fl2){
				i++;
				fl2 = (dmass[i] < 0) & ( i < 200);
			}
			negar[j][1]= i;
			j++;
			if(j == 3){
				int len1 = negar[0][1] - negar[0][0];
				int len2 = negar[1][1] - negar[1][0];
				int len3 = negar[2][1] - negar[2][0];
				if(len1 < len2){
					int buf[2]; 
					buf[0]=negar[0][0];
					buf[1] =negar[0][1];
					
					negar[0][0] = negar[1][0];
					negar[0][1] = negar[1][1];
					
					negar[1][0] = buf[0];
					negar[1][1] = buf[1];
				}
				if(len2 < len3){
					negar[1][0] = negar[2][0];
					negar[1][1] = negar[2][1];
					if(len1 < len3){
						
					}
				}
				if(len1 < len3){
					negar[1][0] = negar[0][0];
					negar[1][1] = negar[0][1];
					negar[0][0] = negar[2][0];
					negar[0][1] = negar[2][1];
				}
				j = 2;
			}
		}
		else{
			i++;
		}
	}
	if(negar[0][0] > negar[1][0]){
		negar[0][0] = negar[1][0];
		negar[0][1] = negar[1][1];
	}
	sec2[0] = negar[0][0];
	sec2[1] = negar[0][1];
	int anser = negar[0][1] - negar[0][0];
	return(anser);
}

// ��������� ����� �����
void Cwork_2Dlg::cutline()
{
	//int max = findmax(mass);
	///if(sec1[1] == sec2[0]){}

	//int separ2;
	int buf1 = dmass[sec2[0]];
		for(int i = (sec2[0] + 1); i < sec2[1]; i++){
			if(buf1 > dmass[i]){
				buf1 = dmass[i];					
			}
		}
		separ2 = (buf1 * 25) / 100;
		int n =sec2[0];
		while(dmass[n] > separ2){
			n++;
			sec2[0] = n;
			
		}

		n  = sec2[0] + 1;
		while(dmass[n] < separ2){
			n++;
			sec2[1] = n;
		}

}

// ���������� ����� ����� �� �������� �������� � �����������
int Cwork_2Dlg::find3long(int** posar, int** negar)
{
	int sory1[2];
	int sory2[2];
	//������ ������� �������������
	int len= posar[0][1] - posar[0][0];
	int cord = 0;
	for (int i = 1; i < 99;  i++){
		int len2 = posar[i][1] - posar[i][0];
		if(len < len2){
			len = len2;
			cord = i;
		}
	}
	sec1[0] = posar[cord][0];
	sec1[1] = posar[cord][1];
	//
	
	cord = 0;
	while(negar[cord][0] < sec1[0]){
		cord++;
	}
	len = negar[cord][1] - negar[cord][0];
	int len2 = negar[cord+1][1] - negar[cord+1][0];
	int cord2 = cord + 1;

	if(len < len2){
		len2 = len;
		len = negar[cord+1][1] - negar[cord+1][0];
		cord =cord + 1;
		cord2 = cord;
	}

	for(int i = cord + 2; i < 99; i++){
		int lenb = negar[i][1] - negar[i][0];
		if(len < lenb){
			len2 = len;
			cord2 = cord;
			len = lenb;
			cord = i;
		}

	}

	sory1[0]=negar[cord][0];
	sory2[0]=negar[cord][1];
	sory1[1]=negar[cord2][0];
	sory2[1]=negar[cord2][1];
	// ��� ������� ����������� ������
	
	if(sory1[0]<sory1[1]){
		int oper = sory1[0];
		int minid = findmind(dmass)* 20 / 100;
		while(dmass[oper] < minid){
			oper++;
		}
		sec2[0] = sory1[0];
		sec2[1] = oper;
	}
	else{
		int oper = sory1[1];
		int minid = (findmind(dmass)*20)/100;
		while(dmass[oper] < minid){
			oper++;
		}
		sec2[0] = sory1[1];
		sec2[1] = oper;
	}
	int anser = sec2[1] - sec2[0];
	return(anser);
}

// ������ ������ �����������
void Cwork_2Dlg::OnBnClickedButton2()
{
	if(showgr[2] == 1){
		showgr[2] = 0;
		m_screen.set_ain(amass);
	}
	else{
		showgr[2] = 1;
		for(int i = 0; i < 255; i++){
			dmass[i] = strmass[1 + i] - strmass[i];
		}

		for(int i = 0; i < 254; i++){
			amass[i] = dmass[i + 1] - dmass[i];	
		}
		m_screen.set_ain(amass);
	}

}

// ��������� ��� ������� ��� ����������� ���� ��������� �� �������� ���������
void Cwork_2Dlg::three_graph(void)
{
	memset(strmass1, 0 , sizeof(strmass1));
	memset(strmass2, 0 , sizeof(strmass2));
	memset(strmass3, 0 , sizeof(strmass3));


	for(int i = 9, k = 0; i < 246; i++, k++){
		for(int j = 9; j < 88; j++){
			strmass1[k] += mass[j][k];
		}
	}
	for(int i = 9, k = 0; i < 246; i++, k++){
		for(int j = 88; j < 167; j++){
			strmass2[k] += mass[j][k];
		}
	}	
	for(int i = 9 , k = 0; i < 246; i++, k++){
		for(int j = 167; j < 247; j++){
			strmass3[k] += mass[j][k];
		}
	}
}


void Cwork_2Dlg::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	CDialogEx::OnOK();
}




// ���������� 20 % ���������� 1-�� �����������
int Cwork_2Dlg::findmind(int* mass)
{
	int min = mass[0];
	for(int i = 1; i < 254; i++){
		if(min > mass[i]){
			min = mass[i];
		}
	}
	return(min);
}


// ���������� ������������ �������� �������
int Cwork_2Dlg::findmax(int* mass)
{
	int max = mass[0];
	for(int i = 0 ; i < 256; i++){
		if(max < mass[i]){
			max = mass[i];
		}
	}
	return(max);
}


// ���� ������ ������
int Cwork_2Dlg::detach(void)
{
	int max = findmax(strmass);
	separ1 = (max*45) / 100;
	int cord[2];
	int i =0;

	while(strmass[i] < separ1){
		i++;
	}
	cord[0] = i;
	while(strmass[i] > separ1){
		i++;
	}
	cord[1] =i;
	int  len = cord[1]- cord[0];
	CString rex;
	rex.Format(L"������ = %d ", len);
	MessageBox(rex,L"������", MB_OK);
	//m_screen.set_mline(cord, cord);
	return(len);
	
}


//BOOL CAboutDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
//
//	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
//}


void Cwork_2Dlg::OnBnClickedButton6()
{
	m_screen.un_zoom();
}
