
// work_2Dlg.h : ���� ���������
//

#pragma once

#include <string>
#include "WinScreen.h"
#include "CwinGrad.h"

//#include "density.h"
using namespace std;

// ���������� ���� Cwork_2Dlg
class Cwork_2Dlg : public CDialogEx
{
// ��������
public:
	Cwork_2Dlg(CWnd* pParent = NULL);	// ����������� �����������
	int mass[256][256];					//	������ ������ ������� �������� ������������ ������ � ������ �������
	int dmass [255];					// ������ ���������
	int strmass[256];
    int maxPok;							// ������������ ��������
	int sec1[2];
	int sec2[2];
	//int posar[100][2];					// ������������� ������� ������
	//int negar[100][2];					// ������������� ������� ������
	int amass[254];
	int strmass1[236];
	int strmass2[236];
	int strmass3[236];
	int showgr[4];

	// ������ �������
	int thik;
	int linelength;

	//delete//
	int separ1;
	int separ2;
	//////////


	// ������ ����������� ����
	enum { IDD = IDD_WORK_2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// ������ ����
	void read_file(CString txt);
	// �������� ���� � ������
	void parth(string a, int n);

	CWinScreen m_screen;   // ���� ��������
    CwinGrad m_poleGrad;
	afx_msg void OnBnClickedButton3();

	// ����������� ������� � ������ ����� 
	int findposled(void);
	
	// �������� ������ � ����� ����� ����� 
	void cutline(void);
	
	// ���������� ����� ����� �� �������� �������� � �����������
	int find3long(int** posar, int** negar);

	afx_msg void OnBnClickedButton2();
	// ��������� ��� ������� ��� ����������� ���� ��������� �� �������� ���������
	void three_graph(void);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton4();
	// ���������� ���������� 1-�� �����������
	int findmind(int* mass);
	// ���������� ������������ �������� �������
	int findmax(int* mass);
	// ���� ������ ������
	int detach(void);
};
