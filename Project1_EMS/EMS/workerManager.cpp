/********************************************************************
*
* 文件名：workerManager.cpp
*
* 文件描述：职工管理系统的各类函数实现，提供主函数的调用接口
*
* 创建人： Rain, 2024 年 10 月 2 日
*
* 版本号：1.0
*
* 修改记录：
*
********************************************************************/

#include "workerManager.h"
#include <iostream>
#include "windows.h"

using namespace std;

WorkerManager::WorkerManager()
{

    //1、文件不存在

    ifstream ifs;
    ifs.open(FILENAME, ios::in);//用输入的方式打开文件--读文件

    if (!ifs.is_open())
    {
        //cout << "文件不存在!" << endl;
        this->m_EmpNum = 0;                 //初始化人数为0
        this->m_EmpArray = NULL;            //初始化数组指针
        this->m_FileIsEmpty = true;         //文件为空
        ifs.close();
        return;
    }


    //2、文件存在 数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        //代表文件为空
        //cout << "文件为空!" << endl;
        this->m_EmpNum = 0;                 //初始化人数为0
        this->m_EmpArray = NULL;            //初始化数组指针
        this->m_FileIsEmpty = true;         //文件为空
        ifs.close();
        return;
    }

    //3、文件存在 并且记录数据
    int num = this->get_EmpNum();
    //cout<<"职工人数为："<<num<<endl;
    this->m_EmpNum = num;

    //开辟空间
    this->m_EmpArray = new Worker*[this->m_EmpNum];//创建堆区容量
    //将文件中的数据，存到数组中
    this->init_Emp();

    ////测试代码
    //for (int i = 0; i < this->m_EmpNum; i++)
    //{
    //    cout<<"职工编号："<< this->m_EmpArray[i]->m_Id
    //        <<" 姓名："<< this->m_EmpArray[i]->m_Name
    //        <<" 部门："<< this->m_EmpArray[i]->m_DeptId << endl;
    //}

}


void WorkerManager::Show_Menu()
{
    cout << "欢迎使用职工管理系统" << endl;
    cout << "0. 退出管理系统" << endl;
    cout << "1. 增加职工信息" << endl;
    cout << "2. 显示职工信息" << endl;
    cout << "3. 删除离职职工" << endl;
    cout << "4. 修改职工信息" << endl;
    cout << "5. 查找职工信息" << endl;
    cout << "6. 按照编号排序" << endl;
    cout << "7. 清空所有信息" << endl;
    cout << endl;
}

void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);  // 退出程序
}

//添加职工
void WorkerManager::Add_Emp()
{
    cout<<"请输入添加职工数量："<<endl;

    int addNum = 0;//输入的添加职工数量
    cin >> addNum;

    if (addNum > 0)
    {
        //添加
        //计算新空间大小
        int newSize=this->m_EmpNum+addNum;//新空间大小=原来职工人数+新增人数

        //开辟新空间
        Worker** newSpace = new Worker*[newSize];

        //将原来空间下数据，拷贝到新空间数据
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //批量添加新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;//职工编号
            string name;//职工姓名
            int dSelect;//部门选择

            cout << "请输入第" << i + 1 << "个职工的编号：" << endl;
            cin >> id;

            while(this->IsExist(id)!=-1)//判断职工是否存在
            {
                cout << "输入编号重复，请重新输入！"<<endl;
                cout << "请输入第" << i + 1 << "个职工的编号："<<endl;
                cin >> id;
            }

            cout << "请输入第" << i + 1 << "个职工的姓名："<<endl;
            cin >> name;

            cout << "选择该职工岗位" << endl;
            cout << "1. 普通职工" << endl;
            cout << "2. 经理" << endl;
            cout << "3. 总裁" << endl;
            cin >> dSelect;

            Worker* worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                cout << "输入的岗位有误，请重新输入" << endl;
                break;
            }
            //将创建职工职责，保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }

        //释放原来空间
        delete[] this->m_EmpArray;

        //更改新空间的指向
        this->m_EmpArray = newSpace;

        //更新职工人数
        this->m_EmpNum = newSize;

        //更新职工不为空标志
        this->m_FileIsEmpty = false;

        //提示添加成功
        cout << "成功添加" << addNum << "名新职工" << endl;

        //保存数据到文件
        this->save();


    }
    else
    {
        cout << "输入的数量有误，请重新输入" << endl;
    }


    //按任意键后，清屏回到上级目录
    system("pause");
    system("cls");

}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME,ios::out);//用输出的方式打开文件--写文件

    //将每个人数据写入到文件中
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }

    ofs.close();

}

int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//用输入的方式打开文件--读文件

    int id;
    string name;
    int dId;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        //统计人数变量
        num++;
    }
    return num;
}

void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//用输入的方式打开文件--读文件

    int id;
    string name;
    int dId;

    int index = 0;

    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker* worker = NULL;

        if (dId == 1)//普通员工部门
        {
            worker = new Employee(id, name, dId);
        }
        else if (dId == 2)//经理部门
        {
            worker = new Manager(id, name, dId);
        }
        else if (dId == 3)//总裁部门
        {
            worker = new Boss(id, name, dId);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }

    //关闭文件
    ifs.close();
}

//显示所有职工信息
void WorkerManager::Show_Emp()
{
    //判断文件是否为空
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        for (int i = 0; i < m_EmpNum; i++)
        {
            //利用多态调用程序接口
            this->m_EmpArray[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}

//删除职工
void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else//
    {
        cout << "请输入要删除的职工编号：" << endl;
        int id = 0;
        cin >> id;

        int index = this->IsExist(id);

        if (index != -1)//职工存在 找到职工所在数组中的位置index
        {
            //数据前移
            for (int i = index; i < m_EmpNum - 1; i++)
{
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;//更新数组中记录人员个数
            //同步更新到文件中
            this->save();

            cout << "删除成功！" << endl;
        }
        else
        {
            cout << "删除失败，没有找到该职工！" << endl;
        }
    }

    //按任意键后，清屏回到上级目录
    system("pause");
    system("cls");
}

//判断职工是否存在 如果存在，返回职工所在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
    int index = -1;

    for (int i = 0; i < m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_Id == id)
        {
            //找到职工
            index = i;
            break;
        }
    }

return index;
}

//修改职工信息
void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "请输入要修改职工的编号：" << endl;
        int id = 0;
        cin >> id;

        int ret = this->IsExist(id);
        if (ret != -1)
        {
            //查找到编号的职工

            delete this->m_EmpArray[ret];//释放原来的职工内存

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "查到： " << id << " 号职工，请输入新的职工号： " << endl;
            cin >> newId;

            cout << "请输入新姓名：" << endl;
            cin >> newName;

            cout << "请输入岗位：" << endl;
            cout << "1. 普通职工" << endl;
            cout << "2. 经理" << endl;
            cout << "3. 总裁" << endl;
            cin >> dSelect;

            Worker* worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(newId, newName, 1);
                break;
            case 2:
                worker = new Manager(newId, newName, 2);
                break;
            case 3:
                worker = new Boss(newId, newName, 3);
                break;
            default:
                cout << "输入的岗位有误，请重新输入" << endl;
                break;
            }

            //更新数据 到数组中
            this->m_EmpArray[ret] = worker;

            cout << "修改成功！" << endl;

            //同步更新到文件中
            this->save();
        }
        else
        {
            cout << "修改失败，查无此人！" << endl;
        }
    }
    //按任意键，清屏回到上级目录
    system("pause");
    system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "请输入查找的方式：" << endl;
        cout << "1. 按职工编号查找" << endl;
        cout << "2. 按职工姓名查找" << endl;
        int select = 0;
        cin >> select;

        switch (select)
        {
        case 1:             //按照编号查
            {
                int id = 0;
                cout << "请输入要查找的职工编号：" << endl;
                cin >> id;

                int ret = this->IsExist(id);
                if (ret != -1)
                {
                    cout << "查找成功！该职工信息如下：" << endl;
                    this->m_EmpArray[ret]->showInfo();//利用多态调用程序接口
                }
                else
                {
                    cout << "查找失败，没有找到该职工！" << endl;
                }
            }
            break;
        case 2:             //按照姓名查
        {
            string name = "";
            cout << "请输入要查找的职工姓名：" << endl;
            cin >> name;

            //加入判断是否查到的标志
            bool flag = false;

            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    cout << "查找成功！职工编号为："
                        << this->m_EmpArray[i]->m_Id
                        << "号职工的信息如下：" << endl;

                    flag = true;
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if (flag == false)
            {
                cout << "查找失败，没有找到该职工！" << endl;
            }
        }
            break;
        default:
            cout << "输入的查找方式有误，请重新输入！" << endl;
            break;
        }
    }
    //按任意键，清屏回到上级目录
    system("pause");
    system("cls");
}

//按照编号排序职工
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        start:                              //goto语句标签
        cout << "请选择排序方式："<<endl;
        cout << "1. 按照职工号进行升序" << endl;
        cout << "2. 按照职工号进行降序" << endl;

        int select = 0;
        cin >> select;
        for (int i = 0; i < m_EmpNum - 1; i++)
        {
            int minOrMax = i;//声明最小值 或 最大值下标

            for (int j = i + 1; j < this->m_EmpNum; j++)
            {
                if (select == 1)//升序
                {
                    if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else if (select == 2)//降序
                {
                    if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else
                {
                    cout << "输入的排序方式有误，请重新输入！" << endl;
                    goto start;                 //如果有误，跳转到start标签
                }
            }
            //判断一开始认定 最小值或最大值 是不是 计算的最小值或最大值，如果不是，交换数据
            if (minOrMax != i)
            {
                Worker* temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] = temp;
            }
        }
        cout << "排序成功！排序后的结果为：" << endl;
        this->save();//排序后结果保存到文件中
        this->Show_Emp();//展示所有职工信息
    }
}

//清空文件
void WorkerManager::Clear_File()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
    cout << "是否确认清空文件？" << endl;
    cout << "1. 确认清空" << endl;
    cout << "2. 取消清空" << endl;

    int select = 0;
    cin >> select;

    if (select == 1)
    {
        //清空文件
        ofstream ofs(FILENAME, ios::trunc);                //创造ofstream对象
        ofs.close();

        if (this->m_EmpArray != NULL)
        {
            //删除堆区的每个职工对象
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }

            //删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }

        cout << "文件已清空！" << endl;
    }
    }
    //按任意键，清屏回到上级目录
    system("pause");
    system("cls");
}

WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)//堆区文件手动开辟，手动释放
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            if (this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
    }
}
