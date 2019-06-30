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
    // Kp = Kp_;
    // Kd = Kd_;
    // Ki = Ki_;
    p[0] = Kp_;
    p[1] = Kd_;
    p[2] = Ki_;
    p_error = 0.0;
    d_error = 0.0;
    i_error = 0.0;
    prev_cte = 0.0; 

    dp[0] = 1.0;
    dp[1] = 1.0;
    dp[2] = 1.0;
    best_err = 0.0;
    err = 0.0;
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
    err = accum_err2/step;

}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
//   return -Kp*p_error - Kd*d_error - Ki*i_error;  // TODO: Add your total error calc here!
  return -p[0]*p_error - p[1]*d_error - p[2]*i_error;  // TODO: Add your total error calc here!
}

void PID::Twiddle(double err, int pid_flag){
    if(err < best_err){
        best_err = err;
        dp[pid_flag] *= 1.1;
    }
    else{
        p[pid_flag] += dp[pid_flag];
        dp[pid_flag] *= 0.9;
    }
}