
#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries1(0),
	geometries2(0),
    //texture(0),
	angularSpeed(0)
{
}

MainWidget::~MainWidget()
{
    
    makeCurrent();
   // delete texture;
    delete geometries1;
	delete geometries2;
    doneCurrent();
}


void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{

    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;


    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();


    qreal acc = diff.length() / 10000.0;


    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();


    angularSpeed += acc;
}

void MainWidget::timerEvent(QTimerEvent *)
{	    
    angularSpeed *= 0.99;

 
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
 
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;        
    }


	update();
}


void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    //initTextures();


    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);


	geometries1 = new GeometryEngine(0.001f, { 1,1,-2 }, { 0.0,0.0,-5.0 }, { 0.39f, 1.0f, 0.0f },":textures/earthmap1k.jpg");

	geometries2 = new GeometryEngine(0.001f, { -1,-1,-2 }, { 1.0,1.0,-5.0 }, { 1.0f, .39f, 0.0f },":textures/moonmap1k.jpg");



    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

	for (QOpenGLShader* shader:program.shaders()) {
		if (shader)
			qDebug() << shader->log();
	}

	qDebug() << program.log();
}


//void MainWidget::initTextures()
//{
//    // Load cube.png image
//    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
//
//    // Set nearest filtering mode for texture minification
//    texture->setMinificationFilter(QOpenGLTexture::Nearest);
//
//    // Set bilinear filtering mode for texture magnification
//    texture->setMagnificationFilter(QOpenGLTexture::Linear);
//
//    // Wrap texture coordinates by repeating
//    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
//    texture->setWrapMode(QOpenGLTexture::Repeat);
//}

void MainWidget::resizeGL(int w, int h)
{
	
	qreal aspect = qreal(w) / qreal(h ? h : 1);


	const qreal zNear = 3.0, zFar = 7.0, fov = 45;


	projection.setToIdentity();


	projection.perspective(fov, aspect, zNear, zFar);
}


void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //texture->bind();


	QMatrix4x4 worldMatrix;

	worldMatrix.rotate(rotation);

	program.setUniformValue("projMatrix", projection);
	program.setUniformValue("worldMatrix", worldMatrix);
	program.setUniformValue("lightPos", QVector3D(0, 0, 2));

	program.setUniformValue("normalMatrix", worldMatrix.normalMatrix());

    // Draw cube geometry
    geometries1->drawGeometry(&program);
	geometries2->drawGeometry(&program);
}
