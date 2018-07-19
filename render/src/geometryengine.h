#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions> 
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "model.h"

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine(qreal linearSpeed, QVector3D linearMove, QVector3D beginPos, QVector3D color,const QString& texturePath = QString());
    virtual ~GeometryEngine();

    void drawGeometry(QOpenGLShaderProgram *program);

private:
    void initGeometry();
	void initTextures(const QString& texturePath);

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
	QOpenGLVertexArrayObject vao;

	qreal m_linearSpeed;
	QVector3D m_linearMove;
	QVector3D m_beginPos;
	QVector3D m_translate;
	QVector3D m_color;
	QOpenGLTexture* m_texture;
	unsigned int currentTextureIndex;
	
	Model model;

	static unsigned int textureCounter;

};

#endif // GEOMETRYENGINE_H
