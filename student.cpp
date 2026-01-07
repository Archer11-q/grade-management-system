#include"student.h"

Student::Student()
{

}

void Student::ShowMenu()
{

}

void Student::Init()
{
	//初始化学生类私有变量
	this->Class = 0;
	this->Class_Rank = 0;
	this->School_Rank = 0;
	this->Sum_Score = 0;
	
	this->Is_Excellent = false;
	this->Is_Pass = false;

}