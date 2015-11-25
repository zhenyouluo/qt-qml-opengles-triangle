#ifndef QOETRENDERER_H
#define QOETRENDERER_H

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

namespace Qoet {

class GLESTriangleRenderer : public QObject, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	GLESTriangleRenderer();
	~GLESTriangleRenderer();

	void setRotateAngleZ(const float &angle);
	float getRotateAngleZ();

	void setViewportSize(const QSize &size);

public slots:
	void render();

private:
	void init();
	void updateColor();

private:
	float rotateAngleZ;
	QSize viewportSize;
	QOpenGLShaderProgram *program; //TODO rename vars

	GLfloat currentColor[3]; //{R, G, B}
	GLfloat vertices[6];
	GLfloat colors[9]; //vertices' colors
};

} //Qoet

#endif // QOETRENDERER_H
