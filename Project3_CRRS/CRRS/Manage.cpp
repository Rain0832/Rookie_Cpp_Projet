/*********************************************************************

文件名：Manage.cpp
文件描述：管理系统的菜单和基本常用函数实现
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#include "Manage.h"

//构造函数
Manage::Manage()
{

}

//显示菜单
void Manage::showMainMenu()
{
	cout << "欢迎来到机房预约系统" << endl;
	cout << "---------------------" << endl;
	cout << "请选择您的身份" << endl;
	cout << endl;
	cout << "1.学 生 身份" << endl;
	cout << "2.教 师 身份" << endl;
	cout << "3.管理员身份" << endl;
	cout << "0.退出本系统" << endl;
	cout << endl;
	cout << "请输入您的选择" << endl;
}

//未定义的输入
void Manage::undefindInput()
{
	cout << "输入错误，请重新输入" << endl;
	system("pause");
	system("cls");
}

//退出系统
void Manage::ExitSystem()
{
	cout<<"欢迎下次使用"<<endl;
	system("pause");
	exit(0);
}

//析构函数
Manage::~Manage()
{

}