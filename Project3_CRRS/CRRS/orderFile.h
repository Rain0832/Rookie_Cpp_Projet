/*********************************************************************

文件名：orderFile.h
文件描述：预约文件操作类和函数声明
创建人： Rain, 2024 年 10 月 4 日
版本号：1.0
修改记录：
********************************************************************/

#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "globalFile.h"
using namespace std;

class OrderFile
{
public:

	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//记录预约条数
	int m_Size;

	//记录所有预约信息的容器 key记录条数 value记录信息
	map<int, map<string, string>> m_orderData;
};
