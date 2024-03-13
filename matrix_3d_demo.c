#include "mex.h"

void matrix_3d_demo(double *d, mwSize rows, mwSize cols, mwSize pages, double *output_dd) {
    int i, j, k;

    printf("matlab的三维数组d以一维的形式传入c中\n\n");

    //错误的形式
    printf("当把d的深度看作第 三 维度, 每一页按照c以列储存的下标输出为(错误的形式): \n");
    printf("d in C：\n");
    // 计算三维数组
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            for (k = 0; k < pages; k++) {
                printf("depth = %d\n", k);
                printf("%f ", d[i + j * rows + k * rows * cols]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");

    //正确的形式
    printf("当把d的深度看作第 一 维度, 每一页按照c以列储存的下标输出为(正确的形式): \n");
    printf("d in C：\n");
    for (k = 0; k < pages; k++){
        printf("depth = %d\n", k);
        for (i = 0; i < rows; i++){
            for (j = 0; j < cols; j++){
                printf("%f ", d[i + j * rows + k * rows * cols]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n\n");

    printf("-------------在C中创建的矩阵, 在C中输出-------------\n");

    printf("在c中创建指针形式的以一维线性储存的三维数组d_1d:\n");
    double *d_1d = (double *)calloc(pages*rows*cols, sizeof(double));
    for (i = 0; i < pages*rows*cols; i++) {
            d_1d[i] = i;
    }
    printf("d_3d:\n");
    for (k = 0; k < pages; k++) {
        printf("depth = %d\n", k);
        for (i = 0; i < rows; i++) {
            for(j = 0; j < cols; j++){
                printf("%f ", d_1d[k * rows * cols + i * cols + j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
    
    //正确的形式
    printf("在c中d_1d赋值给三维数组d_3d(正确的形式): \n");
    double ***d_3d = (double ***)calloc(pages, sizeof(double **));
    for (k = 0; k < pages; k++) {
        d_3d[k] = (double **)calloc(rows, sizeof(double *));
        for (i = 0; i < rows; i++) {
            d_3d[k][i] = (double *)calloc(cols, sizeof(double));
        }
    }
    printf("d_3d:\n");
    for (k = 0; k < pages; k++) {
        printf("depth = %d\n", k);
        for (i = 0; i < rows; i++) {
            for(j = 0; j < cols; j++){
                d_3d[k][i][j] = d_1d[k * rows * cols + i * cols + j];
                printf("%f ", d_3d[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");


    //正确的形式
    printf("把从matlab中传来的一维形式的三维数组d, 赋值给c中创建的三维数组d_3d(正确的形式): \n");
    printf("d_3d:\n");
    for (k = 0; k < pages; k++) {
        printf("depth = %d\n", k);
        for (i = 0; i < rows; i++) {
            for(j = 0; j < cols; j++){
                d_3d[k][i][j] = d[i + j * rows + k * rows * cols];
                printf("%f ", d_3d[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
    
    //正确的形式
    printf("c中创建的三维数组d_3d赋值给要输出到matlab中的output_dd(一维)(正确的形式): \n");
    printf("output_dd在C中的输出为: \n");
    for (k = 0; k < pages; k++) {
        printf("depth = %d\n", k);
        for (i = 0; i < rows; i++) {
            for(j = 0; j < cols; j++){
                output_dd[i + j * rows + k * rows * cols] = d_3d[k][i][j];
                printf("%f ", output_dd[i + j * rows + k * rows * cols]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");



}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

    // 获取输入参数
    double *d = mxGetPr(prhs[0]);
    mwSize rows = mxGetDimensions(prhs[0])[0];
    mwSize cols = mxGetDimensions(prhs[0])[1];
    mwSize pages = mxGetDimensions(prhs[0])[2];
    printf("rows = %d, cols = %d, pages = %d\n", rows, cols, pages);

    // 分配输出参数内存
    plhs[0] = mxCreateNumericArray(3, (const mwSize[]){rows, cols, pages}, mxDOUBLE_CLASS, mxREAL); // dd

    // 获取输出参数指针
    double *output_dd = mxGetPr(plhs[0]);

    // 调用函数计算结果
    matrix_3d_demo(d, rows, cols, pages, output_dd);
}
