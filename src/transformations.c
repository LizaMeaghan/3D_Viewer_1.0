#include "transformations.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double **getEmptyMatr(int rows, int columns) {
  double **matrix = (double **)malloc(sizeof(double *) * rows);
  for (int i = 0; i < rows; i++) {
    matrix[i] = (double *)calloc(columns, sizeof(double));
  }
  return matrix;
}

double **getTransMatr(axis ax, direction dir, double step) {
  // Choose step depending in modeling size and maybe pass to func later
  double move = step * dir;
  double **matr = getEmptyMatr(TRANSFORM_MATR_SIZE, TRANSFORM_MATR_SIZE);

  matr[0][0] = 1;
  matr[1][1] = 1;
  matr[2][2] = 1;
  matr[3][3] = 1;
  switch (ax) {
    case X:
      matr[0][3] = move;
      break;
    case Y:
      matr[1][3] = move;
      break;
    case Z:
      matr[2][3] = move;
      break;
  }

  return matr;
}

double **getScaleMatr(double *scale, direction dir) {
  double step = 1 + (0.2 * dir) / *scale;
  *scale = *scale + 0.2 * dir;

  double **matr = getEmptyMatr(TRANSFORM_MATR_SIZE, TRANSFORM_MATR_SIZE);

  matr[0][0] = step;
  matr[1][1] = step;
  matr[2][2] = step;
  matr[3][3] = 1;

  return matr;
}

double **getRotMatr(axis ax, direction dir, double degree) {
  double radians = degree * -dir * PI / 180;
  double **matr = getEmptyMatr(TRANSFORM_MATR_SIZE, TRANSFORM_MATR_SIZE);

  switch (ax) {
    case X:
      matr[0][0] = 1;
      matr[3][3] = 1;
      matr[1][1] = cos(radians);
      matr[1][2] = -sin(radians);
      matr[2][1] = sin(radians);
      matr[2][2] = cos(radians);
      break;
    case Y:
      matr[0][0] = cos(radians);
      matr[0][2] = sin(radians);
      matr[1][1] = 1;
      matr[2][0] = -sin(radians);
      matr[2][2] = cos(radians);
      matr[3][3] = 1;
      break;
    case Z:
      matr[0][0] = cos(radians);
      matr[0][1] = -sin(radians);
      matr[1][0] = sin(radians);
      matr[1][1] = cos(radians);
      matr[2][2] = 1;
      matr[3][3] = 1;
      break;
  }

  return matr;
}

void freeMatrice(double **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void freeMatriceInt(int **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

double **calculateNewCoords(double **transform, double **oldCoords) {
  double **res = getEmptyMatr(COORD_MATR_ROWS, COORD_MATR_COLUMNS);

  for (int i = 0; i < TRANSFORM_MATR_SIZE; ++i) {
    for (int j = 0; j < COORD_MATR_COLUMNS; ++j) {
      for (int k = 0; k < TRANSFORM_MATR_SIZE; ++k) {
        res[i][j] += transform[i][k] * oldCoords[k][j];
      }
    }
  }

  return res;
}

void translate(double **vertices, int length, axis ax, direction dir,
               double step) {
  double **trans = getTransMatr(ax, dir, step);
  double **coords = getEmptyMatr(COORD_MATR_ROWS, COORD_MATR_COLUMNS);
  double **res = NULL;

  for (int i = 0; i < length; i++) {
    coords[0][0] = vertices[i][0];
    coords[1][0] = vertices[i][1];
    coords[2][0] = vertices[i][2];
    coords[3][0] = 1;
    res = calculateNewCoords(trans, coords);
    vertices[i][0] = res[0][0];
    vertices[i][1] = res[1][0];
    vertices[i][2] = res[2][0];
    freeMatrice(res, COORD_MATR_ROWS);
  }

  freeMatrice(trans, TRANSFORM_MATR_SIZE);
  freeMatrice(coords, COORD_MATR_ROWS);
}

void scale(double **vertices, int length, double *scale, direction dir) {
  double **trans = getScaleMatr(scale, dir);
  double **coords = getEmptyMatr(COORD_MATR_ROWS, COORD_MATR_COLUMNS);
  double **res = NULL;

  for (int i = 0; i < length; i++) {
    coords[0][0] = vertices[i][0];
    coords[1][0] = vertices[i][1];
    coords[2][0] = vertices[i][2];
    coords[3][0] = 1;
    res = calculateNewCoords(trans, coords);
    vertices[i][0] = res[0][0];
    vertices[i][1] = res[1][0];
    vertices[i][2] = res[2][0];
    freeMatrice(res, COORD_MATR_ROWS);
  }

  freeMatrice(trans, TRANSFORM_MATR_SIZE);
  freeMatrice(coords, COORD_MATR_ROWS);
}

void rotate(double **vertices, int length, axis ax, direction dir,
            double degree) {
  double **trans = getRotMatr(ax, dir, degree);
  double **coords = getEmptyMatr(COORD_MATR_ROWS, COORD_MATR_COLUMNS);
  double **res = NULL;

  for (int i = 0; i < length; i++) {
    coords[0][0] = vertices[i][0];
    coords[1][0] = vertices[i][1];
    coords[2][0] = vertices[i][2];
    coords[3][0] = 1;
    res = calculateNewCoords(trans, coords);
    vertices[i][0] = res[0][0];
    vertices[i][1] = res[1][0];
    vertices[i][2] = res[2][0];
    freeMatrice(res, COORD_MATR_ROWS);
  }

  freeMatrice(trans, TRANSFORM_MATR_SIZE);
  freeMatrice(coords, COORD_MATR_ROWS);
}
