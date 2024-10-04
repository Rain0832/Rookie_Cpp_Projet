/********************************************************************
*
* 文件名：employee.h
*
* 文件描述：普通职工类文件和函数声明
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
#include "worker.h"

using namespace std;

class Employee :public Worker
{
public:

    //构造函数
    Employee(int id,string name,int dId);
    //显示个人信息
    virtual void showInfo();

    //获取岗位名称
    virtual string getDeptName();
    
};