#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions> 
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "model.h"
#include "modelstate.h"

class ModelGeomerty : protected QOpenGLFunctions
{
public:

    ModelGeomerty(const QVariant& state);

    //ModelGeomerty(qreal linearSpeed, QVector3D linearMove, QVector3D beginPos, QVector3D color, const QString& modelPath, bool modelNormalized,const QString& texturePath = QString());

    virtual ~ModelGeomerty();

    void drawGeometry(const QMatrix4x4& projection, const QMatrix4x4& worldMatrix, QVector3D lightPos, const QMatrix3x3 &normalMatrix);

    QVariant getState() const;

private:
    void initGeometry();
	void initTextures(const QString& texturePath);
    void initShaders();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
	QOpenGLVertexArrayObject vao;

    ModelState m_state;

//	qreal m_linearSpeed;
//	QVector3D m_linearMove;
//	QVector3D m_beginPos;
//	QVector3D m_translate;
//	QVector3D m_color;


	QOpenGLTexture* m_texture;
	unsigned int currentTextureIndex;

    QOpenGLShaderProgram program;
	
	Model model;

	static unsigned int textureCounter;

};

#endif // GEOMETRYENGINE_H
