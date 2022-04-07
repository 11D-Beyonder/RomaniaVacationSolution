
// RomaniaVacationSolutionDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "RomaniaVacationSolution.h"
#include "RomaniaVacationSolutionDlg.h"
#include "afxdialogex.h"
#include "CityInfo.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRomaniaVacationSolutionDlg 对话框



CRomaniaVacationSolutionDlg::CRomaniaVacationSolutionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROMANIAVACATIONSOLUTION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRomaniaVacationSolutionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRomaniaVacationSolutionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_UCS, &CRomaniaVacationSolutionDlg::OnBnClickedButtonUcs)
	ON_BN_CLICKED(IDC_GREEDY, &CRomaniaVacationSolutionDlg::OnBnClickedGreedy)
	ON_BN_CLICKED(IDC_ASTAR, &CRomaniaVacationSolutionDlg::OnBnClickedAstar)
END_MESSAGE_MAP()


// CRomaniaVacationSolutionDlg 消息处理程序

BOOL CRomaniaVacationSolutionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRomaniaVacationSolutionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRomaniaVacationSolutionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}

	showGraph();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRomaniaVacationSolutionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRomaniaVacationSolutionDlg::showGraph() {
	CClientDC dc(this);
	dc.FillRect(CRect(0,0,680,420),new CBrush(RGB(255,255,255)));
	for (int i = 0; i < CITY_NUM; i++) {
		for (int j = i + 1; j < CITY_NUM; j++) {
			if (distance[i][j] != INF) {
				CClientDC dc(this);
				CPen pen;
				pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
				dc.MoveTo(position[i][0], position[i][1]);
				dc.LineTo(position[j][0], position[j][1]);
				pen.DeleteObject();
				CString str;
				str.Format(_T("%d"), distance[i][j]);
				dc.TextOutW(position[i][0] + position[j][0] >> 1, position[i][1] + position[j][1] >> 1, str);
			}
		}
	}
	for (int i = 0; i < CITY_NUM; i++) {
		CClientDC dc(this);
		dc.TextOutW(namePos[i][0] + 5, namePos[i][1], CString(name[i].c_str()));
		dc.FillRect(CRect(position[i][0] - 5, position[i][1] - 5, position[i][0] + 5, position[i][1] + 5), new CBrush(RGB(255, 0, 0)));
	}
}

void CRomaniaVacationSolutionDlg::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString pos;
	pos.Format(_T("%d %d"), point.x, point.y);
	SetDlgItemText(IDC_EDIT_POS, pos);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CRomaniaVacationSolutionDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnLButtonUp(nFlags, point);
}

int CRomaniaVacationSolutionDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}


void CRomaniaVacationSolutionDlg::OnBnClickedButtonUcs() {
	showGraph();
	// TODO: 在此添加控件通知处理程序代码
	//代价一致的宽度优先
	std::vector<int>pre(CITY_NUM, -1);
	struct node {
		int ID;
		int dis;
		bool operator<(const node& other) const {
			return other.dis < dis;
		}
	};
	//统计生成结点数
	int cnt = 1;
	CClientDC dc(this);
	dc.FillRect(CRect(position[0][0] - 5, position[0][1] - 5, position[0][0] + 5, position[0][1] + 5), new CBrush(RGB(0, 0, 255)));
	Sleep(500);
	//优先队列O(logN)维护最小代价
	std::priority_queue<node>q;
	//记录最小代价
	std::vector<int>dis(CITY_NUM, INF);
	//计时
	clock_t time = -clock();
	q.push(node{ 0,0 });
	dis[0] = 0;
	while (!q.empty()) {
		//得到代价最小状态
		node cur = q.top();
		q.pop();
		if (cur.ID == 1) {
			break;
		}
		for (int i = 0; i < CITY_NUM; i++) {
			if (distance[cur.ID][i] == INF || i == cur.ID) {
				continue;
			}
			if (dis[i] > dis[cur.ID] + distance[cur.ID][i]) {
				//撤销画图时间
				time += clock();
				if (~pre[i]) {
					//覆盖原来的路径
					CPen pen;
					pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
					dc.SelectObject(pen);
					dc.MoveTo(position[pre[i]][0], position[pre[i]][1]);
					dc.LineTo(position[i][0], position[i][1]);
					pen.DeleteObject();
				}
				time -= clock();
				//松弛操作
				dis[i] = dis[cur.ID] + distance[cur.ID][i];
				pre[i] = cur.ID;
				q.push(node{ i,dis[i] });
				//结点数增加
				++cnt;
				time += clock();
				Sleep(500);
				dc.FillRect(CRect(position[i][0] - 5, position[i][1] - 5, position[i][0] + 5, position[i][1] + 5), new CBrush(RGB(0, 0, 255)));
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
				dc.SelectObject(pen);
				dc.MoveTo(position[pre[i]][0], position[pre[i]][1]);
				dc.LineTo(position[i][0], position[i][1]);
				pen.DeleteObject();
				time -= clock();
			}
		}
	}
	time += clock();
	CString ans;
	ans.Format(_T("路程%d\r\n耗时%ldms\r\n生成节点数%d"), dis[1], time, 20);
	MessageBox(ans);
}

void CRomaniaVacationSolutionDlg::OnBnClickedGreedy() {
	showGraph();
	// TODO: 在此添加控件通知处理程序代码
	//贪婪算法
	std::vector<int>pre(CITY_NUM, -1);
	struct node {
		int ID;
		int h;
		bool operator<(const node& other) const {
			return other.h < h;
		}
	};
	CClientDC dc(this);
	dc.FillRect(CRect(position[0][0] - 5, position[0][1] - 5, position[0][0] + 5, position[0][1] + 5), new CBrush(RGB(0, 0, 255)));
	Sleep(500);
	//优先队列O(logN)维护最小代价
	std::priority_queue<node>q;
	//记录最小代价
	std::vector<int>dis(CITY_NUM, INF);
	clock_t time = -clock();
	q.push(node{ 0,h[0] });
	dis[0] = 0;
	int cnt = 0;
	while (!q.empty()) {
		//得到代价最小状态
		node cur = q.top();
		q.pop();
		if (cur.ID == 1) {
			break;
		}
		for (int i = 0; i < CITY_NUM; i++) {
			if (distance[cur.ID][i] == INF || i == cur.ID) {
				continue;
			}
			++cnt;
			q.push(node{ i,h[i] });
			if (dis[i] > dis[cur.ID] + distance[cur.ID][i]) {
				if (~pre[i]) {
					//覆盖原来的路径
					CPen pen;
					pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
					dc.SelectObject(pen);
					dc.MoveTo(position[pre[i]][0], position[pre[i]][1]);
					dc.LineTo(position[i][0], position[i][1]);
					pen.DeleteObject();
				}
				//松弛操作
				dis[i] = dis[cur.ID] + distance[cur.ID][i];
				pre[i] = cur.ID;
				//撤销画图时间
				time += clock();
				Sleep(500);
				dc.FillRect(CRect(position[i][0] - 5, position[i][1] - 5, position[i][0] + 5, position[i][1] + 5), new CBrush(RGB(0, 0, 255)));
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
				dc.SelectObject(pen);
				dc.MoveTo(position[pre[i]][0], position[pre[i]][1]);
				dc.LineTo(position[i][0], position[i][1]);
				pen.DeleteObject();
				time -= clock();
			}
		};
	}
	time += clock();
	CString ans;
	ans.Format(_T("路程%d\r\n耗时%ldms\r\n生成节点数%d"), dis[1], time, cnt);
	MessageBox(ans);
}


void CRomaniaVacationSolutionDlg::OnBnClickedAstar() {
	showGraph();
	// TODO: 在此添加控件通知处理程序代码
	//A*
	std::vector<int>pre(CITY_NUM, -1);
	struct node {
		int ID;
		int f;
		bool operator<(const node& other) const {
			return other.f < f;
		}
	};
	//统计生成结点数
	int cnt = 1;
	CClientDC dc(this);
	dc.FillRect(CRect(position[0][0] - 5, position[0][1] - 5, position[0][0] + 5, position[0][1] + 5), new CBrush(RGB(0, 0, 255)));
	Sleep(500);
	//优先队列O(logN)维护最小代价
	std::priority_queue<node>q;
	//记录最小代价
	std::vector<int>dis(CITY_NUM, INF);
	clock_t time = -clock();
	q.push(node{ 0,h[0] });
	dis[0] = 0;
	while (!q.empty()) {
		//得到代价最小状态
		node cur = q.top();
		q.pop();
		if (cur.ID == 1) {
			break;
		}
		for (int i = 0; i < CITY_NUM; i++) {
			if (distance[cur.ID][i] == INF || i == cur.ID) {
				continue;
			}
			q.push(node{ i,dis[cur.ID] + distance[cur.ID][i] + h[i] });
			++cnt;
			if (dis[i] > dis[cur.ID] + distance[cur.ID][i]) {
				if (~pre[i]) {
					//覆盖原来的路径
					CPen pen;
					pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
					dc.SelectObject(pen);
					dc.MoveTo(position[pre[i]][0], position[pre[i]][1]);
					dc.LineTo(position[i][0], position[i][1]);
					pen.DeleteObject();
				}
				//松弛操作
				dis[i] = dis[cur.ID] + distance[cur.ID][i];
				pre[i] = cur.ID;
				//撤销画图时间
				time += clock();
				Sleep(500);
				dc.FillRect(CRect(position[i][0] - 5, position[i][1] - 5, position[i][0] + 5, position[i][1] + 5), new CBrush(RGB(0, 0, 255)));
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
				dc.SelectObject(pen);
				dc.MoveTo(position[pre[i]][0], position[pre[i]][1]);
				dc.LineTo(position[i][0], position[i][1]);
				pen.DeleteObject();
				time -= clock();
			}
		}
	}
	time += clock();
	CString ans;
	ans.Format(_T("路程%d\r\n耗时%ldms\r\n生成节点数%d"), dis[1], time, cnt);
	MessageBox(ans);
}