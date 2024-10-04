/********************************************************************
*
* 文件名：workerManager.h
*
* 文件描述：函数声明文件
*
* 创建人： Rain, 2024 年 10 月 2 日
*
* 版本号：1.0
*
* 修改记录：
*
********************************************************************/

#pragma once                //防止头文件重复包含
#include <iostream>         //包含输入输出流头文件
#include <fstream>          //包含文件输入输出流头文件
#include "worker.h"         //包含Worker类头文件
#include "employee.h"       //包含Employee类头文件
#include "manager.h"        //包含Manager类头文件
#include "boss.h"           //包含Boss类头文件

#define FILENAME "empFile.txt"   //定义文件名


using namespace std;        //使用标准命名空间

class WorkerManager
{
public:

    //构造函数
    WorkerManager();

    //显示菜单
    void Show_Menu();

    //退出系统
    void ExitSystem();

    //记录职工人数
    int m_EmpNum;

    //职工数组指针
    Worker ** m_EmpArray;

    //添加职工
    void Add_Emp();

    //保存文件
    void save();

    //判断文件是否为空 标志
    bool m_FileIsEmpty;

    //统计文件中人数
    int get_EmpNum();

    //初始化职工
    void init_Emp();

    //显示职工
    void Show_Emp();

    //删除职工
    void Del_Emp();

    //判断职工是否存在 如果存在，返回职工所在数组中的位置，不存在返回-1
    int IsExist(int id);

    //修改职工信息
    void Mod_Emp();

    //查找职工
    void Find_Emp();


    //按照编号排序职工
    void Sort_Emp();


    //清空文件
    void Clear_File();

    //析构函数
    ~WorkerManager();

};