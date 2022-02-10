// CwinGrad.cpp: ���� ����������
//

#include "stdafx.h"
#include "work_2.h"
#include "CwinGrad.h"


// CwinGrad

IMPLEMENT_DYNAMIC(CwinGrad, CStatic)

CwinGrad::CwinGrad()
{
  numColor = 0;
  coldColor = RGB(255,255,255); // �����
  hotColor = RGB(0, 0, 0);

}

CwinGrad::~CwinGrad()
{
}


BEGIN_MESSAGE_MAP(CwinGrad, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// ����������� ��������� CwinGrad




void CwinGrad::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �������� ���� ��� ����������� ���������
	// �� �������� CStatic::OnPaint() ��� ��������� ���������
	  CRect rect;	  
		GetClientRect(rect); // �������� ������ ������� ���������
		// �������� ������� ���������
		GradientFillRect(dc.GetSafeHdc(), rect, coldColor, hotColor);// �����, ������

}

void CwinGrad::GradientFillRect(HDC pDC, CRect ARect,
	         COLORREF StartColor,COLORREF EndColor){// �����, ������
  //���� ������� ������ �� �����
  if (ARect.IsRectEmpty()) return;
 HBRUSH Brush;
  int Colors = numColor;

  //���� ���-�� ������ ������ ���� �� ��������� ������ ������ � �����
  if (Colors < 2) {
    Brush = CreateSolidBrush(StartColor);
    FillRect(pDC, ARect, Brush);
    DeleteObject(Brush);
    return;
  }

 CRect ColorBand;
 int I, Delta;

  //��������� ������������ �����
  StartRGB[0] = GetRValue(EndColor);
  StartRGB[1] = GetGValue(EndColor);
  StartRGB[2] = GetBValue(EndColor);
  //��� ��������� �����
  RGBDelta[0] = GetRValue(StartColor) - StartRGB[0];
  RGBDelta[1] = GetGValue(StartColor) - StartRGB[1];
  RGBDelta[2] = GetBValue(StartColor) - StartRGB[2];
  ColorBand = ARect;
  Colors = max(2, min(Colors, ARect.Height()));
  Delta = (int)(ARect.Height() / Colors);

  //��������� �������� ����� ����
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


  //��������� ���������� ����� ����
  div_t Res;
  Res = div(ARect.Height() , Colors);
  Delta =Res.rem;//������� �� �������
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
  // ����������� ��������
  minTemp = (int)min;
  if(min > max)
    minTemp = (int)max;
  // ������ ��� �����
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