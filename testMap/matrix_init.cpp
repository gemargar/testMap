#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::matrix_init3()
{
    double det;

    // Populate combination array
    int comb = 0;
    // set key values
    for(int i=0; i<ANCHORS; i++) {
        for(int j=i+1; j<ANCHORS; j++) {
            for(int k=j+1; k<ANCHORS; k++) {
                key3[comb][0] = i;
                key3[comb][1] = j;
                key3[comb][2] = k;
//                qDebug() << i << j << k;
                comb++;
            }
        }
    }

    for(comb=0; comb<20; comb++) {
        // Populate A matrix
        for(int i=0; i<2; i++){
            A3[comb][i][0] = xa[key3[comb][i+1]] - xa[key3[comb][0]];
            A3[comb][i][1] = ya[key3[comb][i+1]] - ya[key3[comb][0]];
        }

        // Invert A matrix
        det = A3[comb][0][0]*A3[comb][1][1] - A3[comb][0][1]*A3[comb][1][0];
        if (det == 0) {
            qDebug() << "Matrix is not invertible! (det = 0)";
        } else {
            A_inv3[comb][0][0] = A3[comb][1][1]/det;
            A_inv3[comb][1][1] = A3[comb][0][0]/det;
            A_inv3[comb][0][1] = -A3[comb][0][1]/det;
            A_inv3[comb][1][0] = -A3[comb][1][0]/det;
        }
    }
}

void MainWindow::matrix_init4()
{
    // Local variables
    double At[2][3], temp2x2[2][2], temp_inv[2][2], det;

    // Populate combination array
    int comb = 0;
    // set key values
    for(int i=0; i<ANCHORS; i++) {
        for(int j=i+1; j<ANCHORS; j++) {
            for(int k=j+1; k<ANCHORS; k++) {
                for(int l=k+1; l<ANCHORS; l++) {
                    key4[comb][0] = i;
                    key4[comb][1] = j;
                    key4[comb][2] = k;
                    key4[comb][3] = l;
//                    qDebug() << i << j << k << l;
                    comb++;
                }
            }
        }
    }

    for(comb=0; comb<15; comb++) {
        // Populate A and At matrix
        for(int i=0; i<3; i++){
            A4[comb][i][0] = xa[key4[comb][i+1]] - xa[key4[comb][0]];
            A4[comb][i][1] = ya[key4[comb][i+1]] - ya[key4[comb][0]];
            At[0][i] = A4[comb][i][0];
            At[1][i] = A4[comb][i][1];
        }
        // Find (A^T * A)
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
                temp2x2[i][j] = 0;
                for(int k=0; k<3; k++){
                    temp2x2[i][j] += At[i][k]*A4[comb][k][j];
                }
            }
        }
        // Inverse temp2x2
        det = temp2x2[0][0]*temp2x2[1][1] - temp2x2[0][1]*temp2x2[1][0];
        if (det == 0) {
            qDebug() << "Matrix is not invertible! (det = 0)";
        } else {
            temp_inv[0][0] = temp2x2[1][1]/det;
            temp_inv[1][1] = temp2x2[0][0]/det;
            temp_inv[0][1] = -temp2x2[0][1]/det;
            temp_inv[1][0] = -temp2x2[1][0]/det;
        }
        // Find (A^T * A)^-1 * A^T
        for(int i=0; i<2; i++){
            for(int j=0; j<3; j++){
                A_inv4[comb][i][j] = 0;
                for(int k=0; k<2; k++){
                    A_inv4[comb][i][j] += temp_inv[i][k]*At[k][j];
                }
            }
        }
    }
}

void MainWindow::matrix_init5()
{
    // Local variables
    double At[2][4], temp2x2[2][2], temp_inv[2][2], det;

    // Populate combination array
    int comb = 0;
    // set key values
    for(int i=0; i<ANCHORS; i++) {
        for(int j=i+1; j<ANCHORS; j++) {
            for(int k=j+1; k<ANCHORS; k++) {
                for(int l=k+1; l<ANCHORS; l++) {
                    for(int m=l+1; m<ANCHORS; m++) {
                        key5[comb][0] = i;
                        key5[comb][1] = j;
                        key5[comb][2] = k;
                        key5[comb][3] = l;
                        key5[comb][4] = m;
//                        qDebug() << i << j << k << l << m;
                        comb++;
                    }
                }
            }
        }
    }

    for(comb=0; comb<6; comb++) {
        // Populate A and At matrix
        for(int i=0; i<4; i++){
            A5[comb][i][0] = xa[key5[comb][i+1]] - xa[key5[comb][0]];
            A5[comb][i][1] = ya[key5[comb][i+1]] - ya[key5[comb][0]];
            At[0][i] = A5[comb][i][0];
            At[1][i] = A5[comb][i][1];
        }
        // Find (A^T * A)
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
                temp2x2[i][j] = 0;
                for(int k=0; k<4; k++){
                    temp2x2[i][j] += At[i][k]*A5[comb][k][j];
                }
            }
        }
        // Inverse temp2x2
        det = temp2x2[0][0]*temp2x2[1][1] - temp2x2[0][1]*temp2x2[1][0];
        if (det == 0) {
            qDebug() << "Matrix is not invertible! (det = 0)";
        } else {
            temp_inv[0][0] = temp2x2[1][1]/det;
            temp_inv[1][1] = temp2x2[0][0]/det;
            temp_inv[0][1] = -temp2x2[0][1]/det;
            temp_inv[1][0] = -temp2x2[1][0]/det;
        }
        // Find (A^T * A)^-1 * A^T
        for(int i=0; i<2; i++){
            for(int j=0; j<4; j++){
                A_inv5[comb][i][j] = 0;
                for(int k=0; k<2; k++){
                    A_inv5[comb][i][j] += temp_inv[i][k]*At[k][j];
                }
            }
        }
    }
}

void MainWindow::matrix_init6()
{
    // Local variables
    double At[2][5], temp2x2[2][2], temp_inv[2][2], det;

    // Populate A and At matrix
    for(int i=0; i<5; i++){
        A6[i][0] = xa[i+1] - xa[0];
        A6[i][1] = ya[i+1] - ya[0];
        At[0][i] = A6[i][0];
        At[1][i] = A6[i][1];
    }

    // Find (A^T * A)
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            temp2x2[i][j] = 0;
            for(int k=0; k<5; k++){
                temp2x2[i][j] += At[i][k]*A6[k][j];
            }
        }
    }

    // Inverse temp2x2
    det = temp2x2[0][0]*temp2x2[1][1] - temp2x2[0][1]*temp2x2[1][0];
    if (det == 0) {
        qDebug() << "Matrix is not invertible! (det = 0)";
    } else {
        temp_inv[0][0] = temp2x2[1][1]/det;
        temp_inv[1][1] = temp2x2[0][0]/det;
        temp_inv[0][1] = -temp2x2[0][1]/det;
        temp_inv[1][0] = -temp2x2[1][0]/det;
    }

    // Find (A^T * A)^-1 * A^T
    for(int i=0; i<2; i++){
        for(int j=0; j<5; j++){
            A_inv6[i][j] = 0;
            for(int k=0; k<2; k++){
                A_inv6[i][j] += temp_inv[i][k]*At[k][j];
            }
        }
    }
}

anchor2key MainWindow::encodeEnableAnchors()
{
    anchor2key data;
    int key2key[ANCHORS];

//    qDebug() << enabled[0] << enabled[1] << enabled[2] << enabled[3] << enabled[4] << enabled[5];

    data.totalAnchors = 0;
    for(int idx=0; idx<ANCHORS; idx++)
    {
        if(enabled[idx]) {
            key2key[data.totalAnchors] = idx;
            data.totalAnchors++;
        }
    }

    switch (data.totalAnchors) {
        case 3:
//            qDebug() << "3!";
//            qDebug() << key2key[0] << key2key[1] << key2key[2];
            for(int comb=0; comb<20; comb++) {
//                qDebug() << comb;
                if(key2key[0] == key3[comb][0] && key2key[1] == key3[comb][1] && key2key[2] == key3[comb][2]) {
                    data.finalKey = comb;
                    break;
                }
            }
            break;
        case 4:
//            qDebug() << "4!";
//            qDebug() << key2key[0] << key2key[1] << key2key[2] << key2key[3];
            for(int comb=0; comb<15; comb++) {
//                qDebug() << comb;
                if(key2key[0] == key4[comb][0] && key2key[1] == key4[comb][1] && key2key[2] == key4[comb][2] && key2key[3] == key4[comb][3]) {
                    data.finalKey = comb;
                    break;
                }
            }
            break;
        case 5:
//            qDebug() << "5!";
//            qDebug() << key2key[0] << key2key[1] << key2key[2] << key2key[3] << key2key[4];
            for(int comb=0; comb<6; comb++) {
//                qDebug() << comb;
                if(key2key[0] == key5[comb][0] && key2key[1] == key5[comb][1] && key2key[2] == key5[comb][2] && key2key[3] == key5[comb][3] && key2key[4] == key5[comb][4]) {
                    data.finalKey = comb;
                    break;
                }
            }
            break;
        case 6:
            data.finalKey = 0;
            break;
        default:
            break;
    }

//    qDebug() << "Total Anchors = " << data.totalAnchors << ", Best combo = " << data.finalKey;

    return data;
}
