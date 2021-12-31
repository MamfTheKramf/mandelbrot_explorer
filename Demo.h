#ifndef DEMO_H
#define DEMO_H

#include <QMainWindow>
#include <QFrame>
#include <QtCore>
#include <QLocale>
#include <QTimer>
#include <QMatrix4x4>

#include <iostream>
#include <array>

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>


class MyGLWidget;

class CGMainWindow : public QMainWindow {

	Q_OBJECT

public:

    CGMainWindow (QWidget* parent = 0);

	MyGLWidget* ogl;
};


class MyGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core {

	Q_OBJECT

public:

    MyGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
        setFocusPolicy(Qt::StrongFocus);
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MyGLWidget::updateAnimation);
        timer->start(20);
    }

public slots:
    void updateAnimation();

private:

	void initShader(QOpenGLShaderProgram& shader, std::string const& vertex, std::string const& fragment);
	void initShaders();

	std::pair<GLuint,GLuint> makeVAOfromAttributes(std::vector<QVector3D> const& attributes);

	void drawTriangles(GLuint vao, size_t size);

	void initializeGL();
	void paintGL();
	void resizeGL(int,int);

	void wheelEvent(QWheelEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent* event);

    QMatrix4x4 getScalingMatrix();


    int mouseX,mouseY,button;

    QTimer* timer{nullptr};
    float scaling{1.0f};
    bool increasing{true};

	QOpenGLShaderProgram simpleShader;

	GLuint vboTri, vaoTri;
};

#endif
