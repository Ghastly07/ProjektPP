#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <vector>
//#include <Windows.h>
struct wsp {
	int x;
	int y;
	int b;
	int g;
	int r;
	wsp(int a1, int b1, int k, int h, int j) { x = a1; y = b1; b = k; g = h; r = j;}
};

std::vector <std::vector<wsp>> wektorKsztaltow;
std::vector <wsp> wektorTemp;
std::vector <wsp> vRelativeX0;
std::vector <wsp> vRelativeX100;

int count = 0, iwsk, jwsk, xpos , ypos;
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
	ui->xposspin->setMaximum(INT_MAX);
	valid = false;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent * event)
{
	QMenu *menu = new QMenu();
	//QAction *limpiarAction = new QAction("Limpiar" ,this);
	//connect(limpiarAction, SIGNAL(triggered()), this,SLOT(limpiar()));
	//menu->addAction((limpiarAction));
	//menu->addSeparator();
	menu->addAction(ui->actionDelete_Vertex);
	QMenu *list = new QMenu("Color", this);
	connect(list, SIGNAL(triggered()), this, SLOT(list()));

	QAction *mediumBlueAction = new QAction("Medium Blue" ,this);
	connect(mediumBlueAction, SIGNAL(triggered()), this,SLOT(mediumBlue()));

	QAction *lightBlueAction = new QAction("Light Blue", this);
	connect(lightBlueAction, SIGNAL(triggered()), this, SLOT(lightBlue()));

	QAction *lightRedAction = new QAction("Light Red", this);
	connect(lightRedAction, SIGNAL(triggered()), this, SLOT(lightRed()));
	
	QAction *greenAction = new QAction("Green", this);
	connect(greenAction, SIGNAL(triggered()), this, SLOT(green()));
	
	QAction *yellowAction = new QAction("Yellow", this);
	connect(yellowAction, SIGNAL(triggered()), this, SLOT(yellow()));
	
	QAction *magentaAction = new QAction("Magenta", this);
	connect(magentaAction, SIGNAL(triggered()), this, SLOT(magenta()));

	QAction *cyanAction = new QAction("Cyan", this);
	connect(cyanAction, SIGNAL(triggered()), this, SLOT(cyan()));

	QAction *lightGrayAction = new QAction("Light Gray", this);
	connect(lightGrayAction, SIGNAL(triggered()), this, SLOT(lightGray()));

	QAction *blackAction = new QAction("Black", this);
	connect(blackAction, SIGNAL(triggered()), this, SLOT(black()));

	list->addAction(mediumBlueAction);
	list->addAction(lightBlueAction);
	list->addAction(lightRedAction);
	list->addAction(greenAction);
	list->addAction(yellowAction);
	list->addAction(magentaAction);
	list->addAction(cyanAction);
	list->addAction(lightGrayAction);
	list->addAction(blackAction);
	menu->addMenu(list);
	menu->exec(QCursor::pos());		

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
							wektorKsztaltow[iwsk].insert(wektorKsztaltow[iwsk].begin() + jwsk, wsp(mouseEvent->pos().x(), mouseEvent->pos().y(),255,0,0));
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
void MainWindow::DrawFigure(int x, int y,int b,int g, int r) {

	if (count == 0) {
		wektorTemp.push_back(wsp(x, y,255,0,0));
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
			wektorTemp.push_back(wsp(x, y,255,0,0));
			circle(matImg, cv::Point(wektorTemp[count].x, wektorTemp[count].y), 3.0, cv::Scalar(255, 0, 0), -1, 8);
			cv::line(matImg, cv::Point(wektorTemp[count - 1].x, wektorTemp[count - 1].y), cv::Point(wektorTemp[count].x, wektorTemp[count].y), cv::Scalar(255, 0, 0), 1, 8);
			reloadImage(matImg);
		}
	}
	count++;
}

void MainWindow::DrawRelativePoint(int choice) {
	// Dla 0 rysujemy Relative_X0, dla 100 rysujemy Relative_X100
	switch (choice) {
	case 0:
		circle(matImg, cv::Point(vRelativeX0[0].x, vRelativeX0[0].y), 3.0, cv::Scalar(0, 0, 255), -1, 0);
		reloadImage(matImg);
		doit = -1;
		break;

	case 100:
		circle(matImg, cv::Point(vRelativeX100[0].x, vRelativeX100[0].y), 3.0, cv::Scalar(0, 0, 0), -1, 0);
		reloadImage(matImg);
		doit = -1;
		break;

	default:
		break;
	}
}

void MainWindow::on_actionTop_Hat_triggered() {
	if (matImg.data != NULL) {
		// Trzeba dodać w opcjach możliwość modyfikowania ustawień Top Hat'a

		cv::Mat element = cv::getStructuringElement(morph_elem, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));
		cv::morphologyEx(matImg, matImg, cv::MORPH_TOPHAT, element);
		reloadImage(matImg);
	}
	else {
		QMessageBox::information(this, tr("Error"), "No image loaded!", 0, QFileDialog::DontUseNativeDialog);
	}
}

void MainWindow::on_actionRelative_X0_triggered()
{
	if (matImg.data != NULL) {
		// Sprawdzamy czy relative x0 był już wcześniej zdefiniowany, jeśli tak ...
		if (relativeX0) {
			// to go usuwamy
			vRelativeX0.erase(vRelativeX0.begin());
		}
		doit = 2;
	}
	else {
		QMessageBox::information(this, tr("Error"), "No image loaded!", 0, QFileDialog::DontUseNativeDialog);
	}
}

void MainWindow::on_actionRelative_X100_triggered()
{
	if (matImg.data != NULL) {
		// Sprawdzamy czy relative x100 był już wcześniej zdefiniowany, jeśli tak ...
		if (relativeX100) {
			// to go usuwamy
			vRelativeX100.erase(vRelativeX100.begin());
		}
		doit = 3;
	}
	else {
		QMessageBox::information(this, tr("Error"), "No image loaded!", 0, QFileDialog::DontUseNativeDialog);
	}
}


void MainWindow::on_actionPoli_triggered()
{
	
}

void MainWindow::on_actionOpen_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("All files (*.*);;JPEG (*.jpg *.jpeg);;BMP (*.bmp);;PNG (*.png);;TIFF (*.tif)"), 0, QFileDialog::DontUseNativeDialog);

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
void MainWindow::on_actionSDA_Find_Cells_triggered() {
	//przykladowe wywolanie
	QMessageBox::information(this, tr("SDA"), "Test SDA!");
	cv::Mat dst;
	matImg.convertTo(dst, CV_64F, 1, 0);
	array< double, 2 >^ workCopy = gcnew array<double, 2>(dst.rows, matImg.cols);


	double **ptrDst = new double*[dst.rows];
	for (int i = 0; i < dst.rows; ++i) {
		ptrDst[i] = new double[dst.cols];
		ptrDst[i] = dst.ptr<double>(i);

		for (int j = 0; j < dst.cols; ++j) {

			workCopy[i, j] = ptrDst[i][j];
			//std::cout << std::setw(5) << workCopy[i, j];
		}
		//std::cout << std::endl;
	}

	sda.SDA_disc(workCopy, dst.rows, dst.cols, 40, 0, 50);
	//array< double, 2 >^ SDA::SDA_disc(array< double, 2 >^%mac, int sx, int sy, double r = 40, int mode = 0, int min_roznica = 50)

	for (int i = 0; i < dst.rows; ++i) {
		ptrDst[i] = new double[dst.cols];
		ptrDst[i] = dst.ptr<double>(i);

		for (int j = 0; j < dst.cols; ++j) {

			ptrDst[i][j] = workCopy[i, j];
			//std::cout << workCopy[i, j] << "  ";
			dst.at<double>(i, j);
		}
		//std::cout << std::endl;
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
			&extension, QFileDialog::DontUseNativeDialog);

		fileName += extension;

		std::string fileNameString = fileName.toLocal8Bit().constData();
		cv::imwrite(fileNameString, matImg);
	}
	else {
		QMessageBox::information(this, tr("Unable to open file"), "You must first open the image.", 0, QFileDialog::DontUseNativeDialog);
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

	//ui->xposspin->setValue(event->x());
	//onMouseEvent("Move", event->pos());
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
	xpos = event->pos().x();
	ypos = event->pos().y()-20;
	switch (doit) {
	case 0:
		//if (event->button() == Qt::RightButton) {
		//	DeleteAngle(event->pos().x(), event->pos().y());
		//}

		break;
	case 1:
		onMouseEvent("Move", event->pos());
		break;
	case 2:
		onMouseEvent("RelativeX0", event->pos());
		break;
	case 3:
		onMouseEvent("RelativeX100", event->pos());
		break;
	}
	//ui->xposspin->setValue(ypos);

	//onMouseEvent("Move", event->pos());
	//QWidget::mouseMoveEvent(event);
}


void MainWindow::onMouseEvent(const QString &eventName, const QPoint &pos)
{
	//ui->xposspin->setValue(10);

	switch (doit) {
	case 0:
		if (movePoint == false) {
			movePoint = true;
		}
		else {
			movePoint = false;
		}
		break;

	case 1:
		DrawFigure(pos.x(), pos.y(),255,0,0);
		break;

	case 2:
		vRelativeX0.push_back(wsp(pos.x(), pos.y(),0,0,255));
		if (relativeX0) {
			// jeśli już wcześniej mieliśmy jakiś punkt to musimy przerysować całość
			DrawAll();
		}
		else {
			// jeśli nie, to wystarczy narysować nasz punkt
			relativeX0 = true;
			DrawRelativePoint(0);
		}
		break;

	case 3:
		vRelativeX100.push_back(wsp(pos.x(), pos.y(),255,255,255));
		if (relativeX100) {
			DrawAll();
		}
		else {
			relativeX100 = true;
			DrawRelativePoint(100);
		}
		break;

	default:
		break;
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
	if (matImg.data != NULL)
		doit = 1;
	else
		QMessageBox::information(this, tr("Error"), "No image loaded!", 0, QFileDialog::DontUseNativeDialog);

}

void MainWindow::DrawAll() {

	orginalImg.copyTo(matImg);
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j <= wektorKsztaltow[i].size() - 1; j++) {
			if (j == wektorKsztaltow[i].size() - 1) {
				circle(matImg, cv::Point(wektorKsztaltow[i][j].x, wektorKsztaltow[i][j].y), 3.0, cv::Scalar(wektorKsztaltow[i][j].b, wektorKsztaltow[i][j].g, wektorKsztaltow[i][j].r), -1, 8);
				cv::line(matImg, cv::Point(wektorKsztaltow[i][j].x, wektorKsztaltow[i][j].y), cv::Point(wektorKsztaltow[i][0].x, wektorKsztaltow[i][0].y), cv::Scalar(wektorKsztaltow[i][j].b, wektorKsztaltow[i][j].g, wektorKsztaltow[i][j].r), 1, 8);

			}
			else {
				circle(matImg, cv::Point(wektorKsztaltow[i][j].x, wektorKsztaltow[i][j].y), 3.0, cv::Scalar(wektorKsztaltow[i][j].b, wektorKsztaltow[i][j].g, wektorKsztaltow[i][j].r), -1, 8);
				cv::line(matImg, cv::Point(wektorKsztaltow[i][j].x, wektorKsztaltow[i][j].y), cv::Point(wektorKsztaltow[i][j + 1].x, wektorKsztaltow[i][j + 1].y), cv::Scalar(wektorKsztaltow[i][j].b, wektorKsztaltow[i][j].g, wektorKsztaltow[i][j].r), 1, 8);
			}
		}
	}

	// Sprawdzamy czy trzeba narysować nowe Relativy
	if (relativeX0)
		DrawRelativePoint(0);
	if (relativeX100)
		DrawRelativePoint(100);

	reloadImage(matImg);
	//cv::imshow("splash", img);
}
void MainWindow::on_actionDivide_section_triggered()
{
	DivideSection();

}

void MainWindow::on_actionDelete_Vertex_triggered()
{
	//ui->xposspin->setValue(event->pos().x());
	DeleteAngle(xpos, ypos);
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
void MainWindow::on_actionColor_triggered()
{

}

void MainWindow::mediumBlue()
{

	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 255;
					wektorKsztaltow[i][k].g = 0;
					wektorKsztaltow[i][k].r = 0;
				}
			}
		}
	}
	DrawAll();
}

void MainWindow::lightBlue()
{
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 100;
					wektorKsztaltow[i][k].g = 15;
					wektorKsztaltow[i][k].r = 15;
				}
			}
		}
	}
	DrawAll();
}

void MainWindow::lightRed()
{
	ui->xposspin->setValue(wektorKsztaltow[0][0].y);
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 0;
					wektorKsztaltow[i][k].g = 0;
					wektorKsztaltow[i][k].r = 255;
				}
			}
		}
	}
	DrawAll();
}

void MainWindow::green()
{
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 0;
					wektorKsztaltow[i][k].g = 255;
					wektorKsztaltow[i][k].r = 0;
				}
			}
		}
	}
	DrawAll();
}

void MainWindow::yellow()
{
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 0;
					wektorKsztaltow[i][k].g = 255;
					wektorKsztaltow[i][k].r = 255;
				}
			}
		}
	}
	DrawAll();
}

void MainWindow::magenta()
{
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 214;
					wektorKsztaltow[i][k].g = 112;
					wektorKsztaltow[i][k].r = 218;
				}
			}
		}
	}
	DrawAll();
}

void MainWindow::cyan()
{
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 255;
					wektorKsztaltow[i][k].g = 255;
					wektorKsztaltow[i][k].r = 0;
				}
			}
		}
	}
	DrawAll();
}

void MainWindow::lightGray()
{
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 211;
					wektorKsztaltow[i][k].g = 211;
					wektorKsztaltow[i][k].r = 211;
				}
			}
		}
	}
	DrawAll();
}

void MainWindow::black()
{
	for (int i = 0; i < wektorKsztaltow.size(); i++) {
		for (int j = 0; j < wektorKsztaltow[i].size(); j++) {
			if ((abs(wektorKsztaltow[i][j].x - xpos) < 8) && (abs(wektorKsztaltow[i][j].y - ypos) < 8)) {
				for (int k = 0; k < wektorKsztaltow[i].size(); k++) {
					wektorKsztaltow[i][k].b = 0;
					wektorKsztaltow[i][k].g = 0;
					wektorKsztaltow[i][k].r = 0;
				}
			}
		}
	}
	DrawAll();
}

