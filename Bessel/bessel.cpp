#include "bessel.h"
#include "iostream"
int64_t BesselCurve::Combination(const CombineParam& param)
{
	int64_t up = param.up;
	int64_t down = param.down;
	if (up > down / 2)
	{
		up = down - up;
	}
	int64_t a = 1, b = 1;
	for (int i = 1; i <= up; i++)
	{
		a *= down + 1 - i;
		b *= i;
		if (a % b == 0)
		{
			a /= b;
			b = 1;
		}
	}
	return a / b;
}

std::vector<QPoint> BesselCurve::GetBesselPoints(const std::vector<QPoint>& points, int sample_point_cnt)
{
	if (!CheckDataValid(points, sample_point_cnt))
	{
		return std::vector<QPoint>();
	}
	int bessel_n = points.size() - 1;
	std::vector<QPoint> results;
	
	for (int index = 0; index <= sample_point_cnt; index++)
	{
		double t_ratio = (index / 100.0) * (100.0 / sample_point_cnt);
		QPoint new_ptr;
		for (int i = 0; i < points.size(); i++)
		{
			new_ptr += points[i] * GetB_i_n(t_ratio, i, bessel_n);
		}
		results.push_back(new_ptr);
	}
	return results;
}

std::vector<QPoint> BesselCurve::GetBesselLines(const std::vector<QPoint>& pts_vec, int sample_point_cnt)
{
	std::vector<QPoint> line_res;
	auto points = GetBesselPoints(pts_vec,sample_point_cnt);
	if (points.empty()) 
	{
		return line_res;
	}
	for (int i = 1; i < points.size(); i++)
	{
		line_res.push_back(points[i - 1]);
		line_res.push_back(points[i]);
	}
	return line_res;
}

bool BesselCurve::CheckDataValid(const std::vector<QPoint>& pts_vec, int sample_point_cnt)
{
	if (sample_point_cnt == 0)
	{
		std::cout << "Error.Sample count can't be zero" << std::endl;
		return false;
	}

	if (pts_vec.size() < 2)
	{
		std::cout << "Error.Point count num is not enough" << std::endl;
		return false;
	}
	if (sample_point_cnt < pts_vec.size() + 1)
	{
		std::cout << "Error,sample point cnt is not enough" << std::endl;
		return false;
	}
	return true;
}

double BesselCurve::GetB_i_n(double t, int i, int bessel_n)
{
	CombineParam param;
	param.down = bessel_n;
	param.up = i;
	return Combination(param) * pow(t, i) * pow(1 - t, bessel_n - i);
}