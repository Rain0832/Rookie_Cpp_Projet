/*********************************************************************

文件名：Identify.h
文件描述：所有身份的父类基类，提供了一些公用的属性和函数（纯虚函数）便于创造子类
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#pragma once

#include <iostream>

using namespace std;

//身份抽象基类
class Identity
{
public:
		//操作菜单    纯虚函数
		virtual void openMenu() = 0;


		//用户名
		string m_Name;
		//密码
		string m_Pwd;
};

