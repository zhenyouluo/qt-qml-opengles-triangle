#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "gles-triangle-view.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<Qoet::GLESTriangleView>("QOETDemo", 1, 0, "GLESTriangleView");

	QQuickView view;
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:///qml-ui/main.qml"));
	view.show();

	return app.exec();
}
