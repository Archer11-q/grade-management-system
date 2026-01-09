#pragma once
#include<iostream>

#include"student.h"
#include<vector>
#include<fstream>
#include"FileType.h"
#include<numeric>
#include<algorithm>
#include<map>
#include<string>
#include"situation.hpp"
#include <iomanip>			//提供setw/setprecision/fixed调整输出格式
#include<set>

//系统类：
//主要职责：1.进行总分排序（两个班放一起排序，显示班排名和校排名）
//			2.学校成绩情况（各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率）
//			3.班级成绩情况
//			4.开发查询功能（支持模糊查找）
//			5.统计缺考名单（姓名、学号、班级、缺考科目、分数）
//			6.统计挂科名单
//			7.统计优秀名单
//			8.统计成绩进退步情况	


//将计算好的结果放文件供学生老师查看
class System
{
public:
	//总分排序函数
	void Sum_Sort();

	//学校成绩情况
	void School_Score();

	//班级成绩情况
	void Class_Score();

	//查询功能
	void Search();

	//缺考名单统计
	void Absence_List();

	//挂科名单统计
	void Fail_List();

	//优秀名单统计
	void Excellent_List();

	//成绩进退步情况统计
	void Progress_List();

	//存放学生信息容器
	std::vector<Student> v_Stu;

	//存放一班学生信息容器 key:学生学号最后两位 value:学生对象容器
	std::map<int, std::vector<Student>> Class_One;
	//存放二班学生信息容器
	std::map<int, std::vector<Student>> Class_Two;

	//初始化容器
	void Init_Vec(int select);		//select接收某一次考试

	//计算班级排名和学校排名	参数：select：选择某一次考试
	void Calculate_Rank(int select);

	//同步学校容器v_Stu到班级容器Class_One和Class_Two
	void Sync_Vec();

	//如果姓名是两个字，用空格在中间补齐成三个字大小（补齐格式）
	std::string Name_TwoToThree(std::string name);

	//将成绩容器转化为容纳六门科目的map容器 key：0-5科目数 value 学生六门成绩
	std::map<int, std::vector<int>> m_Score;

	//析构函数
	~System();

};

