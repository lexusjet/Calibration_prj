
// work_2Dlg.h : файл заголовка
//

#pragma once

#include <string>
#include "WinScreen.h"
#include "CwinGrad.h"

//#include "density.h"
using namespace std;

// диалоговое окно Cwork_2Dlg
class Cwork_2Dlg : public CDialogEx
{
// Создание
public:
	Cwork_2Dlg(CWnd* pParent = NULL);	// стандартный конструктор
	int mass[256][256];					//	массив каждый элемент которого соответсвует данным с одного пикселя
	int dmass [255];					// массив разностей
	int strmass[256];
    int maxPok;							// максимальное значение
	int sec1[2];
	int sec2[2];
	//int posar[100][2];					// положительные отрезки приращ
	//int negar[100][2];					// отрицательные отрезки приращ
	int amass[254];
	int strmass1[236];
	int strmass2[236];
	int strmass3[236];
	int showgr[4];

	// оценка графика
	int thik;
	int linelength;

	//delete//
	int separ1;
	int separ2;
	//////////


	// Данные диалогового окна
	enum { IDD = IDD_WORK_2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// читает файл
	void read_file(CString txt);
	// преводит файл в массив
	void parth(string a, int n);

	CWinScreen m_screen;   // окно картинки
    CwinGrad m_poleGrad;
	afx_msg void OnBnClickedButton3();

	// ннахождение участка с линией спада 
	int findposled(void);
	
	// уточняет начало и конец линии спада 
	void cutline(void);
	
	// нахождения линии спада из отрезков убывания и возрастания
	int find3long(int** posar, int** negar);

	afx_msg void OnBnClickedButton2();
	// наполняет три массива для наххождения трех графикаов по участкам детектора
	void three_graph(void);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton4();
	// нахождение наименьшей 1-ой производной
	int findmind(int* mass);
	// определяет максимальное значение массива
	int findmax(int* mass);
	// ищем плохой массив
	int detach(void);
};
