#include <stdio.h>
#include <stdlib.h>

// Định nghĩa kích thước tối đa của ma trận
#define MAX_SIZE 20
// Hàm sinh ma trận ngẫu nhiên
void generateRandomMatrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    srand(time(NULL));

    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 20; // Giả sử giá trị ngẫu nhiên trong khoảng từ 0 đến 99
        }
    }
}
// Hàm đọc ma trận từ file
void readMatrixFromFile(char *filename, int matrix[MAX_SIZE][MAX_SIZE], int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        exit(1);
    }

    fscanf(file, "%d %d", rows, cols);

    int i, j;
    for (i = 0; i < *rows; i++) {
        for (j = 0; j < *cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
}

// Hàm ghi ma trận vào file
void writeMatrixToFile(char *filename, int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        exit(1);
    }

    fprintf(file, "%d %d\n", rows, cols);

    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Hàm in ma trận ra file
void printMatrix(char *filename, int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        exit(1);
    }

    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Hàm in ma trận kiểu số thực ra file
void printMatrix2(char *filename, float matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        exit(1);
    }

    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(file, "%f ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Hàm kiểm tra xem hai ma trận có thể thực hiện phép cộng, trừ, nhân không
int validateMatrixSizes(int rows1, int cols1, int rows2, int cols2) {
    if (rows1 != rows2 || cols1 != cols2) {
        printf("Hai ma tran khong co kich thuoc hop le.\n");
        return 0;
    }
    return 1;
}

// Hàm thực hiện phép cộng hai ma trận
void addMatrices(int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// Hàm thực hiện phép trừ hai ma trận
void subtractMatrices(int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

// Hàm thực hiện phép nhân hai ma trận
void multiplyMatrices(int matrix1[MAX_SIZE][MAX_SIZE], int rows1, int cols1, int matrix2[MAX_SIZE][MAX_SIZE], int rows2, int cols2, int result[MAX_SIZE][MAX_SIZE]) {
    if (cols1 != rows2) {
        printf("Hai ma tran khong co kich thuoc hop le.\n");
        return;
    }

    int i, j, k;
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Hàm nhân vô hướng ma trận với một số thực
void scalarMultiply(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols, float scalar, float result[MAX_SIZE][MAX_SIZE]) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}

// Hàm tính định thức của ma trận 2x2
int calculateDeterminant2x2(int matrix[2][2]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// Hàm tính định thức của ma trận
int calculateDeterminant(int matrix[MAX_SIZE][MAX_SIZE], int size) {
    if (size == 2) {
        return calculateDeterminant2x2((int(*)[2])matrix);
    }

    int determinant = 0;
    int sign = 1;
    int submatrix[MAX_SIZE][MAX_SIZE];
    int i, j, k;

    for (i = 0; i < size; i++) {
        int subi = 0;
        for (j = 1; j < size; j++) {
            int subj = 0;
            for (k = 0; k < size; k++) {
                if (k == i) {
                    continue;
                }
                submatrix[subi][subj] = matrix[j][k];
                subj++;
            }
            subi++;
        }
        determinant += sign * matrix[0][i] * calculateDeterminant(submatrix, size - 1);
        sign = -sign;
    }

    return determinant;
}

// Hàm tính ma trận nghịch đảo theo công thức phần phụ đại số
void inverseMatrixCofactor(int matrix[MAX_SIZE][MAX_SIZE], int size, int inverse[MAX_SIZE][MAX_SIZE]) {
    int submatrix[MAX_SIZE][MAX_SIZE];
    int cofactor[MAX_SIZE][MAX_SIZE];
    int i, j, subi, subj;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            subi = 0;
            for (subi = 0; subi < size - 1; subi++) {
                subj = 0;
                for (subj = 0; subj < size - 1; subj++) {
                    int row = (subi < i) ? subi : subi + 1;
                    int col = (subj < j) ? subj : subj + 1;
                    submatrix[subi][subj] = matrix[row][col];
                }
            }
            cofactor[i][j] = (i + j) % 2 ? -1 : 1;
            cofactor[i][j] *= calculateDeterminant(submatrix, size - 1);
        }
    }

    int transpose[MAX_SIZE][MAX_SIZE];
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            transpose[i][j] = cofactor[j][i];
        }
    }

    int determinant = calculateDeterminant(matrix, size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            inverse[i][j] = transpose[i][j] / determinant;
        }
    }
}

// Hàm tính ma trận nghịch đảo theo phương pháp Gauss-Jordan
void inverseMatrixGaussJordan(int matrix[MAX_SIZE][MAX_SIZE], int size, int inverse[MAX_SIZE][MAX_SIZE]) {
    int augmentedMatrix[MAX_SIZE][2 * MAX_SIZE];
    int i, j, k;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            augmentedMatrix[i][j] = matrix[i][j];
        }
        for (j = size; j < 2 * size; j++) {
            augmentedMatrix[i][j] = (i == (j - size)) ? 1 : 0;
        }
    }

    for (i = 0; i < size; i++) {
        if (augmentedMatrix[i][i] == 0) {
            printf("Ma tran khong co nghich dao.\n");
            return;
        }
        for (j = 0; j < size; j++) {
            if (j != i) {
                float ratio = augmentedMatrix[j][i] / (float)augmentedMatrix[i][i];
                for (k = 0; k < 2 * size; k++) {
                    augmentedMatrix[j][k] -= ratio * augmentedMatrix[i][k];
                }
            }
        }
    }

    for (i = 0; i < size; i++) {
        float divisor = augmentedMatrix[i][i];
        for (j = 0; j < 2 * size; j++) {
            augmentedMatrix[i][j] /= divisor;
        }
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            inverse[i][j] = augmentedMatrix[i][j + size];
        }
    }
}

// Hàm tính hạng của ma trận
int calculateRank(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int rank = 0;
    int temp[MAX_SIZE][MAX_SIZE];
    int i, j, k;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            temp[i][j] = matrix[i][j];
        }
    }

    for (i = 0; i < cols; i++) {
        for (j = 0; j < rows; j++) {
            if (temp[j][i] != 0) {
                rank++;
                for (k = 0; k < cols; k++) {
                    temp[j][k] = 0;
                }
                break;
            }
        }
    }

    return rank;
}

// Hàm tính trị tuyệt đối lớn nhất của một vectơ
float vectorNorm(float vector[MAX_SIZE], int size) {
    float norm = 0.0;
    for (int i = 0; i < size; i++) {
        norm += vector[i] * vector[i];
    }
    return sqrt(norm);
}

// Hàm chia một vectơ cho một số thực
void normalizeVector(float vector[MAX_SIZE], int size) {
    float norm = vectorNorm(vector, size);
    for (int i = 0; i < size; i++) {
        vector[i] /= norm;
    }
}

// Hàm nhân ma trận với vectơ
void matrixVectorMultiply(int matrix[MAX_SIZE][MAX_SIZE], float vector[MAX_SIZE], int size, float result[MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        result[i] = 0.0;
        for (int j = 0; j < size; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

// Hàm in kết quả vào tệp văn bản
void printResultToFile(char *filename, float eigenValue, float eigenVector[MAX_SIZE], int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    fprintf(file, "Trị riêng ước lượng: %f\n", eigenValue);
    fprintf(file, "Vectơ riêng ước lượng:\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%f ", eigenVector[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

// Hàm tính trị riêng và vectơ riêng của ma trận bằng phương pháp lặp (power iteration)
void findEigenvaluesAndEigenvectors(int matrix[MAX_SIZE][MAX_SIZE], int size, char *filename) {
    // Khởi tạo một vectơ ngẫu nhiên
    float eigenVector[MAX_SIZE];
    for (int i = 0; i < size; i++) {
        eigenVector[i] = 1.0;
    }

    // Số lần lặp tối đa và sai số cho phép
    int maxIterations = 1000;
    float epsilon = 1e-6;

    // Biến lưu trữ trị riêng hiện tại và trị riêng trước đó
    float eigenValue = 0.0;
    float prevEigenValue = 1.0;

    // Lặp cho đến khi hội tụ hoặc đạt tới số lần lặp tối đa
    int iteration = 0;
    while (fabs(eigenValue - prevEigenValue) > epsilon && iteration < maxIterations) {
        // Lưu trữ trị riêng trước đó để kiểm tra sự hội tụ
        prevEigenValue = eigenValue;

        // Nhân ma trận với vectơ
        float result[MAX_SIZE];
        matrixVectorMultiply(matrix, eigenVector, size, result);

        // Tính trị riêng là trị tuyệt đối lớn nhất của kết quả
        eigenValue = vectorNorm(result, size);

        // Chuẩn hóa vectơ riêng
        normalizeVector(result, size);

        // Cập nhật vectơ riêng
        for (int i = 0; i < size; i++) {
            eigenVector[i] = result[i];
        }

        iteration++;
    }

    // Ghi kết quả vào tệp văn bản
    printResultToFile(filename, eigenValue, eigenVector, size);
}

int main() {
    int choice;
    char filename[100];
    int matrix1[MAX_SIZE][MAX_SIZE];
    int matrix2[MAX_SIZE][MAX_SIZE];
    int matrix3[MAX_SIZE][MAX_SIZE];
    int result[MAX_SIZE][MAX_SIZE];
    float result2[MAX_SIZE][MAX_SIZE];
    int inverse[MAX_SIZE][MAX_SIZE];
    int rows1, cols1, rows2, cols2, rows3, cols3;
    float scalar;
    system("CLS");
    do {
        printf("1. Nhap ma tran tu file\n");
        printf("2. Cong hai ma tran\n");
        printf("3. Tru hai ma tran\n");
        printf("4. Nhan hai ma tran\n");
        printf("5. Nhan vo huong ma tran voi mot so\n");
        printf("6. Tinh dinh thuc cua ma tran\n");
        printf("7. Tinh ma tran nghich dao (theo cong thuc phan phu dai so)\n");
        printf("8. Tinh ma tran nghich dao (theo phuong phap Gauss-Jordan)\n");
        printf("9. Tinh hang cua ma tran\n");
        printf("10. Tim tri rieng va vecto rieng cua ma tran\n");
        printf("11. Tao ma tran ngau nhien\n");
        printf("0. Thoat\n");
        printf("\nNhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap ten file cua ma tran 1: ");
                scanf("%s", filename);
                readMatrixFromFile(filename, matrix1, &rows1, &cols1);
                printf("Nhap ten file cua ma tran 2: ");
                scanf("%s", filename);
                readMatrixFromFile(filename, matrix2, &rows2, &cols2);
                break;
            case 2:
                if (validateMatrixSizes(rows1, cols1, rows2, cols2)) {
                    addMatrices(matrix1, matrix2, result, rows1, cols1);
                    printf("Nhap ten file de luu ma tran: ");
                    scanf("%s", filename);
                    printMatrix(filename, result, rows1, cols1);
                }
                break;
            case 3:
                if (validateMatrixSizes(rows1, cols1, rows2, cols2)) {
                    subtractMatrices(matrix1, matrix2, result, rows1, cols1);
                    printf("Nhap ten file de luu ma tran: ");
                    scanf("%s", filename);
                    printMatrix(filename, result, rows1, cols1);
                }
                break;
            case 4:
                if (cols1 != rows2) {
                    printf("Hai ma tran khong co kich thuoc hop le.\n");
                    break;
                }
                multiplyMatrices(matrix1, rows1, cols1, matrix2, rows2, cols2, result);
                printf("Nhap ten file de luu ma tran: ");
                scanf("%s", filename);
                printMatrix(filename, result, rows1, cols1);
                break;
            case 5:
                printf("Nhap so thuc: ");
                scanf("%f", &scalar);
                scalarMultiply(matrix1, rows1, cols1, scalar, result2);
                printf("Nhap ten file de luu ma tran: ");
                scanf("%s", filename);
                printMatrix2(filename, result2, rows1, cols1);
                break;
            case 6:
                 int determinant = calculateDeterminant(matrix1, rows1);

                // Ghi kết quả vào file
                printf("Nhap ten file de luu ma tran: ");
                scanf("%s", filename);
                FILE *file = fopen(filename, "w");
                if (file == NULL) {
                    printf("Khong the mo file.\n");
                    break;
                }

                fprintf(file, "%d\n", determinant);
                fclose(file);
                break;
            case 7:
                if (rows1 != cols1) {
                    printf("Ma tran khong phai la ma tran vuong.\n");
                    break;
                }
                inverseMatrixCofactor(matrix1, rows1, inverse);
                printf("Nhap ten file de luu ma tran: ");
                scanf("%s", filename);
                printMatrix(filename, result, rows1, cols1);
                break;
            case 8:
                if (rows1 != cols1) {
                    printf("Ma tran khong phai la ma tran vuong.\n");
                    break;
                }
                inverseMatrixGaussJordan(matrix1, rows1, inverse);
                printf("Nhap ten file de luu ma tran: ");
                scanf("%s", filename);
                printMatrix(filename, result, rows1, cols1);
                break;
            case 9:
                printf("Nhap ten file de luu ma tran: ");
                scanf("%s", filename);
                FILE *file2 = fopen(filename, "w");
                if (file2 == NULL) {
                    printf("Khong the mo file.\n");
                    break;
                }

                fprintf(file2, "%d\n", calculateRank(matrix1, rows1, cols1));
                fclose(file2);
                break;
            case 10:
                if (rows1 != cols1) {
                    printf("Ma tran khong phai la ma tran vuong.\n");
                    break;
                }
                printf("Nhap ten file de luu ket qua: ");
                scanf("%s", filename);
                findEigenvaluesAndEigenvectors(matrix1, rows1, filename);
                break;
            case 11:
                printf("Nhap so hang va cot cua ma tran: ");
                scanf("%d %d", &rows3, &cols3);
                generateRandomMatrix(matrix3, rows3, cols3);
                printf("Nhap ten file de luu ma tran: ");
                scanf("%s", filename);
                writeMatrixToFile(filename, matrix3, rows3, cols3);
                printf("Ma tran da duoc luu vao file.\n");
                break;
            case 0:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long nhap lai.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
