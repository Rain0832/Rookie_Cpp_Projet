/*********************************************************************

文件名：admin.h
文件描述：管理员身份类和函数声明
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "student.h"
#include "teacher.h"
#include "Identity.h"
#include "globalFile.h"
#include "computerRoom.h"

using namespace std;

//管理员类设计
class Admin : public Identity {
public:

	//默认构造
	Admin();

	//有参构造
	Admin(string name, string pwd);

	//菜单界面
	virtual void openMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//初始化容器
	void initVector();

	//检测重复	参数1：学号/职工号id，参数2：检测类型
	bool checkRepeat(int id,int type);

	//学生容器
	vector<Student>vStu;

	//教师容器
	vector<Teacher>vTea;

	//机房信息容器
	vector<ComputerRoom>vCom;

};