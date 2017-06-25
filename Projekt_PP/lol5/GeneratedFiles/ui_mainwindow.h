/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPoli;
    QAction *actionOpen;
    QAction *actionSave_Annotation;
    QAction *actionSave_Image;
    QAction *actionSave_Distribution;
    QAction *actionSave_Cell_Distribution;
    QAction *actionSave_All;
    QAction *actionSave_State;
    QAction *actionLoad_State;
    QAction *actionCell_Param_Settings;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionZoom_Overview;
    QAction *actionPoly;
    QAction *actionDivide_section;
    QAction *actionReference_Brightness;
    QAction *actionReference_Axis;
    QAction *actionRelative_X0;
    QAction *actionRelative_X100;
    QAction *actionSettings;
    QAction *actionExt_H_Mins_Find_Cells;
    QAction *actionSDA_Find_Cells;
    QAction *actionNegative;
    QAction *actionOption_Window;
    QAction *actionTop_Hat;
    QAction *actionDelete_Vertex;
    QAction *actionColor;
    QWidget *centralWidget;
    QLabel *lbl_image;
    QGroupBox *lbl_mousepos;
    QLabel *label;
    QSpinBox *xposspin;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuZoom;
    QMenu *menuAnnotation;
    QMenu *menuProcess;
    QMenu *menuAbout;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(971, 557);
        MainWindow->setMouseTracking(true);
        MainWindow->setAcceptDrops(true);
        actionPoli = new QAction(MainWindow);
        actionPoli->setObjectName(QStringLiteral("actionPoli"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave_Annotation = new QAction(MainWindow);
        actionSave_Annotation->setObjectName(QStringLiteral("actionSave_Annotation"));
        actionSave_Image = new QAction(MainWindow);
        actionSave_Image->setObjectName(QStringLiteral("actionSave_Image"));
        actionSave_Distribution = new QAction(MainWindow);
        actionSave_Distribution->setObjectName(QStringLiteral("actionSave_Distribution"));
        actionSave_Cell_Distribution = new QAction(MainWindow);
        actionSave_Cell_Distribution->setObjectName(QStringLiteral("actionSave_Cell_Distribution"));
        actionSave_All = new QAction(MainWindow);
        actionSave_All->setObjectName(QStringLiteral("actionSave_All"));
        actionSave_State = new QAction(MainWindow);
        actionSave_State->setObjectName(QStringLiteral("actionSave_State"));
        actionLoad_State = new QAction(MainWindow);
        actionLoad_State->setObjectName(QStringLiteral("actionLoad_State"));
        actionCell_Param_Settings = new QAction(MainWindow);
        actionCell_Param_Settings->setObjectName(QStringLiteral("actionCell_Param_Settings"));
        actionZoom_In = new QAction(MainWindow);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        actionZoom_Out = new QAction(MainWindow);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        actionZoom_Overview = new QAction(MainWindow);
        actionZoom_Overview->setObjectName(QStringLiteral("actionZoom_Overview"));
        actionPoly = new QAction(MainWindow);
        actionPoly->setObjectName(QStringLiteral("actionPoly"));
        actionDivide_section = new QAction(MainWindow);
        actionDivide_section->setObjectName(QStringLiteral("actionDivide_section"));
        actionReference_Brightness = new QAction(MainWindow);
        actionReference_Brightness->setObjectName(QStringLiteral("actionReference_Brightness"));
        actionReference_Axis = new QAction(MainWindow);
        actionReference_Axis->setObjectName(QStringLiteral("actionReference_Axis"));
        actionRelative_X0 = new QAction(MainWindow);
        actionRelative_X0->setObjectName(QStringLiteral("actionRelative_X0"));
        actionRelative_X100 = new QAction(MainWindow);
        actionRelative_X100->setObjectName(QStringLiteral("actionRelative_X100"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionExt_H_Mins_Find_Cells = new QAction(MainWindow);
        actionExt_H_Mins_Find_Cells->setObjectName(QStringLiteral("actionExt_H_Mins_Find_Cells"));
        actionSDA_Find_Cells = new QAction(MainWindow);
        actionSDA_Find_Cells->setObjectName(QStringLiteral("actionSDA_Find_Cells"));
        actionNegative = new QAction(MainWindow);
        actionNegative->setObjectName(QStringLiteral("actionNegative"));
        actionNegative->setCheckable(true);
        actionNegative->setChecked(false);
        actionOption_Window = new QAction(MainWindow);
        actionOption_Window->setObjectName(QStringLiteral("actionOption_Window"));
        actionTop_Hat = new QAction(MainWindow);
        actionTop_Hat->setObjectName(QStringLiteral("actionTop_Hat"));
        actionDelete_Vertex = new QAction(MainWindow);
        actionDelete_Vertex->setObjectName(QStringLiteral("actionDelete_Vertex"));
        actionColor = new QAction(MainWindow);
        actionColor->setObjectName(QStringLiteral("actionColor"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lbl_image = new QLabel(centralWidget);
        lbl_image->setObjectName(QStringLiteral("lbl_image"));
        lbl_image->setGeometry(QRect(0, 0, 400, 400));
        lbl_mousepos = new QGroupBox(centralWidget);
        lbl_mousepos->setObjectName(QStringLiteral("lbl_mousepos"));
        lbl_mousepos->setGeometry(QRect(780, 60, 400, 400));
        label = new QLabel(lbl_mousepos);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 50, 47, 13));
        xposspin = new QSpinBox(lbl_mousepos);
        xposspin->setObjectName(QStringLiteral("xposspin"));
        xposspin->setGeometry(QRect(40, 80, 42, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 971, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuZoom = new QMenu(menuBar);
        menuZoom->setObjectName(QStringLiteral("menuZoom"));
        menuAnnotation = new QMenu(menuBar);
        menuAnnotation->setObjectName(QStringLiteral("menuAnnotation"));
        menuProcess = new QMenu(menuBar);
        menuProcess->setObjectName(QStringLiteral("menuProcess"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuZoom->menuAction());
        menuBar->addAction(menuAnnotation->menuAction());
        menuBar->addAction(menuProcess->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_Annotation);
        menuFile->addAction(actionSave_Image);
        menuFile->addAction(actionSave_Distribution);
        menuFile->addAction(actionSave_Cell_Distribution);
        menuFile->addAction(actionSave_All);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_State);
        menuFile->addAction(actionLoad_State);
        menuFile->addSeparator();
        menuFile->addAction(actionCell_Param_Settings);
        menuZoom->addAction(actionZoom_In);
        menuZoom->addAction(actionZoom_Out);
        menuZoom->addSeparator();
        menuZoom->addAction(actionZoom_Overview);
        menuAnnotation->addAction(actionPoly);
        menuAnnotation->addAction(actionDivide_section);
        menuAnnotation->addSeparator();
        menuAnnotation->addAction(actionReference_Brightness);
        menuAnnotation->addAction(actionReference_Axis);
        menuAnnotation->addAction(actionRelative_X0);
        menuAnnotation->addAction(actionRelative_X100);
        menuAnnotation->addSeparator();
        menuAnnotation->addAction(actionSettings);
        menuProcess->addAction(actionExt_H_Mins_Find_Cells);
        menuProcess->addAction(actionSDA_Find_Cells);
        menuProcess->addAction(actionNegative);
        menuProcess->addAction(actionOption_Window);
        menuProcess->addAction(actionTop_Hat);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionPoli->setText(QApplication::translate("MainWindow", "Poli", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave_Annotation->setText(QApplication::translate("MainWindow", "Save Annotation", 0));
        actionSave_Image->setText(QApplication::translate("MainWindow", "Save Image", 0));
        actionSave_Distribution->setText(QApplication::translate("MainWindow", "Save Distribution", 0));
        actionSave_Cell_Distribution->setText(QApplication::translate("MainWindow", "Save Cell Distribution", 0));
        actionSave_All->setText(QApplication::translate("MainWindow", "Save All", 0));
        actionSave_State->setText(QApplication::translate("MainWindow", "Save State", 0));
        actionLoad_State->setText(QApplication::translate("MainWindow", "Load State", 0));
        actionCell_Param_Settings->setText(QApplication::translate("MainWindow", "Cell Param Settings", 0));
        actionZoom_In->setText(QApplication::translate("MainWindow", "Zoom In", 0));
        actionZoom_Out->setText(QApplication::translate("MainWindow", "Zoom Out", 0));
        actionZoom_Overview->setText(QApplication::translate("MainWindow", "Zoom Overview", 0));
        actionPoly->setText(QApplication::translate("MainWindow", "Poly", 0));
        actionDivide_section->setText(QApplication::translate("MainWindow", "Divide section", 0));
        actionReference_Brightness->setText(QApplication::translate("MainWindow", "Reference Brightness", 0));
        actionReference_Axis->setText(QApplication::translate("MainWindow", "Reference Axis", 0));
        actionRelative_X0->setText(QApplication::translate("MainWindow", "Relative X0", 0));
        actionRelative_X100->setText(QApplication::translate("MainWindow", "Relative X100", 0));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0));
        actionExt_H_Mins_Find_Cells->setText(QApplication::translate("MainWindow", "Ext-H-Mins Find Cells", 0));
        actionSDA_Find_Cells->setText(QApplication::translate("MainWindow", "SDA Find Cells", 0));
        actionNegative->setText(QApplication::translate("MainWindow", "Negative", 0));
        actionOption_Window->setText(QApplication::translate("MainWindow", "Option Window", 0));
        actionTop_Hat->setText(QApplication::translate("MainWindow", "Top-Hat", 0));
        actionDelete_Vertex->setText(QApplication::translate("MainWindow", "Delete_Vertex", 0));
        actionColor->setText(QApplication::translate("MainWindow", "color", 0));
        lbl_image->setText(QString());
        lbl_mousepos->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        label->setText(QApplication::translate("MainWindow", "X= Y=", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuZoom->setTitle(QApplication::translate("MainWindow", "Zoom", 0));
        menuAnnotation->setTitle(QApplication::translate("MainWindow", "Annotation", 0));
        menuProcess->setTitle(QApplication::translate("MainWindow", "Process", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
