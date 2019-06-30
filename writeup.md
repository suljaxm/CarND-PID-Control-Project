## Writeup

**PID Controller**

The goals / steps of this project are the following:

* The PID procedure follows what was taught in the lessons.
* Describe the eect each of the P, I, D components had in your implementation.
* Describe how the nal hyperparameters were chosen.
* The vehicle must successfully drive a lap around the track.

------------------
### Main program module(PID):
-----------
- **Init**：Initialize PID.
- **UpdateError**：Update the PID error variables given cross track error.
- **TotalError**：Calculate the total PID error.
- **Twiddle**：Twiddle calculate the PID coefficients.
---------
### Reflection
---------------
### 1.Describe the effect each of the P, I, D components had in your implementation.
*(PID stands for Proportional Integral Derivative)*
 ####  1.1 P Controller
The larger the scale, the smaller the magnification of the controller, the more stable the curve of the controlled parameters. The smaller the scale, the larger the magnification of the controller, and the more fluctuating the curve of the controlled parameters.
 #### 1.2 D Controller
Differential action is mainly used to overcome the lag of the controlled object, and is often used in temperature control system.In addition to differential action, attention should be paid to the lag of measurement transmission when using the control system, such as the selection of temperature measuring elements and the installation location.
 ####  1.3 I Controller
The integral function of the controller is set to eliminate the residual error of the automatic control system.

### 2. Describe how the final hyperparameters(P, I, D coefficients) were chosen
At first, I set all **PID** coefficients to 0.01. First, I kept the coefficients of **I** and **D** unchanged, and only adjusted **P** parameters It was found that when **P**=1.5, it was relatively good.
After that, I adjusted the **D** parameter and found that when **D** =6, it was relatively good and I could run a long distance.
Finally, I kept the parameter of **D** unchanged and adjusted the parameter of **P**. When **P**=0.25, I could finish the whole course successfully. So the **PID** coefficients I manually set is,
```
P = 0.25, I = 0.01, D = 6
```
### 3. In the future

#### 1.About the Twiddle ([line 74 to line 97](./src/main.cpp)).
 I designed the code according to the Twiddle algorithm, but the effect was not good, so I haven't found the reason for it. This work will be improved next time.





