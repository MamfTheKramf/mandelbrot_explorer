#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVector3D>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <map>
#include <vector>

#include "Demo.h"
#include "Util.h"

#define WIN_WIDTH 1080
#define WIN_HEIGHT 720


CGMainWindow::CGMainWindow (QWidget* parent) : QMainWindow (parent) {
    resize(WIN_WIDTH,WIN_HEIGHT);
	QFrame* f = new QFrame (this);
	f->setFrameStyle(QFrame::Sunken | QFrame::Panel);
	f->setLineWidth(2);
    ogl = new MyGLWidget(f, this);
	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(ogl);
	layout->setMargin(0);
	f->setLayout(layout);
    setCentralWidget(f);
}

void MyGLWidget::updateAnimation() {
    if (mandelbrotScaling >= 2.0) {
        increasing = false;
    } else if (mandelbrotScaling <= -2.0) {
        increasing = true;
    }
    if (increasing) {
        mandelbrotScaling += 0.01f;
    } else {
        mandelbrotScaling -= 0.01f;
    }
    update();
}

void MyGLWidget::initShader(QOpenGLShaderProgram& shader, std::string const& vertex, std::string const& fragment) {
	setlocale(LC_NUMERIC,"C");
	if (!shader.addShaderFromSourceFile(QOpenGLShader::Vertex,   vertex.c_str())) close();
	if (!shader.addShaderFromSourceFile(QOpenGLShader::Fragment, fragment.c_str())) close();
	if (!shader.link()) close();
	if (!shader.bind()) close();
	setlocale(LC_ALL,"");
}

void MyGLWidget::initShaders() {
	initShader(simpleShader, ":/SimpleVertex.glsl", ":/SimpleFragment.glsl");
    initShader(juliaShader, ":/SimpleVertex.glsl", ":/JuliaFragment.glsl");
}

std::pair<GLuint,GLuint> MyGLWidget::makeVAOfromAttributes(std::vector<QVector3D> const& attributes) {
	GLuint vboId;
	glGenBuffers(1,&vboId);
	glBindBuffer(GL_ARRAY_BUFFER,vboId);
	glBufferData(GL_ARRAY_BUFFER,attributes.size()*sizeof(QVector3D),&attributes[0],GL_STATIC_DRAW);
	GLuint vaoId;
	glGenVertexArrays(1,&vaoId);
	glBindVertexArray(vaoId);
	{
        //pixelColor changes from lecture
        constexpr int numAttribs = 2;
        constexpr int stride = numAttribs * sizeof(QVector3D);
		glBindBuffer(GL_ARRAY_BUFFER,vboId);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid const*)(sizeof(QVector3D)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);
	return {vaoId,vboId};
}

void MyGLWidget::drawTriangles(GLuint vao, size_t size) {
	if(size <= 0) return;
    { // draw mandelbrot
        QMatrix4x4 scalingMat{getScalingMatrix(false)};
        QMatrix4x4 translationMat{getTranslationMatrix(false)};
        simpleShader.bind();
        simpleShader.setUniformValue("drawingJulia", false);
        simpleShader.setUniformValue("rhombusColor", QVector3D(1.,1.,1.));
        {
            //rhombusPosition
            simpleShader.setUniformValue("rhombusPosition", QVector3D(juliaC.x(), juliaC.y(), 0));
            simpleShader.setUniformValue("scalar", mandelbrotScaling);
        }

        glBindVertexArray(vao);
        {
            simpleShader.setUniformValue("trafo", translationMat * scalingMat);
            glDrawArrays(GL_TRIANGLES,0,(GLsizei)size);
        }
        glBindVertexArray(0);
    }
    { // draw lulia
        QMatrix4x4 scalingMat{getScalingMatrix(true)};
        QMatrix4x4 translationMat{getTranslationMatrix(true)};
        juliaShader.bind();
        juliaShader.setUniformValue("drawingJulia", true);
        juliaShader.setUniformValue("c", juliaC);
        juliaShader.setUniformValue("trafo", translationMat * scalingMat);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)size);
        glBindVertexArray(0);
    }
}

void MyGLWidget::initializeGL() {
	initializeOpenGLFunctions();
	initShaders();

	auto format = this->format();
	std::cout << "OpenGL version: " << format.majorVersion() << "." << format.minorVersion() << std::endl;

	{
		auto vert = util::genTriangle();
		std::tie(vaoTri,vboTri) = makeVAOfromAttributes(vert);
	}

	glClearColor(0.8f, 0.8f, .8f, 1.0f);
}

void MyGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);
    drawTriangles(vaoTri, 6);
}

void MyGLWidget::resizeGL(int width, int height) {
    glViewport(0,0,width,height);
	update();
}

void MyGLWidget::wheelEvent(QWheelEvent*) {
	update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent* event) {
    mousePressEvent(event);
    //update();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event) {
	button = event->button();
	mouseX = event->x();
	mouseY = event->y();
    QMatrix4x4 scalingMat{getScalingMatrix(false)};
    QMatrix4x4 translationMat{getTranslationMatrix(false)};
    QMatrix4x4 combined = translationMat * scalingMat;
    QVector3D compCoords{pxToCompCoords(mouseX, mouseY)};
    juliaC = combined * compCoords;
    updateTitle();
	update();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent*) {}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
	switch(event->key()) {
        case Qt::Key_Space:
            drawJulia = !drawJulia;
            break;
        case Qt::Key_Up:
            updateTranslation({0.0f, 0.05f, 0.0f});
            break;
        case Qt::Key_Down:
            updateTranslation({0.0f, -0.05f, 0.0f});
            break;
        case Qt::Key_Left:
            updateTranslation({-0.05f, 0.0f, 0.0f});
            break;
        case Qt::Key_Right:
            updateTranslation({0.05f, 0.0f, 0.0f});
            break;
        case Qt::Key_N:
            updateScaling(1.1f);
            break;
        case Qt::Key_M:
            updateScaling(0.9f);
            break;
        default: QWidget::keyPressEvent(event);
	}
    updateTitle();
    update();
}

void MyGLWidget::updateTitle() {
    QString title{ "Active side: " };
    if (drawJulia) {
        title += "Julia";
    } else {
        title += "Mandelbrot";
    }

    title += "    ";
    title += QString::number(juliaC.x()) + " + " + QString::number(juliaC.y()) + "i";
    mainWin->setWindowTitle(title);
}

void MyGLWidget::updateScaling(float change) {
    if (drawJulia) {
        juliaScaling *= change;
    } else {
        mandelbrotScaling *= change;
    }
}

void MyGLWidget::updateTranslation(QVector3D change) {
    if (drawJulia) {
        juliaTranslation += change * juliaScaling;
    } else {
        mandelbrotTranslation += change * mandelbrotScaling;
    }
}

QMatrix4x4 MyGLWidget::getScalingMatrix(bool forJulia) {
    float scaling;
    if (forJulia) {
        scaling = juliaScaling;
    } else {
        scaling = mandelbrotScaling;
    }
    QMatrix4x4 ret;
    ret.scale(scaling);
    return ret;
}

QMatrix4x4 MyGLWidget::getTranslationMatrix(bool forJulia) {
    QVector3D translation;
    if (forJulia) {
        translation = juliaTranslation;
    } else {
        translation = mandelbrotTranslation;
    }
    QMatrix4x4 ret;
    ret.translate(translation);
    return ret;
}

QVector2D MyGLWidget::pxToCompCoords(int x, int y) {
    float ret_x = -2.0 + 6.0 * static_cast<float>(x) / width();
    float ret_y = 1.0 - 4.0 * (static_cast<float>(y) - height() / 4.0) / height();
    return {ret_x, ret_y};
}

int main (int argc, char **argv) {
	QSurfaceFormat glFormat;
	glFormat.setVersion(3,3);
	glFormat.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(glFormat);
	QApplication app(argc, argv);
	CGMainWindow w(nullptr);
	w.show();
	return app.exec();
}
