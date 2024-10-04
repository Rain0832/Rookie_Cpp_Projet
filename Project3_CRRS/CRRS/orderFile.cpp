/*********************************************************************

文件名：orderFile.cpp
文件描述：预约文件类和相关函数实现
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#include "orderFile.h"

//构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;		//日期
	string interval;	//时间段
	string stuId;		//学生编号
	string stuName;		//学生姓名
	string roomId;		//机房编号
	string status;		//预约状态

	this->m_Size = 0;

	while (ifs >> date && ifs >> interval && ifs >> stuId
		&& ifs >> stuName && ifs >> roomId
		&& ifs >> status)
	{

		string key;
		string value;
		map<string, string>m;

		//利用string内置函数，找到date键值对中第一个冒号	
		int pos = date.find(":");//返回 4 

		if (pos != -1)//截取日期
		{
			//得到截断字串：key
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);

			m.insert(make_pair(key, value));

		}

		pos = interval.find(":");

		if (pos != -1)//截取时间段
		{
			//得到截断字串：key
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);

			m.insert(make_pair(key, value));

		}

		pos = stuId.find(":");

		if (pos != -1)//截取学生编号
		{
			//得到截断字串：key
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);

			m.insert(make_pair(key, value));

		}

		pos = stuName.find(":");

		if (pos != -1)//截取学生姓名
		{
			//得到截断字串：key
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);

			m.insert(make_pair(key, value));

		}

		pos = roomId.find(":");

		if (pos != -1)//截取机房编号
		{
			//得到截断字串：key
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);

			m.insert(make_pair(key, value));

		}

		pos = status.find(":");

		if (pos != -1)//截取预约状态
		{
			//得到截断字串：key
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);

			m.insert(make_pair(key, value));
		}

		//将小map容器放到大的map容器中
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;

	}
	ifs.close();
}

//更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;//如果没有预约记录，则不更新
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}

	ofs.close();
}
