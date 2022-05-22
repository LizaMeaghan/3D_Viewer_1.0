#include "opengl.h"

#include "ui_opengl.h"

OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent), ui(new Ui::OpenGL) {
  ui->setupUi(this);
}

void OpenGL::perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear,
                           GLdouble zFar) {
  const GLdouble pi = 3.1415926535897932384626433832795;
  GLdouble fW, fH;
  fH = tan(fovY / 360 * pi) * zNear;
  fW = fH * aspect;
  if (this->view_type == CENTRAL) {
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
  } else {
    glOrtho(-fW, fW, -fH, fH, zNear, zFar);
  }
}

void OpenGL::setfilename(char *filename, int size) {
  if(this->open_flag) figure.free_figure();
  this->filename = (char *)malloc(size * sizeof(char));
  strncpy(this->filename, filename, size);
  this->figure = Figure(getData(this->filename));
  this->open_flag = true;
}

void OpenGL::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(color_background.redF(), color_background.greenF(),
               color_background.blueF(), color_background.alphaF());
}

void OpenGL::resizeGL(int w, int h) {
  glClearColor(color_background.redF(), color_background.greenF(),
               color_background.blueF(), color_background.alphaF());
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  perspectiveGL(70, 1, 10, 100);
}

void OpenGL::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -15);
  PLOTTER();
}

void OpenGL::rotate_(direction dir, axis ax, double deg) {
  rotate(this->figure.getVerticeArr(), this->figure.getVerticeRows(), ax, dir,
         deg);
}

void OpenGL::scale_(direction dir) {
  scale(this->figure.getVerticeArr(), this->figure.getVerticeRows(),
        this->figure.getScale(), dir);
}

void OpenGL::translate_(direction dir, axis ax, double step) {
  translate(this->figure.getVerticeArr(), this->figure.getVerticeRows(), ax,
            dir, step);
}

void OpenGL::PLOTTER() {
  int edgeCounter = 0;
  int maxVerticesInFace = 0;

  double **vertices = figure.getVerticeArr();
  glPointSize(this->vertex_size);

  if (this->vertex_type != EMPTY_VERTEX) {
    if (this->vertex_type == CIRCLE_VERTEX) {
      glEnable(GL_POINT_SMOOTH);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    for (int i = 0; i < figure.getVerticeRows(); i++) {
      glBegin(GL_POINTS);
      glColor3d(color_vertex.redF(), color_vertex.greenF(),
                color_vertex.blueF());
      glVertex3d(vertices[i][0], vertices[i][1], vertices[i][2]);
      glEnd();
    }
  }

     for (int i = 0; i < figure.getFacesRows(); i++) {
       maxVerticesInFace = figure.getVerticesInFace()[i];
       glBegin(GL_POLYGON);
       glColor3d(color_polygon.redF(), color_polygon.greenF(),
                 color_polygon.blueF());
       for (int j = 0; j < maxVerticesInFace; j++) {
         glVertex3d(figure.getVerticeArr()[figure.getFacesArr()[i][j] - 1][0],
                    figure.getVerticeArr()[figure.getFacesArr()[i][j] - 1][1],
                    figure.getVerticeArr()[figure.getFacesArr()[i][j] -
                    1][2]);
       }
       glEnd();
       for (int j = 0; j < maxVerticesInFace; j++) {
         int startInd = figure.getFacesArr()[i][j];
         int endInd = (j == maxVerticesInFace - 1)
                          ? figure.getFacesArr()[i][0]
                          : figure.getFacesArr()[i][j + 1];
         Line line(startInd, endInd);
         if (line.checkLine(&this->lines, edgeCounter, &line)) {
           edgeCounter++;
           glLineWidth(lines_width);
           glEnable(GL_LINE_STIPPLE);
           //
           if (this->lines_type == DASHED_LINE) {
             glLineStipple(1, 0x00FF);
           } else {
             glLineStipple(1, 0xFFFF);
           }
           //
           glBegin(GL_LINES);
           glColor3d(color_lines.redF(), color_lines.greenF(),
                     color_lines.blueF());
           glVertex3d(figure.getVerticeArr()[startInd - 1][0],
                      figure.getVerticeArr()[startInd - 1][1],
                      figure.getVerticeArr()[startInd - 1][2]);
           glVertex3d(figure.getVerticeArr()[endInd - 1][0],
                      figure.getVerticeArr()[endInd - 1][1],
                      figure.getVerticeArr()[endInd - 1][2]);
           glEnd();
         }
       }
     }
  this->Edge = edgeCounter;
}

int OpenGL::get_edge() { return this->Edge; }

int OpenGL::get_vertices() { return this->figure.getVerticeRows(); }

void OpenGL::set_colors(QColor lines, QColor background, QColor polygon, QColor vertex) {
  this->color_lines = lines;
  this->color_background = background;
  this->color_polygon = polygon;
  this->color_vertex = vertex;
}

void OpenGL::set_lines_type(int type) { this->lines_type = type; }

void OpenGL::set_lines_width(double width) { this->lines_width = width; }

void OpenGL::set_vertex_type(int type) { this->vertex_type = type; }

void OpenGL::set_vertex_size(int size) { this->vertex_size = size; }

void OpenGL::set_view_type(int type) { this->view_type = type; }

OpenGL::~OpenGL() {
  if (this->open_flag) free(this->filename);
  if (this->open_flag) this->figure.free_figure();
  delete ui;
}
