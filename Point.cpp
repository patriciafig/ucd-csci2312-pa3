//
//  Point.cpp
//  PA3
//
//  Created by Patricia Figueroa on 3/22/16.

//

#include "Point.h"
#include "Exceptions.h"

#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>


namespace Clustering

{
    unsigned int Point::__idGen = 0;
    // Static ID generator
    void Point::rewindIdGen()
    {

    }
    //  Constructors

    Point::Point(unsigned int dim)

    {
        __id = __idGen++;

        // Assigns the dimension
        __dim = dim;
        __values = new double[__dim];

        for (int i = 0; i < __dim; ++i) // array

        {
            setValue(1,0);
        }
    }

    Point::Point(unsigned int dimensions, double *array)
    {
        __id = __idGen;
        ++__idGen;

        __dim = dimensions;
        __values = new double[__dim];
        for (int i = 0; i < __dim; ++i)
        {
            __values[i] = array[i];
        }
    }

    // The Big Three: copy cpnstructor ,the overloaded operator=, destructor

    //1.Copy Constructor
    Point::Point(const Point &copy) {
        __dim = copy.__dim;
        __values = new double[__dim];

        for (int count = 0; count < __dim; ++count) {
            __values[count] = copy.__values[count];
            __id = copy.__id;
        }
    }
    //2.Overload = Assignment
    Point &Point::operator=(const Point &origin)
    {
        if (this != &origin) {
            __dim = origin.__dim;
            __id = origin.__id;

            // this describes if the array is already assigned, it will delete first
            if ( this != &origin)
                delete[] __values;
            {
                __values = new double[__dim];
            }
            this ->__dim = origin.__dim;
            this ->__id = origin.__id;
            this ->__values= new double [origin.__dim];

            for (int i = 0; i < __dim; ++i)
            {
                __values[i] = origin.__values[i];
                this ->__values [i] = origin.__values[i];
            }
        }

        return *this;

    }

    //3. The Destructor

    Point::~Point()
    {
        delete [] __values;
    }

    // Get Methods: Accessors & mutators

    unsigned int Point::getId() const
    {
        return __id;
    }

    unsigned int Point::getDims() const
    {
        return __dim;
    }

    //For the Distance

    // double Point::getValue(unsigned int dim, double newValue) const
    // {
    // __values[dim] = newValue;

    //if (dim >= 0 && dim < __dim) {
    //    __values[dim] = newValue;
    //}

    double Point::getValue(unsigned int dim)const
    {
        return __values[dim];
    }
}

void Clustering::Point ::setValue(unsigned int dim, double val)
{

    __values[dim] = val;

}

/* double Point::getValue(unsigned int dim) const
 {
     if (dim >= 0 && dim < __dim)
         return __values[dim];
     else
         return 0;
 }
 */

//  For distanceTo estimates the distance between the calling point and another point

double Clustering::Point::distanceTo(const Point &comparePoint) const
{
    if (__dim != comparePoint.__dim)
        return false;
    //return statement
    double calculateProduct = 0;          //  Equation (xn2 - xn1)^2

    for (int i = 0; i < __dim; ++i) {
        calculateProduct += pow(comparePoint.getValue(i) - getValue(i), 2);
    }

    return sqrt(calculateProduct);
}

// Overloaded operators

// 1. Multiplication Assignment Operator
Clustering::Point &Clustering::Point::operator*=(double val)
{
    for (int i = 0; i < __dim; ++i)
    {
        __values[i] *= val;
    }


    return *this;
}
//2.Division Assignment Operator

Clustering::Point &Clustering::Point::operator/=(double val)
{   assert (val!=0);
    for (int i=0; i < __dim; ++i)
        //for (int i = 0; i < __dim; ++i)
    {
        __values[i] /= val;
    }

    return *this;
}

const Clustering::Point Clustering::Point::operator*(double val) const
{
    for (int i= 0; i < __dim; ++i)
        __values[i]/=val;
    return *this;
}

const Clustering::Point Clustering::Point::operator/(double val) const
{
    Point p(*this);
    p *= val;
    return p;
}

//to read out of index and boundary

double &Clustering::Point::operator[](unsigned int bound)
{
    //out of bounds
    if (bound < 0 || bound >= __dim)
        bound = 0;

    return __values[bound];
}


Point &operator+=(Point &leftPoint, const Point &rightPoint) //from lecture

{

    for (int i=0; i < leftPoint.__dim; i++)
        leftPoint.__values[i]+=rightPoint.__values[i];
    return leftPoint;
    // Used dimensions is the greater of the two points
    int usedDims = std::max(leftPoint.getDims(), rightPoint.getDims());

    /*  // Resize left array if right is larger
      if (leftPoint.__dim < usedDims) {
          delete [] leftPoint.__values;

          leftPoint.__values = new double[usedDims];
      }

     */


}


// Add values of right to values of left
for (int i = 0; i < usedDims; ++i) {
leftPoint[i] += rightPoint.getValue(i);      // note: getValue returns 0 if out of bounds
}

return leftPoint;
}

Point &operator-=(Point &lhs, const Point &rhs)
{
    if (&lhs == &rhs) {
        for (int count = 0; count < lhs.__dim; count++) {
            lhs.__values[count] = 0;
        }
    }
    else if (lhs.__dim == rhs.__dim) {
        for (int count = 0; count < lhs.__dim; count++)
            lhs.__values[count] -= rhs.__values[count];
    }
    return lhs;
}

const Point operator+(const Point &lhs, const Point &rhs)
{
    Point p(lhs);

    return p += rhs;

}

const Point operator-(const Point &lhs, const Point &rhs) {
    Point p(lhs);

    p -= rhs;

    return p;
}

bool operator==(const Point &lhs, const Point &rhs)
{
    bool equal = true;
    if(lhs.__id !=rhs.__id)
        equal=false;
    else
    {
        for(int count =0; count < lhs.__dim; count++)
            if(lhs.__values[count] != rhs.__values[count])
                equal=false;
    }
    return equal;
}

bool operator!=(const Point &lhs, const Point &rhs)
{
    return !operator ==(lhs, rhs);
}

bool operator<(const Point &lhs, const Point &rhs)
{
    // int usedDims = std::max(lhs.__dim, rhs.__dim);

    for (int count = 0; count < lhs.__dim; count++)
    {
        if (lhs.__values[count] < rhs.__values[count])
            return true;
        if(lhs.__values[count] > rhs.__values[count])
            return false;
    }

    return false;
}

bool operator>(const Point &lhs, const Point &rhs)
{
    return (rhs < lhs);
}

bool operator<=(const Point &lhs, const Point &rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const Point &lhs, const Point &rhs)
{
    return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &out, const Point &point)
{
    unsigned int count = 0;
    for ( ; count < point.__dim - 1; ++count)
        out << point.__values[count] << ", ";

    out << point.__values[count];
    return out;
}

std::istream &operator>>(std::istream &input, Point &point)
{
    std::string line;
    double d;
    for(int count =0; count < point.__dim; count++)
    {
        getline(input, line, ',');
        std::stringstream string_input(line);
        string_input>>d;
        point.__values[count] = d;
    }
    return input;
}
}
