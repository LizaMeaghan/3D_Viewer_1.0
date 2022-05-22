#ifndef SRC_PARSE_H_
#define SRC_PARSE_H_

#define NO_ERROR 0
#define OBJ_FILE_NOT_FOUND 1

typedef struct Data Data;

struct Data {
  double scale;
  double **vertices;
  int vertexRows;
  int **faces;
  int faceRows;
  int *verticesInFace;
};

Data createData();
Data getData(char *fileName);
void destroyData(Data data);
void dot_killer(char *str);

#endif  // SRC_PARSE_H_
