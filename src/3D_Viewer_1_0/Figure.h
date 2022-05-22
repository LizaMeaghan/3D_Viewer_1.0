#ifndef FIGURE_H
#define FIGURE_H

extern "C" {
#include "../parse.h"
#include "../transformations.h"
}

class Figure {
  Data data;

 public:
  Figure() {}
  explicit Figure(Data data) { this->data = data; }

  void free_figure(){ destroyData(this->data); }
  double **getVerticeArr() { return this->data.vertices; }
  int getVerticeRows() { return this->data.vertexRows; }
  int **getFacesArr() { return this->data.faces; }
  int getFacesRows() { return this->data.faceRows; }
  double *getScale() { return &(this->data.scale); }
  int *getVerticesInFace() { return this->data.verticesInFace; }
};

#endif  // FIGURE_H
