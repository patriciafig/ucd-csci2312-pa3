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
    const char Point::POINT_VALUE_DELIM = ',';
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

    Point::Point(unsigned int dim, double *array)
    {
        __id = __idGen;

        ++__idGen;

        __dim = dim;
        __values = new double[__dim];
        for (unsigned int i = 0; i < __dim; ++i)
        {
            __values[i] = array[i];
        }
    }

    // The Big Three: copy cpnstructor ,the overloaded operator=, destructor

    //1.Copy Constructor
    Point::Point(const Point &copy)
    {
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
        //   delete [] __values;
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

    double Point::getValue(unsigned int dim) const
    {
        return __values [dim];
    }


    //Set Method

    void Point::setValue(unsigned int dim, double val)
    {

        __values[dim] = val;

    }


//  For distanceTo estimates the distance between the calling point and another point

    double Point::distanceTo(const Point &comparePoint) const
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
    Point &Point::operator*=(double val)
    {
        for (int i = 0; i < __dim; ++i)
        {
            __values[i] *= val;
        }


        return *this;
    }
    //2.Division Assignment Operator

    Point &Point::operator/=(double val)
    {   assert (val!=0);
        for (int i=0; i < __dim; ++i)
            //for (int i = 0; i < __dim; ++i)
        {
            __values[i] /= val;
        }

        return *this;
    }

    const Point Point::operator*(double val) const
    {
        for (int i= 0; i < __dim; ++i)
            __values[i]/=val;
        return *this;
    }

    const Point Point::operator/(double val) const
    {
        Clustering:Point p(*this);
        p *= val;
        return p;
    }

    //to read out of index and boundary

    double &Point::operator[](unsigned int index)
    {
        return __values[index];
    }



    Point &operator+=(Point &lhs, const Point &rhs) //from lecture

    {

        for (int i=0; i < lhs.__dim; i++)
            lhs.__values[i]+=rhs.__values[i];
        return lhs;

    }


    Point &operator-=(Point &lhs, const Point &rhs)
    {
        if (&lhs == &rhs)
        {
            for (int count = 0; count < lhs.__dim; count++)
            {
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
