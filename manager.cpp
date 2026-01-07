#include"manager.h"

//重写父类纯虚函数 菜单显示
void Manager::ShowMenu()
{
	std::cout << "\n\t\t\t                    成绩管理系统\n";
	std::cout << "\t\t\t********************************************************\n";
	std::cout << "\t\t\t***********                                  ***********\n";
	std::cout << "\t\t\t***********           1.添加账号             ***********\n";
	std::cout << "\t\t\t***********                                  ***********\n";
	std::cout << "\t\t\t***********           2.查看账号             ***********\n";
	std::cout << "\t\t\t***********                                  ***********\n";
	std::cout << "\t\t\t***********           3.删除账号             ***********\n";
	std::cout << "\t\t\t***********                                  ***********\n";
	std::cout << "\t\t\t***********           4.清空信息             ***********\n";
	std::cout << "\t\t\t***********                                  ***********\n";
	std::cout << "\t\t\t***********           0.退出                 ***********\n";
	std::cout << "\t\t\t***********                                  ***********\n";
	std::cout << "\t\t\t********************************************************\n";
}

//初始化容器
void Manager::InitVector()
{
	//清空教师和学生容器
	m_Tea.clear();
	m_Stu.clear();

	//初始化学生信息
	std::ifstream ifs;
	ifs.open(STUDENT, std::ios::in);			//用读的方式打开文件
	if (!ifs.is_open())
	{
		std::cout << "学生文件打开失败！\n";
		return;
	}

	std::string fId;		//接收学号
	std::string fName;		//接收姓名
	std::string fPwd;		//接收密码
	while (ifs >> fId && ifs >> fName && ifs >> fPwd)
	{
		Student stu(fId, fName, fPwd);	//创建学生对象
		m_Stu.push_back(stu);			//将学生对象放入学生容器中
	}

	ifs.close();

	//初始化老师信息
	ifs.open(TEACHER, std::ios::in);			//用读的方式打开文件
	if (!ifs.is_open())
	{
		std::cout << "老师文件打开失败！\n";
		return;
	}

	while (ifs >> fId && ifs >> fName && ifs >> fPwd)
	{
		Teacher tea(fId, fName, fPwd);	//创建老师对象
		m_Tea.push_back(tea);			//将老师对象放入老师容器中
	}

	ifs.close();
}

//检测账号是否重复
bool Manager::IsRepeat(std::string id, int type)
{
	//type 1-学生 2-老师
	if (type == 1)
	{
		//检测学生
		for (Student& s : m_Stu)
			if ( s.getId() == id)
				return true;
	}
	else
	{
		for (Teacher& t : m_Tea)
			if (t.getId() == id)
				return true;
		//检测老师
	}
	return false;
}

//添加老师账号
void Manager::AddAccount()
{
	// 添加账号前，先初始化容器，确保内存数据和文件同步
	InitVector();

	std::cout << "请选择需要添加的账号类型：\n";
	std::cout << "1.学生\n";
	std::cout << "2.老师\n";
	
	std::string FileName;	//操作文件的名称
	std::string Tip;		//提示输入学号/职工号
	std::string ErrorTip;	//提示添加账号重复

	int select = 0;			//接收用户选择
	std::cin >> select;
	if (select == 1)
	{
		//添加学生
		FileName = STUDENT;
		Tip = "请输入学生学号：";
		ErrorTip = "该学号已存在，请重新输入！";
	}
	else
	{
		//添加老师
		FileName = TEACHER;
		Tip = "请输入老师职工号：";
		ErrorTip = "该职工号已存在，请重新输入！";
	}

	//先判断添加的账号是否重复，再引导输入姓名和密码，最后将信息写入文件中
	std::string fId;		//接收用户输入的学号/职工号
	std::string fName;		//接收用户输入的姓名
	std::string fPwd;		//接收用户输入的密码

	//引导输入账号
	std::cout << Tip;
	while (true)
	{
		std::cin >> fId;
		//检测账号是否重复
		if (IsRepeat(fId, select))
			std::cout << ErrorTip << std::endl;
		else
			break;
	}

	//引导输入姓名和密码
	std::cout << "请输入姓名：";
	std::cin >> fName;
	std::cout << "请输入密码：";
	std::cin >> fPwd;

	//将信息写入文件
	std::ofstream ofs;
	ofs.open(FileName, std::ios::out | std::ios::app);
	ofs << fId << " " << fName << " " << fPwd << "\n";
	std::cout << "账号添加成功！\n";


	system("pause");
	system("cls");

	ofs.close();
}

//查看账号
void Manager::ShowAccount()
{
	std::cout << "请选择需要查看的账号类型：\n";
	std::cout << "1.查看所有学生\n";
	std::cout << "2.查看所有老师\n";

	int select = 0;			//接收用户选择
	std::cin >> select;

	//用读的方式打开文件
	std::ifstream ifs;
	if (select == 1)
		ifs.open(STUDENT, std::ios::in);
	else
		ifs.open(TEACHER, std::ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		std::cout << "文件打开失败！\n";
		system("pause");
		system("cls");
		ifs.close();
		return;
	}

	//判断文件是否为空
	char ch;
	ifs.get(ch);
	if (ifs.eof())		//文件为空
	{
		std::cout << "文件为空！\n";
		system("pause");
		system("cls");
		ifs.close();
		return;
	}
	else				//文件不为空，恢复读指针位置
		ifs.seekg(0);



	//文件存在，读取文件中的信息
	std::string fId;		//接收学号/职工号
	std::string fName;		//接收姓名
	std::string fPwd;		//接收密码

	while (ifs >> fId && ifs >> fName && ifs >> fPwd)
	{
		std::cout << "账号：" << fId << "\t姓名：" << fName << "\t密码：" << fPwd << std::endl;
	}

	system("pause");
	system("cls");

	ifs.close();
}

//删除账号
void Manager::DeleteAccount()
{
	std::cout << "请选择需要删除的账号类型：\n";
	std::cout << "1.学生\n";
	std::cout << "2.老师\n";

	int select = 0;
	std::cin >> select;

	//用读的方式打开文件，判断文件是否打开成功
	std::ifstream ifs;
	if (select == 1)
		ifs.open(STUDENT, std::ios::in);
	else
		ifs.open(TEACHER, std::ios::in);

	if (!ifs.is_open())
	{
		std::cout << "文件打开失败！\n";
		system("pause");
		system("cls");
		ifs.close();
		return;
	}

	//文件存在，读取文件中的信息到容器中
	std::string fId;		//接收学号/职工号
	std::string fName;		//接收姓名
	std::string fPwd;		//接收密码

	std::string tempId;		//接收用户输入的要删除的账号
	if (select == 1)
		std::cout << "请输入要删除的学生学号：";
	else
		std::cout << "请输入要删除的老师职工号：";
	std::cin >> tempId;
	
	//匹配到要删除的账号，就跳过该账号信息，不写入到临时文件中
	while (ifs >> fId && ifs >> fName && ifs >> fPwd)
	{
		if (tempId == fId)
		{
			//找到要删除的账号，进行删除操作
			std::cout << "找到该账号，正在进行删除操作...\n";
			system("pause");
			continue;				//跳过该账号信息，不写入到临时文件中
		}

		//将未被删除的账号信息写入到临时文件中
		std::ofstream ofs;
		if (select == 1)	//写入临时学生文件
			ofs.open(TEMPSTUDENT, std::ios::out | std::ios::app);
		else				//写入临时教师文件
			ofs.open(TEMPTEACHER, std::ios::out | std::ios::app);
		ofs << fId << " " << fName << " " << fPwd << "\n";
		ofs.close();
	}

	ifs.close();

	if(select==1)
	{
		//删除原学生文件
		std::remove(STUDENT);

		//将临时学生文件改名为正式学生文件
		std::rename(TEMPSTUDENT, STUDENT);
	}
	else
	{
		//删除原教师文件
		std::remove(TEACHER);
		//将临时教师文件改名为正式教师文件
		std::rename(TEMPTEACHER, TEACHER);
	}

	std::cout << "账号删除成功！\n";
	system("pause");
	system("cls");
}

//清空信息
void Manager::ClearAccount()
{
	std::cout << "请选择需要清空的账号类型：\n";
	std::cout << "1.清空所有学生账号\n";
	std::cout << "2.清空所有老师账号\n";

	int select = 0;
	std::cin >> select;
	
	std::ofstream ofs;

	if (select == 1)
		ofs.open(STUDENT, std::ios::trunc);	//以清空方式打开学生文件
	else
		ofs.open(TEACHER, std::ios::trunc);	//以清空方式打开教师文件

	std::cout << "账号清空成功！\n";
	system("pause");
	system("cls");

	ofs.close();
}
