#include <cmath>
#include "quadratic.h"

/*!
 * @brief Number is almost zero, if it's in range [-EPSILON; +EPSILON]
 */
static const double EPSILON = 1e-6;

/*!
 * @brief Gets number and returns true if it's almost zero (in range [-EPSILON; +EPSILON])
 * @param a DOUBLE Putted number
 * @return 1 if putted number is almost zero (in range [-EPSILON; +EPSILON])
 */
static int isZero(const double a) {
    return fabs(a) <= EPSILON;
}

/*!
 * @brief Gets number and returns true if it's negative (lower zero) and is not almost zero (not in range [-EPSILON; +EPSILON])
 * @param a Putted number
 * @return 1 if putted number is negative (lower zero) and is not almost zero (not in range [-EPSILON; +EPSILON])
 */
static int isNegative(const double a) {
    return a < 0 && !isZero(a);
}

/*!
 * @brief Solves a linear equation and returns number of roots (ax + b = 0)
 * @param a     DOUBLE Linear equation's coefficients 'A'
 * @param b     DOUBLE Linear equation's coefficients 'B'
 * @param roots DOUBLE[] Array for calculated roots
 * @return Number of roots (1 - one root; 0 - zero roots; -1 - infinity roots)
 */
static int solveLinear(const double a, const double b,  QuadraticRoots* quadraticRoots) {
    if (isZero(a) && isZero(b))
        quadraticRoots->numberOfRoots = -1; // infinity roots
    else if (isZero(a))
        quadraticRoots->numberOfRoots = 0; // no roots
    else {
        quadraticRoots->x1 = -b / a;
        quadraticRoots->numberOfRoots = 1; // one root
    }
    
    // return 1;
    return -1 <= quadraticRoots->numberOfRoots && quadraticRoots->numberOfRoots <= 1;
}

int solveQuadratic(const double a, const double b, const double c, QuadraticRoots* quadraticRoots) {
    if (isZero(a))
        return solveLinear(b, c, quadraticRoots); // linear equation
    
    /*
if (isZero(b)) {
    if (isPositive(a) && isPositive(c))
        quadraticRoots->numberOfRoots = 0;
    else if (isZero(c)) {
        quadraticRoots->x1 = 0;
        quadraticRoots->numberOfRoots = 1;
    }
    else {
        double root = sqrt(-c / a);
        
        quadraticRoots->x1 = root;
        quadraticRoots->x2 = -root;
        quadraticRoots->numberOfRoots = 2;
    }
}
else if (isZero(c)) {
    quadraticRoots->x1 = 0;
    quadraticRoots->x2 = -b / a;
    quadraticRoots->numberOfRoots = 2;
}
else {
    double discriminant = b * b - 4 * a * c;
    if (!isPositive(discriminant))
        quadraticRoots->numberOfRoots = 0;
    else if (isZero(discriminant)) {
        quadraticRoots->x1 = -b / (2 * a);
        quadraticRoots->numberOfRoots = 1;
    }
    else {
        double sqrtDiscriminant = sqrt(discriminant),
                doubleA          = 2 * a;
        
        quadraticRoots->x1 = (-b + sqrtDiscriminant) / doubleA;
        quadraticRoots->x2 = (-b - sqrtDiscriminant) / doubleA;
        quadraticRoots->numberOfRoots = 2;
    }
}
*/
    
    double discriminant = b * b - 4 * a * c;
    
    if (isNegative(discriminant))
        quadraticRoots->numberOfRoots = 0;
    else if (isZero(discriminant)) {
        quadraticRoots->x1 = -b / (2 * a);
        quadraticRoots->numberOfRoots = 1;
    }
    else {
        double sqrtDiscriminant = sqrt(discriminant),
               doubledA         = 2 * a;
        
        quadraticRoots->x1 = (-b - sqrtDiscriminant) / doubledA;
        quadraticRoots->x2 = (-b + sqrtDiscriminant) / doubledA;
        quadraticRoots->numberOfRoots = 2;
    }
    
    // return 1;
    return -1 <= quadraticRoots->numberOfRoots && quadraticRoots->numberOfRoots <= 2;
}
