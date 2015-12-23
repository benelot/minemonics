#ifndef UTILS_NUMERICUTILS_HPP_
#define UTILS_NUMERICUTILS_HPP_

//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/chaotic/ChaoticController.hpp>

//## view headers
//## utils headers

/**
 * @brief		The Numeric utils is a helper class to perform numerical methods
 * @details		Details
 * @date		2015-11-02
 * @author		Benjamin Ellenberger
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
		f0 = dt * derivFunction(t0, (*u0));

		t1 = t0 + dt / 2.0;
		u1 = (*u0) + f0 / 2.0;
		f1 = dt * derivFunction(t1, u1);

		t2 = t0 + dt / 2.0;
		u2 = (*u0) + f1 / 2.0;
		f2 = dt * derivFunction(t2, u2);

		t3 = t0 + dt;
		u3 = (*u0) + f2;
		f3 = dt * derivFunction(t3, u3);

		//  Combine to estimate the solution at time T0 + DT.
		u = (*u0) + (f0 + 2.0 * f1 + 2.0 * f2 + f3) / 6.0;

		(*u0) = u;
	}

	static void calcRK6(double t0, double* u0, double dt,
		double derivFunction(double t, double u)) {
		double f0, f1, f2, f3, f4, f5;

		double t1, t2, t3, t4, t5;

		double u, u1, u2, u3, u4, u5;
		//-------------------------------
		// Start the Runge-Kutta solving
		//-------------------------------
		//		double x = currentState.getx();
		//		double y = currentState.gety();
		//		double z = currentState.getz();
		//		double t = currentState.getTime();

		//----------------------------
		// Calculate k1x, k1y and k1z
		//----------------------------
		f0 = dt * derivFunction(t0, (*u0));
		//		double tempt = t;
		//		double tempx = x;
		//		double tempy = y;
		//		double tempz = z;
		//		double k1x = dt * f(tempx, tempy, tempz, tempt);
		//		double k1y = dt * g(tempx, tempy, tempz, tempt);
		//		double k1z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k2x, k2y and k2z
		//----------------------------
		t1 = t0 + dt / 4.0;
		u1 = (*u0) + f0 / 4.0;
		f1 = dt * derivFunction(t1, u1);

		//		tempt = t + dt / 4.0;
		//		tempx = x + k1x / 4.0;
		//		tempy = y + k1y / 4.0;
		//		tempz = z + k1z / 4.0;
		//		double k2x = dt * f(tempx, tempy, tempz, tempt);
		//		double k2y = dt * g(tempx, tempy, tempz, tempt);
		//		double k2z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k3x, k3y and k3z
		//----------------------------

		t2 = t0 + (3.0 / 8.0) * dt;
		u2 = (*u0) + (3.0 / 32.0) * f0 + (9.0 / 32.0) * f1;
		f2 = dt * derivFunction(t2, u2);

		//		tempt = t + (3.0 / 8.0) * dt;
		//		tempx = x + (3.0 / 32.0) * k1x + (9.0 / 32.0) * k2x;
		//		tempy = y + (3.0 / 32.0) * k1y + (9.0 / 32.0) * k2y;
		//		tempz = z + (3.0 / 32.0) * k1z + (9.0 / 32.0) * k2z;
		//		double k3x = dt * f(tempx, tempy, tempz, tempt);
		//		double k3y = dt * g(tempx, tempy, tempz, tempt);
		//		double k3z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k4x, k4y and k4z
		//----------------------------
		t3 = t0 + (12.0 / 13.0) * dt;
		u3 = (*u0) + (1932.0 / 2197.0) * f0 - (7200.0 / 2197.0) * f1
			+ (7296.0 / 2197.0) * f2;
		f3 = dt * derivFunction(t3, u3);

		//		tempt = t + (12.0 / 13.0) * dt;
		//		tempx = x + (1932.0 / 2197.0) * k1x - (7200.0 / 2197.0) * k2x
		//			+ (7296.0 / 2197.0) * k3x;
		//		tempy = y + (1932.0 / 2197.0) * k1y - (7200.0 / 2197.0) * k2y
		//			+ (7296.0 / 2197.0) * k3y;
		//		tempz = z + (1932.0 / 2197.0) * k1z - (7200.0 / 2197.0) * k2z
		//			+ (7296.0 / 2197.0) * k3z;
		//		double k4x = dt * f(tempx, tempy, tempz, tempt);
		//		double k4y = dt * g(tempx, tempy, tempz, tempt);
		//		double k4z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k5x, k5y and k5z
		//----------------------------
		t4 = t0 + dt;
		u4 = (*u0) + (439.0 / 216.0) * f0 - 8.0 * f1 + (3680.0 / 513.0) * f2
			- (845.0 / 4104.0) * f3;
		f4 = dt * derivFunction(t4, u4);

		//		tempt = t + dt;
		//		tempx = x + (439.0 / 216.0) * k1x - 8.0 * k2x + (3680.0 / 513.0) * k3x
		//			- (845.0 / 4104.0) * k4x;
		//		tempy = y + (439.0 / 216.0) * k1y - 8.0 * k2y + (3680.0 / 513.0) * k3y
		//			- (845.0 / 4104.0) * k4y;
		//		tempz = z + (439.0 / 216.0) * k1z - 8.0 * k2z + (3680.0 / 513.0) * k3z
		//			- (845.0 / 4104.0) * k4z;
		//		double k5x = dt * f(tempx, tempy, tempz, tempt);
		//		double k5y = dt * g(tempx, tempy, tempz, tempt);
		//		double k5z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k6x, k6y and k6z
		//----------------------------
		t5 = t0 + dt / 2.0;
		u5 = (*u0) - (8.0 / 27.0) * f0 + 2.0 * f1 - (3544.0 / 2565.0) * f2
			+ (1859.0 / 4104.0) * f3 - (11.0 / 40.0) * f4;
		f5 = dt * derivFunction(t5, u5);

		//		tempt = t + dt / 2.0;
		//		tempx = x - (8.0 / 27.0) * k1x + 2.0 * k2x - (3544.0 / 2565.0) * k3x
		//			+ (1859.0 / 4104.0) * k4x - (11.0 / 40.0) * k5x;
		//		tempy = y - (8.0 / 27.0) * k1y + 2.0 * k2y - (3544.0 / 2565.0) * k3y
		//			+ (1859.0 / 4104.0) * k4y - (11.0 / 40.0) * k5y;
		//		tempz = z - (8.0 / 27.0) * k1z + 2.0 * k2z - (3544.0 / 2565.0) * k3z
		//			+ (1859.0 / 4104.0) * k4z - (11.0 / 40.0) * k5z;
		//		double k6x = dt * f(tempx, tempy, tempz, tempt);
		//		double k6y = dt * g(tempx, tempy, tempz, tempt);
		//		double k6z = dt * h(tempx, tempy, tempz, tempt);

		//-----------------------------------------------
		// Compute the next t, next x, y and z values,
		// with global error O(h^5).
		//-----------------------------------------------

		//  Combine them to estimate the solution.
		u = (*u0) + (16.0 / 135.0) * f0 + (6656.0 / 12825.0) * f2
			+ (28561.0 / 56430.0) * f3 - (9.0 / 50.0) * f4 + (2.0 / 55.0) * f5;

		//  Combine them to estimate the solution.
		(*u0) = u;

		//		currentState.setx(
		//			x + (16.0 / 135.0) * k1x + (6656.0 / 12825.0) * k3x
		//				+ (28561.0 / 56430.0) * k4x - (9.0 / 50.0) * k5x
		//				+ (2.0 / 55.0) * k6x);
		//
		//		currentState.sety(
		//			y + (16.0 / 135.0) * k1y + (6656.0 / 12825.0) * k3y
		//				+ (28561.0 / 56430.0) * k4y - (9.0 / 50.0) * k5y
		//				+ (2.0 / 55.0) * k6y);
		//
		//		currentState.setz(
		//			z + (16.0 / 135.0) * k1z + (6656.0 / 12825.0) * k3z
		//				+ (28561.0 / 56430.0) * k4z - (9.0 / 50.0) * k5z
		//				+ (2.0 / 55.0) * k6z);
		//
		//		currentState.setTime(currentState.getTime() + dt);
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

	static void calcRK6(double t0, int dimensions, double* u0, double dt,
		double *derivFunction(double t, int dimensions, double u[])) {
		double *f0, *f1, *f2, *f3, *f4, *f5;
		int i;
		double t1, t2, t3, t4, t5;
		double *u, *u1, *u2, *u3, *u4, *u5;

		//-------------------------------
		// Start the Runge-Kutta solving
		//-------------------------------
//		double x = currentState.getx();
//		double y = currentState.gety();
//		double z = currentState.getz();
//		double t = currentState.getTime();

		//----------------------------
		// Calculate k1x, k1y and k1z
		//----------------------------
		f0 = derivFunction(t0, dimensions, u0);
//		double tempt = t;
//		double tempx = x;
//		double tempy = y;
//		double tempz = z;
//		double k1x = dt * f(tempx, tempy, tempz, tempt);
//		double k1y = dt * g(tempx, tempy, tempz, tempt);
//		double k1z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k2x, k2y and k2z
		//----------------------------
		t1 = t0 + dt / 4.0;
		u1 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u1[i] = u0[i] + dt * f0[i] / 4.0;
		}

		f1 = derivFunction(t1, dimensions, u1);

//		tempt = t + dt / 4.0;
//		tempx = x + k1x / 4.0;
//		tempy = y + k1y / 4.0;
//		tempz = z + k1z / 4.0;
//		double k2x = dt * f(tempx, tempy, tempz, tempt);
//		double k2y = dt * g(tempx, tempy, tempz, tempt);
//		double k2z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k3x, k3y and k3z
		//----------------------------

		t2 = t0 + (3.0 / 8.0) * dt;
		u2 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u2[i] = u0[i] + (3.0 / 32.0) * dt * f0[i]
				+ (9.0 / 32.0) * dt * f1[i];
		}

		f2 = derivFunction(t2, dimensions, u2);

//		tempt = t + (3.0 / 8.0) * dt;
//		tempx = x + (3.0 / 32.0) * k1x + (9.0 / 32.0) * k2x;
//		tempy = y + (3.0 / 32.0) * k1y + (9.0 / 32.0) * k2y;
//		tempz = z + (3.0 / 32.0) * k1z + (9.0 / 32.0) * k2z;
//		double k3x = dt * f(tempx, tempy, tempz, tempt);
//		double k3y = dt * g(tempx, tempy, tempz, tempt);
//		double k3z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k4x, k4y and k4z
		//----------------------------
		t3 = t0 + (12.0 / 13.0) * dt;
		u3 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u3[i] = u0[i] + (1932.0 / 2197.0) * dt * f0[i]
				- (7200.0 / 2197.0) * dt * f1[i]
				+ (7296.0 / 2197.0) * dt * f2[i];
		}

		f3 = derivFunction(t3, dimensions, u3);

//		tempt = t + (12.0 / 13.0) * dt;
//		tempx = x + (1932.0 / 2197.0) * k1x - (7200.0 / 2197.0) * k2x
//			+ (7296.0 / 2197.0) * k3x;
//		tempy = y + (1932.0 / 2197.0) * k1y - (7200.0 / 2197.0) * k2y
//			+ (7296.0 / 2197.0) * k3y;
//		tempz = z + (1932.0 / 2197.0) * k1z - (7200.0 / 2197.0) * k2z
//			+ (7296.0 / 2197.0) * k3z;
//		double k4x = dt * f(tempx, tempy, tempz, tempt);
//		double k4y = dt * g(tempx, tempy, tempz, tempt);
//		double k4z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k5x, k5y and k5z
		//----------------------------
		t4 = t0 + dt;
		u4 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u4[i] = u0[i] + (439.0 / 216.0) * dt * f0[i] - 8.0 * dt * f1[i]
				+ (3680.0 / 513.0) * dt * f2[i] - (845.0 / 4104.0) * dt * f3[i];
		}

		f4 = derivFunction(t4, dimensions, u4);

//		tempt = t + dt;
//		tempx = x + (439.0 / 216.0) * k1x - 8.0 * k2x + (3680.0 / 513.0) * k3x
//			- (845.0 / 4104.0) * k4x;
//		tempy = y + (439.0 / 216.0) * k1y - 8.0 * k2y + (3680.0 / 513.0) * k3y
//			- (845.0 / 4104.0) * k4y;
//		tempz = z + (439.0 / 216.0) * k1z - 8.0 * k2z + (3680.0 / 513.0) * k3z
//			- (845.0 / 4104.0) * k4z;
//		double k5x = dt * f(tempx, tempy, tempz, tempt);
//		double k5y = dt * g(tempx, tempy, tempz, tempt);
//		double k5z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k6x, k6y and k6z
		//----------------------------
		t5 = t0 + dt / 2.0;
		u5 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u5[i] = u0[i] - (8.0 / 27.0) * dt * f0[i] + 2.0 * dt * f1[i]
				- (3544.0 / 2565.0) * dt * f2[i]
				+ (1859.0 / 4104.0) * dt * f3[i] - (11.0 / 40.0) * dt * f4[i];
		}

		f5 = derivFunction(t5, dimensions, u5);

//		tempt = t + dt / 2.0;
//		tempx = x - (8.0 / 27.0) * k1x + 2.0 * k2x - (3544.0 / 2565.0) * k3x
//			+ (1859.0 / 4104.0) * k4x - (11.0 / 40.0) * k5x;
//		tempy = y - (8.0 / 27.0) * k1y + 2.0 * k2y - (3544.0 / 2565.0) * k3y
//			+ (1859.0 / 4104.0) * k4y - (11.0 / 40.0) * k5y;
//		tempz = z - (8.0 / 27.0) * k1z + 2.0 * k2z - (3544.0 / 2565.0) * k3z
//			+ (1859.0 / 4104.0) * k4z - (11.0 / 40.0) * k5z;
//		double k6x = dt * f(tempx, tempy, tempz, tempt);
//		double k6y = dt * g(tempx, tempy, tempz, tempt);
//		double k6z = dt * h(tempx, tempy, tempz, tempt);

		//-----------------------------------------------
		// Compute the next t, next x, y and z values,
		// with global error O(h^5).
		//-----------------------------------------------
		u = new double[dimensions];
		for (i = 0; i < dimensions; i++) { //  Combine them to estimate the solution.
			u[i] = u0[i] + (16.0 / 135.0) * dt * f0[i]
				+ (6656.0 / 12825.0) * dt * f2[i]
				+ (28561.0 / 56430.0) * dt * f3[i] - (9.0 / 50.0) * dt * f4[i]
				+ (2.0 / 55.0) * dt * f5[i];
		}

		delete[] f0; //  Free memory.
		delete[] f1; //  Free memory.
		delete[] f2; //  Free memory.
		delete[] f3; //  Free memory.
		delete[] f4; //  Free memory.
		delete[] f5; //  Free memory.
		delete[] u1; //  Free memory.
		delete[] u2; //  Free memory.
		delete[] u3; //  Free memory.
		delete[] u4; //  Free memory.
		delete[] u5; //  Free memory.

		for (i = 0; i < dimensions; i++) { //  Combine them to estimate the solution.
			u0[i] = u[i];
		}
		delete[] u;

//		currentState.setx(
//			x + (16.0 / 135.0) * k1x + (6656.0 / 12825.0) * k3x
//				+ (28561.0 / 56430.0) * k4x - (9.0 / 50.0) * k5x
//				+ (2.0 / 55.0) * k6x);
//
//		currentState.sety(
//			y + (16.0 / 135.0) * k1y + (6656.0 / 12825.0) * k3y
//				+ (28561.0 / 56430.0) * k4y - (9.0 / 50.0) * k5y
//				+ (2.0 / 55.0) * k6y);
//
//		currentState.setz(
//			z + (16.0 / 135.0) * k1z + (6656.0 / 12825.0) * k3z
//				+ (28561.0 / 56430.0) * k4z - (9.0 / 50.0) * k5z
//				+ (2.0 / 55.0) * k6z);
//
//		currentState.setTime(currentState.getTime() + dt);
	}

	//TODO: Can I use the ChaoticController specific derivFunction without specifying ChaoticController explicitly?
	static void calcRK4(double t0, int dimensions, double* u0,
		ChaoticController* controller, double dt,
		double* derivFunction(double t, int dimensions, double u[],
			ChaoticController* controller)) {
		double *f0, *f1, *f2, *f3;
		int i;
		double t1, t2, t3;
		double *u, *u1, *u2, *u3;

		//  Get four sample values of the derivative.
		f0 = derivFunction(t0, dimensions, u0, controller);

		t1 = t0 + dt / 2.0;
		u1 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u1[i] = u0[i] + dt * f0[i] / 2.0;
		}
		f1 = derivFunction(t1, dimensions, u1, controller);

		t2 = t0 + dt / 2.0;
		u2 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u2[i] = u0[i] + dt * f1[i] / 2.0;
		}
		f2 = derivFunction(t2, dimensions, u2, controller);

		t3 = t0 + dt;
		u3 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u3[i] = u0[i] + dt * f2[i];
		}
		f3 = derivFunction(t3, dimensions, u3, controller);

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

	static void calcRK6(double t0, int dimensions, double* u0,
		ChaoticController* controller, double dt,
		double* derivFunction(double t, int dimensions, double u[],
			ChaoticController* controller)) {
		double *f0, *f1, *f2, *f3, *f4, *f5;
		int i;
		double t1, t2, t3, t4, t5;
		double *u, *u1, *u2, *u3, *u4, *u5;

		//-------------------------------
		// Start the Runge-Kutta solving
		//-------------------------------
//		double x = currentState.getx();
//		double y = currentState.gety();
//		double z = currentState.getz();
//		double t = currentState.getTime();

		//----------------------------
		// Calculate k1x, k1y and k1z
		//----------------------------
		f0 = derivFunction(t0, dimensions, u0, controller);
//		double tempt = t;
//		double tempx = x;
//		double tempy = y;
//		double tempz = z;
//		double k1x = dt * f(tempx, tempy, tempz, tempt);
//		double k1y = dt * g(tempx, tempy, tempz, tempt);
//		double k1z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k2x, k2y and k2z
		//----------------------------
		t1 = t0 + dt / 4.0;
		u1 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u1[i] = u0[i] + dt * f0[i] / 4.0;
		}

		f1 = derivFunction(t1, dimensions, u1, controller);

//		tempt = t + dt / 4.0;
//		tempx = x + k1x / 4.0;
//		tempy = y + k1y / 4.0;
//		tempz = z + k1z / 4.0;
//		double k2x = dt * f(tempx, tempy, tempz, tempt);
//		double k2y = dt * g(tempx, tempy, tempz, tempt);
//		double k2z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k3x, k3y and k3z
		//----------------------------

		t2 = t0 + (3.0 / 8.0) * dt;
		u2 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u2[i] = u0[i] + (3.0 / 32.0) * dt * f0[i]
				+ (9.0 / 32.0) * dt * f1[i];
		}

		f2 = derivFunction(t2, dimensions, u2, controller);

//		tempt = t + (3.0 / 8.0) * dt;
//		tempx = x + (3.0 / 32.0) * k1x + (9.0 / 32.0) * k2x;
//		tempy = y + (3.0 / 32.0) * k1y + (9.0 / 32.0) * k2y;
//		tempz = z + (3.0 / 32.0) * k1z + (9.0 / 32.0) * k2z;
//		double k3x = dt * f(tempx, tempy, tempz, tempt);
//		double k3y = dt * g(tempx, tempy, tempz, tempt);
//		double k3z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k4x, k4y and k4z
		//----------------------------
		t3 = t0 + (12.0 / 13.0) * dt;
		u3 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u3[i] = u0[i] + (1932.0 / 2197.0) * dt * f0[i]
				- (7200.0 / 2197.0) * dt * f1[i]
				+ (7296.0 / 2197.0) * dt * f2[i];
		}

		f3 = derivFunction(t3, dimensions, u3, controller);

//		tempt = t + (12.0 / 13.0) * dt;
//		tempx = x + (1932.0 / 2197.0) * k1x - (7200.0 / 2197.0) * k2x
//			+ (7296.0 / 2197.0) * k3x;
//		tempy = y + (1932.0 / 2197.0) * k1y - (7200.0 / 2197.0) * k2y
//			+ (7296.0 / 2197.0) * k3y;
//		tempz = z + (1932.0 / 2197.0) * k1z - (7200.0 / 2197.0) * k2z
//			+ (7296.0 / 2197.0) * k3z;
//		double k4x = dt * f(tempx, tempy, tempz, tempt);
//		double k4y = dt * g(tempx, tempy, tempz, tempt);
//		double k4z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k5x, k5y and k5z
		//----------------------------
		t4 = t0 + dt;
		u4 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u4[i] = u0[i] + (439.0 / 216.0) * dt * f0[i] - 8.0 * dt * f1[i]
				+ (3680.0 / 513.0) * dt * f2[i] - (845.0 / 4104.0) * dt * f3[i];
		}

		f4 = derivFunction(t4, dimensions, u4, controller);

//		tempt = t + dt;
//		tempx = x + (439.0 / 216.0) * k1x - 8.0 * k2x + (3680.0 / 513.0) * k3x
//			- (845.0 / 4104.0) * k4x;
//		tempy = y + (439.0 / 216.0) * k1y - 8.0 * k2y + (3680.0 / 513.0) * k3y
//			- (845.0 / 4104.0) * k4y;
//		tempz = z + (439.0 / 216.0) * k1z - 8.0 * k2z + (3680.0 / 513.0) * k3z
//			- (845.0 / 4104.0) * k4z;
//		double k5x = dt * f(tempx, tempy, tempz, tempt);
//		double k5y = dt * g(tempx, tempy, tempz, tempt);
//		double k5z = dt * h(tempx, tempy, tempz, tempt);

		//----------------------------
		// Calculate k6x, k6y and k6z
		//----------------------------
		t5 = t0 + dt / 2.0;
		u5 = new double[dimensions];
		for (i = 0; i < dimensions; i++) {
			u5[i] = u0[i] - (8.0 / 27.0) * dt * f0[i] + 2.0 * dt * f1[i]
				- (3544.0 / 2565.0) * dt * f2[i]
				+ (1859.0 / 4104.0) * dt * f3[i] - (11.0 / 40.0) * dt * f4[i];
		}

		f5 = derivFunction(t5, dimensions, u5, controller);

//		tempt = t + dt / 2.0;
//		tempx = x - (8.0 / 27.0) * k1x + 2.0 * k2x - (3544.0 / 2565.0) * k3x
//			+ (1859.0 / 4104.0) * k4x - (11.0 / 40.0) * k5x;
//		tempy = y - (8.0 / 27.0) * k1y + 2.0 * k2y - (3544.0 / 2565.0) * k3y
//			+ (1859.0 / 4104.0) * k4y - (11.0 / 40.0) * k5y;
//		tempz = z - (8.0 / 27.0) * k1z + 2.0 * k2z - (3544.0 / 2565.0) * k3z
//			+ (1859.0 / 4104.0) * k4z - (11.0 / 40.0) * k5z;
//		double k6x = dt * f(tempx, tempy, tempz, tempt);
//		double k6y = dt * g(tempx, tempy, tempz, tempt);
//		double k6z = dt * h(tempx, tempy, tempz, tempt);

		//-----------------------------------------------
		// Compute the next t, next x, y and z values,
		// with global error O(h^5).
		//-----------------------------------------------
		u = new double[dimensions];
		for (i = 0; i < dimensions; i++) { //  Combine them to estimate the solution.
			u[i] = u0[i] + (16.0 / 135.0) * dt * f0[i]
				+ (6656.0 / 12825.0) * dt * f2[i]
				+ (28561.0 / 56430.0) * dt * f3[i] - (9.0 / 50.0) * dt * f4[i]
				+ (2.0 / 55.0) * dt * f5[i];
		}

		delete[] f0; //  Free memory.
		delete[] f1; //  Free memory.
		delete[] f2; //  Free memory.
		delete[] f3; //  Free memory.
		delete[] f4; //  Free memory.
		delete[] f5; //  Free memory.
		delete[] u1; //  Free memory.
		delete[] u2; //  Free memory.
		delete[] u3; //  Free memory.
		delete[] u4; //  Free memory.
		delete[] u5; //  Free memory.

		for (i = 0; i < dimensions; i++) { //  Combine them to estimate the solution.
			u0[i] = u[i];
		}
		delete[] u;

//		currentState.setx(
//			x + (16.0 / 135.0) * k1x + (6656.0 / 12825.0) * k3x
//				+ (28561.0 / 56430.0) * k4x - (9.0 / 50.0) * k5x
//				+ (2.0 / 55.0) * k6x);
//
//		currentState.sety(
//			y + (16.0 / 135.0) * k1y + (6656.0 / 12825.0) * k3y
//				+ (28561.0 / 56430.0) * k4y - (9.0 / 50.0) * k5y
//				+ (2.0 / 55.0) * k6y);
//
//		currentState.setz(
//			z + (16.0 / 135.0) * k1z + (6656.0 / 12825.0) * k3z
//				+ (28561.0 / 56430.0) * k4z - (9.0 / 50.0) * k5z
//				+ (2.0 / 55.0) * k6z);
//
//		currentState.setTime(currentState.getTime() + dt);
	}
};

#endif /* UTILS_NUMERICUTILS_HPP_ */
