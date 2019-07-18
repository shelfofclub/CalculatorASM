
// CalculatorASMDlg.h: 头文件
//

#pragma once


// CCalculatorASMDlg 对话框
class CCalculatorASMDlg : public CDialogEx
{
// 构造
public:
	CCalculatorASMDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATORASM_DIALOG };
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
	void clickBTNum(char* num);
	void clickBTUnary(int op);
	void clickBTBinary(int op);
public:
	afx_msg void OnBnClickedbt0();
	afx_msg void OnBnClickedbt1();
	afx_msg void OnBnClickedbt2();
	afx_msg void OnBnClickedbt3();
	afx_msg void OnBnClickedbt4();
	afx_msg void OnBnClickedbt5();
	afx_msg void OnBnClickedbt6();
	afx_msg void OnBnClickedbt7();
	afx_msg void OnBnClickedbt8();
	afx_msg void OnBnClickedbt9();
	afx_msg void OnBnClickedbtdot();
	afx_msg void OnBnClickedbtplus();
	afx_msg void OnBnClickedbtsubtract();
	afx_msg void OnBnClickedbtmultiply();
	afx_msg void OnBnClickedbtdivide();
	afx_msg void OnBnClickedbtmod();
	afx_msg void OnBnClickedbtsin();
	afx_msg void OnBnClickedbtcos();
	afx_msg void OnBnClickedbttan();
	afx_msg void OnBnClickedbtequal();
	afx_msg void OnBnClickedbtclean();
	afx_msg void OnBnClickedbtyeah();
};
