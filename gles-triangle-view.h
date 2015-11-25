#ifndef QOETTRIANGLE_H
#define QOETTRIANGLE_H

#include <QtQuick/QQuickItem>

#include "gles-triangle-renderer.h"

namespace Qoet {

class GLESTriangleView : public QQuickItem
{
	Q_OBJECT

public:
	GLESTriangleView();
	~GLESTriangleView();

public slots:
	void sync();
	void cleanup();

protected:
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

private slots:
	void handleWindowChanged(QQuickWindow *win);

private:
	void updateView();
	void updateRotateAngleZ(float diff);

private:
	QPoint previousPosition; //storing previous mouse position to calculate diff
	bool isMouseButtonPressed; //rotating only with mouse pressed
	GLESTriangleRenderer *renderer;
};

} //Qoet

#endif // QOETTRIANGLE_H
