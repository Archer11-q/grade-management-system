#pragma once
#include<iostream>
#include<vector>

#include"Identify.h"

//学生类：	继承父类Identity
//主要职责：1.查看每次考试排名
//		    2.查看学校成绩情况（整个年级各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率）
//			3.查看班级成绩情况（整个班级各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率）
//			4.查看进退步情况
//			5.查看优秀名单

//					学号 学生个体（姓名、六科成绩、总成绩）
//按班级划分两个map<int,vector<Student>> Class_One; 

class Student:public Identity
{
public:
	Student();

	Student(std::string id, std::string name, std::string pwd)	//显式调用父类的带参构造
		: Identity(name, pwd),Id(id) { }

	//重写父类纯虚函数——显示菜单
	virtual void ShowMenu();

	//初始化变量函数
	void Init();

	//获取学生学号
	std::string getId() { return Id; }

	//获取学生总成绩
	int getSumScore() { return Sum_Score; }

	//获取班级排名
	int getClassRank() { return Class_Rank; }

	//获取学校排名
	int getSchoolRank() { return School_Rank; }

	//获得班级
	int getClass() { return Class; }

	//设置学生学号
	void setId(std::string id) { this->Id = id; }

	//设置学生总成绩
	void setSumScore(int score) { this->Sum_Score = score; }

	//设置班级排名
	void setClassRank(int rank) { this->Class_Rank = rank; }

	//设置学校排名
	void setSchoolRank(int rank) { this->School_Rank = rank; }

	//设置班级
	void setClass(int cls) { this->Class = cls; }

	std::vector<int> v_Score;			//记录六门科目的容器

private:
	std::string Id;		//学号2024034743xxx(倒数第三位0：1班，1：2班；后两位：学号)

	int Class;			//班级
	int Class_Rank;		//班级排名
	int School_Rank;	//学校排名
	int Sum_Score;		//总成绩

	bool Is_Pass;		//及格状态
	bool Is_Excellent;	//优秀状态
};