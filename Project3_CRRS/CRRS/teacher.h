/*********************************************************************

文件名：teacher.h
文件描述：教师类和函数声明
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#pragma once
#include <iostream>
#include <vector>
#include "orderFile.h"
#include "Identity.h"

using namespace std;

class Teacher : public Identity
{
public:

	//默认构造
	Teacher();

	//有参构造
	Teacher(int empId, string name, string pwd);

	//菜单界面
	virtual void openMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//职工号
	int m_EmpId;
};
