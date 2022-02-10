#pragma once


// CwinGrad

class CwinGrad : public CStatic
{
	DECLARE_DYNAMIC(CwinGrad)

public:
	CwinGrad();
	virtual ~CwinGrad();
 BYTE StartRGB[3];
 int RGBDelta[3];

  // int numColor;
  int minTemp;     // минимальная температура
  float stepGrad;  // шаг градусов

	  int numColor;
  COLORREF coldColor, hotColor;
  void GradientFillRect(HDC pDC, CRect ARect,COLORREF StartColor,COLORREF EndColor);
  void setTemperature(int max, int min);
  void setNumColor(int num){ numColor = num; }
  COLORREF getColor(int);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


