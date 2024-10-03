/********************************************************************
*
* 文件名：speechManager.cpp
*
* 文件描述：管理比赛的主要函数实现
*
* 创建人： Rain, 2024 年 10 月 3 日
*
* 版本号：1.0
*
* 修改记录：
*
********************************************************************/

#include "speechManager.h"

//构建函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();

	//创建12名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
}

//菜单功能
void SpeechManager::show_Menu()
{
	cout << "欢迎参加演讲比赛！"<< endl;
	cout << "1. 开始演讲比赛"<< endl;
	cout << "2. 查看往届记录"<< endl;
	cout << "3. 清空比赛记录"<< endl;
	cout << "0. 退出比赛系统"<< endl;
	cout << endl;
}

//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//初始化容器和属性
void SpeechManager::initSpeech()
{
	//容器都初始化为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮数
	this->m_Index = 1;

	//将记录的容器也清空
	this->m_Record.clear();
}

//创建12名选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//创建选手编号，并且放入到v1容器中
		this->v1.push_back(i+10001);

		//选手编号以及对应选手 放入到map容器中
		this->m_Speaker.insert(make_pair(i+10001, sp));
	}
}

//开始比赛 比赛整个流程控制函数
void SpeechManager::startSpeech()
{
	//第一轮开始比赛

	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示晋级结果
	this->showScore();

	//第二轮开始比赛
	this->m_Index = 2;

	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示最终结果
	this->showScore();

	//4、保存分数到文件
	this->saveRecord();

	//重置比赛，获取记录
	//初始化容器和属性
	this->initSpeech();

	//创建12名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();

	cout << "本届比赛结束！" << endl;
	underline();
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第 << " <<this->m_Index<< " >> 轮比赛选手正在抽签" << endl;
	underline();//分割线，函数化
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1)
	{
		//第一轮比赛抽签
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛抽签
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	underline();
	system("pause");
}

//比赛
void SpeechManager::speechContest()
{
	underline();
	cout << "第 << " <<this->m_Index<< " >> 轮比赛正式开始！" << endl;
	cout << endl;
	

	//准备临时容器 存放小组成绩
	multimap<double,int,greater<double>>groupScore;

	//记录人员个数 6人一组
	int num = 0;


	vector<int>v_Src;//比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());//降序排序
		d.pop_front();//去掉最高分
		d.pop_back();//去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//累加总分
		double avg = sum / (double)d.size();			//平均分

		//打印平均分
		/*cout << "编号 " << *it << "姓名：" << this->m_Speaker[*it].m_Name <<
			" 的平均分为：" << avg << endl;*/

		//将平均分放入到map容器里
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//将打分数据放入临时小组容器中
		groupScore.insert(make_pair(avg, *it));//key是成绩，value是选手编号

		//每6人取出前三名
		if (num % 6 == 0)
		{
			cout << "第 " << num / 6 << " 组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "  姓名："
					<< this->m_Speaker[it->second].m_Name
					<< "  成绩：\t" << this->m_Speaker[it->second].m_Score[this->m_Index - 1]
					<< endl;
			}
			//取走前三名放入下一个容器
			int count = 0;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++)
			{
				count++;
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);//second取出multimap的第二个参数
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear();//清空临时容器
			cout << endl;
		}
	}
	cout << "第 << " << this->m_Index << " >> 轮比赛结束！" << endl;
	underline();
	system("pause");
}

//显示得分
void SpeechManager::showScore()
{
	underline();
	if (this->m_Index == 1)
	{
		cout << "第 << " << this->m_Index << " >> 轮晋级选手信息如下：" << endl;
	}
	else
	{
		cout << "第 << " << this->m_Index << " >> 轮最终结果如下：" << endl;
	}


	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout<<"选手编号："<<*it<<"  姓名："<<this->m_Speaker[*it].m_Name
			<<"  得分：\t"<<this->m_Speaker[*it].m_Score[this->m_Index - 1]
			<<endl;
	}
	cout << endl;
	underline();
	system("pause");
	system("cls");
	show_Menu();
}

//保存分数记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//打开文件，追加模式，写文件
	
	//将每个选手数据 写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();
	cout << "比赛记录已保存！" << endl;

	//更改文件不为空的状态
	this->fileIsEmpty = false;
}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv",ios::in);//打开文件，读文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty=true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	//文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空！"<< endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);//将上面读取的单个字符 放回来

	string data;
	int index = 0;

	while (ifs >> data)
	{
		//cout << data << endl;
		vector<string>v;//存放6个string字符串


		int pos = -1;//查到逗号“,”的位置的变量
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//没有找到的情况
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);

			start = pos + 1;
		}
		
		this->m_Record.insert(make_pair(index, v));
		v.clear();
		index++;
	}

	ifs.close();

	//for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	//{
	//	cout << "第 <<"<<it->first <<">> 届" << "冠军编号：" << it->second[0] << "分数：" << it->second[1] << endl;
	//}
}

//显示往届记录
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空或记录不存在"<< endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第 " << i + 1 << " 届"
			<< " 冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << "\t "
			<< " 亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << "\t "
			<< " 季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}
		underline();
	}
	system("pause");
	system("cls");
}

//清空文件
void SpeechManager::clearRecord()
{
	cout << "是否确认清空记录？" << endl;
	cout << "1. 确认清空" << endl;
	cout << "2. 取消清空" << endl;

	int choice;

	cin >> choice;
	if (choice == 1)//确认清空
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();

		//创建12名选手
		this->createSpeaker();

		//加载往届记录
		this->loadRecord();

		this->fileIsEmpty = true;
		cout << "清空成功！" << endl;
	}
	else if (choice == 2)//取消清空
	{
		cout << "操作已取消！" << endl;
	}
	else
	{
		cout << "输入错误！" << endl;
	}

	system("pause");
	system("cls");
}

//析构函数
SpeechManager::~SpeechManager()
{

}

//下划线（美化交互界面）
void SpeechManager::underline()
{
	cout << "-----------------------------------------------------------------------" << endl;
}