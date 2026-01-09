#pragma once
#include<iostream>

class Identity
{
public:
	Identity();

	//纯虚函数：强制基类重写菜单函数
	virtual void ShowMenu() = 0;

	//初始化变量
	Identity(std::string name, std::string pwd) : m_Name(name), m_Pwd(pwd)
	{ }

	//设置姓名与密码
	void setName(std::string name) { this->m_Name = name; }
	void setPwd(std::string pwd) { this->m_Pwd = pwd; }

	//获取姓名与密码
	std::string getName() const{ return this->m_Name; }
	std::string getPwd() const{ return this->m_Pwd; }


	//1. 查看每次考试排名

	//2. 查看学校成绩情况（各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率）
	
	//3. 查看班级成绩情况（各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率）
	
	//4. 查看进退步情况	
	
	//5. 查看优秀名单

	//6.查找缺考名单

	//7.查看挂科名单

	virtual ~Identity() {}
private:
	std::string m_Name;		//姓名
	std::string m_Pwd;		//密码
};
