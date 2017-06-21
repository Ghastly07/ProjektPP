#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <vector>
struct wsp {
	int x;
	int y;
	wsp(int a, int b) { x = a; y = b; }
};
std::vector <std::vector<wsp>> wektorKsztaltow;
std::vector <wsp> wektorTemp;
int count = 0;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//ui->xposspin->setMinimum(-INT_MAX);
	ui->xposspin->setMaximum(INT_MAX);
	valid = false;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::DrawFigure(int x, int y) {

	if (count == 0) {
		wektorTemp.push_back(wsp(x, y));
		circle(matImg, cv::Point(x, y), 3.0, cv::Scalar(255, 0, 0), -1, 8);
	}
	if (count > 0) {

		if ((abs(wektorTemp[0].x - x) < 8) && (abs(wektorTemp[0].y - y) < 8)) {
			cv::line(matImg, cv::Point(wektorTemp[count - 1].x, wektorTemp[count - 1].y), cv::Point(wektorTemp[0].x, wektorTemp[0].y), cv::Scalar(255, 0, 0), 1, 8);
			//imshow("splash", img);
			reloadImage();
			wektorKsztaltow.push_back(wektorTemp);//przepisz();
			wektorTemp.clear();
			count = -1;
		//	isPoli = false;
		}
		else {
			wektorTemp.push_back(wsp(x, y));
			circle(matImg, cv::Point(wektorTemp[count].x, wektorTemp[count].y), 3.0, cv::Scalar(255, 0, 0), -1, 8);
			cv::line(matImg, cv::Point(wektorTemp[count - 1].x, wektorTemp[count - 1].y), cv::Point(wektorTemp[count].x, wektorTemp[count].y), cv::Scalar(255, 0, 0), 1, 8);
			cv::imshow("splash", matImg);
			reloadImage();
		}
	}
	count++;
}


void MainWindow::on_actionPoli_triggered()
{

	//cv::setMouseCallback("MainWindow", onMouse, 0);
	//ui->mousepos->setText(QString("X =%1, Y = %2").arg(x).arg(y));
}

void MainWindow::on_actionOpen_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("All files (*.*);;JPEG (*.jpg *.jpeg);;BMP (*.bmp);;PNG (*.png);;TIFF (*.tif)"));

	std::string filenameString = filename.toLocal8Bit().constData();

	if (QString::compare(filename, QString()) != 0) {

		try {
			matImg = cv::imread(filenameString);
			valid = true;
		}

		catch (cv::Exception &ex) {
			valid = false;
		}

		if (valid) {
			if (reloadImage())
				;
			else {
				QMessageBox::information(this, tr("Image conversion problem"), "Couldn't convert image from Mat to QImage.");

			}
		}
		else
		{
			QMessageBox::information(this, tr("Unable to open file"), "Unable to open specified file.");
		}
	}
}

void MainWindow::on_actionSave_Image_triggered()
{
	if (valid) {
		QString extension;

		QString fileName = QFileDialog::getSaveFileName
		(this,
		tr("Save File"),
		"",
		tr(".bmp;; .jpeg;; .jpg;; .png;; .tiff"),
		&extension);

		fileName += extension;

		std::string fileNameString = fileName.toLocal8Bit().constData();
		cv::imwrite(fileNameString, matImg);
	}
	else {
		QMessageBox::information(this, tr("Unable to open file"), "You must first open the image.");
	}
}
void MainWindow::mousePressEvent(QMouseEvent * event)
{

	//	ui->xposspin->setValue(event->x());
	
	onMouseEvent("Move", event->pos());
	QWidget::mouseMoveEvent(event);
}

void MainWindow::onMouseEvent(const QString &eventName, const QPoint &pos)
{
	DrawFigure(pos.x(), pos.y());
	ui->xposspin->setValue(pos.x());

}


/*
	Zmodyfikowany obraz Mat wrzucacie do matImg i wywo�ujecie funkcje reload.
	Konwertuje obraz z Mata do QImage i wrzuca go do zmiennej qImg.
*/
bool MainWindow::reloadImage() {
	// Convert the image to the RGB888 format
	switch (matImg.type()) {
		case CV_8UC1:
			cvtColor(matImg, tempImg, CV_GRAY2RGB);
			break;
		case CV_8UC3:
			cvtColor(matImg, tempImg, CV_BGR2RGB);
			break;
	}

	// QImage needs the data to be stored continuously in memory
	assert(tempImg.isContinuous());
	// Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
	// (http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6) is 3*width because each pixel
	// has three bytes.
	try {
		qImg = QImage(tempImg.data, tempImg.cols, tempImg.rows, tempImg.cols * 3, QImage::Format_RGB888);
	}
	catch(...){
		return false;
	}

	if (qImg.width() <= qImg.height()) {
		qImg = qImg.scaledToHeight(ui->lbl_image->height(), Qt::SmoothTransformation);
		ui->lbl_image->setPixmap(QPixmap::fromImage(qImg));
	}
	else {
		qImg = qImg.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
		ui->lbl_image->setPixmap(QPixmap::fromImage(qImg));
	}
	return true;

}