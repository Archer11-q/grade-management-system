#include<iostream>
#include"Identify.h"
#include<string>
#include<fstream>

#include"student.h"
#include"teacher.h"
#include"manager.h"
#include"FileType.h"
#include"system.h"

//进入管理员子菜单界面
void ManagerMenu(Identity *manager)
{
	//将父类指针强制转化为子类指针
	Manager* man = (Manager*)manager;

	while (true)
	{
		//调用管理员的子菜单显示功能
		manager->ShowMenu();
		//提供用户选择
		int select = 0;
		std::cout << "请输入你要选择的功能：";
		std::cin >> select;

		if (select == 1) {				//添加账号
			man->AddAccount();
		}
		else if (select == 2) {			//查看账号
			man->ShowAccount();
		}
		else if (select == 3) {			//删除账号
			man->DeleteAccount();

		}
		else if (select == 4) {			//清空信息
			man->ClearAccount();
		}
		else {                          //注销登录	
			delete manager;				//销毁堆区对象
			std::cout << "注销成功\n";
			system("pause");
			system("cls");
			return;
		}
	}
}

//登录函数 1.学生 2.老师 3.管理员
//作用：让用户进入系统输入自己的账号密码等相关信息，验证成功进入相应菜单页面
void Login(std::string fileName,int type)
{
	Identity* person = NULL;			//后续指向学生/老师/管理员

	//读文件形式打开文件
	std::ifstream ifs;			
	ifs.open(fileName, std::ios::in);

	//判断文件是否存在（文件创建失败）
	if (!ifs.is_open())
	{
		std::cout << "文件打开失败\n";
		system("pause");
		system("cls");
		ifs.close();
		return;
	}

	//引导用户输入个人信息
	std::string id;			//学号
	std::string name;		//账号姓名
	std::string pwd;		//账号密码


	//首先：通过判断是输入学号还是职工号
	if (type == 1)		//学生
	{
		std::cout << "请输入您的学号\n";
		std::cin >> id;
	}
	else if(type==2)	//老师
	{
		std::cout << "请输入您的职工号：\n";
		std::cin >> id;
	}


	//然后：引导输入姓名和密码
	std::cout << "请输入您的姓名：\n";
	std::cin >> name;

	std::cout << "请输入您的密码：\n";
	std::cin >> pwd;


	//最后：与打开的文件信息进行匹配，若一致则进入相应菜单界面
	std::string fId ;			//接收文件中的学号
	std::string fName;			//接收文件中的姓名
	std::string fPwd;			//接收文件中的密码

	if (type == 1){	//学生
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)	//读的方式获取学生信息
		{
			if (fId == id && fName == name && fPwd == pwd)	//匹配学生
			{
				std::cout << "学生验证登录成功！\n";
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);

				//进入学生登录界面

			}
		}
	}
	else if (type == 2) {	//老师
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)	//读的方式获取学生信息
		{
			if (fId == id && fName == name && fPwd == pwd)	//匹配教师
			{
				std::cout << "教师验证登录成功！\n";
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);

				//进入教师登录界面
			}
		}
	}
	else {					//管理员
		while (ifs >> fName && ifs >> fPwd)	//读的方式获取学生信息
		{
			if (fId == id && fName == name && fPwd == pwd)	//匹配管理员
			{
				std::cout << "管理员验证登录成功！\n";
				system("pause");
				system("cls");

				person = new Manager(name, pwd);

				//进入管理员登录界面
				ManagerMenu(person);
			}
		}
	}
}

int main()
{
	////全校第一次考试成绩初始化测试
	//System s;
	//s.Init_Vec();
	//for (Student& stu : s.v_Stu)
	//{
	//	std::cout << stu.getId() << " " << stu.getName() << " " << stu.v_Score[0] << " " << stu.v_Score[1] << " " << stu.v_Score[2] << " " << stu.v_Score[3] << " " << stu.v_Score[4] << " " << stu.v_Score[5] << " "<<stu.getSumScore()<<std::endl;
	//}

	/*全校分班考试成绩初始化测试*/
	System s;
	//s.School_Score();
	s.Class_Score();
	
	
	
	/*int select = 0;
	while (true)
	{
		std::cout << "\n\t\t\t                    成绩管理系统\n";
		std::cout << "\t\t\t********************************************************\n";
		std::cout << "\t\t\t***********                                  ***********\n";
		std::cout << "\t\t\t***********           1.学生登录             ***********\n";
		std::cout << "\t\t\t***********                                  ***********\n";
		std::cout << "\t\t\t***********           2.教师登录             ***********\n";
		std::cout << "\t\t\t***********                                  ***********\n";
		std::cout << "\t\t\t***********           3.管理员登录           ***********\n";
		std::cout << "\t\t\t***********                                  ***********\n";
		std::cout << "\t\t\t***********           0.退出                 ***********\n";
		std::cout << "\t\t\t***********                                  ***********\n";
		std::cout << "\t\t\t********************************************************\n";
		
		std::cout << "请输入你的选择：\n";
		std::cin >> select;

		switch (select)
		{
		case 1:
			Login(STUDENT, 1);
			break;
		case 2:
			Login(TEACHER, 2);
			break;
		case 3:
			Login(MANAGER, 3);
			break;
		case 0:
			std::cout << "欢迎下次使用！！\n";
			system("pause");
			return 0;
			system("cls");
			break;
		default:
			std::cout << "输入有误，请重新输入！\n";
			break;
		}
	}*/
}