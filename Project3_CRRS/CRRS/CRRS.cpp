/*********************************************************************

文件名：CRRS.cpp
文件描述：机房管理系统主程序，提供主菜单和子菜单显示功能
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "globalFile.h"
#include "Identity.h"
#include "Manage.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"

using namespace std;

//进入学生子菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		//调用学生子菜单
		student->openMenu();

		Student * stu = (Student*)student;

		int select = 0;
		//接受用户选项
		cin >> select;

		switch (select)
		{
		case 1://申请预约
			stu->applyOrder();
			break;
		case 2://查看自身预约
			stu->showMyOrder();
			break;
		case 3://查看所有人预约
			stu->showAllOrder();
			break;
		case 4://取消预约
			stu->cancelOrder();
			break;
		case 0://注销登录
			{
				delete student;
				cout << "注销登录成功" << endl;
				system("pause");
				system("cls");
				return;
			}
		default:
			//未定义输入
			cout << "输入错误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//进入教师子菜单
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//调用教师子菜单
		teacher->openMenu();

		Teacher * tea = (Teacher*)teacher;

		int select = 0;
		//接受用户选项
		cin >> select;

		switch (select)
		{
		case 1://查看所有预约
			tea->showAllOrder();
			break;
		case 2://审核预约
			tea->validOrder();
			break;
		case 0://注销登录
			delete teacher;
			cout << "注销登录成功" << endl;
			system("pause");
			system("cls");
			return;
		default:
			//未定义输入
			cout << "输入错误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//进入管理员子菜单
void adminMenu(Identity * &admin)
{
	while (true)
	{
		//调用管理员子菜单
		admin->openMenu();

		//将父类指针转为子类指针，调用子类里其他接口
		Admin * adm = (Admin*)admin;

		int select = 0;
		//接受用户选项
		cin >> select;

		switch (select)
		{
			case 1://添加账号
				//cout <<"添加账号"<<endl;					//适当中文提示，为开发做准备
				adm->addPerson();
				break;
			case 2://查看账号
				//cout << "查看账号" << endl;
				adm->showPerson();
				break;
			case 3://查看机房
				//cout << "查看机房" << endl;
				adm->showComputer();
				break;
			case 4://清空预约
				//cout << "清空预约" << endl;
				adm->cleanFile();
				break;
			case 0://注销登录
				delete admin;
				cout << "注销登录成功" << endl;
				system("pause");
				system("cls");
				return;
			default:
				//未定义输入
				cout << "输入错误，请重新输入" << endl;
				system("pause");
				system("cls");
		}

	}
}

using namespace std;

//登录功能 参数1 操作文件名 参数2 操作身份类型
void LoginIn(string fileName, int type)
{
	//父类指针，用于指向子类对象
	Identity * person=NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	//准备接受用户的信息
	int id = 0;
	string name;
	string pwd;


	//判断身份
	switch (type)
	{
	case 1:						//学生身份
		cout << "请输入您的学号：" << endl;
		cin >> id;
		break;
	case 2:						//教师身份
		cout << "请输入您的职工号：" << endl;
		cin >> id;
		break;
	default:
		break;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	switch (type)
	{
		case 1:						//学生登录验证
		{
			int fId;				//文件中获取的id号
			string fName;			//文件中获取的姓名
			string fPwd;			//文件中获取的密码
			while (ifs >> fId && ifs >> fName && ifs >> fPwd)
			{
				//与用户输入信息做对比
				if (fId == id && fName == name && fPwd == pwd)
				{
					cout << "学生验证成功" << endl;
					system("pause");
					system("cls");
					person = new Student(id,name,pwd);		//创建学生对象

					//进入学生身份子菜单
					studentMenu(person);

					return;
				}

			}
		}
			break;
		case 2:						//教师登录验证
		{
				int fId;				//文件中获取的id号
				string fName;			//文件中获取的姓名
				string fPwd;			//文件中获取的密码
				while (ifs >> fId && ifs >> fName && ifs >> fPwd)
				{
					//与用户输入信息做对比
					if (fId == id && fName == name && fPwd == pwd)
					{
						cout << "教师验证成功" << endl;
						system("pause");
						system("cls");
						person = new Teacher(id, name, pwd);		//创建教师对象

						//进入教师身份子菜单
						teacherMenu(person);

						return;
					}
				}
		}
			break;
		case 3:						//管理员登陆验证
		{
				string fName;			//文件中获取的姓名
				string fPwd;			//文件中获取的密码
				while (ifs >> fName && ifs >> fPwd)
				{
					//与用户输入信息做对比

					if (fName == name && fPwd == pwd)
					{
						cout << "管理员验证成功" << endl;
						system("pause");
						system("cls");

						person = new Admin(name, pwd);		//创建管理员对象

						//进入管理员身份子菜单
						adminMenu(person);

						return;
					}
				}
		}
			break;
		default:
			break;
	}

	cout <<"验证登录失败！"<<endl;
	system("pause");
	system("cls");

	return;
}

int main(void)
{
	//初始化管理系统对象
	Manage mg;

	int select = 0;
	while (true)
	{
		mg.showMainMenu();

		cin >> select;//接受用户选择

		switch (select)//根据用户选择进行相应的操作
		{
		case 1:						//学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:						//教师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:						//管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:						//退出系统
			mg.ExitSystem();
			break;
		default:
			mg.undefindInput();		//未定义输入
			break;
		}
	}

	system("pause");

	return 0;
}