#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <vector>
#include <Windows.h>
struct wsp {
	int x;
	int y;
	wsp(int a, int b) { x = a; y = b; }
};
std::vector <std::vector<wsp>> wektorKsztaltow;
std::vector <wsp> wektorTemp;
int count = 0,iwsk, jwsk;;
//float scaleX, scaleY;
int doit = -1;
cv::Mat copy, orginalImg;
bool movePoint = false;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	qApp->installEventFilter(this);
	
	//ui->xposspin->setMinimum(-INT_MAX);
	//ui->xposspin->setMaximum(INT_MAX);
	valid = false;
}

MainWindow::~MainWindow()
{
	delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseMove)
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
		if (doit == 0) {
			
			matImg.copyTo(copy);

			for (int i = 0; i < wektorKsztaltow.size(); i++) {
				for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
					if ((abs(wektorKsztaltow[i][j].x - mouseEvent->pos().x()) < 8) && (abs(wektorKsztaltow[i][j].y - mouseEvent->pos().y()) < 8)) {
						circle(copy, cv::Point(mouseEvent->pos().x(), mouseEvent->pos().y()), 10.0, cv::Scalar(255, 0, 0), 0, 8);
						iwsk = i;
						jwsk = j;
						if (mouseEvent->buttons() == Qt::LeftButton) {
							wektorKsztaltow[iwsk].erase(wektorKsztaltow[iwsk].begin() + jwsk);
							wektorKsztaltow[iwsk].insert(wektorKsztaltow[iwsk].begin() + jwsk, wsp(mouseEvent->pos().x(), mouseEvent->pos().y()));
							DrawAll();
						}
						
						reloadImage(copy);
					}
				}
			}
		}
		
		if ((count != 0) && (doit == 1)) {
			matImg.copyTo(copy);
			if ((abs(wektorTemp[0].x - mouseEvent->pos().x()) < 8) && (abs(wektorTemp[0].y - mouseEvent->pos().y()) < 8)) {
				circle(copy, cv::Point(mouseEvent->pos().x(), mouseEvent->pos().y()), 10.0, cv::Scalar(255, 0, 0), 0, 8);
			}

			cv::line(copy, cv::Point(wektorTemp[count - 1].x, wektorTemp[count - 1].y), cv::Point(mouseEvent->pos().x(), mouseEvent->pos().y()), cv::Scalar(255, 0, 0), 1, 8);
			reloadImage(copy);
		}
		statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
	
		
	}
	return false;
}

void MainWindow::DeleteAngle(int x, int y) {
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		if ((wektorKsztaltow[i].size() == 1)) {
			wektorKsztaltow.erase(wektorKsztaltow.begin() + i);
			DrawAll();
		}
		else {
			for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
				if ((abs(wektorKsztaltow[i][j].x - x) < 5) && (abs(wektorKsztaltow[i][j].y - y) < 5)) {
					wektorKsztaltow[i].erase(wektorKsztaltow[i].begin() + j);
					DrawAll();
				}
			}

		}
	}
}
void MainWindow::DrawFigure(int x, int y) {

	if (count == 0) {
		wektorTemp.push_back(wsp(x, y));
		circle(matImg, cv::Point(x, y), 3.0, cv::Scalar(255, 0, 0), -1, 8);
	}
	if (count > 0) {

		if ((abs(wektorTemp[0].x - x) < 8) && (abs(wektorTemp[0].y - y) < 8)) {
			cv::line(matImg, cv::Point(wektorTemp[count - 1].x, wektorTemp[count - 1].y), cv::Point(wektorTemp[0].x, wektorTemp[0].y), cv::Scalar(255, 0, 0), 1, 8);
			reloadImage(matImg);
			wektorKsztaltow.push_back(wektorTemp);//przepisz();
			wektorTemp.clear();
			count = -1;
			doit = 0;
		}
		else {
			wektorTemp.push_back(wsp(x, y));
			circle(matImg, cv::Point(wektorTemp[count].x, wektorTemp[count].y), 3.0, cv::Scalar(255, 0, 0), -1, 8);
			cv::line(matImg, cv::Point(wektorTemp[count - 1].x, wektorTemp[count - 1].y), cv::Point(wektorTemp[count].x, wektorTemp[count].y), cv::Scalar(255, 0, 0), 1, 8);
			reloadImage(matImg);
		}
	}
	count++;
}


void MainWindow::on_actionPoli_triggered()
{
	
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
			if (reloadImage(matImg)) {
				qImg = qImg.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
				ui->lbl_image->setPixmap(QPixmap::fromImage(qImg));
			}
			else {
				QMessageBox::information(this, tr("Image conversion problem"), "Couldn't convert image from Mat to QImage.");

			}
		}
		else
		{
			QMessageBox::information(this, tr("Unable to open file"), "Unable to open specified file.");
		}
	}
	reloadImage(matImg);
	matImg.copyTo(orginalImg);
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

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	
	//ui->xposspin->setValue(event->x());
	//onMouseEvent("Move", event->pos());
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{

	
	switch (doit) {
	case 0:
		if (event->button() == Qt::RightButton) {
			DeleteAngle(event->pos().x(), event->pos().y());
		}
		
		break;
	case 1:
		onMouseEvent("Move", event->pos());
		break;
	}
	//ui->xposspin->setValue(event->x());
	
	//onMouseEvent("Move", event->pos());
	//QWidget::mouseMoveEvent(event);
}


void MainWindow::onMouseEvent(const QString &eventName, const QPoint &pos)
{
	ui->xposspin->setValue(10);
	if (doit == 0) {
		
		if (movePoint == false) {
			movePoint = true;
		}
		else {
			movePoint = false;
		}
		
	}

	if (doit == 1) {
		DrawFigure(pos.x(), pos.y());
	}
}


/*
	Zmodyfikowany obraz Mat wrzucacie do matImg i wywo�ujecie funkcje reload.
	Konwertuje obraz z Mata do QImage i wrzuca go do zmiennej qImg.
*/
bool MainWindow::reloadImage(cv::Mat matImg) {
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
	catch (...) {
		return false;
	}
//	scaleX = qImg.width();

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
void MainWindow::on_actionPoly_triggered()
{
	doit = 1;
}

void MainWindow::DrawAll() {

	orginalImg.copyTo(matImg);
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j <= wektorKsztaltow[i].size() - 1; j++) {
			if (j == wektorKsztaltow[i].size() - 1) {
				circle(matImg, cv::Point(wektorKsztaltow[i][j].x, wektorKsztaltow[i][j].y), 3.0, cv::Scalar(255, 0, 0), -1, 8);
				cv::line(matImg, cv::Point(wektorKsztaltow[i][j].x, wektorKsztaltow[i][j].y), cv::Point(wektorKsztaltow[i][0].x, wektorKsztaltow[i][0].y), cv::Scalar(255, 0, 0), 1, 8);

			}
			else {
				circle(matImg, cv::Point(wektorKsztaltow[i][j].x, wektorKsztaltow[i][j].y), 3.0, cv::Scalar(255, 0, 0), -1, 8);
				cv::line(matImg, cv::Point(wektorKsztaltow[i][j].x, wektorKsztaltow[i][j].y), cv::Point(wektorKsztaltow[i][j + 1].x, wektorKsztaltow[i][j + 1].y), cv::Scalar(255, 0, 0), 1, 8);
			}
		}
	}
	reloadImage(matImg);
	//cv::imshow("splash", img);
}
void MainWindow::on_actionDivide_section_triggered()
{
	DivideSection();

}


static int calculatePoint(int x1, int y1, int x2, int y2, int x) {
	float a = (float)(y1 - y2) / (float)(x1 - x2);
	float b = (float)y1 - (float)a*x1;
	return (a * x + b);
}
void MainWindow::DivideSectionCalculate(int pos) {
	int points = 20, j = 20;
	int vectorSize = wektorKsztaltow[pos].size();///-1 !!!!!!!!!!!
												 //std::cout << "   " << vectorSize;
	POINT tabPointUp[50], tabPointDown[50];
	float point = 0;
	float x = 0, y1 = 0, sum = 0, y2 = 0, high = 0;

	int up = 0, down = 0;
	int left = wektorKsztaltow[pos][0].x;
	int right = wektorKsztaltow[pos][0].x;
	for (int i = 1; i < vectorSize; i++) {
		if (left > wektorKsztaltow[pos][i].x) {
			left = wektorKsztaltow[pos][i].x;
			up = i;
		}
		else if (right<wektorKsztaltow[pos][i].x) {
			right = wektorKsztaltow[pos][i].x;
		}
	}
	down = up;

	sum = (float)(right - left) / points;

	x = left + sum;
	std::cout << "   " << sum << "   " << left << "   " << x;
	//ktory jest najbardziej w lewo

	do {

		for (int i = 0; i < vectorSize; i++) {
			if (down == 0) {
				if (x > wektorKsztaltow[pos][vectorSize - 1].x) {
					down--;
					if (down == -1) {
						down = vectorSize - 1;
					}
				}
			}
			else if (x > wektorKsztaltow[pos][down - 1].x) {
				down--;
				if (down == -1) {
					down = vectorSize - 1;
				}
			}

			if (x > wektorKsztaltow[pos][up + 1].x) {
				up++;
				if (up == vectorSize - 1) {
					up = 0;
				}
			}
		}
		if (down == 0) {
			//y1 = calculatePoint(tab[up][0], tab[up][1], tab[up + 1][0], tab[up + 1][1], x);
			//y2 = calculatePoint(tab[down][0], tab[down][1], tab[countAngle - 1][0], tab[countAngle - 1][1], x);
			y1 = calculatePoint(wektorKsztaltow[pos][up].x, wektorKsztaltow[pos][up].y, wektorKsztaltow[pos][up + 1].x, wektorKsztaltow[pos][up + 1].y, x);
			y2 = calculatePoint(wektorKsztaltow[pos][down].x, wektorKsztaltow[pos][down].y, wektorKsztaltow[pos][vectorSize - 1].x, wektorKsztaltow[pos][vectorSize - 1].y, x);
		}
		else if (up == vectorSize - 1) {//vektorsize -1
										//y1 = calculatePoint(tab[up][0], tab[up][1], tab[0][0], tab[0][1], x);
										//y2 = calculatePoint(tab[down][0], tab[down][1], tab[down - 1][0], tab[down - 1][1], x);
			y1 = calculatePoint(wektorKsztaltow[pos][up].x, wektorKsztaltow[pos][up].y, wektorKsztaltow[pos][0].x, wektorKsztaltow[pos][0].y, x);
			y2 = calculatePoint(wektorKsztaltow[pos][down].x, wektorKsztaltow[pos][down].y, wektorKsztaltow[pos][down - 1].x, wektorKsztaltow[pos][down - 1].y, x);
		}
		else {
			//y1 = calculatePoint(tab[up][0], tab[up][1], tab[up + 1][0], tab[up + 1][1], x);
			//y2 = calculatePoint(tab[down][0], tab[down][1], tab[down - 1][0], tab[down - 1][1], x);
			y1 = calculatePoint(wektorKsztaltow[pos][up].x, wektorKsztaltow[pos][up].y, wektorKsztaltow[pos][up + 1].x, wektorKsztaltow[pos][up + 1].y, x);
			y2 = calculatePoint(wektorKsztaltow[pos][down].x, wektorKsztaltow[pos][down].y, wektorKsztaltow[pos][down - 1].x, wektorKsztaltow[pos][down - 1].y, x);

		}

		high = y1 - y2;

		circle(matImg, cv::Point(x, (2 * high / 3) + y2), 3.0, cv::Scalar(0, 255, 0), -1, 8);
		circle(matImg, cv::Point(x, (high / 3) + y2), 3.0, cv::Scalar(0, 255, 255), -1, 8);
		tabPointUp[points].x = x;
		tabPointUp[points].y = (2 * high / 3) + y2;
		tabPointDown[points].x = x;
		tabPointDown[points].y = high / 3 + y2;


		x = x + sum;

		points--;
	} while (points > 1);


	for (j; j != 2; j--) {
		cv::line(matImg, cv::Point(tabPointUp[j].x, tabPointUp[j].y), cv::Point(tabPointUp[j - 1].x, tabPointUp[j - 1].y), cv::Scalar(0, 255, 0), 1, 8);
		cv::line(matImg, cv::Point(tabPointDown[j].x, tabPointDown[j].y), cv::Point(tabPointDown[j - 1].x, tabPointDown[j - 1].y), cv::Scalar(0, 255, 255), 1, 8);
	}
	reloadImage(matImg);
}


void MainWindow::DivideSection() {

	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		DivideSectionCalculate(i);
	}
}