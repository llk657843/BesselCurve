#pragma once
#include "QWidget"
#include "vector"
#include "QPoint"
#include "bessel.h"
namespace Ui 
{
	class CanvasFormUI;
}
class CanvasForm : public QWidget 
{
	Q_OBJECT
public:
	CanvasForm(QWidget* wid = nullptr);
	~CanvasForm();

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

函数参数解释
Painter为paintEvent中的绘笔
std::vector<QPoint>为需要进行bessel曲线绘制的点，点的数量大于2，太大的数未经测试，如需传入大数，需要自行对计算流程进行优化，此处提供一个优化点，可以转到math.h
sample_point_cnt为绘制精度，也可以叫绘制采样率，一条曲线上插值(sample_point_cnt + 1)个点，对这些点绘制直线，得到最终曲线，默认为10，采样率最低不要低于pts_vec.size()。
*/
	void DrawBesselCurves(QPainter&, const std::vector<QPoint>& pts_vec, int sample_point_cnt = 10);


protected:
	void paintEvent(QPaintEvent* paint) override;

private:
	void OnModifyUI();
	void DrawPoints(QPoint* points,QPainter& painter,int size);
	void DrawLines(QPoint*,QPainter& painter,int line_size);



private:
	Ui::CanvasFormUI* ui;
	std::vector<QPoint> points_;
	BesselCurve curve_tool_;	//核心计算方法放置在这个类中
};