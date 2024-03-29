﻿// DrawDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "R_Interpreter.h"
#include "DrawDialog.h"
#include "afxdialogex.h"
#include <random>


// DrawDialog 对话框

IMPLEMENT_DYNAMIC(DrawDialog, CDialogEx)

std::default_random_engine e;
int randomRange(int lo, int hi)
{
	return e() % (hi - lo) + lo;
}

DrawDialog::DrawDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DRAW, pParent)
{
	
}

DrawDialog::~DrawDialog()
{
}

void DrawDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void DrawDialog::OnPaint()
{
	CPaintDC content(this); // device context for painting
	//PaintDemo(content);
	switch (dialogType)
	{
	case BarplotView:
		DrawBarplotView(content);
		break;
	case PieView:
		DrawPieView(content);
		break;
	default:
		break;
	}



}

BOOL DrawDialog::OnInitDialog()
{

	return 0;
}

void DrawDialog::DrawPieView(CPaintDC& content)
{
	/// init all params
	dlgWidth = STANDARDWIDTH;
	dlgHeight = 0.6f * dlgWidth;
	int count = data.size();
	int pieHeight = dlgHeight * 3.0 / 5.0;
	int pieWidth = pieHeight;
	int allData = GetSumData();
	int radius = pieHeight / 2.0;

	/// init font
	CFont font;
	LOGFONT log;
	log.lfHeight = 0;
	log.lfEscapement = 0;
	log.lfItalic = 0;
	log.lfUnderline = 0;
	log.lfStrikeOut = 0;
	font.CreateFontIndirect(&log);

	/// init color
	if (m_color.size() != data.size())
	{
		m_color.clear();
		for (int i = 0; i < data.size(); i++)
		{
			m_color.push_back(RGB(randomRange(10, 230), randomRange(10, 255), randomRange(30, 170)));
		}
	}


	UpdateDlgSize();

	/// draw pie
	int preEndx = int(radius * cos(0)), preEndy = int(radius * sin(0));
	int Midpos = dlgHeight / 2.0;
	int sum = 0;
	for (int i = 0; i < data.size(); i++)
	{
		CBrush pieBrush(m_color[i]);
		sum += data[i];
		content.SelectObject(&pieBrush);
		int endx = int(radius * cos(sum * 1.0 / allData * PI * 2)), endy = int(radius * sin(sum * 1.0 / allData * PI * 2));
		content.Pie(Midpos - radius, Midpos - radius, Midpos + radius, Midpos + radius, Midpos + endx, Midpos + endy, Midpos + preEndx, Midpos + preEndy);
		preEndx = endx, preEndy = endy;
	}

	/// draw labels
	int rectWidth = pieHeight * 1.0f/ count;
	int interval = rectWidth * 0.6;
	rectWidth -= interval;
	int startx = dlgHeight, starty = dlgHeight * 4.0 / 5.0 - rectWidth;
	for (int i = 0; i < data.size(); i++)
	{
		CBrush recBrush(m_color[i]);
		CRect recClone(startx, starty - i * (rectWidth + interval), startx + rectWidth, starty - rectWidth - i * (rectWidth + interval));
		content.FillRect(recClone, &recBrush);
		CString labelName(label[i].c_str());
		content.TextOutW(startx + rectWidth + rectWidth, starty - rectWidth - i * (rectWidth + interval) + 4, labelName);
		CString amount((to_string(data[i]).c_str()));
		content.TextOutW(0.8f * dlgWidth, starty - rectWidth - i * (rectWidth + interval) + 4, amount);
	}
}

void DrawDialog::UpdateDlgSize()
{
	CRect temprect(0, 0, dlgWidth, dlgHeight);
	CWnd::SetWindowTextW(title);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);
}

void DrawDialog::DrawBarplotView(CPaintDC& content)
{
	CBrush rectBrush(RGB(140, 140, 140));

	/// init all params
	int count = data.size();
	int recWidth = 25;
	int interval = recWidth / 1.6;
	int picWidth = interval * (count + 1) + recWidth * count;
	dlgWidth = picWidth * 5. / 3.;
	int picHeight = picWidth * 2. / 3.;
	dlgHeight = picHeight * 5. / 3.;

	/// init font
	CFont font;
	LOGFONT log;
	log.lfHeight = 0;
	log.lfEscapement = 0;
	log.lfItalic = 0;
	log.lfUnderline = 0;
	log.lfStrikeOut = 0;
	font.CreateFontIndirect(&log);

	// standard params
	float widthRatio = STANDARDWIDTH * 1.0 / dlgWidth;
	recWidth *= widthRatio;
	picWidth *= widthRatio;
	dlgWidth *= widthRatio;
	dlgHeight *= widthRatio;
	picHeight *= widthRatio;
	interval *= widthRatio;
	UpdateDlgSize();
	content.SelectObject(&font);

	/// coordinate
	CPen pen(PS_SOLID, 2, RGB(80, 80, 80));
	content.SelectObject(&pen);

	//纵坐标
	content.MoveTo(dlgWidth / 5.0, dlgHeight - picHeight / 3.);
	content.LineTo(dlgWidth / 5.0, picHeight / 3.);
	content.LineTo(dlgWidth / 4.8, picHeight / 2.8);
	content.MoveTo(dlgWidth / 5.0, picHeight / 3.);
	content.LineTo(dlgWidth / 5.2, picHeight / 2.8);
	//横坐标
	content.MoveTo(dlgWidth / 5.0, dlgHeight - picHeight / 3. + 1);
	content.LineTo(dlgWidth - dlgWidth / 5.0, dlgHeight - picHeight / 3. + 1);
	content.LineTo(dlgWidth - dlgWidth / 4.8, dlgHeight - picHeight / 2.8 + 1);
	content.MoveTo(dlgWidth - dlgWidth / 5.0, dlgHeight - picHeight / 3. + 1);
	content.LineTo(dlgWidth - dlgWidth / 4.8, dlgHeight - picHeight / 3.2 + 1);

	/// label
	CString xContent(xlabel.c_str());
	content.TextOutW(dlgWidth - dlgWidth / 6., dlgHeight - picHeight / 3.2, xContent);
	CString yContent(ylabel.c_str());
	content.TextOutW(dlgWidth / 8, picHeight / 5.2, yContent);

	/// rects labels
	int mxData = GetMaxData();
	int startWidth = dlgWidth / 5.0;
	content.SelectObject(&font);
	int fontwidth = 6;
	for (int i = 0; i < count; i++)
	{
		int recStartWidth = startWidth + interval + (interval + recWidth) * i;
		CRect recClone(recStartWidth, dlgHeight - data[i] / float(mxData) * picHeight - picHeight / 3., recStartWidth + recWidth, dlgHeight - picHeight / 3.);
		content.FillRect(recClone, &rectBrush);
		CString xContent((to_string(i + 1)).c_str());
		content.TextOutW(recStartWidth + recWidth / 2. - fontwidth * to_string(i).length() / 2., dlgHeight - picHeight / 3.5, xContent);
	}
	for (int i = 0; i < 5; i++)
	{
		CString labelCountent((to_string(mxData / 5 * (i + 1))).c_str());
		content.TextOutW(dlgWidth / 7, dlgHeight - picHeight / 3 - picHeight / 5.0 * (i + 1), labelCountent);
	}

}

int DrawDialog::GetMaxData()
{
	int mx = -1;
	for (int i = 0; i < data.size(); i++)
	{
		if (mx < data[i])
		{
			mx = data[i];
		}
	}
	return mx;
}

int DrawDialog::GetSumData()
{
	int result = 0;
	for (int i = 0; i < data.size(); i++)
	{
		result += data[i];
	}
	return result;
}

void DrawDialog::OnEraseBkGnd()
{

}

BEGIN_MESSAGE_MAP(DrawDialog, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DrawDialog 消息处理程序


void DrawDialog::OnStnClickedStaticDrawPic()
{
	// TODO: 在此添加控件通知处理程序代码
}



