
#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),    
    angularSpeed(0),
    m_manager("./geometry.json")
{
}

MainWidget::~MainWidget()
{    
    makeCurrent();

    for(auto geom:m_geometries)
        delete geom;

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

    //initShaders();
    //initTextures();



    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);



//    QVariantMap geom1;

//    geom1["linearSpeed"] = 0.001f;
//    geom1["linearMove"] =  "1,1,-2";
//    geom1["currPos"] = "0.0,0.0,-5.0";
//    geom1["color"] = "0.39f,1.0f,0.0f";
//    geom1["modelPath"] = "./models/sphere.obj";
//    geom1["modelNormalized"] = false;
//    geom1["texturePath"] = ":textures/earthmap1k.jpg";
//    geom1["id"] = "sphere_1";

//    QVariantMap geom2;

//    geom2["linearSpeed"] = 0.001f;
//    geom2["linearMove"] = "-1,-1,-2";
//    geom2["currPos"] = "1.0,1.0,-5.0";
//    geom2["color"] = "1.0f,0.39f,0.0f";
//    geom2["modelPath"] = "./models/sphere.obj";
//    geom2["modelNormalized"] = false;
//    geom2["texturePath"] = ":textures/moonmap1k.jpg";
//    geom2["id"] = "sphere_2";


    for(auto model: m_manager.models()){
        m_geometries.push_back(new ModelGeomerty(model));
    }


//    geometries1 = new ModelGeomerty(geom1);
//    geometries2 = new ModelGeomerty(geom2);

    //m_manager.setModels(QList<QVariant>() << geom1 << geom2);

    //m_manager.save();


    timer.start(12, this);
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

	projection.scale(1.5);


	projection.perspective(fov, aspect, zNear, zFar);
}


void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //texture->bind();


	QMatrix4x4 worldMatrix;

	worldMatrix.rotate(rotation);

//	program.setUniformValue("projMatrix", projection);
//	program.setUniformValue("worldMatrix", worldMatrix);
//	program.setUniformValue("lightPos", QVector3D(0, 0, 2));
    //program.setUniformValue("normalMatrix", worldMatrix.normalMatrix());


    for(auto geom:m_geometries)
        geom->drawGeometry(projection,worldMatrix,{0, 0, 2},worldMatrix.normalMatrix());

//    geometries1->drawGeometry(&program);
//	geometries2->drawGeometry(&program);
}
