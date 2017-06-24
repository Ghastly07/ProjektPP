#pragma once
#include <QWidget>
#include "ui_settings.h"

class Settings : public QWidget {
	Q_OBJECT

public:
	Settings(QWidget * parent = Q_NULLPTR);
	~Settings();

private:
	Ui::Settings ui;
};
