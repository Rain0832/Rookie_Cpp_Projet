/*********************************************************************

文件名：student.cpp
文件描述：学生身份类和函数实现
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/
#include "student.h"

//默认构造
Student::Student()
{

}

//有参构造
Student::Student(int id, string name, string pwd)
{
	//初始化属性
	this->m_Id=id;
	this->m_Name=name;
	this->m_Pwd=pwd;

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		//将读取到的信息放入到容器中
		vCom.push_back(com);
	}

	ifs.close();
}

//菜单界面
void Student::openMenu()
{
	cout << "欢迎学生：" << this->m_Name << " 登录机房管理系统!" << endl;
	cout << endl;
	cout << "1. 申请预约" << endl;
	cout << "2. 查看我的预约" << endl;
	cout << "3. 查看所有预约" << endl;
	cout << "4. 取消预约" << endl;
	cout << "0. 注销登录" << endl;
	cout << endl;
	cout << "请输入选项的编号：" << endl;
}

//申请预约
void Student::applyOrder()
{
	int date = 0;//日期
	int interval = 0;//时间段
	int room = 0;//机房编号

	cout << "机房开放时间为周一至周五！" << endl;//周末不上班（
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "日期输入错误，请重新输入" << endl;
	}

	cout << "请输入申请预约的时间段：" << endl;//晚上不上班（
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "时间段输入错误，请重新输入" << endl;
	}

	cout << "请选择机房：" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << " 号机房容量为：" << vCom[i].m_MaxNum << " 人" << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= vCom.size())
		{
			break;
		}
		cout << "机房编号输入错误，请重新输入" << endl;
	}

	cout << "预约成功！审核中" << endl;
	
	//写入预约信息到文件
	ofstream ofs;//创建输出文件流
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" <<  date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:"<< this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");

}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout <<"无预约记录！"<<endl;
		system("pause");
		system("cls");
		return;
	}

	for(int i=0;i<of.m_Size;i++)
	{
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))//要转换类型（string->int）
		//string 利用c_str()函数 转换为const char*类型 再利用atoi()函数 转换为int类型
		{

			//判断日期
			string date = "预约日期：周";
			if (of.m_orderData[i]["date"] == "1")
			{
				date += "一";
			}
			else if (of.m_orderData[i]["date"] == "2")
			{
				date += "二";
			}
			else if (of.m_orderData[i]["date"] == "3")
			{
				date += "三";
			}
			else if (of.m_orderData[i]["date"] == "4")
			{
				date += "四";
			}
			else if (of.m_orderData[i]["date"] == "5")
			{
				date += "五";
			}
			cout << date << endl;


			cout << "时间段：" << (of.m_orderData[i]["interval"]=="1"?"上午":"下午")<<endl;
			cout << "机房编号：" << of.m_orderData[i]["roomId"]<<" 号机房" << endl;


			//判断预约状态 1 -审核中 2 -通过 -1 -未通过 0 -取消
			string status = "状态：";
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
				status += "预约取消";
			}
			cout << status << endl;
			cout << endl;
		}
	}

	//按任意键
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
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

		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") ;
		cout << " 学号："<< of.m_orderData[i]["stuId"] ;
		cout << " 姓名：" << of.m_orderData[i]["stuName"] ;
		cout << " 机房编号：" << of.m_orderData[i]["roomId"] << " 号机房";

		//判断预约状态 1 -审核中 2 -通过 -1 -未通过 0 -取消
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
			status += "预约取消";
		}
		cout << status << endl;
	}
	//按任意键
	system("pause");
	system("cls");
}

//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout<<"审核中或预约成功的记录可以取消，请输入取消的记录"<<endl;
	vector<int>v;//存放在最大容器中的下标编号

	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//判断是否是自己预约的
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			//判断预约状态 1 -审核中 2 -通过 -1 -未通过 0 -取消
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
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

				cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") ;
				cout << " 机房编号：" << of.m_orderData[i]["roomId"] << " 号机房";

				string status = " 状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "预约审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
			}

	}
	cout << "请输入要取消的记录编号：" << endl;
	int select = 0;

	while (true)
	{
		cin >> select;

		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				cout << "取消操作已取消！" << endl;
				break;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";//修改状态为取消
				of.updateOrder();

				cout << "预约取消成功！" << endl;
				break;
			}
		}
		cout<<"输入错误，请重新输入！"<<endl;
	}
	system("pause");
	system("cls");
}