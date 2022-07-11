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
	* ����ֵ�������ϵ�'�㼯',����Ϊ(sample_point_cnt + 1)��������
	*/
	std::vector<QPoint> GetBesselPoints(const std::vector<QPoint>& pts_vec, int sample_point_cnt);
	
	
	/*
	* ����ֵ�������ϵ�'�߶μ�',ÿ2����Ϊһ���߶Σ��ں˷�����������һ����
	*/
	std::vector<QPoint> GetBesselLines(const std::vector<QPoint>& pts_vec, int sample_point_cnt);

private:
	int64_t Combination(const CombineParam& param);//���������C(n,m) ,m up,n down.�˴�������unordered map����ʱ��Ч���Ż�����������С�����û��Ҫ
	double GetB_i_n(double t, int i, int bessel_n);	//t >= 0 && t<=1,i>=0&& i<=n
	bool CheckDataValid(const std::vector<QPoint>& pts_vec, int sample_point_cnt);
};