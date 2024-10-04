/*********************************************************************

文件名：student.h
文件描述：学生身份类和函数声明
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#pragma once		//防止头文件重复包含

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "globalFile.h"
#include "ComputerRoom.h"
#include "Identity.h"
#include "orderFile.h"

using namespace std;

//学生类
class Student : public Identity {
public:

	//默认构造
	Student();

	//有参构造
	Student(int id,string name, string pwd);

	//菜单界面
	void openMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

	//学生学号
	int m_Id;

	//机房容器
	vector<ComputerRoom> vCom;

};