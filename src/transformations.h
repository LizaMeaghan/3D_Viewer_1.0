#ifndef SRC_TRANSFORMATIONS_H_
#define SRC_TRANSFORMATIONS_H_

#define COORD_MATR_ROWS 4
#define COORD_MATR_COLUMNS 1
#define TRANSFORM_MATR_SIZE 4
#define PI 3.14159265358979323846

typedef enum { X, Y, Z } axis;
typedef enum { POSITIVE = 1, NEGATIVE = -1 } direction;

void translate(double **vertices, int length, axis ax, direction dir,
               double step);
void scale(double **vertices, int length, double *scale, direction dir);
void rotate(double **vertices, int length, axis ax, direction dir,
            double degree);

double **getEmptyMatr(int rows, int columns);
double **getTransMatr(axis ax, direction dir, double step);
double **getScaleMatr(double *scale, direction dir);
double **getRotMatr(axis ax, direction dir, double degree);
void freeMatrice(double **matrix, int rows);
void freeMatriceInt(int **matrix, int rows);
double **calculateNewCoords(double **oldCoords, double **transform);

#endif  // SRC_TRANSFORMATIONS_H_
