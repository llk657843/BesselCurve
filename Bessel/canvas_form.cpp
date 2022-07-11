#include "canvas_form.h"
#include "ui_canvas_form.h"
#include "QPainter"
#include "iostream"
CanvasForm::CanvasForm(QWidget* wid):QWidget(wid),ui(new Ui::CanvasFormUI)
{
	OnModifyUI();
}

CanvasForm::~CanvasForm()
{
	delete ui;
}

void CanvasForm::paintEvent(QPaintEvent* paint)
{
	QPainter painter(this);
	
	painter.setPen(QPen(Qt::green, 5,Qt::SolidLine,Qt::RoundCap));
	//绘制bessel曲线
	DrawBesselCurves(painter,points_,30);

	//绘制输入顶点
	painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap));
	DrawPoints(points_.data(), painter, points_.size());
}

void CanvasForm::OnModifyUI()
{
	setFixedSize(480, 360);
	//测试数据
	
	points_.push_back(QPoint(100, 70));
	points_.push_back(QPoint(200, 120));
	points_.push_back(QPoint(300, 60));
	

	/*
	points_.push_back(QPoint(50, 20));
	points_.push_back(QPoint(100,70));
	points_.push_back(QPoint(200, 120));
	points_.push_back(QPoint(300, 60));
	points_.push_back(QPoint(330, 220));
	points_.push_back(QPoint(340, 80));
	*/
}

void CanvasForm::DrawPoints(QPoint* points, QPainter& painter,int size)
{
	painter.drawPoints(points,size);
}

void CanvasForm::DrawLines(QPoint* points,QPainter& painter,int line_size)
{
	painter.drawLines(points, line_size);
}

void CanvasForm::DrawBesselCurves(QPainter& painter, const std::vector<QPoint>& points, int sample_point_cnt)
{
	//画点
	/*auto res = curve_tool_.GetBesselPoints(points,sample_point_cnt);
	DrawPoints(res.data(), painter, res.size());*/

	//画线
	auto lines = curve_tool_.GetBesselLines(points, sample_point_cnt);
	DrawLines(lines.data(),painter, lines.size() / 2);
}

