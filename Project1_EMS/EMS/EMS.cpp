/********************************************************************
*
* 文件名：EMS.cpp
*
* 文件描述：EMS职工管理系统主程序，展示菜单并接收用户选择功能，
*           调用相应的成员函数和程序接口。
*
* 创建人： Rain, 2024 年 10 月 2 日
*
* 版本号：1.0
*
* 修改记录：
*
********************************************************************/

#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;


int main()
{

     //实例化管理者对象
     WorkerManager wm;

     int choice = 0;//用户选择的选项

     while(true)
     {
         //调用展示菜单成员函数
         wm.Show_Menu();

         cout << "请输入您的选择：" << endl;
         cin >> choice; //接受用户选项

         switch (choice)
         {
         case 0:                                 //退出系统
             wm.ExitSystem();
             break;
         case 1:                                 //增加职工
             wm.Add_Emp();
             break;
         case 2:                                 //显示职工
             wm.Show_Emp();
             break;
         case 3:                                 //删除职工
             wm.Del_Emp();
             break;
         case 4:                                 //修改职工
             wm.Mod_Emp();
             break;
         case 5:                                 //查找职工
             wm.Find_Emp();
             break;
         case 6:                                 //排序职工
             wm.Sort_Emp();
             break;
         case 7:                                 //清空文档
             wm.Clear_File();
             break;
         default:
             cout << "输入错误，请重新输入！" << endl;
             system("cls");//清屏
             break;
         }
         system("cls");//清屏
     }




    return 0;
}