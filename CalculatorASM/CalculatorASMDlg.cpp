
// CalculatorASMDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CalculatorASM.h"
#include "CalculatorASMDlg.h"
#include "afxdialogex.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int restart;
double numStack[10];
int numStackTop;
int opStack[10];
int opStackTop;
// double retDouble;

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


// CCalculatorASMDlg 对话框



CCalculatorASMDlg::CCalculatorASMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATORASM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorASMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculatorASMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(bt0, &CCalculatorASMDlg::OnBnClickedbt0)
	ON_BN_CLICKED(bt1, &CCalculatorASMDlg::OnBnClickedbt1)
	ON_BN_CLICKED(bt2, &CCalculatorASMDlg::OnBnClickedbt2)
	ON_BN_CLICKED(bt3, &CCalculatorASMDlg::OnBnClickedbt3)
	ON_BN_CLICKED(bt4, &CCalculatorASMDlg::OnBnClickedbt4)
	ON_BN_CLICKED(bt5, &CCalculatorASMDlg::OnBnClickedbt5)
	ON_BN_CLICKED(bt6, &CCalculatorASMDlg::OnBnClickedbt6)
	ON_BN_CLICKED(bt7, &CCalculatorASMDlg::OnBnClickedbt7)
	ON_BN_CLICKED(bt8, &CCalculatorASMDlg::OnBnClickedbt8)
	ON_BN_CLICKED(bt9, &CCalculatorASMDlg::OnBnClickedbt9)
	ON_BN_CLICKED(btDot, &CCalculatorASMDlg::OnBnClickedbtdot)
	ON_BN_CLICKED(btPlus, &CCalculatorASMDlg::OnBnClickedbtplus)
	ON_BN_CLICKED(btSubtract, &CCalculatorASMDlg::OnBnClickedbtsubtract)
	ON_BN_CLICKED(btMultiply, &CCalculatorASMDlg::OnBnClickedbtmultiply)
	ON_BN_CLICKED(btDivide, &CCalculatorASMDlg::OnBnClickedbtdivide)
	ON_BN_CLICKED(btMod, &CCalculatorASMDlg::OnBnClickedbtmod)
	ON_BN_CLICKED(btSin, &CCalculatorASMDlg::OnBnClickedbtsin)
	ON_BN_CLICKED(btCos, &CCalculatorASMDlg::OnBnClickedbtcos)
	ON_BN_CLICKED(btTan, &CCalculatorASMDlg::OnBnClickedbttan)
	ON_BN_CLICKED(btEqual, &CCalculatorASMDlg::OnBnClickedbtequal)
	ON_BN_CLICKED(btClean, &CCalculatorASMDlg::OnBnClickedbtclean)
	ON_BN_CLICKED(btYeah, &CCalculatorASMDlg::OnBnClickedbtyeah)
END_MESSAGE_MAP()


// CCalculatorASMDlg 消息处理程序

BOOL CCalculatorASMDlg::OnInitDialog()
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
	CEdit* pEcDisplayText;
	pEcDisplayText = (CEdit*) GetDlgItem(ecDisplayText);
	pEcDisplayText->SetWindowTextW(_T("0"));

	restart = 1;
	memset(numStack, 0, sizeof(numStack));
	numStackTop = 0;
	memset(opStack, 0, sizeof(opStack));
	opStackTop = 0;
	
	this->GetFocus();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorASMDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorASMDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorASMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double  readNumText(char* src) {
	int i = 0;
	int len = strlen(src);
	double dotone = 0.1;
	int ten = 10;
	double retDouble=0;
	int temp = 0;
	_asm {
		push esi
		push ebx
		push ecx
		push edx

		finit
		fldz
		mov esi,i
		mov ebx,src
	L1:
		cmp esi, len
		jnb BREAK1
		movzx ecx, [ebx][esi]
		cmp ecx,2eh
		jz BREAK1
		fild ten
		fmul
		sub ecx,30h
		mov temp,ecx
		fild temp
		fadd
		inc esi
		jmp L1
	BREAK1:
		mov edx, esi
		;mov ebx, len - 1
		;inc esi
		mov esi,len
		dec esi
		fldz
	L2 :
		cmp esi, edx
		jna BREAK2
		movzx ecx, [ebx][esi]
		fld dotone
		fmul
		sub ecx,30h
		mov temp,ecx
		fild temp
		fadd
		dec esi
		jmp L2
	BREAK2:
		fmul dotone
		fadd
		fstp retDouble

		pop edx
		pop ecx
		pop ebx
		pop esi
	}
	return retDouble;
}

double add(double a,double b) {
	double retDouble = 0;
	_asm {
		finit
		fld a
		fadd b
		fstp retDouble
	}
	return retDouble;
}

double subtract(double a, double b) {
	double retDouble = 0;
	_asm {
		finit
		fld a
		fsub b
		fstp retDouble
	}
	return retDouble;
}

double multiply(double a, double b) {
	double retDouble = 0;
	_asm {
		finit
		fld a
		fmul b
		fstp retDouble
	}
	return retDouble;
}

double divide(double a, double b) {
	double retDouble = 0;
	_asm {
		finit
		fld a
		fdiv b
		fstp retDouble
	}
	return retDouble;
}

double mod(double a, double b) {
	double retDouble = 0;
	_asm {
		finit
		fld b
		fld a
		fprem
		fstp retDouble
	}
	return retDouble;
}

double mySin(double a) {
	double retDouble = 0;
	_asm {
		finit
		fld a
		fsin
		fstp retDouble
	}
	
	return retDouble;
}

double myCos(double a) {
	double retDouble = 0;
	_asm {
		finit
		fld a
		fcos
		fstp retDouble
	}

	return retDouble;
}

double myTan(double a) {
	double retDouble = 0;
	_asm {
		finit
		fld a
		fptan
		fstp retDouble
		fstp retDouble
	}

	return retDouble;
}

double calculate(void) {
	double a = 0, b = 0;
	int op = 0;
	//int switchaddress[8] = { 0 };
	double retDouble = 0;
	_asm {
		push ebx
		push ecx
		push esi

		mov ebx, offset opStack
		mov esi, opStackTop
		dec esi
		mov ecx, [ebx + esi * 4]
		mov op, ecx
		dec opStackTop

		mov ebx, offset numStack
		mov esi, numStackTop
		dec esi
		mov ecx, [ebx+esi*8]
		mov dword ptr b, ecx
		mov ecx, [ebx+esi*8] + 4
		mov dword ptr b + 4, ecx
		dec esi
		dec numStackTop
		cmp op,6
		jnb UPSTKTOP
		mov ecx, [ebx+esi*8]
		mov dword ptr a, ecx
		mov ecx, [ebx+esi*8] + 4
		mov dword ptr a + 4, ecx
		dec esi
		dec numStackTop
	UPSTKTOP:
		; mov numStackTop, esi

		pop esi
		pop ecx
		pop ebx
	}
	//	mov ebx,offset switchaddress
	//	mov [ebx+0*4],offset FUNADD
	//	mov [ebx+1*4],offset FUNSUB
	//	mov [ebx+2*4],offset FUNMUL
	//	mov [ebx+3*4],offset FUNDIV
	//	mov [ebx+4*4],offset FUNMOD
	//	mov [ebx+5*4],offset FUNSIN
	//	mov [ebx+6*4],offset FUNCOS
	//	mov [ebx+7*4],offset FUNTAN

	//	mov ecx,op
	//	jmp [ebx+ecx*4]

	//	jmp ENDCALCU

	//FUNADD:
	//	invoke add,a,b
	//	jmp ENDCALCU

	//FUNSUB:
	//	invoke subtract,a,b
	//	jmp ENDCALCU

	//FUNMUL:
	//	invoke multiply,a,b
	//	jmp ENDCALCU
	//
	//FUNDIV:
	//	invoke divide,a,b
	//	jmp ENDCALCU
	//
	//FUNMOD:
	//	invoke mod,a,b
	//	jmp ENDCALCU
	//
	//FUNSIN:
	//	invoke mySin,a
	//	jmp ENDCALCU
	//
	//FUNCOS:
	//	invoke myCos,a
	//	jmp ENDCALCU
	//
	//FUNTAN:
	//	invoke myTan,a

	//ENDCALCU:
	//	mov ebx,offset numStack
	//	mov esi,numStackTop
	//	mov ecx,retDouble
	//	mov dword ptr [ebx][esi],retDouble
	//	mov edx,retDouble+4
	//	mov dword ptr [ebx][esi]+4,edx
	//	inc numStackTop
	//}
	switch (op)
	{
	case 1:
		retDouble=add(a, b);
		break;

	case 2:
		retDouble=subtract(a, b);
		break;

	case 3:
		retDouble=multiply(a, b);
		break;

	case 4:
		retDouble=divide(a, b);
		break;

	case 5:
		retDouble=mod(a, b);
		break;

	case 6:
		retDouble=mySin(b);
		break;

	case 7:
		retDouble=myCos(b);
		break;

	case 8:
		retDouble=myTan(b);
		break;

	default:
		break;
	}
	_asm {
		push ebx
		push ecx
		push edx
		push esi

		mov ebx,offset numStack
		mov esi,numStackTop
		mov ecx,dword ptr retDouble
		mov dword ptr [ebx+esi*8],ecx
		mov edx,dword ptr retDouble+4
		mov dword ptr [ebx+esi*8]+4,edx
		inc numStackTop

		pop esi
		pop edx
		pop ecx
		pop ebx
	}
	return retDouble;
}

//void clickBTNum(char* num) {
//		CString input;
//	CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
//	pEcDisplayText->GetWindowTextW(input);
//
//	if (restart)
//	{
//		input = "1";
//	}
//	else
//	{
//		input += "1";
//	}
//	restart = 0;
//
//	pEcDisplayText->SetWindowTextW(input);
//
//}

void CCalculatorASMDlg::clickBTNum(char* num)
{
	CString input;
	CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	pEcDisplayText->GetWindowTextW(input);

	if (restart)
	{
		input = num;
	}
	else
	{
		input += num;
	}
	restart = 0;

	pEcDisplayText->SetWindowTextW(input);

}

void CCalculatorASMDlg::clickBTUnary(int op)
{
	double resDouble = 0;
	CString input;
	CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	pEcDisplayText->GetWindowTextW(input);

	USES_CONVERSION;
	char* pcInput = T2A(input);

	double num = readNumText(pcInput);
	_asm {
		push ebx
		push ecx
		push esi

		mov ebx, offset numStack
		mov esi, numStackTop
		mov ecx, dword ptr num
		mov[ebx + esi * 8], ecx
		mov ecx, dword ptr num + 4
		mov[ebx + esi * 8] + 4, ecx
		inc numStackTop
		; mov ebx, esi
		; mov numStackTop, esi

		; mov dword ptr resDouble, 0
		; mov dword ptr resDouble + 4, 0
		pop esi
		pop ecx
		pop ebx
	}
	// 	;.if opStackTop == 0
	// 	cmp opStackTop,0
	// 	jna ENDIFEMPTY
	// 	;.else
	// 	;计算
	// 	invoke calculate

	// ENDIFEMPTY:
	if (opStackTop > 0) {
		resDouble = calculate();
	}
	_asm {
		push ebx
		push ecx
		push esi

		mov ebx, offset opStack
		mov esi, opStackTop
		mov ecx,op
		mov[ebx + esi * 4], ecx
		inc opStackTop
		mov restart, 1

		pop esi
		pop ecx
		pop ebx
	}
	resDouble = calculate();

	// restart=1;
	CString input2;
	input2.Format(_T("%lf"), resDouble);

	// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	pEcDisplayText->SetWindowTextW(input2);

}

void CCalculatorASMDlg::clickBTBinary(int op)
{
	double resDouble = 0;
	CString input;
	CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	pEcDisplayText->GetWindowTextW(input);

	USES_CONVERSION;
	char* pcInput = T2A(input);

	double num = readNumText(pcInput);
	_asm {
		push ebx
		push ecx
		push esi

		mov ebx, offset numStack
		mov esi, numStackTop
		mov ecx, dword ptr num
		mov[ebx + esi * 8], ecx
		mov ecx, dword ptr num + 4
		mov[ebx + esi * 8] + 4, ecx
		inc numStackTop
		; mov ebx, esi
		; mov numStackTop, esi

		; mov dword ptr resDouble, 0
		; mov dword ptr resDouble + 4, 0

		pop esi
		pop ecx
		pop ebx
	}
	// 	;.if opStackTop == 0
	// 	cmp opStackTop,0
	// 	jna ENDIFEMPTY
	// 	;.else
	// 	;计算
	// 	invoke calculate

	// ENDIFEMPTY:
	if (opStackTop > 0) {
		resDouble = calculate();
	}
	_asm {
		push ebx
		push ecx
		push esi

		mov ebx, offset opStack
		mov esi, opStackTop
		mov ecx,op
		mov[ebx + esi * 4], ecx
		inc opStackTop
		mov restart, 1

		pop esi
		pop ecx
		pop ebx
	}

	// restart=1;
	CString input2;
	input2.Format(_T("%lf"), resDouble);

	// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	pEcDisplayText->SetWindowTextW(input2);

}

void CCalculatorASMDlg::OnBnClickedbt0()
{
	clickBTNum("0");
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "0";
	//}
	//else
	//{
	//	input += "0";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);

	//USES_CONVERSION;
	//char* pc = T2A(input);
	//printf("%s\n%d\n", pc, strlen(pc));


	//_as/*m {
	//	.if restart == 0
	//		
	//}*/
}


void CCalculatorASMDlg::OnBnClickedbt1()
{
	clickBTNum("1");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "1";
	//}
	//else
	//{
	//	input += "1";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbt2()
{
	clickBTNum("2");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "2";
	//}
	//else
	//{
	//	input += "2";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbt3()
{
	clickBTNum("3");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "3";
	//}
	//else
	//{
	//	input += "3";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbt4()
{
	clickBTNum("4");

//	CString input;
//	CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
//	pEcDisplayText->GetWindowTextW(input);
//
//	if (restart)
//	{
//		input = "4";
//	}
//	else
//	{
//		input += "4";
//	}
//	restart = 0;
//
//	pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbt5()
{
	clickBTNum("5");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "5";
	//}
	//else
	//{
	//	input += "5";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbt6()
{
	clickBTNum("6");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "6";
	//}
	//else
	//{
	//	input += "6";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbt7()
{
	clickBTNum("7");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "7";
	//}
	//else
	//{
	//	input += "7";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbt8()
{
	clickBTNum("8");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "8";
	//}
	//else
	//{
	//	input += "8";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbt9()
{
	clickBTNum("9");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = "9";
	//}
	//else
	//{
	//	input += "9";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}


void CCalculatorASMDlg::OnBnClickedbtdot()
{
	clickBTNum(".");

	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//if (restart)
	//{
	//	input = ".";
	//}
	//else
	//{
	//	input += ".";
	//}
	//restart = 0;

	//pEcDisplayText->SetWindowTextW(input);
}

/*******************
运算符代号
+ 1
- 2
* 3
/ 4
mod 5
sin 6
cos 7
tan 8
********************/


void CCalculatorASMDlg::OnBnClickedbtplus()
{
	clickBTBinary(1);

	//double resDouble=0;
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//USES_CONVERSION;
	//char* pcInput = T2A(input);
	//
	//double num = readNumText(pcInput);
	//_asm {
	//	push ebx
	//	push ecx
	//	push esi

	//	mov ebx, offset numStack
	//	mov esi, numStackTop
	//	mov ecx, dword ptr num
	//	mov [ebx+esi*8], ecx
	//	mov ecx, dword ptr num + 4
	//	mov [ebx+esi*8] + 4, ecx
	//	inc numStackTop
	//	;mov ebx, esi
	//	;mov numStackTop, esi

	//	;mov dword ptr resDouble,0
	//	;mov dword ptr resDouble+4,0

	//	pop esi
	//	pop ecx
	//	pop ebx
	//}
	//// 	;.if opStackTop == 0
	//// 	cmp opStackTop,0
	//// 	jna ENDIFEMPTY
	//// 	;.else
	//// 	;计算
	//// 	invoke calculate

	//// ENDIFEMPTY:
	//if(opStackTop>0){
	//	resDouble=calculate();
	//}
	//_asm{
	//	push ebx
	//	push esi

	//	mov ebx,offset opStack
	//	mov esi,opStackTop
	//	mov [ebx+esi*4],1
	//	inc opStackTop
	//	mov restart,1

	//	pop esi
	//	;pop ecx
	//	pop ebx
	//}

	//// restart=1;
	//CString input2;
	//input2.Format(_T("%lf"), resDouble);

	//// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->SetWindowTextW(input2);
}


void CCalculatorASMDlg::OnBnClickedbtsubtract()
{
	clickBTBinary(2);

	//double resDouble = 0;
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//USES_CONVERSION;
	//char* pcInput = T2A(input);

	//double num = readNumText(pcInput);
	//_asm {
	//	push ebx
	//	push ecx
	//	push esi

	//	mov ebx, offset numStack
	//	mov esi, numStackTop
	//	mov ecx, dword ptr num
	//	mov[ebx + esi * 8], ecx
	//	mov ecx, dword ptr num + 4
	//	mov[ebx + esi * 8] + 4, ecx
	//	inc numStackTop
	//	; mov ebx, esi
	//	; mov numStackTop, esi

	//	; mov dword ptr resDouble, 0
	//	; mov dword ptr resDouble + 4, 0

	//	pop esi
	//	pop ecx
	//	pop ebx
	//}
	//// 	;.if opStackTop == 0
	//// 	cmp opStackTop,0
	//// 	jna ENDIFEMPTY
	//// 	;.else
	//// 	;计算
	//// 	invoke calculate

	//// ENDIFEMPTY:
	//if (opStackTop > 0) {
	//	resDouble = calculate();
	//}
	//_asm {
	//	push ebx
	//	push esi

	//	mov ebx, offset opStack
	//	mov esi, opStackTop
	//	mov[ebx + esi * 4], 2
	//	inc opStackTop
	//	mov restart, 1

	//	pop esi
	//	; pop ecx
	//	pop ebx
	//}

	//// restart=1;
	//CString input2;
	//input2.Format(_T("%lf"), resDouble);

	//// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->SetWindowTextW(input2);
}


void CCalculatorASMDlg::OnBnClickedbtmultiply()
{
	clickBTBinary(3);

	//double resDouble = 0;
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//USES_CONVERSION;
	//char* pcInput = T2A(input);

	//double num = readNumText(pcInput);
	//_asm {
	//	push ebx
	//	push ecx
	//	push esi

	//	mov ebx, offset numStack
	//	mov esi, numStackTop
	//	mov ecx, dword ptr num
	//	mov[ebx + esi * 8], ecx
	//	mov ecx, dword ptr num + 4
	//	mov[ebx + esi * 8] + 4, ecx
	//	inc numStackTop
	//	; mov ebx, esi
	//	; mov numStackTop, esi

	//	; mov dword ptr resDouble, 0
	//	; mov dword ptr resDouble + 4, 0

	//	pop esi
	//	pop ecx
	//	pop ebx
	//}
	//// 	;.if opStackTop == 0
	//// 	cmp opStackTop,0
	//// 	jna ENDIFEMPTY
	//// 	;.else
	//// 	;计算
	//// 	invoke calculate

	//// ENDIFEMPTY:
	//if (opStackTop > 0) {
	//	resDouble = calculate();
	//}
	//_asm {
	//	push ebx
	//	push esi

	//	mov ebx, offset opStack
	//	mov esi, opStackTop
	//	mov[ebx + esi * 4], 3
	//	inc opStackTop
	//	mov restart, 1

	//	pop esi
	//	; pop ecx
	//	pop ebx
	//}

	//// restart=1;
	//CString input2;
	//input2.Format(_T("%lf"), resDouble);

	//// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->SetWindowTextW(input2);
}


void CCalculatorASMDlg::OnBnClickedbtdivide()
{
	clickBTBinary(4);

	//double resDouble = 0;
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//USES_CONVERSION;
	//char* pcInput = T2A(input);

	//double num = readNumText(pcInput);
	//_asm {
	//	push ebx
	//	push ecx
	//	push esi

	//	mov ebx, offset numStack
	//	mov esi, numStackTop
	//	mov ecx, dword ptr num
	//	mov[ebx + esi * 8], ecx
	//	mov ecx, dword ptr num + 4
	//	mov[ebx + esi * 8] + 4, ecx
	//	inc numStackTop
	//	; mov ebx, esi
	//	; mov numStackTop, esi

	//	; mov dword ptr resDouble, 0
	//	; mov dword ptr resDouble + 4, 0

	//	pop esi
	//	pop ecx
	//	pop ebx
	//}
	//// 	;.if opStackTop == 0
	//// 	cmp opStackTop,0
	//// 	jna ENDIFEMPTY
	//// 	;.else
	//// 	;计算
	//// 	invoke calculate

	//// ENDIFEMPTY:
	//if (opStackTop > 0) {
	//	resDouble = calculate();
	//}
	//_asm {
	//	push ebx
	//	push esi
	//	mov ebx, offset opStack
	//	mov esi, opStackTop
	//	mov[ebx + esi * 4], 4
	//	inc opStackTop
	//	mov restart, 1

	//	pop esi
	//	; pop ecx
	//	pop ebx
	//}

	//// restart=1;
	//CString input2;
	//input2.Format(_T("%lf"), resDouble);

	//// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->SetWindowTextW(input2);
}


void CCalculatorASMDlg::OnBnClickedbtmod()
{
	clickBTBinary(5);

	//double resDouble = 0;
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//USES_CONVERSION;
	//char* pcInput = T2A(input);

	//double num = readNumText(pcInput);
	//_asm {
	//	push ebx
	//	push ecx
	//	push esi

	//	mov ebx, offset numStack
	//	mov esi, numStackTop
	//	mov ecx, dword ptr num
	//	mov[ebx + esi * 8], ecx
	//	mov ecx, dword ptr num + 4
	//	mov[ebx + esi * 8] + 4, ecx
	//	inc numStackTop
	//	; mov ebx, esi
	//	; mov numStackTop, esi

	//	; mov dword ptr resDouble, 0
	//	; mov dword ptr resDouble + 4, 0

	//	pop esi
	//	pop ecx
	//	pop ebx
	//}
	//// 	;.if opStackTop == 0
	//// 	cmp opStackTop,0
	//// 	jna ENDIFEMPTY
	//// 	;.else
	//// 	;计算
	//// 	invoke calculate

	//// ENDIFEMPTY:
	//if (opStackTop > 0) {
	//	resDouble = calculate();
	//}
	//_asm {
	//	push ebx
	//	push esi
	//	mov ebx, offset opStack
	//	mov esi, opStackTop
	//	mov[ebx + esi * 4], 5
	//	inc opStackTop
	//	mov restart, 1

	//	pop esi
	//	; pop ecx
	//	pop ebx
	//}

	//// restart=1;
	//CString input2;
	//input2.Format(_T("%lf"), resDouble);

	//// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->SetWindowTextW(input2);
}


void CCalculatorASMDlg::OnBnClickedbtsin()
{
	clickBTUnary(6);

	//double resDouble = 0;
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//USES_CONVERSION;
	//char* pcInput = T2A(input);

	//double num = readNumText(pcInput);
	//_asm {
	//	push ebx
	//	push ecx
	//	push esi

	//	mov ebx, offset numStack
	//	mov esi, numStackTop
	//	mov ecx, dword ptr num
	//	mov[ebx + esi * 8], ecx
	//	mov ecx, dword ptr num + 4
	//	mov[ebx + esi * 8] + 4, ecx
	//	inc numStackTop
	//	; mov ebx, esi
	//	; mov numStackTop, esi

	//	; mov dword ptr resDouble, 0
	//	; mov dword ptr resDouble + 4, 0
	//	pop esi
	//	pop ecx
	//	pop ebx
	//}
	//// 	;.if opStackTop == 0
	//// 	cmp opStackTop,0
	//// 	jna ENDIFEMPTY
	//// 	;.else
	//// 	;计算
	//// 	invoke calculate

	//// ENDIFEMPTY:
	//if (opStackTop > 0) {
	//	resDouble = calculate();
	//}
	//_asm {
	//	push ebx
	//	push esi

	//	mov ebx, offset opStack
	//	mov esi, opStackTop
	//	mov[ebx + esi * 4], 6
	//	inc opStackTop
	//	mov restart, 1

	//	pop esi
	//	; pop ecx
	//	pop ebx
	//}
	//resDouble = calculate();

	//// restart=1;
	//CString input2;
	//input2.Format(_T("%lf"), resDouble);

	//// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->SetWindowTextW(input2);
}


void CCalculatorASMDlg::OnBnClickedbtcos()
{
	clickBTUnary(7);

	//double resDouble = 0;
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//USES_CONVERSION;
	//char* pcInput = T2A(input);

	//double num = readNumText(pcInput);
	//_asm {
	//	push ebx
	//	push ecx
	//	push esi

	//	mov ebx, offset numStack
	//	mov esi, numStackTop
	//	mov ecx, dword ptr num
	//	mov[ebx + esi * 8], ecx
	//	mov ecx, dword ptr num + 4
	//	mov[ebx + esi * 8] + 4, ecx
	//	inc numStackTop
	//	; mov ebx, esi
	//	; mov numStackTop, esi

	//	; mov dword ptr resDouble, 0
	//	; mov dword ptr resDouble + 4, 0
	//	pop esi
	//	pop ecx
	//	pop ebx
	//}
	//// 	;.if opStackTop == 0
	//// 	cmp opStackTop,0
	//// 	jna ENDIFEMPTY
	//// 	;.else
	//// 	;计算
	//// 	invoke calculate

	//// ENDIFEMPTY:
	//if (opStackTop > 0) {
	//	resDouble = calculate();
	//}
	//_asm {
	//	push ebx
	//	push esi

	//	mov ebx, offset opStack
	//	mov esi, opStackTop
	//	mov[ebx + esi * 4], 7
	//	inc opStackTop
	//	mov restart, 1

	//	pop esi
	//	; pop ecx
	//	pop ebx
	//}
	//resDouble = calculate();

	//// restart=1;
	//CString input2;
	//input2.Format(_T("%lf"), resDouble);

	//// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->SetWindowTextW(input2);
}


void CCalculatorASMDlg::OnBnClickedbttan()
{
	clickBTUnary(8);

	//double resDouble = 0;
	//CString input;
	//CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->GetWindowTextW(input);

	//USES_CONVERSION;
	//char* pcInput = T2A(input);

	//double num = readNumText(pcInput);
	//_asm {
	//	push ebx
	//	push ecx
	//	push esi

	//	mov ebx, offset numStack
	//	mov esi, numStackTop
	//	mov ecx, dword ptr num
	//	mov[ebx + esi * 8], ecx
	//	mov ecx, dword ptr num + 4
	//	mov[ebx + esi * 8] + 4, ecx
	//	inc numStackTop
	//	; mov ebx, esi
	//	; mov numStackTop, esi

	//	; mov dword ptr resDouble, 0
	//	; mov dword ptr resDouble + 4, 0

	//	pop esi
	//	pop ecx
	//	pop ebx
	//}
	//// 	;.if opStackTop == 0
	//// 	cmp opStackTop,0
	//// 	jna ENDIFEMPTY
	//// 	;.else
	//// 	;计算
	//// 	invoke calculate

	//// ENDIFEMPTY:
	//if (opStackTop > 0) {
	//	resDouble = calculate();
	//}
	//_asm {
	//	push ebx
	//	push esi

	//	mov ebx, offset opStack
	//	mov esi, opStackTop
	//	mov[ebx + esi * 4], 8
	//	inc opStackTop
	//	mov restart, 1

	//	pop esi
	//	; pop ecx
	//	pop ebx
	//}
	//resDouble = calculate();

	//// restart=1;
	//CString input2;
	//input2.Format(_T("%lf"), resDouble);

	//// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	//pEcDisplayText->SetWindowTextW(input2);
}


void CCalculatorASMDlg::OnBnClickedbtequal()
{
	double resDouble = 0;
	CString input;
	CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	pEcDisplayText->GetWindowTextW(input);

	USES_CONVERSION;
	char* pcInput = T2A(input);

	double num = readNumText(pcInput);
	_asm {
		push ebx
		push ecx
		push esi

		mov ebx, offset numStack
		mov esi, numStackTop
		mov ecx, dword ptr num
		mov[ebx + esi * 8], ecx
		mov ecx, dword ptr num + 4
		mov[ebx + esi * 8] + 4, ecx
		inc numStackTop
		; mov ebx, esi
		; mov numStackTop, esi

		; mov dword ptr resDouble, 0
		; mov dword ptr resDouble + 4, 0

		pop esi
		pop ecx
		pop ebx
	}
	if (opStackTop > 0) {
		resDouble = calculate();
		CString input2;
		input2.Format(_T("%lf"), resDouble);

		// CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
		pEcDisplayText->SetWindowTextW(input2);

	}
	_asm {
		mov restart,1
	}
}


void CCalculatorASMDlg::OnBnClickedbtclean()
{
	CString input;
	input = "0";
	CEdit* pEcDisplayText = (CEdit*)GetDlgItem(ecDisplayText);
	pEcDisplayText->SetWindowTextW(input);
	restart = 1;
}


void CCalculatorASMDlg::OnBnClickedbtyeah()
{
	printf("%c", 7);
}
