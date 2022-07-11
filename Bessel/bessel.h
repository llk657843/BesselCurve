#pragma once
#include <cstdint>
#include <map>
#include <vector>
#include <QtCore/qpoint.h>

struct CombineParam
{
	int64_t up;
	int64_t down;
};

class BesselCurve 
{
public:
	/*
	* 返回值是曲线上的'点集',数量为(sample_point_cnt + 1)个采样点
	*/
	std::vector<QPoint> GetBesselPoints(const std::vector<QPoint>& pts_vec, int sample_point_cnt);
	
	
	/*
	* 返回值是曲线上的'线段集',每2个点为一个线段，内核方法与上面是一样的
	*/
	std::vector<QPoint> GetBesselLines(const std::vector<QPoint>& pts_vec, int sample_point_cnt);

private:
	int64_t Combination(const CombineParam& param);//计算组合数C(n,m) ,m up,n down.此处可以用unordered map进行时间效率优化，但数据量小的情况没必要
	double GetB_i_n(double t, int i, int bessel_n);	//t >= 0 && t<=1,i>=0&& i<=n
	bool CheckDataValid(const std::vector<QPoint>& pts_vec, int sample_point_cnt);
};