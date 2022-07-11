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
	依据bessel曲线公式：
Point(t) = sigma(i=0 to n)[ Point(i) * B(i,n,t),t>=0 && t<=1]
其中B(i,n,t) = combination(i,n)*(t^i)*(1-t)^(n-i)
公式参数解释:
n为贝塞尔曲线的阶数
贝塞尔曲线阶数 = 你需要计算的Point的数量（入参pts_vec） - 1
i>=0 && i<=n
i为遍历层数
t>=0 && t<=1
t是一个采样百分比，他表示在向量的(t*100.0)%处进行一次曲线采样计算，理论上采样的精度越高，曲线越平滑，但由于绘制原因，并不绝对会画的更平滑
t的采样率由参数sample_point_cnt决定，sample_point_cnt为10表示进行(10 + 1)次采样，分别取(t = 0,t= 0.1,t=0.2,t=0.3...t = 1.0)
	*/


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