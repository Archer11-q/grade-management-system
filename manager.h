#pragma once
#include<iostream>

#include"Identify.h"
#include<fstream>
#include"FileType.h"
#include"student.h"
#include"teacher.h"
#include<cstdio>

//管理员类：继承父类Identity
//主要职责：1.添加账号
//			2.查看账号
//			3.删除账号
//			4.清空信息

class Manager :public Identity
{
public:
	//初始化
	Manager(std::string name,std::string pwd):Identity(name,pwd){}

	//重写父类纯虚函数 菜单显示
	virtual void ShowMenu();

	//添加账号
	void AddAccount();

	//查看账号
	void ShowAccount();

	//删除老师账号
	void DeleteAccount();

	//清空信息
	void ClearAccount();

	//检测账号是否重复
	bool IsRepeat(std::string id, int type);

	//初始化容器
	void InitVector();

	//存放学生信息
	std::vector<Student> m_Stu;

	//存放老师信息
	std::vector<Teacher> m_Tea;
};