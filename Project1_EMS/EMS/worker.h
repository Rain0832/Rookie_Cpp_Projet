/********************************************************************
*
* 文件名：worker.h
*
* 文件描述：全体职工类和函数声明
*
* 创建人： Rain, 2024 年 10 月 2 日
*
* 版本号：1.0
*
* 修改记录：
*
********************************************************************/

#pragma once
#include <iostream>
#include <string>

using namespace std;

//职工抽象类

class Worker {
    public:


        //显示个人信息
        virtual void showInfo()=0;
        //获取岗位名称
        virtual string getDeptName()=0;

        //编号
        int m_Id;
        //姓名
        string m_Name;
        //部门
        int m_DeptId;
};