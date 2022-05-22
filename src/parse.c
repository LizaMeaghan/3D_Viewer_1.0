#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transformations.h"

void dot_killer(char *str) {
  for (unsigned long j = 0; j < strlen(str); j++) {
    if (str[j] == '.') str[j] = ',';
  }
}

int addVertice(Data *data, char *line) {
  int error = NO_ERROR;
  int vRows = data->vertexRows;

  data->vertices =
      (double **)realloc(data->vertices, sizeof(double *) * ++vRows);
  data->vertices[vRows - 1] = (double *)malloc(3 * sizeof(double));

  char *save = NULL;
  strtok_r(line, " ", &save);
  for (int i = 0; i < 3; i++) {
    char *tok_tok = strtok_r(NULL, " ", &save);
    dot_killer(tok_tok);
    sscanf(tok_tok, "%lf", &data->vertices[vRows - 1][i]);
  }

  data->vertexRows = vRows;
  return error;
}

int addFace(Data *data, char *line) {
  int error = NO_ERROR;
  int fRows = data->faceRows;

  data->faces = (int **)realloc(data->faces, sizeof(int *) * ++fRows);
  data->faces[fRows - 1] = NULL;

  data->verticesInFace =
      (int *)realloc(data->verticesInFace, fRows * sizeof(int));

  char *save = NULL;
  char *token = strtok_r(line, " ", &save);
  int counter = 0;
  int num = 0;

  while ((token = strtok_r(NULL, " ", &save)) != NULL) {
    data->faces[fRows - 1] =
        (int *)realloc(data->faces[fRows - 1], ++counter * sizeof(int));
    sscanf(token, "%d", &num);
    data->faces[fRows - 1][counter - 1] = num;
  }
  data->verticesInFace[fRows - 1] = counter;
  data->faceRows = fRows;
  return error;
}

Data createData() {
  Data data;
  data.scale = 1;
  data.vertices = NULL;
  data.vertexRows = 0;
  data.faces = NULL;
  data.faceRows = 0;
  data.verticesInFace = NULL;
  return data;
}

void destroyData(Data data) {
    freeMatrice(data.vertices, data.vertexRows);
    freeMatriceInt(data.faces, data.faceRows);
    free(data.verticesInFace);
}

Data getData(char *fileName) {
  Data data = createData();
  FILE *objFile;
  objFile = fopen(fileName, "r");
  if (objFile == NULL) {
    printf("Указанный .obj-файл не найден\n");
    printf("name of file is: %s\n", fileName);
  } else {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, objFile)) != -1) {
      if (strstr(line, "v ") != NULL)
        addVertice(&data, line);
      else if (strstr(line, "f ") != NULL)
        addFace(&data, line);
    }

    free(line);
    fclose(objFile);
  }

  return data;
}
