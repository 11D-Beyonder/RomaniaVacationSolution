
// RomaniaVacationSolutionDlg.h: 头文件
//

#pragma once
// CRomaniaVacationSolutionDlg 对话框
class CRomaniaVacationSolutionDlg : public CDialogEx
{
// 构造
public:
	CRomaniaVacationSolutionDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROMANIAVACATIONSOLUTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButtonUcs();
	afx_msg void OnBnClickedGreedy();
	afx_msg void OnBnClickedAstar();
private:
	void showGraph();
};
