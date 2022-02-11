#pragma once

#include "CwinGrad.h"
// CWinScreen

class CWinScreen : public CButton
{
	DECLARE_DYNAMIC(CWinScreen)

public:
	CWinScreen();
	virtual ~CWinScreen();
	//		���-�� //
	int margX; //  ������ �� X
	int margY; // ������ �� Y
	int sz; // ������ ����������
	int x, y;  // ������ ������

	CwinGrad *statGrad;// ��������
	BYTE StartRGB[3];
	int RGBDelta[3];
	COLORREF StartColor; // �����
	COLORREF EndColor;

	/////////////////

	int* ppmass[4];	//������ ��������� �� ������� ��������

	// 0 - int *data;		// ������ ��� �������� �������
	// 1 - int *pdmass;		// ������ ��� ��� ��������
	// 2 - int *pamass;		// ����� ������� ������ ����������
	// 3 - ������ ��� ������������� (�� ���� �������� ��� ���)

	//////////////////

	int begin_graph;	// ������ ������� �������� ��� ���������
	int end_graph;		// ������ ���������� �������� ��� ���������
	
	//int strmulti [3][236];	 // ������������ ������� �������
	int liner[2][2];

	int pmaxmass[4];//�������� �� ������������ ��������  

	int max;		//���������� ����� �  ������� �������
	int maxp;		// ����� ������������ �������� 
	int dmax;		// ������������ ���������
	int amax;		// ������������ ������ ���������� 

	int numColor;
	int leng[3][2];

	int* flgraph;	// ����� ��� ����������

	// ��� ����� //
	CPen* penal[4]; 
	CPen pen1;
	CPen pen2;
	CPen pen3;
	CPen pen4;

	// ����� ��� ���������� ��� ��������� //
	int pointx[4];
	int pointy[4];

	//������� 
	int sp1;
	int sp2;
 
 	void GraphPloting(COLORREF GraphColor);


	void GradientFillRect(HDC pDC);
	void setIN(int, int, int*, int, CwinGrad*);

	 COLORREF getColor(int);


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	// ��������� �������� ��� �������� �������
	void setIN(int,int* showgr ,int* mass , int* strmass1, int* strmass2, int* strmass3);

	// ��������� �������� ��� �������� ������ �����������
	void set_ain(int* mass);
	
	// ��������� �������� ��� ����������������� ��������
	void setin_dif(int dmax, int* dmass);
	
	// ��������� �������� ��� ������� �����
	void set_mline(int * sory1, int * sory2, int sep1, int sep2);	

	// ������������� ���������� �������� (��� ���� � ���� )
	void plot(int beg, int end, int max, int* mass,int init);
	
	// ���������� ���� � ����
	void standartfiller(void);

	// ���������� ������� � �������������� ����
	void un_zoom();
	
	

	// ������������ ������ 
	void underliter(int * begend);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


