#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	const QJsonObject &json(jsonData());

	if (!json.isEmpty()
		&& json.contains("language")
		&& loadTranslations(json["language"].toString())) {
		QWidget *widget = createCentralWidget(json);

		if (widget) {
			setWindowTitle(tr("External Translations"));
			setCentralWidget(widget);
			resize(480, 240);
		}
	}
}

bool MainWindow::loadTranslations(const QString &lang)
{
	if (lang == "en")
		return true;

	auto *translator = new QTranslator(this);

	if (!translator->load(QString(":/bin/translations/myapp_%1").arg(lang))
		|| !qApp->installTranslator(translator))
		return false;

	return true;
}

QWidget *MainWindow::createCentralWidget(const QJsonObject &json)
{
	if (!json.contains("title") || !json.contains("fields"))
		return nullptr;

	auto *widget = new QWidget(this);
	auto *layoutMain = new QVBoxLayout(widget);
	auto *labTitle = new QLabel(this);

	labTitle->setText(tr(json["title"].toString().toUtf8().data()));

	layoutMain->addWidget(labTitle);
	layoutMain->addLayout(createForm(json["fields"].toArray()));
	layoutMain->addStretch();

	return widget;
}

QFormLayout *MainWindow::createForm(const QJsonArray &fields)
{
	auto *formLayout = new QFormLayout(this);

	foreach (const QJsonValue &field, fields) {
		const QJsonObject &json(field.toObject());

		if (json.contains("name"))
			formLayout->addRow(tr(json["name"].toString().toUtf8().data()),
							   new QLineEdit(this));
	}

	return formLayout;
}

QJsonObject MainWindow::jsonData()
{
	QFile file(":/txt/data.json");

	if (!file.open(QFile::ReadOnly | QFile::Text))
		return QJsonObject();

	const QJsonObject &json(QJsonDocument::fromJson(file.readAll()).object());

	file.close();

	return json;
}
