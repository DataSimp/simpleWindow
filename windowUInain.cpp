/* C语言：UI窗口类程序，haixin - 561，于2020-03-28 14:20:48发布
 * https://blog.csdn.net/weixin_41049188/article/details/105151947
 * 示例代码：windowUImai.cpp, create date: 2022-07-19-Tue.
 * 项目标题：Windows C UI 窗口界面
*/

#include<Windows.h>
#include<strsafe.h>  //字符串安全函数头文件
#define TEXTCOUNT 128
#define TEXTHIGHT 20

/*********************************
消息回调函数声明，参数等同于 消息结构体(MSG)的前4个成员
	HWND        ：窗口句柄
	UINT        ：消息
	WPARAM      ：消息参数
	LPARAM      ：消息参数
**********************************/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*********************************************************************************************
程序主入口
	HINSTANCE hInstance         ：HINSTANCE为实例句柄，句柄无非是一个数值，
									程序用它来标识某些东西。在此该句柄唯一标识我们这个程序。
	HINSTANCE hPrevInstance     ：前一个实例句柄，在win32程序中这一概念已不再采用，
									因此WinMain的第二个参数通常是NULL。
	PSTR szCmdLine              ：PSTR是一个字符指针，用来运行程序的命令行，
									有些程序在启动时用它来把文件装入内存。
	int iCmdShow                ：用来指明程序最初如何显示：正常显示、最大化到全屏、最小化到任务栏。
************************************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyFirstWindow");  //定义窗口类的名称

	HWND hwnd;//窗口句柄
	MSG msg; //消息结构体
	WNDCLASS wndclass;//窗口类
	wndclass.style = CS_HREDRAW | CS_VREDRAW;  //指定窗口类型，可以使用按位或操作符组合起来
	wndclass.lpfnWndProc = WndProc;            //指定窗口过程(必须是回调函数)
	wndclass.cbClsExtra = 0;                   //预留的额外空间，一般为 0
	wndclass.cbWndExtra = 0;                   //预留的额外空间，一般为 0
	wndclass.hInstance = hInstance;            //应用程序的实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //为所有基于该窗口类的窗口设定一个图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);   //为所有基于该窗口类的窗口设定一个鼠标指针
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //指定窗口背景色
	wndclass.lpszMenuName = NULL;           //指定窗口菜单                     
	wndclass.lpszClassName = szAppName;     //指定窗口类名
	if (!RegisterClass(&wndclass))          //注册当前窗口类
	{
		MessageBox(NULL, TEXT("程序需要在WindowsNT框架下才能运行！"), szAppName, MB_ICONERROR);
		return 0;
	}
	//创建窗口句柄
	hwnd = CreateWindow(szAppName, //窗口类名称
		TEXT("C UI windows"),      //窗口标题
		WS_OVERLAPPEDWINDOW,       //窗口的风格样式
		CW_USEDEFAULT,             //初始化 X 坐标
		CW_USEDEFAULT,             //初始化 Y 坐标
		CW_USEDEFAULT,             //初始化 X 方向尺寸
		CW_USEDEFAULT,             //初始化 Y 方向尺寸
		NULL,                      //父窗口句柄
		NULL,                      //窗口菜单句柄
		hInstance,                 //程序实例句柄
		NULL);                     //创建参数
	//显示和更新已创建的窗口
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);//相当于刷新
	//消息循环
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);  //消息翻译：函数将虚拟键消息转换成字符消息
		DispatchMessage(&msg);   //消息分发：把消息传给操作系统，操作系统调用当前窗口实例句柄的回调函数
	}
	return msg.wParam;
}

//消息回调函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC  hdc;        //设备环境句柄 使用GDI函数绘制图形
	PAINTSTRUCT ps;  //绘制窗口图形参数
	RECT rect;
	TCHAR txt[TEXTCOUNT];
	size_t txtlen;
	errno_t err;     //捕获错误 NULL | 0
	static int cxChar, cyChar; //存储当前程序字体大小和行距
	TEXTMETRIC tmt;

	switch (message)
	{
	case WM_CREATE://当程序被创建时
		hdc = GetDC(hwnd); //公用 获取设备环境句柄
		GetTextMetrics(hdc, &tmt);
		cxChar = tmt.tmAveCharWidth;//字体宽度
		cyChar = tmt.tmExternalLeading + tmt.tmHeight;//字体高度
		ReleaseDC(hwnd, hdc); //释放环境句柄(GetDC -> ReleaseDC 必须成对出现)
		return 0;
	case WM_PAINT://要求一个窗口重绘自己
		hdc = BeginPaint(hwnd, &ps);//获取绘制设备环境句柄 函数为指定窗口进行绘画作准备，并用将和绘画有关的信息填充到一个PAINTSTRUCT结构中。
		GetClientRect(hwnd, &rect);//获取客户区(绘制区)获取窗口客户区的坐标，客户区坐标指定客户区的左上角和右下角。
		for (size_t i = 0; i < 10; i++)
		{
			/*wsprintf(txt, TEXT("NO.%d : 我是第【%d】行文字。"), i + 1, i + 1);
			TextOut(hdc, 0, i*TEXTHIGHT, txt, lstrlen(txt));*/
			//使用字符串处理安全函数
			StringCchPrintf(txt, TEXTCOUNT, TEXT("NO.%d : 我是第【%d】行文字。"), i + 1, i + 1);//格式化字符串
			err = StringCchLength(txt, TEXTCOUNT, &txtlen);//获取字符串长度
			TextOut(hdc, cxChar, i * cyChar, txt, txtlen);
		}
		cxChar = GetSystemMetrics(SM_CXSCREEN); //获取分辨率宽
		cyChar = GetSystemMetrics(SM_CYSCREEN);//获取分辨率的高
		DrawText(hdc, TEXT("Hello world -- programming language c! \n Chino at Data Simp Comm, China."), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);//绘制文本
		StringCchPrintf(txt, TEXTCOUNT, TEXT("当前环境的分辨率：%d * %d px."), cxChar, cyChar);//格式化字符串
		err = StringCchLength(txt, TEXTCOUNT, &txtlen);//获取字符串长度
		TextOut(hdc, 500, 200, txt, txtlen);

		EndPaint(hwnd, &ps);//函数标记指定窗口的绘画过程结束 这个函数在每次调用 BeginPaint 函数之后被调用(释放设备描述表)，但仅仅在绘画完成以后。(函数要匹配成对使用 BeginPaint-> EndPaint)
		return 0;
	case WM_CLOSE://点你关闭按钮时
		if (MessageBox(hwnd, TEXT("你要关闭吗？"), TEXT("提示："), MB_YESNO) == IDYES)
		{
			PostQuitMessage(0);
		}
		else
		{
			return 0;
		}
	case WM_LBUTTONUP:
		MessageBox(hwnd, TEXT("你双击了鼠标左键！"), TEXT("提示："), MB_DEFMASK);
		return 0;
		//case WM_DESTROY://一个窗口被销毁
		//	PostQuitMessage(0);
		//	return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);//默认消息处理方式
}

/* 窗口的创建流程：
【1】初始化窗口类结构：WNDCLASS
【2】注册窗口类：RegisterClass(&wndclass)
【3】创建窗口实例：CreateWindow
【4】显示窗口：ShowWindow
【5】更新窗口：UpdateWindow
【6】消息循环： CALLBACK WndProc
 关于消息机制：
【1】消息队列是先进先出(FIFO)形式。
【2】WM_PAINT, WM_TIMER和WM_QUIT这三个消息属于特例。操作系统会把它们时刻放在消息队列的最后面。
【3】队列化消息 和 非队列化消息(由windows 直接发送给窗口)
项目配配置：VS2019, console application. build and debug successfully on 2022-07-19-Tue.
 */