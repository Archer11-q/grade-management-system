#pragma once
#include<iostream>


class Situation
{
public:
	//构造函数
	Situation()
	{
		averageScore.resize(6, 0.0);
		highestScore.resize(6, 0);
		lowestScore.resize(6, 100);
		failCount.resize(6, 0);
		excellentCount.resize(6, 0);
		excellentRate.resize(6, 0.0);
	}
	//析构函数
	~Situation() {}
	
	//获取各项数据的接口函数
	const std::vector<double>& getAverageScore() const { return averageScore; }
	const std::vector<int>& getHighestScore() const { return highestScore; }
	const std::vector<int>& getLowestScore() const { return lowestScore; }
	const std::vector<int>& getFailCount() const { return failCount; }
	const std::vector<int>& getExcellentCount() const { return excellentCount; }
	const std::vector<double>& getExcellentRate() const { return excellentRate; }

	//设置各项数组的接口函数
	std::vector<double>& setAverageScore() { return averageScore; }
	std::vector<int>& setHighestScore() { return highestScore; }
	std::vector<int>& setLowestScore() { return lowestScore; }
	std::vector<int>& setFailCount() { return failCount; }
	std::vector<int>& setExcellentCount() { return excellentCount; }
	std::vector<double>& setExcellentRate() { return excellentRate; }

private:
	std::vector<double> averageScore;    // 平均分
	std::vector<int> highestScore;		 // 最高分
	std::vector<int> lowestScore;		 // 最低分
	std::vector<int> failCount;          // 不及格学生数
	std::vector<int> excellentCount;     // 优秀学生数
	std::vector<double> excellentRate;   // 优秀率
};

