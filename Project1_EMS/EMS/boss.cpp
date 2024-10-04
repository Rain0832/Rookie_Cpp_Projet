/********************************************************************
*
* 文件名：boss.cpp
*
* 文件描述：总裁类和相关函数
*
* 创建人： Rain, 2024 年 10 月 2 日
*
* 版本号：1.0
*
* 修改记录：
*
********************************************************************/

#include "boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

//显示个人信息
void Boss::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：管理公司所有事物" << endl;
}

//获取岗位名称
string Boss::getDeptName()
{
	return string("总裁");
}