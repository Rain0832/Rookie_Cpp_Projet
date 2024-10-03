/********************************************************************
*
* 文件名：SCMS.cpp
*
* 文件描述：演讲比赛管理系统的主函数，展示菜单和选择选项，调用接口
*
* 创建人： Rain, 2024 年 10 月 3 日
*
* 版本号：1.0
*
* 修改记录：
*
********************************************************************/

#include <iostream>
#include <string>
#include "speechManager.h"

using namespace std;

int main()
{
	//随机数种子
	srand(unsigned int(time(NULL)));

	//创建管理类的对象
	SpeechManager sm;




	int choice = 0;					//用于存储用户输入

	while (true)
	{
		sm.show_Menu();

		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:										//开始比赛
			sm.startSpeech();
			break;
		case 2:										//查看往届记录
			sm.showRecord();
			break;
		case 3:										//清空比赛记录
			sm.clearRecord();
			break;
		case 0:										//退出系统
			sm.exitSystem();
			break;
		default:
			cout << "输入错误，请重新输入！" << endl;
			system("pause");
			system("cls");							//清屏
			break;
		}
	}

	system("pause");
	return 0;
}