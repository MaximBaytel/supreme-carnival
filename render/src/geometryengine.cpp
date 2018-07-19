#include "geometryengine.h"


#include <QVector2D>
#include <QVector3D>


// 

GeometryEngine::GeometryEngine(qreal linearSpeed, QVector3D linearMove, QVector3D beginPos,QVector3D color):
	m_linearSpeed(linearSpeed),m_linearMove(linearMove),m_beginPos(beginPos),m_translate(beginPos),m_color(color),
	model("./models/sphere.obj",true,false)
	//model("C:/Users/m.baytel/Dropbox/education/opengl/render/pokeball.obj")
	//model("C:/Users/m.baytel/Dropbox/education/opengl/render/sphere1.obj",false,true)
	,indexBuf(QOpenGLBuffer::IndexBuffer)
{
	initializeOpenGLFunctions();

    
	vao.create();	

    indexBuf.create();
	arrayBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void GeometryEngine::initGeometry()
{
	
	vao.bind();

//! [1]
    // Transfer vertex data to VBO 0
    qDebug() << arrayBuf.bind();
    arrayBuf.allocate(model.getVbo().data(), model.getVbo().size() *  sizeof(float));
	//arrayBuf.allocate(triangle, 24 * sizeof(float));

	qDebug() << glGetError();


    //// Transfer index data to VBO 1
	qDebug() <<  indexBuf.bind();
	indexBuf.allocate(model.getIbo().data(), model.getIbo().size() * sizeof(GLuint));
    //indexBuf.allocate(indices, 3 * sizeof(GLushort));

	qDebug() << glGetError();
}

//! [2]
void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program)
{
	vao.bind();

	m_translate += m_linearMove * m_linearSpeed;

	qDebug() << glGetError();


	QMatrix4x4 mvMatrix;
	mvMatrix.translate(m_translate);
	
	//matrix.scale(30.0f);

	// Set modelview-projection matrix
	program->setUniformValue("mvMatrix", mvMatrix);
	
	//program->setUniformValue("normalMatrix", matrix.normalMatrix());

	program->setUniformValue("lightPos", QVector3D(0, 0, 2));
	program->setUniformValue("baseColor", m_color);



	program->enableAttributeArray("inputNormal");
	program->setAttributeBuffer("inputNormal", GL_FLOAT, 3*sizeof(float), 3, model.getStride()* sizeof(float));

	qDebug() << program->log();


    // Tell OpenGL programmable pipeline how to locate vertex position data
    //int vertexLocation = program->attributeLocation("vertex1");
    program->enableAttributeArray("vertex1");

	qDebug() << glGetError();

	program->setAttributeBuffer("vertex1", GL_FLOAT, 0, 3, model.getStride() * sizeof(float));
	

	qDebug() << glGetError();
    

	qDebug() << program->log();

    
	glDrawArrays(GL_TRIANGLES, 0, model.getIbo().size());

	qDebug() << glGetError();

	vao.release();

}
