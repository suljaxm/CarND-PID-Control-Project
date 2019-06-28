#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
    Kp = Kp_;
    Kd = Kd_;
    Ki = Ki_;
    p_error = 0.0;
    d_error = 0.0;
    i_error = 0.0;
    prev_cte = 0.0; 

    dp[0] = 1.0;
    dp[1] = 1.0;
    dp[2] = 1.0;
    best_err = 0.0;
    accum_err2 = 0.0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
    p_error = cte;
    d_error = cte - prev_cte;
    i_error += cte;

    prev_cte = cte;  // the last cte in diferential error.
    
    accum_err2 += cte*cte;
    best_err = accum_err2/step;

}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return -Kp*p_error - Kd*d_error - Ki*i_error;  // TODO: Add your total error calc here!
}

void PID::Twiddle(double tol=0.2){
    
}