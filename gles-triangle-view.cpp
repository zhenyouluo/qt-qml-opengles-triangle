#include "gles-triangle-view.h"

#include <QtQuick/QQuickWindow>
#include <QDebug>

using Qoet::GLESTriangleView;

GLESTriangleView::GLESTriangleView()
{
	renderer = NULL;
	isMouseButtonPressed = false;

	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::AllButtons);
	setFlag(ItemAcceptsInputMethod, true);

	connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

GLESTriangleView::~GLESTriangleView()
{
	delete renderer;
}

void GLESTriangleView::sync()
{
	if (!renderer) {
		renderer = new Qoet::GLESTriangleRenderer();
		connect(window(), SIGNAL(beforeRendering()), renderer, SLOT(render()), Qt::DirectConnection);
	}
	renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
}

void GLESTriangleView::cleanup()
{
	if (renderer) {
		delete renderer;
		renderer = NULL;
	}
}

void GLESTriangleView::handleWindowChanged(QQuickWindow *wnd)
{
	if (wnd) {
		connect(wnd, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
		connect(wnd, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
		wnd->setClearBeforeRendering(false);
	}
}

void GLESTriangleView::mousePressEvent(QMouseEvent *event)
{
	QQuickItem::mousePressEvent(event);
	qDebug() << "mousePressEvent";
	if (event->buttons() == Qt::LeftButton) {
		previousPosition = event->pos();
		isMouseButtonPressed = true;
		event->accept();
	}
}

void GLESTriangleView::mouseReleaseEvent(QMouseEvent *event)
{
	QQuickItem::mouseReleaseEvent(event);
	qDebug() << "mouseReleaseEvent";
	if (event->buttons() == Qt::LeftButton) {
		isMouseButtonPressed = false;
		event->accept();
	}
}

void GLESTriangleView::mouseMoveEvent(QMouseEvent *event)
{
	QQuickItem::mouseMoveEvent(event);
	//qDebug() << "mouseMoveEvent";
	if (isMouseButtonPressed) {
		QPoint cp = event->pos();
		int cx = cp.x();
		int px = previousPosition.x();

		//qDebug() << (cx - px);
		updateRotateAngleZ(cx - px);
		updateView();

		previousPosition = cp;
	}
}

void GLESTriangleView::updateView()
{
	renderer->render();
	if (window()) {
		window()->update();
	}
}

/**
 * @brief GLESTriangleView::updateRotateAngleZ
 * Keeping angle between 0 and 360 degrees to calculate
 * colours correctly and avoid overflow
 * @param diff
 */
void GLESTriangleView::updateRotateAngleZ(float diff)
{
	float angle = renderer->getRotateAngleZ();
	angle += diff;
	if (angle >= 360) {
		angle -= 360;
	} else if (angle < 0) {
		angle = 360 - angle;
	}
	renderer->setRotateAngleZ(angle);
}
