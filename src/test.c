#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "transformations.h"

int isEqual(double one, double two) { return fabs(one - two) < 0.0000001; }

START_TEST(parsing_test) {
  Data result = getData("testObj");
  double **vertices = result.vertices;
  int **faces = result.faces;

  ck_assert_msg(result.vertexRows == 3, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[0][0], 2) == 1, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[0][1], 1) == 1, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[0][2], 1) == 1, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[1][0], 6) == 1, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[1][1], 2) == 1, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[1][2], 1) == 1, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[2][0], 4) == 1, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[2][1], 3) == 1, "FAILED TEST 1");
  ck_assert_msg(isEqual(vertices[2][2], 1) == 1, "FAILED TEST 1");

  ck_assert_msg(result.faceRows == 1, "FAILED TEST 1");
  ck_assert_msg(faces[0][0] == 1, "FAILED TEST 1");
  ck_assert_msg(faces[0][1] == 2, "FAILED TEST 1");
  ck_assert_msg(faces[0][2] == 3, "FAILED TEST 1");

  destroyData(result);
}
END_TEST

START_TEST(translation_test) {
  Data result = getData("testObj");
  double **vertices = result.vertices;
  int **faces = result.faces;

  translate(vertices, result.vertexRows, X, POSITIVE, 1);
  translate(vertices, result.vertexRows, Y, POSITIVE, 2);
  translate(vertices, result.vertexRows, Z, POSITIVE, -1);

  ck_assert_msg(isEqual(vertices[0][0], 3) == 1, "FAILED TEST 2");
  ck_assert_msg(isEqual(vertices[0][1], 3) == 1, "FAILED TEST 2");
  ck_assert_msg(isEqual(vertices[0][2], 0) == 1, "FAILED TEST 2");
  ck_assert_msg(isEqual(vertices[1][0], 7) == 1, "FAILED TEST 2");
  ck_assert_msg(isEqual(vertices[1][1], 4) == 1, "FAILED TEST 2");
  ck_assert_msg(isEqual(vertices[1][2], 0) == 1, "FAILED TEST 2");
  ck_assert_msg(isEqual(vertices[2][0], 5) == 1, "FAILED TEST 2");
  ck_assert_msg(isEqual(vertices[2][1], 5) == 1, "FAILED TEST 2");
  ck_assert_msg(isEqual(vertices[2][2], 0) == 1, "FAILED TEST 2");

  destroyData(result);
}
END_TEST

START_TEST(scaling_test) {
  Data result = getData("testObj");
  double **vertices = result.vertices;
  int **faces = result.faces;

  scale(vertices, result.vertexRows, &(result.scale), POSITIVE);

  ck_assert_msg(isEqual(vertices[0][0], 2.4) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[0][1], 1.2) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[0][2], 1.2) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[1][0], 7.2) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[1][1], 2.4) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[1][2], 1.2) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[2][0], 4.8) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[2][1], 3.6) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[2][2], 1.2) == 1, "FAILED TEST 4");

  scale(vertices, result.vertexRows, &(result.scale), NEGATIVE);

  ck_assert_msg(isEqual(vertices[0][0], 2) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[0][1], 1) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[0][2], 1) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[1][0], 6) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[1][1], 2) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[1][2], 1) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[2][0], 4) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[2][1], 3) == 1, "FAILED TEST 4");
  ck_assert_msg(isEqual(vertices[2][2], 1) == 1, "FAILED TEST 4");

  destroyData(result);
}
END_TEST

START_TEST(rotation_z_test) {
  Data result = getData("testObj");
  double **vertices = result.vertices;
  int **faces = result.faces;

  rotate(vertices, result.vertexRows, Z, POSITIVE, 90);

  // vertices[0][0] == 2
  // vertices[0][1] == 1
  // vertices[0][2] == 1
  // vertices[1][0] == 6
  // vertices[1][1] == 2
  // vertices[1][2] == 1
  // vertices[2][0] == 4
  // vertices[2][1] == 3
  // vertices[2][2] == 1

  ck_assert_msg(isEqual(vertices[0][0], 1) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[0][1], -2) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[0][2], 1) == 1, "FAILED TEST 5");

  ck_assert_msg(isEqual(vertices[1][0], 2) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[1][1], -6) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[1][2], 1) == 1, "FAILED TEST 5");

  ck_assert_msg(isEqual(vertices[2][0], 3) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[2][1], -4) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[2][2], 1) == 1, "FAILED TEST 5");

  rotate(vertices, result.vertexRows, Z, NEGATIVE, 90);

  ck_assert_msg(isEqual(vertices[0][0], 2) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[0][1], 1) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[0][2], 1) == 1, "FAILED TEST 5");

  ck_assert_msg(isEqual(vertices[1][0], 6) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[1][1], 2) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[1][2], 1) == 1, "FAILED TEST 5");

  ck_assert_msg(isEqual(vertices[2][0], 4) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[2][1], 3) == 1, "FAILED TEST 5");
  ck_assert_msg(isEqual(vertices[2][2], 1) == 1, "FAILED TEST 5");

  destroyData(result);
}
END_TEST

START_TEST(rotation_x_test) {
  Data result = getData("testObj");
  double **vertices = result.vertices;
  int **faces = result.faces;

  rotate(vertices, result.vertexRows, X, POSITIVE, 90);

  // vertices[0][0] == 2
  // vertices[0][1] == 1
  // vertices[0][2] == 1
  // vertices[1][0] == 6
  // vertices[1][1] == 2
  // vertices[1][2] == 1
  // vertices[2][0] == 4
  // vertices[2][1] == 3
  // vertices[2][2] == 1

  ck_assert_msg(isEqual(vertices[0][0], 2) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[0][1], 1) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[0][2], -1) == 1, "FAILED TEST 6");

  ck_assert_msg(isEqual(vertices[1][0], 6) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[1][1], 1) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[1][2], -2) == 1, "FAILED TEST 6");

  ck_assert_msg(isEqual(vertices[2][0], 4) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[2][1], 1) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[2][2], -3) == 1, "FAILED TEST 6");

  rotate(vertices, result.vertexRows, X, NEGATIVE, 90);

  ck_assert_msg(isEqual(vertices[0][0], 2) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[0][1], 1) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[0][2], 1) == 1, "FAILED TEST 6");

  ck_assert_msg(isEqual(vertices[1][0], 6) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[1][1], 2) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[1][2], 1) == 1, "FAILED TEST 6");

  ck_assert_msg(isEqual(vertices[2][0], 4) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[2][1], 3) == 1, "FAILED TEST 6");
  ck_assert_msg(isEqual(vertices[2][2], 1) == 1, "FAILED TEST 6");

  destroyData(result);
}
END_TEST

START_TEST(rotation_y_test) {
  Data result = getData("testObj");
  double **vertices = result.vertices;
  int **faces = result.faces;

  rotate(vertices, result.vertexRows, Y, POSITIVE, 90);

  // vertices[0][0] == 2
  // vertices[0][1] == 1
  // vertices[0][2] == 1
  // vertices[1][0] == 6
  // vertices[1][1] == 2
  // vertices[1][2] == 1
  // vertices[2][0] == 4
  // vertices[2][1] == 3
  // vertices[2][2] == 1

  ck_assert_msg(isEqual(vertices[0][0], -1) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[0][1], 1) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[0][2], 2) == 1, "FAILED TEST 7");

  ck_assert_msg(isEqual(vertices[1][0], -1) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[1][1], 2) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[1][2], 6) == 1, "FAILED TEST 7");

  ck_assert_msg(isEqual(vertices[2][0], -1) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[2][1], 3) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[2][2], 4) == 1, "FAILED TEST 7");

  rotate(vertices, result.vertexRows, Y, NEGATIVE, 90);

  ck_assert_msg(isEqual(vertices[0][0], 2) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[0][1], 1) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[0][2], 1) == 1, "FAILED TEST 7");

  ck_assert_msg(isEqual(vertices[1][0], 6) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[1][1], 2) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[1][2], 1) == 1, "FAILED TEST 7");

  ck_assert_msg(isEqual(vertices[2][0], 4) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[2][1], 3) == 1, "FAILED TEST 7");
  ck_assert_msg(isEqual(vertices[2][2], 1) == 1, "FAILED TEST 7");

  destroyData(result);
}
END_TEST

Suite *suit_create(void) {
  Suite *suite = suite_create("Tests of 3D Viewer");

  TCase *parse = tcase_create("Parsing .obj file");
  tcase_add_test(parse, parsing_test);
  suite_add_tcase(suite, parse);

  TCase *transformations = tcase_create("Affine transformations");
  tcase_add_test(transformations, translation_test);
  tcase_add_test(transformations, scaling_test);
  tcase_add_test(transformations, rotation_z_test);
  tcase_add_test(transformations, rotation_x_test);
  tcase_add_test(transformations, rotation_y_test);
  suite_add_tcase(suite, transformations);

  return suite;
}

int main(void) {
  Suite *suite = suit_create();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  srunner_free(suite_runner);

  if (srunner_ntests_failed(suite_runner) != 0) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
