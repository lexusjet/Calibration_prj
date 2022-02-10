// CwinGrad.cpp: файл реализации
//

#include "stdafx.h"
#include "work_2.h"
#include "CwinGrad.h"


// CwinGrad

IMPLEMENT_DYNAMIC(CwinGrad, CStatic)

CwinGrad::CwinGrad()
{
  numColor = 0;
  coldColor = RGB(255,255,255); // белый
  hotColor = RGB(0, 0, 0);

}

CwinGrad::~CwinGrad()
{
}


BEGIN_MESSAGE_MAP(CwinGrad, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// обработчики сообщений CwinGrad




void CwinGrad::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: добавьте свой код обработчика сообщений
	// Не вызывать CStatic::OnPaint() для сообщений рисования
	  CRect rect;	  
		GetClientRect(rect); // получаем размер области рисования
		// вызываем функцию рисования
		GradientFillRect(dc.GetSafeHdc(), rect, coldColor, hotColor);// белый, черный

}

void CwinGrad::GradientFillRect(HDC pDC, CRect ARect,
	         COLORREF StartColor,COLORREF EndColor){// белый, черный
  //если квадрат пустой то выйти
  if (ARect.IsRectEmpty()) return;
 HBRUSH Brush;
  int Colors = numColor;

  //если кол-во цветов меньше двух то закрасить первым цветом и выйти
  if (Colors < 2) {
    Brush = CreateSolidBrush(StartColor);
    FillRect(pDC, ARect, Brush);
    DeleteObject(Brush);
    return;
  }

 CRect ColorBand;
 int I, Delta;

  //начальные состовляющие цвета
  StartRGB[0] = GetRValue(EndColor);
  StartRGB[1] = GetGValue(EndColor);
  StartRGB[2] = GetBValue(EndColor);
  //шаг изменения цвета
  RGBDelta[0] = GetRValue(StartColor) - StartRGB[0];
  RGBDelta[1] = GetGValue(StartColor) - StartRGB[1];
  RGBDelta[2] = GetBValue(StartColor) - StartRGB[2];
  ColorBand = ARect;
  Colors = max(2, min(Colors, ARect.Height()));
  Delta = (int)(ARect.Height() / Colors);

  //закрасить основную часть окна
  if (Delta>0)
    for (I=0;I<Colors;I++){
	    ColorBand.top = ARect.top + I * Delta;
	    ColorBand.bottom = ColorBand.top + Delta;
	    Brush = CreateSolidBrush(RGB(
	      StartRGB[0] + MulDiv(I, RGBDelta[0], Colors - 1),
	      StartRGB[1] + MulDiv(I, RGBDelta[1], Colors - 1),
	      StartRGB[2] + MulDiv(I, RGBDelta[2], Colors - 1)));
	    FillRect(pDC, ColorBand, Brush);
	    DeleteObject(Brush);
    }


  //закрасить оставшуюся часть окна
  div_t Res;
  Res = div(ARect.Height() , Colors);
  Delta =Res.rem;//остаток от деления
  if (Delta>0)
    for (I=0; I<Colors; I++){
	    ColorBand.top = ARect.bottom - Delta;
	    ColorBand.bottom = ColorBand.top + Delta;
	    Brush = CreateSolidBrush(EndColor);
	    FillRect(pDC, ColorBand, Brush);
	    DeleteObject(Brush);
    }
}

void CwinGrad::setTemperature(int max, int min){
 int n;
  n = abs((int)max - (int)min) + 2;
  //if(n<10)
    //n=10;
  // минимальное значение
  minTemp = (int)min;
  if(min > max)
    minTemp = (int)max;
  // значит шаг будет
  stepGrad = 1;//((int)max - (int)min + 2) / n;



  setNumColor(n/stepGrad);
  Invalidate();
}
COLORREF CwinGrad::getColor(int temp){
 int I;
  I = (temp - minTemp)/stepGrad;

  


  return (RGB(StartRGB[0] + MulDiv(I, RGBDelta[0], numColor - 1),
	            StartRGB[1] + MulDiv(I, RGBDelta[1], numColor - 1),
	            StartRGB[2] + MulDiv(I, RGBDelta[2], numColor - 1)));
/*  return (RGB(StartRGB[0] + MulDiv(I, RGBDelta[0], numColor - 1),
	            StartRGB[1] + MulDiv(I, RGBDelta[1], numColor - 1),
	            StartRGB[2] + MulDiv(I, RGBDelta[2], numColor - 1)));
              */
}