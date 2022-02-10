// WinScreen.cpp: файл реализации
//

#include "stdafx.h"
#include "work_2.h"
#include "WinScreen.h"


// CWinScreen

IMPLEMENT_DYNAMIC(CWinScreen, CStatic)

CWinScreen::CWinScreen()
{
	ppmass[0] = nullptr;
	ppmass[1] = nullptr;
	ppmass[2] = nullptr;
	ppmass[3] = nullptr;

	//data = nullptr;
	//pdmass = nullptr;
	//pamass = nullptr;

	pen1.CreatePen(PS_SOLID, 1 ,0x1EEB70);
	pen2.CreatePen(PS_SOLID, 1, 0x3333FF);
	pen3.CreatePen(PS_SOLID, 1, 0xD011D7);
	pen4.CreatePen(PS_SOLID, 1, 0x0931CE);

	//pmaxmass[0] = &max;
	//pmaxmass[1] = &dmax;
	//pmaxmass[2] = &amax;

	penal[0] = &pen1;
	penal[1] = &pen2;
	penal[2] = &pen3;
	penal[3] = &pen4;
}

CWinScreen::~CWinScreen()
{	
	pen1.DeleteObject();
	pen2.DeleteObject();
	pen3.DeleteObject();

}


BEGIN_MESSAGE_MAP(CWinScreen, CStatic)
	ON_WM_PAINT()
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
				plot(80, 140, pmaxmass[i], ppmass[i], i);
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
void CWinScreen::setIN(int colms,int* showgr, int *dt, int* strmass1, int* strmass2, int* strmass3)
{
	ppmass[0] = dt;
	max = ppmass[0][0];
	flgraph = showgr;

	//for(int j = 0; j < 236; j++){
	//	strmulti[0][j] = strmass1 [j];
	//}
	//for(int j = 0; j < 236; j++){
	//	strmulti[1][j] = strmass2 [j];
	//}
	//for(int j = 0; j < 236; j++){
	//	strmulti[2][j] = strmass3 [j];
	//}

	for(int i = 1; i < 256; i++){
		if(max < ppmass[0][i]){
		max = ppmass[0][i];
	  }
	}
	pmaxmass[0] = max;
 //CWinScreen::GraphPloting(0x000000);

	Invalidate();
  
}

// принимает занчения для дифференциального граффика
void CWinScreen::setin_dif(int dx, int* dmass )
{
	ppmass[1] = dmass;
	maxp = dx;
	dmax =abs(dmass[maxp]);
	pmaxmass[1] = dmax;
	//DGraphPloting(0x000000);
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
	//Plot_agraph();
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
	CDC* pdc = GetDC();
	CRect rect;
	GetClientRect(rect);// получаем размер области рисования
	if (rect.IsRectEmpty()) 
		return;            //если квадрат пустой то выйти	
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


	int mash =len / ( end - beg);
	int cdel = max/ height ;
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



//CWinScreen::setIN(int xx, int yy, int *dt, int max, CwinGrad* gr)
//{
//  x = xx;
//  y = yy;
//  data = dt;
//
//  numColor =  max + 1;
//  StartColor = RGB(255,255,255); // белый
//  EndColor = RGB(0, 0, 0);
//
//  //начальные состовляющие цвета
//  StartRGB[0] = GetRValue(StartColor);
//  StartRGB[1] = GetGValue(StartColor);
//  StartRGB[2] = GetBValue(StartColor);
//  //шаг изменения цвета
//  RGBDelta[0] = abs(GetRValue(StartColor) - GetRValue(EndColor));
//  RGBDelta[1] = abs(GetGValue(StartColor) - GetGValue(EndColor));
//  RGBDelta[2] = abs(GetBValue(StartColor) - GetBValue(EndColor));
//
//
//
//  statGrad = gr;
//  //gr->Invalidate();
//
//}
//void CWinScreen::GradientFillRect(HDC pDC)
//{
// HBRUSH Brush;
// CRect ColorBand;
// COLORREF StartColor = RGB(220, 220, 220);
// CRect rect;	  
//
//  GetClientRect(rect); // получаем размер области рисования
//  if (rect.IsRectEmpty()) 
//    return;            //если квадрат пустой то выйти
//
//  //закрасим поле
//  ColorBand = rect;
//  Brush = CreateHatchBrush(HS_DIAGCROSS, StartColor);
//  FillRect(pDC, ColorBand, Brush);
//  DeleteObject(Brush);
//
//  if(x==0 || y==0)
//    return;
//  sz; // размер квадратика
//  int i = rect.Width()/x;
//  int j = rect.Height()/y;
//  sz = i;
//  if(j < i)
//    sz = j;
//  // отступ слева
//  margX = (rect.Width() - x*sz)/2;
//  margY = (rect.Height() - y*sz)/2;
//
//  // рисуем квадратики 
//  for(i=0; i<x; i++){
//    for(j=0; j<y; j++){
//      
//      Brush = CreateSolidBrush(getColor(*(data+j*x+i)));
//      ColorBand.top = margY + j*sz;
//      ColorBand.bottom = margY + (j+1)*sz;
//      ColorBand.left = margX + i*sz;
//      ColorBand.right = margX + (i+1)*sz;
//      FillRect(pDC, ColorBand, Brush);
//      DeleteObject(Brush);
//	  }
//  }
//}

//// построение граффика обычного
//void CWinScreen::GraphPloting(COLORREF GraphColor)
//{
//	CDC* pdc = GetDC();
//	CPen Mpen;
//	CRect ColorBand;
//	CRect rect;	
//	GetClientRect(rect);// получаем размер области рисования
//	ColorBand = rect;
//
//	
//	// зарисовываем фон белым // 
//	CBrush Brush;
//	COLORREF StartColor = RGB(255, 255, 255);
//
//	if (rect.IsRectEmpty()) 
//	return;            //если квадрат пустой то выйти
//
//	//закрасим поле
//	ColorBand = rect;
//
//	Brush.CreateSolidBrush(StartColor);
//	//CBrush *poldbrush = pdc->SelectObject(&Brush);
//	pdc->FillRect(ColorBand, &Brush);
//	//pdc->SelectObject(poldbrush);
//	Brush.DeleteObject();
//
//
//
//	// коридинаты точек осей
//	
//	pointx[0] = ((rect.right) / 8);
//	pointx[1] = ((rect.right) / 8);
//	pointx[2] = ((rect.right) - (rect.right) / 16) ;
//
//
//	pointy[0] = (rect.bottom  / 8);
//	pointy[1] = rect.bottom - (rect.bottom  / 8);
//	pointy[2] = rect.bottom - (rect.bottom  / 8);
//
//	Mpen.CreatePen(PS_SOLID, 1, GraphColor);
//	CPen *poldpen = pdc->SelectObject(&Mpen);
//	// рисуем оси
//	pdc->MoveTo(pointx[0], pointy[0]);
//	 for(int i = 1;i < 3;i ++){
//		 pdc->LineTo(pointx[i],pointy[i]);	
//	 }
//
//	if (data == nullptr){
//		pdc->SelectObject(poldpen);
//		Mpen.DeleteObject();
//		ReleaseDC(pdc);
//		return; 
//	}
//	int len = pointy[1] -pointy[0]; 
//	int cdel =max/len;
//
//	pdc->MoveTo(pointx[1], pointy[1]);
//	for(int i = 0 ,fl = 80 ; i < 96; i++, fl++){
//		 pdc->LineTo(pointx[1]+(10*i),pointy[1] - (data[fl] / cdel));
//	}
//
//	
//	for(int i = 0; i < 3; i++){
//		pdc->MoveTo(pointx[1], pointy[1]);
//		pdc->SelectObject(penal[i]);
//		int cof = i + 1;
//		for(int j = 0 ,fl = 80; j < 96 ; j++, fl++){
//			pdc->LineTo(pointx[1]+(10*j), pointy[1] - (strmulti[i][fl] / cdel));
//		}
//	}
//
//
//
//
//	pdc->SelectObject(Mpen);
//	pdc->SelectObject(poldpen);
//	Mpen.DeleteObject();
//	ReleaseDC(pdc);
//
//}

//// построение дифференциального графика
/*void CWinScreen::DGraphPloting(COLORREF GraphColor)
//{
//	CDC* pdc = GetDC();
//	CPen Mpen;
//	CRect ColorBand;
//	CRect rect;	
//	GetClientRect(rect);// получаем размер области рисования
//	ColorBand = rect;
//	
//	// зарисовываем фон белым // 
//	CBrush Brush;
//	COLORREF StartColor = RGB(255, 255, 255);
//
//	if (rect.IsRectEmpty()) 
//		return;            //если квадрат пустой то выйти
//
//	//закрасим поле
//	ColorBand = rect;
//
//	Brush.CreateSolidBrush(StartColor);
//	pdc->FillRect(ColorBand, &Brush);
//	Brush.DeleteObject();
//
//
//	// координаты точек осей с отриц 
//	
//	pointx[0] = ((rect.right) / 8);
//	pointx[1] = ((rect.right) / 8);
//	pointx[2] = ((rect.right) / 8);
//	pointx[3] = ((rect.right) - (rect.right) / 16) ;
//
//
//	pointy[0] = (rect.bottom  / 8);
//	pointy[1] = rect.bottom - (rect.bottom  / 8);
//	pointy[2] = (rect.bottom  / 8) + (rect.bottom - (rect.bottom  / 8) - (rect.bottom  / 8)) / 2;
//	pointy[3] = (rect.bottom  / 8) + (rect.bottom - (rect.bottom  / 8) - (rect.bottom  / 8)) / 2;
//
//
//	Mpen.CreatePen(PS_SOLID, 1, GraphColor);
//	CPen *poldpen = pdc->SelectObject(&Mpen);
//	// рисуем оси
//	pdc->MoveTo(pointx[0], pointy[0]);
//	for(int i = 0; i < 4; i++){
//		pdc->LineTo(pointx[i], pointy[i]);
//	}
//
//	if (pdmass == nullptr){
//		pdc->SelectObject(poldpen);
//		Mpen.DeleteObject();
//		ReleaseDC(pdc);
//		return; 
//	}
//	// построение диф граффика // 
//	int len = (pointy[1] - pointy[0]) / 2;
//	int cdel = dmax / len;
//	pdc->MoveTo(pointx[2], pointy[2]);
//	for(int i = 0 ,fl = 100 ; i < 85; i++, fl++){
//		if(pdmass > 0){
//			pdc->LineTo(pointx[1]+(10 * i), pointy[2] - (pdmass[fl] / cdel));
//		}
//		else{
//			pdc->LineTo(pointx[1]+(10 * i), pointy[2] + (pdmass[fl] / cdel));
//		}
//	}
//
//	pdc->SelectObject(Mpen);
//	pdc->SelectObject(poldpen);
//	Mpen.DeleteObject();
//	ReleaseDC(pdc);
//
//}
//
//// график второй производной
//void CWinScreen::Plot_agraph(void)
//{
//
//	CDC* pdc = GetDC();
//	CRect ColorBand;
//	CRect rect;	
//	GetClientRect(rect);// получаем размер области рисования
//	ColorBand = rect;
//	
//	// зарисовываем фон белым // 
//	CBrush Brush;
//	COLORREF StartColor = RGB(255, 255, 255);
//
//	if (rect.IsRectEmpty()) 
//		return;            //если квадрат пустой то выйти
//
//	//закрасим поле
//	ColorBand = rect;
//
//	Brush.CreateSolidBrush(StartColor);
//	pdc->FillRect(ColorBand, &Brush);
//	Brush.DeleteObject();
//
//
//	// координаты точек осей с отриц 
//	
//	pointx[0] = ((rect.right) / 8);
//	pointx[1] = ((rect.right) / 8);
//	pointx[2] = ((rect.right) / 8);
//	pointx[3] = ((rect.right) - (rect.right) / 16) ;
//
//	
//	pointy[0] = (rect.bottom  / 8);
//	pointy[1] = rect.bottom - (rect.bottom  / 8);
//	pointy[2] = (rect.bottom  / 8) + (rect.bottom - (rect.bottom  / 8) - (rect.bottom  / 8)) / 2;
//	pointy[3] = (rect.bottom  / 8) + (rect.bottom - (rect.bottom  / 8) - (rect.bottom  / 8)) / 2;
//
//
//	CPen *poldpen = pdc->SelectObject(penal[0]);
//	
//	// рисуем оси
//	pdc->MoveTo(pointx[0], pointy[0]);
//	for(int i = 0; i < 4; i++){
//		pdc->LineTo(pointx[i], pointy[i]);
//	}
//
//	if (pamass == nullptr){
//		pdc->SelectObject(poldpen);
//		ReleaseDC(pdc);
//		return; 
//	}
//	// построение граффика второй проиводной // 
//	int len = (pointy[1] - pointy[0]) / 2;
//	int cdel = amax / len;
//	pdc->MoveTo(pointx[2], pointy[2]);
//	for(int i = 0 ,fl = 100 ; i < 85; i++, fl++){
//		if(pdmass > 0){
//			pdc->LineTo(pointx[1]+(10 * i), pointy[2] - (pamass[fl] / cdel));
//		}
//		else{
//			pdc->LineTo(pointx[1]+(10 * i), pointy[2] + (pamass[fl] / cdel));
//		}
//	}
//
//	pdc->SelectObject(poldpen);
//	ReleaseDC(pdc);
//
}*/


