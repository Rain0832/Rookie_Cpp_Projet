/*********************************************************************

文件名：admin.cpp
文件描述：管理员类和相关函数实现
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#include "admin.h"

//默认构造
Admin::Admin()
{

}

//有参构造
Admin::Admin(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器 获取所有文件中学生、教师信息
	this->initVector();

	//初始化机房信息容器
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();
	//测试代码
	//cout<<"机房的数量为："<<vCom.size()<<endl;
}

//菜单界面
void Admin::openMenu()
{
	cout << "欢迎管理员："<< this->m_Name << " 登录机房管理系统!" << endl;
	cout << endl;
	cout << "1. 添加账号" << endl;
	cout << "2. 查看账号" << endl;
	cout << "3. 查看机房" << endl;
	cout << "4. 清空预约" << endl;
	cout << "0. 注销登录" << endl;
	cout << endl;
	cout << "请输入选项的编号：" << endl;


}

//添加账号
void Admin::addPerson()
{
	cout << "请输入添加账号类型" << endl;
	cout << "1. 添加学生" << endl;
	cout << "2. 添加教师" << endl;

	string fileName;	//操作的文件名
	string tip;			//提示id号
	string errorTip;	//错误提示信息

	ofstream ofs;		//文件操作对象

	int select = 0;
	cin >> select;//接受选择

	switch (select)
	{
	case 1:
		fileName = STUDENT_FILE;
		tip = "请输入学生学号：";
		errorTip = "学号重复，请重新输入！";
		break;
	case 2:
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入！";
		break;
	default:
		cout << "输入错误，请重新输入！" << endl;
		return;
	}
	//打开文件，追加模式写文件
	ofs.open(fileName, ios::out | ios::app);

	int id;//学号或职工号
	string name;//姓名
	string pwd;//密码

	cout << tip << endl;//提示输入id号/EmpId

	while (true)
	{
		cin >> id;//接受输入id号
		bool ret = checkRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	//写入文件
	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功！" << endl;

	//重新初始化容器
	this->initVector();

	ofs.close();
	system("pause");
	system("cls");
}

//打印学生信息
void printStudent(Student& s)
{
	cout << "学号： " << s.m_Id << " 姓名： " << s.m_Name 
		//<< " 密码： " << s.m_Pwd //可以选择不打印密码
		<< endl;
}

//打印教师信息
void printTeacher(Teacher& t)
{
	cout << "职工号： " << t.m_EmpId << " 姓名： " << t.m_Name 
		//<< " 密码： " << t.m_Pwd //可以选择不打印密码
		<< endl;
}

//查看账号
void Admin::showPerson()
{
	cout << "请输入查看账号类型" << endl;
	cout << "1. 查看所有学生" << endl;
	cout << "2. 查看所有教师" << endl;

	int select = 0;
	cin >> select;

	switch (select)
	{
	case 1://查看所有学生
	{
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	break;
	case 2://查看所有教师
	{
		cout << "所有教师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	break;
	default:
		cout << "输入错误，请重新输入！" << endl;
		return;
	}

	//任意键退出
	system("pause");
	system("cls");
}

//查看机房信息
void Admin::showComputer()
{
	cout<<"机房信息如下："<<endl;

	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号：" << it->m_ComId << " 机房最大容量：" << it->m_MaxNum << endl;
	}

	//任意键退出
	system("pause");
	system("cls");
}

//清空预约记录
void Admin::cleanFile()
{
	cout << "是否清空预约记录？" << endl;
	cout << "1. 是" << endl;
	cout << "2. 否" << endl;

	int select = 0;
	cin >> select;

	switch (select)
	{
	case 1:
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "清空成功！" << endl;
		//任意键退出
		system("pause");
		system("cls");
		break;
	}
	case 2:
	{
		cout << "取消清空！" << endl;
		//任意键退出
		system("pause");
		system("cls");
		return;
	}
	default:
		cout << "输入错误，请重新输入！" << endl;
		return;
	}
}


//初始化容器
void Admin::initVector()
{
	//清空容器
	vStu.clear();
	vTea.clear();

	//读取学生信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "学生信息文件打开失败！" << endl;
		return;
	}

	Student s;
	while(ifs >> s.m_Id&& ifs >> s.m_Name&& ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}

	ifs.close();

	//读取教师信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "教师信息文件打开失败！" << endl;
		return;//提前退出函数，用于退出 void 类型的函数
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}

	ifs.close();
	
}

//检测重复	参数1：学号/职工号id，参数2：检测类型
bool Admin::checkRepeat(int id, int type)
{
	switch (type)
	{
	case 1://学生
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
		return false;
	}
	break;
	case 2://教师
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
		return false;
	}
	break;
	default:
		return false;
	}
}