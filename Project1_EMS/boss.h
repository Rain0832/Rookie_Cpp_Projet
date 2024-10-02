/********************************************************************
*
* 文件名：boss.h
*
* 文件描述：总裁类和相关函数声明
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

//总裁
class Boss : public Worker
{
public:

    Boss(int id, string name, int dId);

    //显示个人信息
    virtual void showInfo();

    //获取岗位名称
    virtual string getDeptName();

};
