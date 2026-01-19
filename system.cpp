#include"system.h"

//初始化容器,并计算每个学生总成绩
void System::Init_Vec(int select)
{
	//从文件中读取学生信息，存放到容器中
	std::ifstream ifs;
	if (select == 1)		//第一次考试文件
		ifs.open(SOURCE1, std::ios::in);
	else					//第二次考试文件
		ifs.open(SOURCE2, std::ios::in);

	//判断文件是否打开成功
	if (!ifs.is_open())
	{
		std::cout << "文件打开失败！" << std::endl;
		ifs.close();
		return;
	}

	std::string fId;	//接收文件学号
	std::string fName;	//接收文件姓名
	int score;			//接收文件六门成绩

	//清空系统容器，防止重复添加数据
	v_Stu.clear();

	while (ifs >> fName && ifs >> fId)
	{
		//创建学生对象，接收文件信息，存放到容器中
		Student stu;

		//先将读取的学号和姓名传给学生对象
		stu.setName(Name_TwoToThree(fName));		//处理姓名格式（姓名两个字用空格补齐）
		stu.setId(fId);

		//再将六门成绩存放到学生对象的容器中
		stu.v_Score.clear();	//清空容器，防止上次数据影响本次数据
		for (int i = 0; i < 6; i++)
		{
			ifs >> score;
			stu.v_Score.push_back(score);
		}

		//计算单个学生总成绩，并将排名置零
		stu.Init();

		stu.setSumScore(std::accumulate(stu.v_Score.begin(), stu.v_Score.end(), 0));

		//读完所有信息，将学生对象存放到系统容器中
		v_Stu.push_back(stu);
	}


	//将一次考试的所有系统学生容器拆分成两个班级容器（方便进行班级排名）
	//调用前清空班级容器，避免数据累积
	Class_One.clear();
	Class_Two.clear();

	//遍历系统容器中的学生，将学生按班级存放到两个班级容器中（过程中已同步学生信息到班级容器中）
	for (Student& stu : v_Stu)
	{
		//学号总计13位，倒数第三位表示班级，最后两位表示学号
		std::string id = stu.getId();

		int class_num = id[10] - '0';				//获取班级号
		int stu_num = std::stoi(id.substr(11, 2));	//获取学号最后两位

		//判断班级，存放到对应班级容器中	若stu_num对应的vector不存在，map会自动创建空vector
		if (class_num == 0) // 一班
		{
			stu.setClass(1);		 // 设置班级为1
			Class_One[stu_num].push_back(stu);
		}

		else // 二班
		{
			stu.setClass(2);		 // 设置班级为2
			Class_One[stu_num].push_back(stu);
		}
	}

	ifs.close();
}

//如果姓名是两个字，用空格在中间补齐成三个字大小（补齐格式）
std::string System::Name_TwoToThree(std::string name)
{
	if (name.length() == 4)
	{
		name.insert(2, "   ");
	}
	return name;
}

//同步信息：学校容器v_Stu到班级容器Class_One和Class_Two
void System::Sync_Vec()
{
	//调用前清空班级容器，避免数据累积
	Class_One.clear();
	Class_Two.clear();

	//遍历系统容器中的学生，将学生按班级存放到两个班级容器中
	for (Student& stu : v_Stu)
	{
		if (stu.getClass() == 1)		//一班
			Class_One[std::stoi(stu.getId().substr(11, 2))].push_back(stu);
		else							//二班
			Class_Two[std::stoi(stu.getId().substr(11, 2))].push_back(stu);
	}
}

//编写仿函数对学生进行总分排序（总分降序排列）
class SumSort
{
public:
	bool operator()(Student& s1, Student& s2)
	{
		return s1.getSumScore() > s2.getSumScore();
	}
};

//计算班级排名和学校排名
void System::Calculate_Rank(int select)
{
	//初始化系统容器
	Init_Vec(select);

	//先对系统容器中的学生进行总分排序(总分降序)
	std::sort(v_Stu.begin(), v_Stu.end(), SumSort());

	//赋予学生学校排名和班级排名
	int school_rank = 1;		//学校排名
	int classOne_rank = 1;		//一班班级排名
	int classTwo_rank = 1;		//二班班级排名

	//遍历排序后的系统容器，依次赋予学校排名和班级排名
	//由于已经进行总分排序，故第一位同学学校排名为1
	v_Stu[0].setSchoolRank(school_rank);
	if (v_Stu[0].getClass() == 1)
	{
		v_Stu[0].setClassRank(classOne_rank);
		classTwo_rank = 0;
	}
	else
	{
		v_Stu[0].setClassRank(classTwo_rank);
		classOne_rank = 0;
	}

	for (size_t i = 1; i < v_Stu.size(); ++i)
	{
		if (v_Stu[i].getSumScore() == v_Stu[i - 1].getSumScore())
		{
			//与前一名同学总分相同，排名相同
			v_Stu[i].setSchoolRank(v_Stu[i - 1].getSchoolRank());
			++school_rank;
		}
		else
		{
			++school_rank;
			//与前一名同学总分不同，排名递增
			v_Stu[i].setSchoolRank(school_rank);
		}


		//赋予班级排名
		if (v_Stu[i].getClass() == 1)
		{
			//如果成绩与前一名同学相同且同班级，排名相同
			if (v_Stu[i].getSumScore() == v_Stu[i - 1].getSumScore() && v_Stu[i].getClass() == v_Stu[i - 1].getClass())
			{
				v_Stu[i].setClassRank(v_Stu[i - 1].getClassRank());
				++classOne_rank;
			}
			else
			{
				++classOne_rank;
				v_Stu[i].setClassRank(classOne_rank);
			}
		}
		else
		{
			if (v_Stu[i].getSumScore() == v_Stu[i - 1].getSumScore() && v_Stu[i].getClass() == v_Stu[i - 1].getClass())
			{
				v_Stu[i].setClassRank(v_Stu[i - 1].getClassRank());
				++classTwo_rank;
			}
			else
			{
				++classTwo_rank;
				v_Stu[i].setClassRank(classTwo_rank);
			}
		}
	}

	//同步学生信息到班级容器（班排名和校排名）
	Sync_Vec();
}

//总分排序函数(包含班级排名和学校排名)
void System::Sum_Sort()
{
	std::cout << "请选择要进行总分排序的考试（1.第一次考试 2.第二次考试）：\n";
	int select = 0;
	std::cin >> select;

	//判断输入是否合法
	while (select != 1 && select != 2) {
		std::cout << "输入非法！请选择1或2：\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> select;
	}

	try{
		//调用提取的排名方法
		Calculate_Rank(select);

		//将总分排序结果写入文件SumSort.txt
		//用写的方式打开文件，若文件不存在则创建
		std::ofstream ofs;
		ofs.open(SUMSORT, std::ios::out | std::ios::trunc);

		ofs << "姓名：\t\t学号：\t\t\t\t语文\t数学\t英语\t物理\t化学\t政治\t总分\t校排名\t班排名\n";
		for (Student& stu : v_Stu)
		{
			ofs << stu.getName() << "\t\t" << stu.getId() << "\t\t";
			for (int score : stu.v_Score)
			{
				ofs << score << "\t";
			}
			ofs << stu.getSumScore() << "\t" << stu.getSchoolRank() << "\t\t" << stu.getClassRank() << "\n";

			ofs.close();
		}
	}
	catch (const std::runtime_error& e) {
		std::cout << "排序失败：" << e.what() << std::endl;
	}
}

//学校成绩情况(某一次考试全校各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率）
void System::School_Score()
{
	std::cout << "请输入要统计成绩情况的考试（1.第一次考试 2.第二次考试）：\n";
	int select = 0;
	std::cin >> select;

	//初始化系统容器(获得全校学生信息)
	Init_Vec(select);

	//创建情况对象数组
	Situation s;

	//清空map，避免重复数据
	m_Score.clear();

	//初始化map（给0-5科目创建空的vector）
	for (int subIdx = 0; subIdx < 6; subIdx++) {
		m_Score[subIdx] = std::vector<int>();
	}

	//遍历所有学生，拆分v_Score到map对应key中
	for (Student& stu : v_Stu)
		for (int i = 0; i < 6; i++)
			m_Score[i].push_back(stu.v_Score[i]);

	//计算各项数据并存放到情况对象中
	for (int i = 0; i < 6; i++)		//遍历六门成绩
	{
		for (int score : m_Score[i])	//遍历每门成绩的所有学生成绩
		{
			//计算当前科目总分
			s.setAverageScore()[i] += score;
			//计算最高分
			if (score > s.getHighestScore()[i])
				s.setHighestScore()[i] = score;
			//计算最低分
			if (score < s.getLowestScore()[i])
				s.setLowestScore()[i] = score;
			//计算不及格人数
			if (score < 60)
				s.setFailCount()[i]++;
			//计算优秀人数
			if (score >= 85)
				s.setExcellentCount()[i]++;
		}
	}

	for (int i = 0; i < 6; i++)		//计算各科平均分和优秀率
	{
		//计算各科平均分
		s.setAverageScore()[i] /= m_Score[i].size();

		//计算各科优秀率
		s.setExcellentRate()[i] = (static_cast<double>(s.getExcellentCount()[i]) / m_Score[i].size()) * 100.0;
	}

	//将学校成绩情况写入文件School_Score.txt
	std::ofstream ofs;
	ofs.open(SCHOOLSCORE, std::ios::out | std::ios::trunc);

	ofs << "第" << select << "次考试学校成绩情况统计：\t\t参考总人数：" << m_Score[0].size() << "\n";
	ofs << "科目\t\t\t\t\t\t\t语文\t\t数学\t\t英语\t\t物理\t\t化学\t\t政治\n";
	std::string subjects[6] = { "各科分数平均分:","各科分数最低分:","各科分数最高分:","各科不及格人数:","各科优秀人数:","各科优秀率(%):" };
	
	//依次输出各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率
	for (int i = 0; i < 6; i++)
	{
		ofs << subjects[i]<<"\t\t\t\t\t";
		for (int j = 0; j < 6; j++)
		{
			switch (i)
			{
			case 0:
				ofs << s.getAverageScore()[j] << "\t";
				break;
			case 1:
				ofs << s.getLowestScore()[j] << "\t\t";
				break;
			case 2:
				ofs << s.getHighestScore()[j] << "\t\t";
				break;
			case 3:
				ofs << s.getFailCount()[j] << "\t\t";
				break;
			case 4:
				ofs  << s.getExcellentCount()[j] << "\t\t";
				break;
			case 5:
				ofs << s.getExcellentRate()[j] << "\t";
				break;
			default:
				break;
			}
		}
		ofs << "\n";
	}
	ofs.close();
}

//班级成绩情况
void System::Class_Score()
{
	//清空班级容器，避免数据累积
	Class_One.clear();
	Class_Two.clear();
	m_Score.clear();

	//选择考试
	std::cout << "请输入要统计班级成绩情况的考试（1.第一次考试 2.第二次考试）：\n";
	int select = 0;
	std::cin >> select;

	//初始化系统容器(获得全校学生信息)
	Init_Vec(select);

	//同步学生信息到班级容器
	Sync_Vec();

	std::cout << "请选择要统计的班级（1.一班 2.二班）：\n";
	int Class = 0;
	std::cin >> Class;


	//将班级map容器中学生成绩放入m_Score中
	if (Class == 1)	//一班
	{
		for (const auto& ClassOne_Pair : Class_One)			//遍历一班这个容器获得value值
		{
			const std::vector<Student>& StuVec = ClassOne_Pair.second;
			for (const Student& stu : StuVec)				//遍历一班每个学生
				for (int i = 0; i < 6; i++)					//遍历六门科目
					m_Score[i].push_back(stu.v_Score[i]);	//将学生的六门成绩放入成绩容器中
		}
	}
	else			//二班
	{
		for (const auto& ClassTwo_Pair : Class_Two)
		{
			const std::vector<Student>& StuVec = ClassTwo_Pair.second;
			for (const Student& stu : StuVec)
				for (int i = 0; i < 6; i++)
					m_Score[i].push_back(stu.v_Score[i]);
		}
	}

	//创建情况对象(自动调用无参构造清空数据)
	Situation s;

	//计算各项数据并存放到情况对象中
	for (int i = 0; i < 6; i++)			//遍历六门科目
	{
		for (int score : m_Score[i])	//遍历学生个体的成绩
		{
			//计算当前科目总分
			s.setAverageScore()[i] += score;
			//计算最高分
			if (score > s.getHighestScore()[i])
				s.setHighestScore()[i] = score;
			//计算最低分
			if (score < s.getLowestScore()[i])
				s.setLowestScore()[i] = score;
			//计算不及格人数
			if (score < 60)
				s.setFailCount()[i]++;
			//计算优秀人数
			if (score >= 85)
				s.setExcellentCount()[i]++;
		}
	}

	for (int i = 0; i < 6; i++)		//计算各科平均分和优秀率
	{
		//计算各科平均分
		s.setAverageScore()[i] /= m_Score[i].size();

		//计算各科优秀率
		s.setExcellentRate()[i] = (static_cast<double>(s.getExcellentCount()[i]) / m_Score[i].size()) * 100.0;
	}

	//将班级成绩情况写入文件Class_Score.txt
	std::ofstream ofs;
	ofs.open(CLASSSCORE, std::ios::out | std::ios::trunc);

	ofs << "第" << select << "次考试"<<Class<<"班成绩情况统计：\t\t参考总人数：" << m_Score[0].size() << "\n";
	ofs << "科目\t\t\t\t\t\t\t语文\t\t数学\t\t英语\t\t物理\t\t化学\t\t政治\n";
	std::string subjects[6] = { "各科分数平均分:","各科分数最低分:","各科分数最高分:","各科不及格人数:","各科优秀人数:","各科优秀率(%):" };

	//依次输出各科平均分、最低分、最高分、不及格人数、优秀人数、优秀率
	for (int i = 0; i < 6; i++)
	{
		ofs << subjects[i] << "\t\t\t\t\t";
		for (int j = 0; j < 6; j++)
		{
			switch (i)
			{
			case 0:
				ofs << std::fixed << std::setprecision(4) << s.getAverageScore()[j]  << "\t";
				break;
			case 1:
				ofs << s.getLowestScore()[j] << "\t\t";
				break;
			case 2:
				ofs << s.getHighestScore()[j] << "\t\t";
				break;
			case 3:
				ofs << s.getFailCount()[j] << "\t\t";
				break;
			case 4:
				ofs << s.getExcellentCount()[j] << "\t\t";
				break;
			case 5:
				ofs << std::fixed << std::setprecision(4) << s.getExcellentRate()[j]  << "\t";
				break;
			default:
				break;
			}
		}
		ofs << "\n";
	}
	ofs.close();
}

//查询功能(支持学号/姓名模糊查询考试成绩)
void System::Search()
{
	std::cout << "请输入您的查询方式（1.按学号查询 2.按姓名查询）：\n";
	int choice = 0;
	std::cin >> choice;

	if (choice == 1)
		std::cout << "请输入要查询的学号（支持模糊查询）：\n";
	else
		std::cout << "请输入要查询的姓名（支持模糊查询）：\n";

	std::string temp;			//接收查询关键字
	std::cin >> temp;			//用户输入查询关键字


	int index = 1;				//控制第一次输出格式

	//查询到的信息写入文件
	std::ofstream ofs;
	ofs.open(SEARCHRESULT, std::ios::out | std::ios::trunc);

	//文件打开失败处理
	if (!ofs.is_open())
	{
		std::cout << "文件打开失败！\n";
		ofs.close();
		return;
	}

	for (int i = 0; i < 2; i++)		//遍历两次考试
	{
		//初始化容器获取全校学生信息
		Init_Vec(i + 1);				//初始化考试信息(第i+1次考试成绩信息同步)	
		Calculate_Rank(i + 1);		//同步学生学习班级排名和校排名

		//遍历全校学生容器，进行模糊查询
		for (Student& stu : v_Stu)
		{
			if (stu.getId().find(temp) != std::string::npos ||
				stu.getName().find(temp) != std::string::npos)	//模糊查询学号或姓名
			{
				if ((index == 1 && i == 0) || (index == 2 && i == 1))	//控制第一次输出格式
				{
					if (index == 1 && i == 1)
						ofs << "查询成功！查询结果如下：\n";
					ofs << "=====第" << index << "次考试成绩如下======\n";
					ofs << "姓名：\t\t学号：\t\t\t\t语文\t数学\t英语\t物理\t化学\t政治\t总分\t校排名\t班排名\n";
					index++;
				}
				ofs << stu.getName() << "\t\t" << stu.getId() << "\t\t";
				for (int score : stu.v_Score)
				{
					ofs << score << "\t";
				}
				ofs << stu.getSumScore() << "\t" << stu.getSchoolRank() << "\t\t" << stu.getClassRank() << "\n\n\n";
			}
		}
	}

	ofs.close();
}

//缺考名单统计（第一次考试全员参加，第二次考试部分参加，即为缺考）
void System::Absence_List()
{
	//创建两个vector容器存放两次考试的学生
	std::vector<Student> firstExam_Students;
	std::vector<Student> secondExam_Students;

	//初始化第二次考试学生容器
	Init_Vec(2);
	secondExam_Students = v_Stu;		//将第二次考试学生信息存放到容器中

	//初始化第一次考试学生容器
	Init_Vec(1);
	firstExam_Students = v_Stu;			//将第一次考试学生信息存放到容器中

	//遍历第一次考试学生容器，通过与参加第二次考试学生容器对比，找出缺考学生
	for (Student& firstStu : firstExam_Students)
	{
		bool isAbsent = true;		//假设该学生缺考
		for (Student& secondStu : secondExam_Students)
		{
			if (firstStu.getId() == secondStu.getId())	//该学生参加了第二次考试
			{
				isAbsent = false;	//该学生未缺考
				break;
			}
		}
		if (isAbsent)	//该学生缺考，输出缺考信息
		{
			//将缺考学生信息写入文件Absence_List.txt
			std::ofstream ofs;
			ofs.open(ABSENCELIST, std::ios::out | std::ios::app);		 //以追加方式打开文件
			if (!ofs.is_open())
			{
				std::cout << "文件打开失败！\n";
				ofs.close();
				return;
			}
			ofs << "姓名：" << firstStu.getName() << "\t学号：" << firstStu.getId() << "\t班级：" << firstStu.getClass() << "\t缺考科目：全部科目\t分数：0\n";
			ofs.close();
		}
	}
	system("pause");
	system("cls");
}

//挂科名单统计
void System::Fail_List()
{
	//询问查找哪次考试的挂科名单
	std::cout << "请输入要统计挂科名单的考试（1.第一次考试 2.第二次考试）：\n";
	int select = 0;
	std::cin >> select;

	//初始化系统容器，并同步班级容器
	Init_Vec(select);
	Sync_Vec();

	//遍历班级容器，找出挂科学生，并写入文件
	std::ofstream ofs;				//将挂科学生信息写入文件Fail_List.txt
	ofs.open(FAILLIST, std::ios::out | std::ios::app);		 //以追加方式打开文件
	if (!ofs.is_open())
	{
		std::cout << "文件打开失败！\n";
		ofs.close();
		return;
	}

	std::string subject[] = { "语文","数学","英语","物理","化学","政治" }; //科目数组

	ofs << "第" << select << "次考试挂科名单统计如下：\n";
	ofs << "一班挂科名单：\n";
	for (auto& classPair : Class_One)		//遍历一班
	{
		std::vector<Student>& StuVec = classPair.second;//接收value值
		for (Student& stu : StuVec)				//遍历每个学生
		{
			for (int i = 0; i < 6; i++)		//遍历六门科目
			{
				if (stu.v_Score[i] < 60)	//该科目挂科
				{
					ofs << "姓名：" << stu.getName() << "\t学号：" << stu.getId() << "\t班级：" << 
						stu.getClass() << "\t挂科科目：" << subject[i] << "\t分数：" << stu.v_Score[i] << "\n";
				}
			}
		}
	}

	ofs << "\n\n二班挂科名单：\n";

	for (auto& classPair : Class_Two)		//遍历二班
	{
		std::vector<Student>& StuVec = classPair.second;//接收value值
		for (Student& stu : StuVec)				//遍历每个学生
		{
			for (int i = 0; i < 6; i++)		//遍历六门科目
			{
				if (stu.v_Score[i] < 60)	//该科目挂科
				{
					ofs << "姓名：" << stu.getName() << "\t学号：" << stu.getId() << "\t班级：" <<
						stu.getClass() << "\t挂科科目：" << subject[i] << "\t分数：" << stu.v_Score[i] << "\n";
				}
			}
		}
	}

	ofs << "\n\n\n";
	ofs.close();
	system("pause");
	system("cls");
}

//优秀名单统计
void System::Excellent_List()
{
	//询问查找哪次考试的优秀名单
	std::cout << "请输入要统计优秀名单的考试（1.第一次考试 2.第二次考试）：\n";
	int select = 0;
	std::cin >> select;

	//初始化系统容器，并同步班级容器
	Init_Vec(select);
	Sync_Vec();

	//遍历班级容器，找出优秀学生，并写入文件
	std::ofstream ofs;				//将优秀学生信息写入文件Excellent_List.txt
	ofs.open(EXCELLENTLIST, std::ios::out | std::ios::app);		 //以追加方式打开文件
	if (!ofs.is_open())
	{
		std::cout << "文件打开失败！\n";
		ofs.close();
		return;
	}

	std::string subject[] = { "语文","数学","英语","物理","化学","政治" }; //科目数组

	ofs << "第" << select << "次考试优秀名单统计如下：\n";
	ofs << "一班优秀名单：\n";
	for (auto& classPair : Class_One)		//遍历一班
	{
		std::vector<Student>& StuVec = classPair.second;//接收value值
		for (Student& stu : StuVec)				//遍历每个学生
		{
			for (int i = 0; i < 6; i++)		//遍历六门科目
			{
				if (stu.v_Score[i] > 85 )	//该科目优秀
				{
					ofs << "姓名：" << stu.getName() << "\t学号：" << stu.getId() << "\t班级：" <<
						stu.getClass() << "\t优秀科目：" << subject[i] << "\t分数：" << stu.v_Score[i] << "\n";
				}
			}
		}
	}

	ofs << "\n\n二班优秀名单：\n";

	for (auto& classPair : Class_Two)		//遍历二班
	{
		std::vector<Student>& StuVec = classPair.second;//接收value值
		for (Student& stu : StuVec)				//遍历每个学生
		{
			for (int i = 0; i < 6; i++)		//遍历六门科目
			{
				if (stu.v_Score[i] < 60)	//该科目优秀
				{
					ofs << "姓名：" << stu.getName() << "\t学号：" << stu.getId() << "\t班级：" <<
						stu.getClass() << "\t优秀科目：" << subject[i] << "\t分数：" << stu.v_Score[i] << "\n";
				}
			}
		}
	}
	ofs << "\n\n\n";
	ofs.close();
	system("pause");
	system("cls");
}

//成绩进退步情况统计
void System::Progress_List()
{
	//初始化两次考试的学生容器
	std::vector<Student> firstExam_Students;
	std::vector<Student> secondExam_Students;
	//初始化第一次考试学生容器
	Init_Vec(1);
	Calculate_Rank(1);		//计算第一次考试班级排名和学校排名
	firstExam_Students = v_Stu;			//将第一次考试学生信息存放到容器中
	//初始化第二次考试学生容器
	Init_Vec(2);
	Calculate_Rank(2);		//计算第二次考试班级排名和学校排名
	secondExam_Students = v_Stu;		//将第二次考试学生信息存放到容器中
	//将成绩进步和退步的学生信息写入文件Progress_List.txt
	std::ofstream ofs;
	ofs.open(PROGRESSLIST, std::ios::out | std::ios::trunc);		 //以覆盖方式打开文件
	if (!ofs.is_open())
	{
		std::cout << "文件打开失败！\n";
		ofs.close();
		return;
	}
	ofs << "成绩进步名单：\n";
	ofs << "姓名\t\t学号\t\t\t\t第一次考试班级排名\t第二次考试班级排名\t第一次考试学校排名\t"
		<<"第二次考试学校排名\t班级排名变化\t学校排名变化\n";
	for (Student& firstStu : firstExam_Students)
	{
		for (Student& secondStu : secondExam_Students)
		{
			if (firstStu.getId() == secondStu.getId())	//找到同一学生
			{
				if (secondStu.getClassRank() > firstStu.getClassRank()) //班级排名退步
				{
					ofs << secondStu.getName() << "\t" << secondStu.getId()
						<< "\t\t\t" << firstStu.getClassRank() << "\t\t\t" << secondStu.getClassRank()
						<< "\t\t\t\t" << firstStu.getSchoolRank() << "\t\t\t\t" << secondStu.getSchoolRank()
						<< "\t\t\t\t" << (firstStu.getClassRank() - secondStu.getClassRank())
						<< "\t\t\t" << (firstStu.getSchoolRank() - secondStu.getSchoolRank()) << "\n";
				}
				break;
			}
		}
	}
	ofs << "\n\n成绩退步名单：\n";
	ofs << "姓名\t\t学号\t\t\t\t第一次考试班级排名\t第二次考试班级排名\t第一次考试学校排名\t"
		<< "第二次考试学校排名\t班级排名变化\t学校排名变化\n";
	for (Student& firstStu : firstExam_Students)
	{
		for (Student& secondStu : secondExam_Students)
		{
			if (firstStu.getId() == secondStu.getId())	//找到同一学生
			{
				if (secondStu.getClassRank() < firstStu.getClassRank()) //班级排名进步
				{
					ofs << secondStu.getName() << "\t" << secondStu.getId()
						<< "\t\t\t" << firstStu.getClassRank() << "\t\t\t" << secondStu.getClassRank()
						<< "\t\t\t\t" << firstStu.getSchoolRank() << "\t\t\t\t" << secondStu.getSchoolRank()
						<< "\t\t\t\t" << (firstStu.getClassRank() - secondStu.getClassRank())
						<< "\t\t\t" << (firstStu.getSchoolRank() - secondStu.getSchoolRank()) << "\n";
				}
				break;
			}
		}
	}
	ofs << "\n\n\n";
	ofs.close();
}


//析构函数
System::~System()
{

}
