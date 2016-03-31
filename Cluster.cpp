//
// Created by Patricia Figueroa on 3/25/16.
//


#include "Cluster.h"
#include "Exceptions.h"
#include "Point.h"

#include <cassert>
#include <string>
#include <sstream>
#include <iomanip>
#include <string>
#include <assert.h>

using namespace std;
namespace Clustering {

    const char POINT_CLUSTER_ID_DELIM = ':' ;

    unsigned int Cluster::__idGenerator = 0;
    LNode::LNode(const Point &p, LNodePtr n) : point(p), next(n)
    {
        point=p;
        next=n;

    }



    void Cluster:: __del()
    {

    }

    void Cluster::__cpy(LNodePtr pts)
    {

    }


    Cluster::Centroid::Centroid (unsigned int d, const Cluster &c): __c(c), __p(d)
    {
        __dimensions = d;
        __valid = false;
        toInfinity();

    }

    bool Cluster::Cluster::__in(const Point &p) const
    {
        return false;
    }



    const Point Cluster::Centroid::get() const
    {
        return __p;
    }

    void Cluster::Centroid::set(const Point &p)
    {
        __valid = true;
        __p = p ;

    }

    bool Cluster::Centroid::isValid() const
    {

        return __valid;

    }

    void Cluster::Centroid::setValid(bool valid)
    {
        __valid=valid;


    }

    //Functions

    void Cluster::Centroid::compute ()
    {

        if (!__valid) {
            __valid = true;
            if (__c.__points == nullptr)
            {
                toInfinity();
                return;
            }
            else {
                toInfinity();

            }

            __valid = true;
        }



        //The Big Three

        // 1.Copy Constructor

        Cluster::Cluster(unsigned int d): centroid(d, *this)

        {
            __size = 0;
            __points = nullptr;
            __dimensionality = d;
        }


        Cluster::Cluster (const Cluster &c1) : centroid(__dimensionality , *this)

        {
            __size = c1.getSize();
            __cpy(c1.__points);
        }


        Cluster::Cluster(const Cluster &rhs) : centroid(__dimensionality , *this)
        {
            for (int count = 0; count < rhs.getSize(); ++count)
            {
                add(rhs[count]);
            }
        }



        //2. Overloaded Assignement
        Cluster &Clustering::Cluster::operator=(const Cluster &rhs)
        {
            LNodePtr curr;

            if(this==&rhs)
                return *this;
            else
            {
                while (__points != nullptr) {
                    curr = __points;
                    __points = __points->next;
                    delete curr;
                    __size--;
                }

                for (int count = 0; count < rhs.__size; count++)
                    add(rhs[count]);
            }

            return *this;
        }

        unsigned int Cluster::getSize() const
        {
            return __size;
        }

        //3. Destructor

        Cluster::~Cluster()
        {
            LNodePtr curr;
            while (__points != nullptr) {
                curr = __points;
                __points = curr->next;

                delete curr;
            }
        }



        //Centroid Class

        Cluster::Centroid::Centroid(unsigned int d, const Cluster &c) : __c(c), __p(Point(d))
        {
            __dimensions = d;
            __valid = false;
            toInfinity();
        }

        const Point Cluster::Centroid::get() const
        {
            return __p;
        }

        void Cluster::Centroid::set(const Point &p)
        {
            __valid = true;
            __p = p;
        }

        bool Cluster::Centroid::isValid() const
        {

            if(__p == __valid)
            {
                return true;
            }

            else
                return false;
        }

        void Cluster ::Centroid::setValid(bool valid)

        {
            __valid = valid;
        }



        // Functions

        void Cluster::Cluster::add(const Point &point)
        {
            if (__size == 0) {
                ++__size;
                __points = new LNode(point, nullptr);
            }
            else {
                if (contains(point))
                    return; // if the point exists, then exit

                LNodePtr curr;
                LNodePtr prev;

                curr = __points;
                prev = nullptr;
                while (curr != nullptr) {
                    if (point < curr->point)
                    {
                        if (prev == nullptr)
                        {
                            __points = new LNode(point, curr);

                            __size++;

                            return;  // Add complete, exit
                        }
                        else
                        {
                            prev->next = new LNode(point, curr);

                            __size++;

                            return;  // complete, exit
                        }
                    }

                    prev = curr;
                    curr = curr->next;

                }


                prev->next = new LNode(point, nullptr);

                __size++;
            }
        }

        const Point &Clustering::Cluster::remove(const Point &point)
        {

            LNodePtr curr=__points;
            LNodePtr prev=__points;

            if(__points==nullptr)
                return point;
            else if(__points->point == point)
            {
                curr=__points;
                __points=__points->next;
                delete curr;
                __size--;
            }
            else
            {
                curr=curr->next;
                while (curr!= nullptr)
                {
                    if (curr->point == point) {
                        prev->next=curr->next;
                        delete curr;
                        __size--;
                        break;
                    }
                    curr = curr->next;
                    prev = prev->next;
                }
            }
            return point;
        }

        bool Clustering::Cluster::contains(const Point &p) const
        {
            LNodePtr curr = this->__points;

            while (curr != nullptr)
            {
                if (curr -> point == p )
                    return true;
                else
                    curr = curr->next;
            }

            return false;
        }

        //Centroid Functions


        void Cluster::pickCentroids(unsigned int k, Point **pointArray)
        {


        }


        const Point &Cluster::operator[](unsigned int index) const
        {
            assert (__size > 0);
            LNodePtr cursor = __points;

            for (int count = 0; count < index; count++)
            {
                cursor = cursor->next;
            }
            return cursor->point;
        }

        class Cluster &Clustering::Cluster::operator+=(const Point &point)
        {
            add(point);

            return *this;
        }

        class Cluster &Clustering::Cluster::operator-=(const Point &point)
        {
            remove(point);

            return *this;
        }

        // Members
        class Cluster &Cluster::operator+=(const Cluster &rhs) {
            for (int i = 0; i < rhs.getSize(); ++i) {
                add(rhs[i]);
            }

            return *this;
        }
        Cluster &Cluster::operator-=(const Cluster &rhs)
        {
            for (int i = 0; i < rhs.getSize(); ++i)
            {
                remove(rhs[i]);
            }

            return *this;
        }

        // Private Members
        void Cluster::__del() {

        }

        void Cluster::__cpy(LNodePtr pts) {

        }

        bool Cluster::__in(const Point &p) const {
            return 0;
        }

        // Operators Friends
        // Friends
        std::ostream &operator<<(std::ostream &os, const class Cluster &cluster1)
        {
            os << std::setprecision(20);
            for (int count = 0; count < cluster1.getSize(); count++)
            {
                os << cluster1[count] << std::endl;

            }

            return os;
        }
        std::istream &operator>>(std::istream &input, class Cluster &cluster1)
        {
            std::string line;
            std::getline(input, line);

            while (!input.eof()) {
                Point point(1);


                if (line.length() > 0) {
                    std::stringstream ss(line);

                    ss >> point;

                    cluster1.add(point);
                }
            }

            return input;
        }

        // friend comparison
        bool operator==(const class Cluster &lhs, const Cluster &rhs)
        {
            if (lhs.getSize() != rhs.getSize())
                return false;

            for (int i = 0; i < lhs.getSize(); ++i)
            {
                if (lhs[i] != rhs[i])
                    return false;
            }

            return true;
        }
        bool operator!=(const class Cluster &lhs, const Cluster &rhs)
        {
            return !(lhs == rhs);
        }

        const class Cluster operator+(const Cluster &lhs, const Point &rhs)
        {
            Cluster sum(lhs);
            sum += rhs;
            return sum;
        }
        const Cluster operator-(const Cluster &lhs, const Point &rhs)
        {
            Cluster sub(lhs);
            sub -= rhs;
            return sub;
        }

        const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
        {
            Cluster sum(lhs);
            sum += rhs;
            return sum;
        }
        const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
        {
            Cluster sub(lhs);
            sub -= rhs;
            return sub;
        }

    }
}