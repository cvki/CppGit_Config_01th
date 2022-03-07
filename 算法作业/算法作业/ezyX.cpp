#include<iostream>
#include<easyx.h>
#pragma comment(lib,"winmm.lib")

using namespace std;

#if 0
int x1() {
	//1.创建窗口
	initgraph(640, 640);

	//2.坐标。窗口左上角为坐标原点，往右是x，往下是y

	//3.颜色。常见颜色用宏定义，如WHITE BLACK BLUE RED, 其他颜色用RGB合成，如：RGB(0,255,255)

	//刷新：
	setbkcolor(RGB(233, 211, 222));	//设置背景颜色
	cleardevice();	//清除设备，使用指定颜色刷新

	//音乐:(音乐处理是windows api的，只是easyX封装了部分win API)
	//1. 包含文件： 头文件(使用include包含)：mmsystem.h    库文件(包含方式：#pragma comment(lib,"winmm.lib"))：winmm.lib，库文件的包含在C语言预处理内容中
	//函数接口：mciSendString();  //media control interface, send, string,媒体控制接口中，用来发送字符串的一个函数
	//音乐文件放在该cpp所在的文件目录中(该cpp和音乐文件应该同级，否则加入绝对路径)

	/***该函数会报错(老师直播用的这个函数)，使用下面的函数正确
	mciSendString("open xxx.mp3", 0, 0, 0); //xxx.mp3为音乐文件名
	mciSendString("play xxx.mp3", 0, 0, 0);
	mciSendString("pause xxx.mp3", 0, 0, 0);
	mciSendString("close xxx.mp3", 0, 0, 0);
	***/
	
	//注意音乐文件的要求：1.网易云下载的不行(网易云压缩的格式和一般的不一样，windows这个API读取不了)，2.文件名不能有空格  3.文件全名  4.该函数只能读取mp3格式音频

	mciSendStringA("open xxx.mp3", 0, 0, 0); //xxx.mp3为音乐文件名，下面包含文件的打开，播放，暂停，关闭。
	mciSendStringA("play xxx.mp3", 0, 0, 0);
	mciSendStringA("pause xxx.mp3", 0, 0, 0);
	mciSendStringA("close xxx.mp3", 0, 0, 0);

	//图片
	/*1.普通贴图
	* 2.批量绘图
	* 3.透明绘图
	***/
	// 1. 普通贴图
	IMAGE pic1; //定义图片变量
	//loadimage(&pic1, "im.jpg",640,640); //会报错，后面表示用多大的宽和高存储这个图片，为了图片显示效果，最好保持原来图片的等比例。
	loadimage(&pic1, L"im.jpg", 640, 640);
	putimage(0, 0, &pic1);//表示原点在（0，0）处来贴上pic1图片

	//2.批量绘图
	BeginBatchDraw();//开始批量绘图
	
	putimage(0, 0, &pic1);//原则上所有的绘图放在中间

	EndBatchDraw();//结束批量绘图

	//3. 透明绘图
	//a 准备2张图片，黑底白面和白底彩面
	IMAGE picx, picy;
	loadimage(&picx, "11.jpg", 50, 50);
	loadimage(&picy, "22.jpg", 50, 50);
	//b 两张图贴在同一位置
	putimage(320, 240, &picx);
	putimage(320, 240, &picy);
	//c 分别使用SRCPAINT,SRCAND 绘图方式
	putimage(320, 240, &picx, SRCPAINT);
	putimage(320, 240, &picy, SRCAND);


	system("pause");
	return 0;
}
#endif
int x2() {
	int a[3] = { 4, 5, 6 };
	cout << 0[a] << 2[a]<<endl; 
	cout << a[0] << a[2]<<endl;
	return 0;
}

int main() {


	return 0;
}