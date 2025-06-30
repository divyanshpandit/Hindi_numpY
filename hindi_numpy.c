#include <stdio.h>
#include <stdlib.h>

// ============ 1D ARRAY ============

typedef struct {
    double *data;
    size_t size;
} ndarray1d;

ndarray1d* banao1d(size_t size, double value) {
    ndarray1d* arr = malloc(sizeof(ndarray1d));
    arr->size = size;
    arr->data = malloc(sizeof(double) * size);
    for (size_t i = 0; i < size; i++) {
        arr->data[i] = value;
    }
    return arr;
}

void chapo1d(ndarray1d* arr) {
    printf("Array: ");
    for (size_t i = 0; i < arr->size; i++) {
        printf("%f ", arr->data[i]);
    }
    printf("\n");
}

void zodo1d(ndarray1d* arr, double value) {
    for (size_t i = 0; i < arr->size; i++) {
        arr->data[i] += value;
    }
}

void guna1d(ndarray1d* arr, double value) {
    for (size_t i = 0; i < arr->size; i++) {
        arr->data[i] *= value;
    }
}

ndarray1d* kaato1d(ndarray1d* arr, size_t start, size_t end) {
    if (start >= end || end > arr->size) {
        printf("Galat slice!\n");
        return NULL;
    }
    ndarray1d* sliced = malloc(sizeof(ndarray1d));
    sliced->size = end - start;
    sliced->data = malloc(sizeof(double) * sliced->size);
    for (size_t i = 0; i < sliced->size; i++) {
        sliced->data[i] = arr->data[start + i];
    }
    return sliced;
}

void free1d(ndarray1d* arr) {
    free(arr->data);
    free(arr);
}

// ============ 2D ARRAY ============

typedef struct {
    double *data;
    size_t rows;
    size_t cols;
} ndarray2d;

ndarray2d* banao2d(size_t rows, size_t cols, double value) {
    ndarray2d* mat = malloc(sizeof(ndarray2d));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = malloc(sizeof(double) * rows * cols);
    for (size_t i = 0; i < rows * cols; i++) {
        mat->data[i] = value;
    }
    return mat;
}

void chapo2d(ndarray2d* mat) {
    printf("Matrix:\n");
    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            printf("%f ", mat->data[i * mat->cols + j]);
        }
        printf("\n");
    }
}

void zodo2d(ndarray2d* mat, double value) {
    for (size_t i = 0; i < mat->rows * mat->cols; i++) {
        mat->data[i] += value;
    }
}

void guna2d(ndarray2d* mat, double value) {
    for (size_t i = 0; i < mat->rows * mat->cols; i++) {
        mat->data[i] *= value;
    }
}

ndarray2d* kaato2d(ndarray2d* mat, size_t row_start, size_t row_end) {
    if (row_start >= row_end || row_end > mat->rows) {
        printf("Galat slice!\n");
        return NULL;
    }
    size_t new_rows = row_end - row_start;
    ndarray2d* sliced = malloc(sizeof(ndarray2d));
    sliced->rows = new_rows;
    sliced->cols = mat->cols;
    sliced->data = malloc(sizeof(double) * new_rows * mat->cols);
    for (size_t i = 0; i < new_rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            sliced->data[i * sliced->cols + j] = mat->data[(row_start + i) * mat->cols + j];
        }
    }
    return sliced;
}

void free2d(ndarray2d* mat) {
    free(mat->data);
    free(mat);
}

// ============ MAIN ============

int main() {
    int choice;

    // we can store up to 2 arrays/matrices
    ndarray1d* arrs[2] = {NULL, NULL};
    ndarray2d* mats[2] = {NULL, NULL};

    printf("Namaste! Hindi NumPy mein swagat hai!\n");

    while (1) {
        printf("\n----- Menu -----\n");
        printf("1. Create 1D array\n");
        printf("2. Create 2D matrix\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            size_t size;
            double val;
            printf("Array size: ");
            scanf("%zu", &size);
            printf("Fill value: ");
            scanf("%lf", &val);

            printf("Slot to store (0 or 1): ");
            int slot;
            scanf("%d", &slot);
            if (slot < 0 || slot > 1) {
                printf("Galat slot!\n");
                continue;
            }

            if (arrs[slot]) free1d(arrs[slot]);
            arrs[slot] = banao1d(size, val);
            chapo1d(arrs[slot]);

            int op;
            do {
                printf("\n1D operations:\n");
                printf("1. Add (zodo)\n2. Multiply (guna)\n3. Slice (kaato)\n0. Back to main menu\n");
                printf("Choose: ");
                scanf("%d", &op);

                if (op == 1) {
                    double x;
                    printf("Kitna add karun? ");
                    scanf("%lf", &x);
                    zodo1d(arrs[slot], x);
                    chapo1d(arrs[slot]);
                } else if (op == 2) {
                    double x;
                    printf("Kitna multiply karun? ");
                    scanf("%lf", &x);
                    guna1d(arrs[slot], x);
                    chapo1d(arrs[slot]);
                } else if (op == 3) {
                    size_t s, e;
                    printf("Start index: ");
                    scanf("%zu", &s);
                    printf("End index: ");
                    scanf("%zu", &e);
                    ndarray1d* sliced = kaato1d(arrs[slot], s, e);
                    if (sliced) {
                        printf("Sliced: ");
                        chapo1d(sliced);
                        free1d(sliced);
                    }
                }
            } while (op != 0);

        } else if (choice == 2) {
            size_t r, c;
            double val;
            printf("Rows: ");
            scanf("%zu", &r);
            printf("Cols: ");
            scanf("%zu", &c);
            printf("Fill value: ");
            scanf("%lf", &val);

            printf("Slot to store (0 or 1): ");
            int slot;
            scanf("%d", &slot);
            if (slot < 0 || slot > 1) {
                printf("Galat slot!\n");
                continue;
            }

            if (mats[slot]) free2d(mats[slot]);
            mats[slot] = banao2d(r, c, val);
            chapo2d(mats[slot]);

            int op;
            do {
                printf("\n2D operations:\n");
                printf("1. Add (zodo)\n2. Multiply (guna)\n3. Slice rows (kaato)\n0. Back to main menu\n");
                printf("Choose: ");
                scanf("%d", &op);

                if (op == 1) {
                    double x;
                    printf("Kitna add karun? ");
                    scanf("%lf", &x);
                    zodo2d(mats[slot], x);
                    chapo2d(mats[slot]);
                } else if (op == 2) {
                    double x;
                    printf("Kitna multiply karun? ");
                    scanf("%lf", &x);
                    guna2d(mats[slot], x);
                    chapo2d(mats[slot]);
                } else if (op == 3) {
                    size_t s, e;
                    printf("Row start: ");
                    scanf("%zu", &s);
                    printf("Row end: ");
                    scanf("%zu", &e);
                    ndarray2d* sliced = kaato2d(mats[slot], s, e);
                    if (sliced) {
                        printf("Sliced:\n");
                        chapo2d(sliced);
                        free2d(sliced);
                    }
                }
            } while (op != 0);

        } else if (choice == 3) {
            printf("Shukriya! Bye.\n");
            break;
        } else {
            printf("Galat choice!\n");
        }
    }

    // cleanup
    for (int i = 0; i < 2; i++) {
        if (arrs[i]) free1d(arrs[i]);
        if (mats[i]) free2d(mats[i]);
    }

    return 0;
}
