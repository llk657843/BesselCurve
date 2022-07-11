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

������������
PainterΪpaintEvent�еĻ��
std::vector<QPoint>Ϊ��Ҫ����bessel���߻��Ƶĵ㣬�����������2��̫�����δ�����ԣ����贫���������Ҫ���жԼ������̽����Ż����˴��ṩһ���Ż��㣬����ת��math.h
sample_point_cntΪ���ƾ��ȣ�Ҳ���Խл��Ʋ����ʣ�һ�������ϲ�ֵ(sample_point_cnt + 1)���㣬����Щ�����ֱ�ߣ��õ��������ߣ�Ĭ��Ϊ10����������Ͳ�Ҫ����pts_vec.size()��
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
	BesselCurve curve_tool_;	//���ļ��㷽���������������
};