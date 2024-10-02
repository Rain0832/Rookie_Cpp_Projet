/********************************************************************
*
* 文件名：employee.cpp
*
* 文件描述：employee类实现文件，普通职工信息包括编号、姓名、部门编号（属性）、
*           显示个人信息、获取岗位名称（虚函数）
*
* 创建人： Rain, 2024 年 10 月 2 日
*
* 版本号：1.0
*
* 修改记录：
*
********************************************************************/

#include "employee.h"

Employee::Employee(int id,string name,int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

//显示个人信息
void Employee::showInfo()
{
    cout<<"职工编号："<<this->m_Id
        <<"\t职工姓名："<<this->m_Name
        <<"\t岗位："<<this->getDeptName()
        <<"\t岗位职责：完成经理交办的工作"<<endl;
}

//获取岗位名称
string Employee::getDeptName()
{
    return string("员工");
}