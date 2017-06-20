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
	bool reloadImage();
	void DrawFigure(int, int);

	private slots:
	void on_actionPoli_triggered();

	void on_actionOpen_triggered();
	void on_actionSave_Image_triggered();
	
private:
	void onMouseEvent(const QString &eventName,const QPoint &pos);
	Ui::MainWindow *ui;

protected:
	void mousePressEvent(QMouseEvent *event)override;
	bool valid;
	QImage qImg;
	cv::Mat matImg;
	cv::Mat tempImg;
};

#endif // MAINWINDOW_H
