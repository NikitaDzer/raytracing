#ifndef C_SOLVEQUADRATIC_H
#define C_SOLVEQUADRATIC_H

/*!
 * @brief Struct for quadratic equation's roots
 * @field numberOfRoots INT Number of calculated roots
 * @field x1            DOUBLE First root of quadratic equation
 * @field x2            DOUBLE Second root of quadratic equation
 */
struct QuadraticRoots {
    int numberOfRoots;
    double x1;
    double x2;
};

/*!
 * @brief Solves a quadratic equation and returns number of roots (ax^2 + bx + c = 0)
 * @param a     DOUBLE Quadratic equation's coefficients 'A'
 * @param b     DOUBLE Quadratic equation's coefficients 'B'
 * @param c     DOUBLE Quadratic equation's coefficients 'C'
 * @param roots DOUBLE[] Array for calculated roots
 * @return 1 if equation was solved correctly
 */
int solveQuadratic(const double a, const double b, const double c, QuadraticRoots* quadraticRoots);

#endif //C_SOLVEQUADRATIC_H
