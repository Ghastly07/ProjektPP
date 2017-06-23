#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include <QImage>
#include <QWidget>
#include <QMouseEvent>
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	QSize sizeHint() const { return qImg.size(); }
	QSize minimumSizeHint() const { return qImg.size(); }

	public slots:
	bool reloadImage(cv::Mat matImg);
	void DrawFigure(int, int);
	void DrawAll();
	void DeleteAngle (int, int);
	void DivideSectionCalculate(int);
	void DivideSection();

	private slots:
	void on_actionPoli_triggered();

	void on_actionOpen_triggered();
	void on_actionSave_Image_triggered();
	
    void on_actionPoly_triggered();

    void on_actionDivide_section_triggered();

private:
	void onMouseEvent(const QString &eventName,const QPoint &pos);
	Ui::MainWindow *ui;

protected:
	void mousePressEvent(QMouseEvent *event)override;
	void mouseMoveEvent(QMouseEvent *event)override;
	bool eventFilter(QObject *obj, QEvent *event);
	bool valid;
	QImage qImg;
	cv::Mat matImg;
	cv::Mat tempImg;
};

#endif // MAINWINDOW_H
