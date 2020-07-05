//
// Created by david on 7/5/2020.
//

#ifndef HOME_ENV_IOT_DASHBOARD_OGL_WIDGET_HPP
#define HOME_ENV_IOT_DASHBOARD_OGL_WIDGET_HPP

#include <QWidget>
#include <QOpenGLWidget>
#include <gl/GLU.h>
#include <gl/GL.h>


class OGLWidget : public QOpenGLWidget {
public:
    explicit OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget() override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};


#endif //HOME_ENV_IOT_DASHBOARD_OGL_WIDGET_HPP
