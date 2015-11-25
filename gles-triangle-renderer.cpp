#include "gles-triangle-renderer.h"

using Qoet::GLESTriangleRenderer;

GLESTriangleRenderer::GLESTriangleRenderer()
{
	program = NULL;
	rotateAngleZ = 0;
	viewportSize = QSize(0, 0);

	//assuming we don't have C++11 or newer

	currentColor[0] = 1.0f;
	currentColor[1] = 1.0f;
	currentColor[2] = 1.0f;

	vertices[0] = 0.0f; vertices[1] = 0.707f;
	vertices[2] = -0.5; vertices[3] = -0.5f;
	vertices[4] = 0.5f; vertices[5] = -0.5f;

	colors[0] = 1.0f; colors[1] = 0.0f; colors[2] = 0.0f;
	colors[3] = 0.0f; colors[4] = 1.0f; colors[5] = 0.0f;
	colors[6] = 0.0f; colors[7] = 0.0f; colors[8] = 1.0f;
}

GLESTriangleRenderer::~GLESTriangleRenderer()
{
	delete program;
}

void GLESTriangleRenderer::setRotateAngleZ(const float &angle)
{
	rotateAngleZ = angle;
}

float GLESTriangleRenderer::getRotateAngleZ()
{
	return rotateAngleZ;
}

void GLESTriangleRenderer::setViewportSize(const QSize &size)
{
	viewportSize = size;
}

void GLESTriangleRenderer::updateColor()
{
	if (rotateAngleZ < 120) {
		currentColor[0] = rotateAngleZ / 120.0f;
	} else if (rotateAngleZ < 240) {
		currentColor[1] = (rotateAngleZ - 120.0f) / 120.0f;
	} else {
		currentColor[2] = (rotateAngleZ - 240.0f) / 120.0f;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			colors[i * 3 + j] = currentColor[j];
		}
	}
}

void GLESTriangleRenderer::init()
{
	initializeOpenGLFunctions();
	program = new QOpenGLShaderProgram();

	program->addShaderFromSourceCode(QOpenGLShader::Vertex,
									 "attribute highp vec4 verts;\n"
									 "attribute lowp vec4 colors;\n"
									 "varying lowp vec4 color;\n"
									 "uniform highp mat4 matrix;\n"
									 "void main() {\n"
									 "   color = colors;\n"
									 "   gl_Position = matrix * verts;\n"
									 "}\n");
	program->addShaderFromSourceCode(QOpenGLShader::Fragment,
									 "varying lowp vec4 color;\n"
									 "void main() {\n"
									 "   gl_FragColor = color;\n"
									 "}\n");
	program->link();
}

void GLESTriangleRenderer::render()
{
	if (!program) {
		init();
	}

	program->bind();

	int vertsLocation = program->attributeLocation("verts");
	int colorsLocation = program->attributeLocation("colors");
	int matrixUniformLocation = program->uniformLocation("matrix");

	program->enableAttributeArray(vertsLocation);
	program->enableAttributeArray(colorsLocation);

	program->setAttributeArray(vertsLocation, GL_FLOAT, vertices, 2);
	program->setAttributeArray(colorsLocation, GL_FLOAT, colors, 3);

	glViewport(0, 0, viewportSize.width(), viewportSize.height());

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateColor();

	QMatrix4x4 matrix;
	matrix.perspective(45.0f, 1.0f, 0.1f, 10.0f);
	matrix.translate(0.0f, 0.0f, -2.0f);
	matrix.rotate(rotateAngleZ, 0.0f, 1.0f, 0.0f);
	program->setUniformValue(matrixUniformLocation, matrix);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	program->disableAttributeArray(vertsLocation);
	program->disableAttributeArray(colorsLocation);
	program->release();
}
