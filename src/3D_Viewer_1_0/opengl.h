#ifndef OPENGL_H
#define OPENGL_H

#define CONTINUOUS_LINE 0
#define DASHED_LINE 1
#define CENTRAL 0
#define PARALLEL 1
#define EMPTY_VERTEX 0
#define CIRCLE_VERTEX 1
#define SQUARE_VERTEX 2

#include "Line.h"
#include "Figure.h"
#include "qt_lib_includes.h"
#include <QOpenGLWidget>

namespace Ui {
class OpenGL;
}

class OpenGL : public QOpenGLWidget
{
private:
    Q_OBJECT
    Ui::OpenGL *ui;
    char* filename;
    float xRot, yRot, zRot;
    QPoint mPos;
    Line *lines = NULL;
    int Edge = 0;
    QColor color_lines;
    QColor color_background;
    QColor color_polygon;
    QColor color_vertex;
    int lines_type;
    double lines_width;
    int vertex_type;
    int vertex_size;
    int view_type;
    void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

public:
    explicit OpenGL(QWidget *parent = nullptr);
    ~OpenGL();
    void setfilename(char* filename, int size);
    bool open_flag = false;
    Figure figure;
    int get_edge();
    int get_vertices();

public slots:
    void rotate_(direction dir, axis ax, double deg);
    void scale_(direction dir);
    void translate_(direction dir, axis ax, double step);
    void set_colors(QColor lines, QColor background, QColor polygon, QColor vertex);
    void set_lines_type(int type);
    void set_lines_width(double width);
    void set_vertex_type(int type);
    void set_vertex_size(int size);
    void set_view_type(int type);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void PLOTTER();
};

#endif // OPENGL_H
