// WinScreen.cpp: файл реализации
//

#include "stdafx.h"
#include "work_2.h"
#include "WinScreen.h"
#include <math.h>


// CWinScreen

IMPLEMENT_DYNAMIC(CWinScreen, CStatic)

CWinScreen::CWinScreen()
{
	ppmass[0] = nullptr;
	ppmass[1] = nullptr;
	ppmass[2] = nullptr;
	ppmass[3] = nullptr;

	pen1.CreatePen(PS_SOLID, 1 ,0x1EEB70);
	pen2.CreatePen(PS_SOLID, 1, 0x3333FF);
	pen3.CreatePen(PS_SOLID, 1, 0xD011D7);
	pen4.CreatePen(PS_SOLID, 1, 0x0931CE);

	penal[0] = &pen1;
	penal[1] = &pen2;
	penal[2] = &pen3;
	penal[3] = &pen4;

	begin_graph = 80;	
	end_graph = 140;		

	//data = nullptr;
	//pdmass = nullptr;
	//pamass = nullptr;


	//pmaxmass[0] = &max;
	//pmaxmass[1] = &dmax;
	//pmaxmass[2] = &amax;
}

CWinScreen::~CWinScreen()
{	
	pen1.DeleteObject();
	pen2.DeleteObject();
	pen3.DeleteObject();

}


BEGIN_MESSAGE_MAP(CWinScreen, CStatic)
	ON_WM_PAINT()
//	ON_WM_MOUSEHWHEEL()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// обработчики сообщений CWinScreen




void CWinScreen::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: добавьте свой код обработчика сообщений
	// Не вызывать CStatic::OnPaint() для сообщений рисования
	// вызываем функцию рисования
	//GradientFillRect(dc.GetSafeHdc());
	if(ppmass[0] != nullptr){
		standartfiller();
		for(int i = 0; i < 3; i++){
			if(flgraph[i] == 1){
				plot(begin_graph, end_graph, pmaxmass[i], ppmass[i], i);
			}
		}
		for(int i = 3; i < 4;i++){
			if(flgraph[i] == 1 ){
				underliter(ppmass[3]);			
			}
		}
	}
	else{
		standartfiller();
	}
	//if(pamass == nullptr){
	//	GraphPloting(0x000000);
	//}
	//else{
	//	Plot_agraph();
	//}
}

// принимает занчения для обычного графика
void CWinScreen::setIN(int colms, int* showgr, int *dt, int* strmass1, int* strmass2, int* strmass3)
{
	ppmass[0] = dt;
	flgraph = showgr; // передаем флаги что показывать

	// поиск максимального значения 
	max = ppmass[0][0];
	for(int i = 1; i < 256; i++){
		if(max < ppmass[0][i]){
			max = ppmass[0][i];
	  }
	}
	pmaxmass[0] = max;

	Invalidate();
  
}

// принимает занчения для дифференциального граффика
void CWinScreen::setin_dif(int dx, int* dmass )
{
	ppmass[1] = dmass;
	maxp = dx;
	dmax =abs(dmass[maxp]);
	pmaxmass[1] = dmax;
	Invalidate();
}

// принимает занчения для граффика второй производной
void CWinScreen::set_ain(int *amass)
{
	ppmass[2] = amass;
	int buf = ppmass[2][0];
	for(int i = 1; i < 254; i++){
		if(buf < abs(ppmass[2][i])){
			buf = abs(ppmass[2][i]);
		}
	}
 
	amax = buf;
	pmaxmass[2] = amax;
	Invalidate();
}


COLORREF CWinScreen::getColor(int temp){
 int I;
 int fl = 1;  // флаг отображения в инверсии: 0 черным цветом
 COLORREF En;
  I = temp;
  if(!fl){
    En =  (RGB(GetRValue(EndColor) + MulDiv(I, RGBDelta[0], numColor ),
	             GetGValue(EndColor) + MulDiv(I, RGBDelta[1], numColor ),
	             GetBValue(EndColor) + MulDiv(I, RGBDelta[2], numColor )));
  }
  else{
    En = RGB(GetRValue(StartColor) - ( MulDiv(I, RGBDelta[0], numColor)),
	           GetGValue(StartColor) - ( MulDiv(I, RGBDelta[1], numColor)),
	           GetBValue(StartColor) - ( MulDiv(I, RGBDelta[2], numColor)));
  }

  return En;/*(RGB(StartRGB[0] - MulDiv(I, RGBDelta[0], numColor - 1),
	            StartRGB[1] - MulDiv(I, RGBDelta[1], numColor - 1),
	            StartRGB[2] - MulDiv(I, RGBDelta[2], numColor - 1)));*/
}

// универсальный рисователь графиков (без осей и фона )
void CWinScreen::plot(int beg, int end, int max, int* mass ,int init)
{
	// beg  - индекс первого элемента для отрисовки
	// end  - индекс последнего элемента для отрисовки
	// max  - наибольшее значение
	// mass - значения
	// init - для выбора цвета ручки

	CDC* pdc = GetDC();
	CRect rect;
	GetClientRect(rect);	// получаем размер области рисования
	if (rect.IsRectEmpty()) 
		return;				//если квадрат пустой то выйти	
	if (ppmass == nullptr){
		ReleaseDC(pdc);
		return; 
	}
		CPen *poldpen = pdc->SelectObject(penal[init]);
	int zero[2];
	int height;
	int len;
	if(pointx[3] == 0){
		zero[0] = pointx[1];
		zero[1] = pointy[1];
		height = pointy[1] - pointy[0];
		len = pointx[2] - pointx[0];
	}
	else{
		zero[0] = pointx[2];
		zero[1] = pointy[2];
		height = pointy[1] - pointy[2];
		len = pointx[3] - pointx[0];
	}


	int mash =len / ( end - beg);	// установка маштаба горизонтальной оси
	int cdel = max/ height ;		// установка маштаба вертикальной оси
	pdc->MoveTo(zero[0], zero[1]);

	for(int i = 0 ,fl = beg ; i < end; i++, fl++){
		pdc->LineTo(pointx[1]+(mash* i), pointy[2] - ((mass[fl]) / cdel));
	}	
	pdc->SelectObject(poldpen);
	ReleaseDC(pdc);
}

// заливка фона (белым) и построение осей координат
void CWinScreen::standartfiller(void)
{
	CDC* pdc = GetDC();
	CPen Mpen;
	CRect ColorBand;
	CRect rect;	
	GetClientRect(rect);// получаем размер области рисования
	ColorBand = rect;
	COLORREF GraphColor = RGB(0, 0, 0);

	// зарисовываем фон белым // 
	CBrush Brush;
	COLORREF StartColor = RGB(255, 255, 255);

	if (rect.IsRectEmpty()) 
		return;            //если квадрат пустой то выйти

	//закрасим поле
	ColorBand = rect;

	Brush.CreateSolidBrush(StartColor);
	pdc->FillRect(ColorBand, &Brush);
	Brush.DeleteObject();


	//выбор точек осей координат
	int buf = 0;
	if(ppmass[0] == nullptr){
		return;
	}
	// проверка флагов графиков производных
	for(int i = 1 ; i < 3; i++){
		if(flgraph[i] == 1){
			buf = 1;
		}
	}

	Mpen.CreatePen(PS_SOLID, 1, GraphColor);
	CPen *poldpen = pdc->SelectObject(&Mpen);

	//только положительные точки
	if(buf == 0){
		
		pointx[0] = ((rect.right) / 8);
		pointx[1] = ((rect.right) / 8);
		pointx[2] = ((rect.right) - (rect.right) / 16);
		pointx[3] = 0;

		pointy[0] = (rect.bottom  / 8);
		pointy[1] = rect.bottom - (rect.bottom  / 8);
		pointy[2] = rect.bottom - (rect.bottom  / 8);
		pointy[3] = 0;
		
		// рисуем оси
		pdc->MoveTo(pointx[0], pointy[0]);
		for(int i = 1;i < 3;i ++){
			pdc->LineTo(pointx[i],pointy[i]);	
		}
	}
	// есть отрицательные
	else{
		pointx[0] = ((rect.right) / 8);
		pointx[1] = ((rect.right) / 8);
		pointx[2] = ((rect.right) / 8);
		pointx[3] = ((rect.right) - (rect.right) / 16) ;
	
		pointy[0] = (rect.bottom  / 8);
		pointy[1] = rect.bottom - (rect.bottom  / 8);
		pointy[2] = (rect.bottom  / 8) + (rect.bottom - (rect.bottom  / 8) - (rect.bottom  / 8)) / 2;
		pointy[3] = (rect.bottom  / 8) + (rect.bottom - (rect.bottom  / 8) - (rect.bottom  / 8)) / 2;

		// рисуем оси
		pdc->MoveTo(pointx[0], pointy[0]);
		for(int i = 0; i < 4; i++){
			pdc->LineTo(pointx[i], pointy[i]);
		}
	}

	pdc->SelectObject(poldpen);
	Mpen.DeleteObject();
	ReleaseDC(pdc);
}

// принимает значения для средней линии
void CWinScreen::set_mline(int * sory1, int * sory2, int sep1, int sep2)
{	
	ppmass[3] = sory1;
	liner[0][0]=sory1[0];
	liner[0][1]=sory1[1];
	liner[1][0]=sory2[0];
	liner[1][1]=sory2[1];

	sp1 =sep1;
	sp2 =sep2;

	ppmass[3][0];
	pmaxmass[3] = pmaxmass[0];
	Invalidate();
}

// подчеркиваем нужное 
void CWinScreen::underliter(int * begend)
{
	int mash;
	int cdel;
	int beg= 80;
	int end =140;
	CDC* pdc = GetDC();
	CRect rect;
	GetClientRect(rect);// получаем размер области рисования
	if (rect.IsRectEmpty()) 
		return;            //если квадрат пустой то выйти	
	if (ppmass[3] == nullptr){
		ReleaseDC(pdc);
		return; 
	}
	CPen *poldpen = pdc->SelectObject(penal[3]);
	int zero[2];
	int height;
	int len;

	if(pointx[3] == 0){
		zero[0] = pointx[1];
		zero[1] = pointy[1];
		height = pointy[1] - pointy[0];
		len = pointx[2] - pointx[0];
	}
	else{
		zero[0] = pointx[2];
		zero[1] = pointy[2];
		height = pointy[1] - pointy[2];
		len = pointx[3] - pointx[0];
	}


	mash = len / (end - beg);
	cdel = pmaxmass[1] / (height);
	
	pdc->MoveTo(zero[0], zero[1]- (sp2/cdel));
	pdc->LineTo(zero[0] + len, zero[1]- (sp2/cdel) );

	cdel = pmaxmass[0] / height ;

	pdc->MoveTo(zero[0], zero[1]- (sp1/cdel));
	pdc->LineTo(zero[0] + len, zero[1]- (sp1/cdel) );

	pdc->MoveTo(zero[0], zero[1]);
	for(int i = 0, fl = beg; i < end;i++ ,fl++){
		if(fl == liner[1][0]){
			pdc->MoveTo(pointx[1] +(i*mash), zero[1]);
			pdc->LineTo(pointx[1] +(i*mash), pointy[2] -(pmaxmass[0]/ cdel));
		}
		if(fl == liner[1][1]){
			pdc->MoveTo(pointx[1] +(i*mash), zero[1]);
			pdc->LineTo(pointx[1] +(i*mash), pointy[2] -(pmaxmass[0]/ cdel));
		}
	}
	pdc->SelectObject(poldpen);
	ReleaseDC(pdc);
}

 // обработка прокуртки колесика мыши 
BOOL CWinScreen::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{	
	// UINT nFlags  - хз какие-то приколы 
	// short zDelta - показывает на сколько сколько делений было повернуто колесо из  (+ вправо, - влево)
	// CPoint pt    - координта в которой произошла прокрутка
	
	if(ppmass[0] == nullptr){
		return CButton::OnMouseWheel(nFlags, zDelta, pt);
	}
	
	// переводим в клиентские координаты
	CPoint mypt = pt;
	ScreenToClient(&mypt);

	// курсор за переделами графика

	if(mypt.x > pointx[2]){
		return CButton::OnMouseWheel(nFlags, zDelta, pt); 
	}
	else if(mypt.x < pointx[0]){
		return CButton::OnMouseWheel(nFlags, zDelta, pt);
	}

	//находим значение индекса массива соответвующее положению курсора
	int x_in_mass = begin_graph + ( ( (mypt.x - pointx[0]) * (end_graph - begin_graph) ) / (pointx[2] - pointx[0]) );	
	
	int mash = 10; // цена деления еденицы прокрутки

	// если курcор находиться в сереедине графика маштабирование просиходит за счет сближения двух границ (end_graph , begin_graph)
	// в противном случае сближается самая удаленная граница 

	if(zDelta > 0){

		if((end_graph - begin_graph) <= 10){
			return CButton::OnMouseWheel(nFlags, zDelta, pt);
		}

		if((x_in_mass - begin_graph) > (end_graph - x_in_mass)){
			begin_graph = begin_graph + mash;
		}
		else if ((x_in_mass - begin_graph) < (end_graph- x_in_mass)) {
			end_graph = end_graph - mash;
	
		}
		else{
			begin_graph = begin_graph + mash;
			end_graph = end_graph - mash;
		} 
		
	}
	else{
		
		if((end_graph - begin_graph) >= 60){
			return CButton::OnMouseWheel(nFlags, zDelta, pt);
		}

		if((x_in_mass - begin_graph) > (end_graph- x_in_mass)){
			//begin_graph = begin_graph - mash;
			end_graph = end_graph + mash;
		}
		else if ((x_in_mass - begin_graph) < (end_graph- x_in_mass)) {
			//end_graph = end_graph + mash;
			begin_graph = begin_graph - mash;
	
		}
		else{
			begin_graph = begin_graph - mash;
			end_graph = end_graph + mash;
		}
	}

	Invalidate();
	return CButton::OnMouseWheel(nFlags, zDelta, pt);

}

// возращения шрафика в первоночальное сост
void CWinScreen::un_zoom()
{
	begin_graph = 80;	
	end_graph = 140;

	Invalidate();
}