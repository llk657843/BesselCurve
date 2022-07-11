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
	����bessel���߹�ʽ��
Point(t) = sigma(i=0 to n)[ Point(i) * B(i,n,t),t>=0 && t<=1]
����B(i,n,t) = combination(i,n)*(t^i)*(1-t)^(n-i)
��ʽ��������:
nΪ���������ߵĽ���
���������߽��� = ����Ҫ�����Point�����������pts_vec�� - 1
i>=0 && i<=n
iΪ��������
t>=0 && t<=1
t��һ�������ٷֱȣ�����ʾ��������(t*100.0)%������һ�����߲������㣬�����ϲ����ľ���Խ�ߣ�����Խƽ���������ڻ���ԭ�򣬲������Իử�ĸ�ƽ��
t�Ĳ������ɲ���sample_point_cnt������sample_point_cntΪ10��ʾ����(10 + 1)�β������ֱ�ȡ(t = 0,t= 0.1,t=0.2,t=0.3...t = 1.0)
	*/


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