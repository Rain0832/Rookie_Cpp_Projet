/*********************************************************************

文件名：teacher.cpp
文件描述：教师身份类和相关函数实现
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#include "teacher.h"
#include "Identity.h"

//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empId, string name, string pwd)
{
	//初始化属性
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//菜单界面
void Teacher::openMenu()
{
	cout << "欢迎教师：" << this->m_Name << " 登录机房管理系统!" << endl;
	cout << endl;
	cout << "1. 查看所有预约" << endl;
	cout << "2. 审核预约" << endl;
	cout << "0. 注销登录" << endl;
	cout << endl;
	cout << "请输入选项的编号：" << endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "当前无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：周";
		if (of.m_orderData[i]["date"] == "1")
		{
			cout << "一";
		}
		else if (of.m_orderData[i]["date"] == "2")
		{
			cout << "二";
		}
		else if (of.m_orderData[i]["date"] == "3")
		{
			cout << "三";
		}
		else if (of.m_orderData[i]["date"] == "4")
		{
			cout << "四";
		}
		else if (of.m_orderData[i]["date"] == "5")
		{
			cout << "五";
		}

		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房编号：" << of.m_orderData[i]["roomId"] << " 号机房";

		//预约状态 判断预约状态 1 -审核中 2 -通过 -1 -未通过 0 -取消
		string status = " 状态：";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "预约审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约审核通过";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约审核未通过";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			status += "预约被取消";
		}
		cout << status << endl;
	}
	//按任意键
	system("pause");
	system("cls");

}

//审核预约
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "当前无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	//待审核状态的预约的保存容器
	vector<int>v;
	int index = 1;

	//显示操作
	cout << "待审核的预约记录如下：" << endl;

	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index << "、";
			index++;
			cout << "预约日期：周";
			if (of.m_orderData[i]["date"] == "1")
			{
				cout << "一";
			}
			else if (of.m_orderData[i]["date"] == "2")
			{
				cout << "二";
			}
			else if (of.m_orderData[i]["date"] == "3")
			{
				cout << "三";
			}
			else if (of.m_orderData[i]["date"] == "4")
			{
				cout << "四";
			}
			else if (of.m_orderData[i]["date"] == "5")
			{
				cout << "五";
			}

			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 学号：" << of.m_orderData[i]["stuId"];
			cout << " 姓名：" << of.m_orderData[i]["stuName"];
			cout << " 机房编号：" << of.m_orderData[i]["roomId"] << " 号机房" ;

			string status = " 状态：";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "预约审核中";
			}
			cout << status << endl;
		}
	}

	//审核操作
	cout << "请输入要审核的预约编号（输入 0 代表返回）：" << endl;
	int select = 0;
	int ret = 0;

	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果" << endl;
				cout << "1、审核通过" << endl;
				cout << "2、审核不通过" << endl;

				cin >> ret;
				if (ret == 1)
				{
					//通过
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					//不通过
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "审核完毕！" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}