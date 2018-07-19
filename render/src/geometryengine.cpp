#include "geometryengine.h"


#include <QVector2D>
#include <QVector3D>


// 

unsigned int GeometryEngine::textureCounter = 0;

GeometryEngine::GeometryEngine(qreal linearSpeed, QVector3D linearMove, QVector3D beginPos,QVector3D color,const QString& texturePath):
	m_linearSpeed(linearSpeed),m_linearMove(linearMove),m_beginPos(beginPos),m_translate(beginPos),m_color(color),
	model("./models/sphere.obj",true,false)
	//model("C:/Users/m.baytel/Dropbox/education/opengl/render/pokeball.obj")
	//model("C:/Users/m.baytel/Dropbox/education/opengl/render/sphere1.obj",false,true)
	,indexBuf(QOpenGLBuffer::IndexBuffer), m_texture(0), currentTextureIndex(textureCounter++)
{	

	initializeOpenGLFunctions();

    
	vao.create();	

    indexBuf.create();
	arrayBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();

	initTextures(texturePath);
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

void GeometryEngine::initTextures(const QString& texturePath)
{
	// Load cube.png image
	m_texture = new QOpenGLTexture(QImage(texturePath).mirrored());

	qDebug() << m_texture->width() << m_texture->height();

	// Set nearest filtering mode for texture minification
	//m_texture->setMinificationFilter(QOpenGLTexture::Nearest);

	// Set bilinear filtering mode for texture magnification
	m_texture->setMagnificationFilter(QOpenGLTexture::Linear);

	// Wrap texture coordinates by repeating
	// f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
	m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);

	
}

//! [2]
void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program)
{
	vao.bind();

	m_texture->bind(currentTextureIndex);


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
	program->setUniformValue("texture", currentTextureIndex);


	program->enableAttributeArray("inputNormal");
	program->setAttributeBuffer("inputNormal", GL_FLOAT, 3*sizeof(float), 3, model.getStride()* sizeof(float));

	qDebug() << program->log();


    // Tell OpenGL programmable pipeline how to locate vertex position data
    //int vertexLocation = program->attributeLocation("vertex1");
    program->enableAttributeArray("vertex1");

	qDebug() << glGetError();

	program->setAttributeBuffer("vertex1", GL_FLOAT, 0, 3, model.getStride() * sizeof(float));


	program->enableAttributeArray("textcord");

	qDebug() << glGetError();

	program->setAttributeBuffer("textcord", GL_FLOAT, 6 * sizeof(float), 2, model.getStride() * sizeof(float));

	
	qDebug() << glGetError();
    

	qDebug() << program->log();

    
	glDrawArrays(GL_TRIANGLES, 0, model.getIbo().size());

	qDebug() << glGetError();

	m_texture->release();
	vao.release();

}
