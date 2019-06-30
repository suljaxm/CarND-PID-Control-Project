#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;

  PID pid;
  /**
   * TODO: Initialize the pid variable.
   */
  pid.Init(0.25, 0.001, 6.01);
  
  h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          if(pid.step < 1){ //To optimize the PID coefficients
            pid.step++;
            
            pid.UpdateError(cte);
            steer_value = pid.TotalError();
            pid.best_err = pid.err;
          }
          else if(pid.step < -1){
            pid.step++;
            int pid_flag = int((pid.step%9)/3);     //Select a controller parameter from [0, 1, 2]
            std::cout << "p_step_pre: " << pid.p_step << std::endl;
            std::cout << "pid_flag: " << pid_flag << std::endl;
            std::cout << "step:" << pid.step << " error:" << pid.err << " best_error:" << pid.best_err <<std::endl;
            if(pid.p_step == 0){
                pid.p[pid_flag] += pid.dp[pid_flag];
                pid.UpdateError(cte);
                steer_value = pid.TotalError();
                if(pid.err < pid.best_err){
                    pid.Twiddle(pid.err, pid_flag);
                }
                else{
                    pid.p_step = 1;
                }
            }
            else{
                pid.p[pid_flag] -= 2*pid.dp[pid_flag];
                pid.UpdateError(cte);
                steer_value = pid.TotalError();
                pid.Twiddle(pid.err, pid_flag);
                pid.p_step = 0;
            }
            std::cout << "p_step: " << pid.p_step << std::endl;
          }
          else{ //Use the optimized PID coefficients with Twiddle
            pid.step++;
            pid.UpdateError(cte);
            steer_value = pid.TotalError();
          }
          
         //limit the range of steering value
         if(steer_value > 1)steer_value = 1;
         if(steer_value < -1)steer_value = -1;


          // DEBUG
          if(pid.step%100 == 0){
            std::cout << std::endl;
            std::cout << "step:" << pid.step << " error:" << pid.err << " best_error:" << pid.best_err <<std::endl;
            std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;
            std::cout << "dp[0]:" << pid.dp[0] << " dp[1]:" << pid.dp[1] << " dp[2]:" << pid.dp[2] <<std::endl;
            std::cout << "Kp:" << pid.p[0] << " ki:" << pid.p[1] << " Kd:" << pid.p[2] <<std::endl <<std::endl;
          }


          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = 0.3;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
        //   std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}