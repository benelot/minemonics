/*
 * NumericUtils.hpp
 *
 *  Created on: Nov 2, 2015
 *      Author: leviathan
 */

#ifndef UTILS_NUMERICUTILS_HPP_
#define UTILS_NUMERICUTILS_HPP_

/*
 *
 */
class NumericUtils {
public:
	NumericUtils();
	virtual ~NumericUtils();

	//
	//  Purpose:
	//
	//    RK4 takes one Runge-Kutta step for a scalar ODE.
	//
	//  Discussion:
	//
	//    It is assumed that an initial value problem, of the form
	//
	//      du/dt = f ( t, u )
	//      u(t0) = u0
	//
	//    is being solved.
	//
	//    If the user can supply current values of t, u, a stepsize dt, and a
	//    function to evaluate the derivative, this function can compute the
	//    fourth-order Runge Kutta estimate to the solution at time t+dt.
	//
	//  Licensing:
	//
	//    This code is distributed under the GNU LGPL license.
	//
	//  Modified:
	//
	//    09 October 2013
	//
	//  Author:
	//
	//    John Burkardt
	//
	//  Parameters:
	//
	//    Input, double T0, the current time.
	//
	//    Input, double U0, the solution estimate at the current time.
	//
	//    Input, double DT, the time step.
	//
	//    Input, double F ( double T, double U ), a function which evaluates
	//    the derivative, or right hand side of the problem.
	//
	//    Output, double RK4, the fourth-order Runge-Kutta solution estimate
	//    at time T0+DT.
	//
	static void calcRK4(double t0, double* u0, double dt,
		double derivFunction(double t, double u)) {
		double f0, f1, f2, f3;

		double t1, t2, t3;

		double u, u1, u2, u3;

		//  Get four sample values of the derivative.
		f0 = derivFunction(t0, (*u0) );

		t1 = t0 + dt / 2.0;
		u1 = (*u0)  + dt * f0 / 2.0;
		f1 = derivFunction(t1, u1);

		t2 = t0 + dt / 2.0;
		u2 = (*u0)  + dt * f1 / 2.0;
		f2 = derivFunction(t2, u2);

		t3 = t0 + dt;
		u3 = (*u0)  + dt * f2;
		f3 = derivFunction(t3, u3);

		//  Combine to estimate the solution at time T0 + DT.
		u = (*u0) + dt * (f0 + 2.0 * f1 + 2.0 * f2 + f3) / 6.0;


		(*u0) = u;
	}
	//
	//  Purpose:
	//
	//    RK4VEC takes one Runge-Kutta step for a vector ODE.
	//
	//  Discussion:
	//
	//    It is assumed that an initial value problem, of the form
	//
	//      du/dt = f ( t, u )
	//      u(t0) = u0
	//
	//    is being solved.
	//
	//    If the user can supply current values of t, u, a stepsize dt, and a
	//    function to evaluate the derivative, this function can compute the
	//    fourth-order Runge Kutta estimate to the solution at time t+dt.
	//
	//  Licensing:
	//
	//    This code is distributed under the GNU LGPL license.
	//
	//  Modified:
	//
	//    09 October 2013
	//
	//  Author:
	//
	//    John Burkardt
	//
	//  Parameters:
	//
	//    Input, double T0, the current time.
	//
	//    Input, int M, the spatial dimension.
	//
	//    Input, double U0[M], the solution estimate at the current time.
	//
	//    Input, double DT, the time step.
	//
	//    Input, double *F ( double T, int M, double U[] ), a function which evaluates
	//    the derivative, or right hand side of the problem.
	//
	//    Output, double RK4VEC[M], the fourth-order Runge-Kutta solution estimate
	//    at time T0+DT.
	//
	static void calcRK4(double t0, int dimensions, double* u0, double dt,
		double *derivFunction(double t, int dimensions, double u[])) {
		double *f0, *f1, *f2, *f3;
		int i;
		double t1, t2, t3;
		double *u, *u1, *u2, *u3;

		//  Get four sample values of the derivative.
		f0 = derivFunction(t0, dimensions, u0);

		t1 = t0 + dt / 2.0;
		u1 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u1[i] = u0[i] + dt * f0[i] / 2.0;
		}
		f1 = derivFunction(t1, dimensions, u1);

		t2 = t0 + dt / 2.0;
		u2 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u2[i] = u0[i] + dt * f1[i] / 2.0;
		}
		f2 = derivFunction(t2, dimensions, u2);

		t3 = t0 + dt;
		u3 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u3[i] = u0[i] + dt * f2[i];
		}
		f3 = derivFunction(t3, dimensions, u3);

		u = new double[dimensions];
		for (i = 0; i < dimensions; i++) { //  Combine them to estimate the solution.
			u[i] = u0[i]
				+ dt * (f0[i] + 2.0 * f1[i] + 2.0 * f2[i] + f3[i]) / 6.0;
		}

		delete[] f0; //  Free memory.
		delete[] f1; //  Free memory.
		delete[] f2; //  Free memory.
		delete[] f3; //  Free memory.
		delete[] u1; //  Free memory.
		delete[] u2; //  Free memory.
		delete[] u3; //  Free memory.

		for (i = 0; i < dimensions; i++) { //  Combine them to estimate the solution.
			u0[i] = u[i];
		}
		delete[] u;
	}
};

#endif /* UTILS_NUMERICUTILS_HPP_ */
