//
//  Exceptions.cpp
//Created by Patricia Figueroa on 3/20/16.
//
// Implementation of Exceptions.h

#include "Exceptions.h"

namespace Clustering
{


    //for class OutOfBoundsEx


    //unsigned int __current;
    //int __rhs;
    //std::string __name;


    OutOfBoundsEx::OutOfBoundsEx (unsigned int c, int r )
    {
        __current = c ;
        __rhs = r ;

    }
    unsigned int OutOfBoundsEx::getCurrent() const
    {
        return __current;
    }

    int OutOfBoundsEx::getRhs() const
    {
        return __rhs;
    }
    std::string OutOfBoundsEx::getName() const
    {
        return __name;
    }


    //sends exceptions to os , and returns os

    std::ostream &operator <<(std::ostream &os, const OutOfBoundsEx &ex)
    {
        os << ex << std::endl;
        return os;
    }



    // For Class DimensionalityMismatchEx

    DimensionalityMismatchEx::DimensionalityMismatchEx (unsigned int c, unsigned int r)

    {
        __rhs = r;
        __current = c;

    }

    unsigned int DimensionalityMismatchEx::getCurrent()const
    {
        return __current;
    }

    unsigned int DimensionalityMismatchEx::getRhs() const
    {

        return __rhs;
    }

    std::string DimensionalityMismatchEx::getName()const
    {
        return __name;
    }


    std::ostream &operator <<(std::ostream &os, const DimensionalityMismatchEx &ex)

    {
        os << ex <<std::endl;
        return os;
    }


