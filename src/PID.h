#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  /**
   * Twiddle calculate the PID coefficients 
   */
  void Twiddle(double err, int pid_flag);
  /**
   * The iteration steps
   */
  int step = 0;
  int p_step = 0;   //Choose one of [0,1]
  double best_err;
  double err;
  /**
   * PID Coefficients
   */ 
  double p[3]; //p[0]:Kp; p[1]:Kd; p[2]:Ki
  double dp[3];
 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;
  double prev_cte;
  /**
   * PID Coefficients
   */ 
//   double Kp;
//   double Ki;
//   double Kd;

  /**
   * twiddle parameter
   */
  
  double accum_err2;
};

#endif  // PID_H