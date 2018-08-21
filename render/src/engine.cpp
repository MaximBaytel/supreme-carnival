#include "engine.h"

Engine::Engine(QOpenGLWidget *glWidget) : QObject(glWidget),mglWidget(glWidget)
{
    timer.start(1000/m_frequency,this);
}

void Engine::timerEvent(QTimerEvent *e)
{
    updateStep();
}

void Engine::updateScene()
{
    updateScene();
    drawScene();
}

void Engine::drawScene()
{

}

void Engine::updateStep()
{

}
