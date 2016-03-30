//
//  KMeans.cpp
//  PA3
//
//  Created by Patricia Figueroa on 3/21/16.
//

#include "KMeans.h"
#include "Exceptions.h"

#include <iostream>
#include <string>
#include <cassert>

namespace Clustering{
    KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter)
    {
        std::ifstream file(filename);

        __dimensionality = dim;
        __k = k;
        __iFileName = filename;
        __maxIter = maxIter;

    }

    //no copying

    KMeans::~KMeans()
    {

    }


    //accessors
    unsigned int KMeans::getMaxIter()
    {

        return __maxIter;
    }

    unsigned int KMeans::getNumIters()
    {

        return __numIter;
    }


    unsigned int KMeans::getNumNonemptyClusters()
    {
        return __numNonempty;
    }

    unsigned int KMeans::getNumMovesLastIter()
    {
        return __numMovesLastIter;
    }


    Cluster &KMeans::operator[](unsigned int u)
    {
        //return initializer
        return *(__clusters[u]);
    }

    const Cluster &KMeans::operator[](unsigned int u) const
    {
        //return initializer
        return *(__clusters[u]);

    }

    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans)
    {
        return os;
    }

    void KMeans::run()
    {

    }

}
