/********************************************************************
 ********************************************************************
 **
 ** libhungarian by Cyrill Stachniss, 2004
 **
 **
 ** Solving the Minimum Assignment Problem using the
 ** Hungarian Method.
 **
 ** ** This file may be freely copied and distributed! **
 **
 ** Parts of the used code was originally provided by the
 ** "Stanford GraphGase", but I made changes to this code.
 ** As asked by  the copyright node of the "Stanford GraphGase",
 ** I hereby proclaim that this file are *NOT* part of the
 ** "Stanford GraphGase" distrubition!
 **
 ** This file is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied
 ** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 ** PURPOSE.
 **
 ********************************************************************
 ********************************************************************/

#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#define HUNGARIAN_NOT_ASSIGNED 0
#define HUNGARIAN_ASSIGNED 1

#define HUNGARIAN_MODE_MINIMIZE_COST 0
#define HUNGARIAN_MODE_MAXIMIZE_UTIL 1
#include <stdio.h>
#include <stdlib.h>

#include <vector>

using namespace std;
#define INF (0x7FFFFFFF)
#define verbose (0)

#define hungarian_test_alloc(X)                                                                                             \
	do {                                                                                                                    \
		if ((void*)(X) == NULL) fprintf(stderr, "Out of memory in %s, (%s, line %d).\n", __FUNCTION__, __FILE__, __LINE__); \
	} while (0)

typedef struct {
	int num_rows;
	int num_cols;
	int** cost;
	int** assignment;
} hungarian_problem_t;

/** This method initialize the hungarian_problem structure and init
 *  the  cost matrices (missing lines or columns are filled with 0).
 *  It returns the size of the quadratic(!) assignment matrix. **/
int hungarian_init(hungarian_problem_t* p, vector<vector<double>>* cost_matrix, int rows, int cols, int mode);

/** Free the memory allocated by init. **/
void hungarian_free(hungarian_problem_t* p);

/** This method computes the optimal assignment. **/
int hungarian_solve(hungarian_problem_t* p);

/** Print the computed optimal assignment. **/
void hungarian_print_assignment(hungarian_problem_t* p);

/** Print the cost matrix. **/
void hungarian_print_costmatrix(hungarian_problem_t* p);

/** Print cost matrix and assignment matrix. **/
void hungarian_print_status(hungarian_problem_t* p);

#endif
