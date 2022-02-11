#pragma once

#include "CwinGrad.h"
// CWinScreen

class CWinScreen : public CButton
{
	DECLARE_DYNAMIC(CWinScreen)

public:
	CWinScreen();
	virtual ~CWinScreen();
	//		что-то //
	int margX; //  отступ по X
	int margY; // отступ по Y
	int sz; // размер квадратика
	int x, y;  // размер данных

	CwinGrad *statGrad;// градиент
	BYTE StartRGB[3];
	int RGBDelta[3];
	COLORREF StartColor; // белый
	COLORREF EndColor;

	/////////////////

	int* ppmass[4];	//массив укзателей на массивы графиков

	// 0 - int *data;		// данные для обычного графика
	// 1 - int *pdmass;		// данные для диф граффика
	// 2 - int *pamass;		// данне графика второй проиводной
	// 3 - данные для подчеркивания (не знаю работает или нет)

	//////////////////

	int begin_graph;	// индекс первого элемента для отрисовки
	int end_graph;		// индекс последнего элемента для отрисовки
	
	//int strmulti [3][236];	 // составляющие обычный граффик
	int liner[2][2];

	int pmaxmass[4];//укзатели на максимальные значения  

	int max;		//наибольшее число в  обычном графике
	int maxp;		// точка максимальная разность 
	int dmax;		// максимальная разцность
	int amax;		// максимальная вторая проиводная 

	int numColor;
	int leng[3][2];

	int* flgraph;	// флаги что показывать

	// мои ручки //
	CPen* penal[4]; 
	CPen pen1;
	CPen pen2;
	CPen pen3;
	CPen pen4;

	// точки для построения оси координат //
	int pointx[4];
	int pointy[4];

	//удалить 
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

	// принимает занчения для обычного графика
	void setIN(int,int* showgr ,int* mass , int* strmass1, int* strmass2, int* strmass3);

	// принимает занчения для граффика второй проивзодной
	void set_ain(int* mass);
	
	// принимает занчения для дифференциального граффика
	void setin_dif(int dmax, int* dmass);
	
	// принимает значения для средней линии
	void set_mline(int * sory1, int * sory2, int sep1, int sep2);	

	// универсальный рисователь графиков (без осей и фона )
	void plot(int beg, int end, int max, int* mass,int init);
	
	// рисователь фона с осью
	void standartfiller(void);

	// возращения графика в первоночальное сост
	void un_zoom();
	
	

	// подчеркиваем нужное 
	void underliter(int * begend);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


