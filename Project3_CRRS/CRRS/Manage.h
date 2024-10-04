/*********************************************************************

文件名：Manage.h
文件描述：机房管理系统的管理类声明
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#pragma once
#include<iostream>

using namespace std;

class Manage
{
public:

	//构造函数
	Manage();

	//显示菜单
	void showMainMenu();

	//未定义的输入
	void undefindInput();

	//退出系统
	void ExitSystem();

	//析构函数
	~Manage();
};