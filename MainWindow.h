#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QFormLayout;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	bool loadTranslations(const QString &lang);
	QWidget *createCentralWidget(const QJsonObject &json);
	QFormLayout *createForm(const QJsonArray &fields);
	QJsonObject jsonData();
};

#endif // MAINWINDOW_H
