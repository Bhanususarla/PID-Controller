#include "PID.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	//= {Kp, Ki, Kd};
	// = {0.1*Kp, 0.1*Ki, 0.1*Kd};	
	p_error = 0;
	i_error = 0;
	d_error = 0;
}

void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;
	iter += 1;
	std::cout << iter << std::endl;
}

double PID::TotalError() {
	return -Kp * p_error - Kd * d_error - Ki * i_error;
}

// Twiddle loop to optimize coefficients Kp, Ki, Kd
// Not implemented as it is successful only if looped over the simulator several times
void PID::Twiddle(double cte) {

	//avg = avg + cte;
	//avg = avg/(iter - 100);
	//best_cte = abs(cte);
	//if ((dp[0] + dp[1] + dp[2]) > 0.02) {

		for (int i=0; i<p.size(); i++) {
			if (abs(cte) < abs(best_cte)){					
				p[i] += dp[i];
				dp[i] *= 1.1;				
				best_cte = cte;											
			} else{
				if (abs(cte) > abs(p_error)){					
					p[i] -= dp[i];
					dp[i] *= 0.9;										
				} else{
					p[i] += dp[i];
					dp[i] *= 1.1;
					best_cte = p_error;				    			    
				}												
			}			
		}
	//}
	Kp = p[0];
	Ki = p[1];
	Kd = p[2];
	std::cout << "best_cte " << best_cte << std::endl;
}

	
