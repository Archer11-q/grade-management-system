#pragma once
#include<iostream>

#include"Identify.h"

//教师类：继承父类Identity
//主要职责：1. 查看每次考试排名
//		    2. 查看学校成绩情况（全校各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率）
//			3. 查看班级成绩情况（全班各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率）
//			4. 查看进退步情况	
//			5. 查看优秀名单
//			6. 查看缺考名单
//			7. 查看挂科名单

//			8. 进行成绩补录
//			9. 删除学生成绩
//			10.修改学生成绩
//			11.查询学生（支持模糊查询）



class Teacher:public Identity
{
public:
	//初始化变量
	Teacher(std::string id,std::string name,std::string pwd)
		:Identity(name,pwd),Id(id){ }

	//重写父类纯虚函数——显示菜单
	virtual void ShowMenu();

	//获取职工号
	std::string getId() { return Id; }

	//初始化变量
	void Init();

private:
	std::string Id;			//职工号

	double Aver_School;		//学校平均分
	double Aver_Class;		//班级平均分
};