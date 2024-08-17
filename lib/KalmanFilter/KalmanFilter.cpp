#include "KalmanFilter.h"

using namespace std;

double KALMAN(double U);

//Kalman Filter function

double KALMAN(double U) {

    static const double R = 40; //noise covariance
    static const double H = 1.00; // measurement map scalar
    static double Q = 10; //initial stimated covariance
    static double P = 0; //initial error covariance (0)
    static double U_hat = 0; //initial estimated state (here we dont know?)
    static double K = 0;

    K = P*H/(H*P*H+R); //updates kalman gain
    U_hat = U_hat + K*(U-H*U_hat); //updates estimated state

    P = (1-K*H)*P+Q; //updates error covariance

    return U_hat;

}

