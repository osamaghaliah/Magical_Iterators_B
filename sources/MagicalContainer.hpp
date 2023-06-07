#pragma once

/**
 * This file represents a container that specializes with 3 different types of iterators:
 *  1. AscendingIterator - Allowing to travers over the container's data in an ascending order.
 *  2. SideCrossIterator - Allowing to travers over the container's data in a side-cross order.
 *  3. PrimeIterator - Allowing to travers over the container's data in a prime-ary order.
 * The container's mechanism is based on a dynamic array.
 *
 * @attention - EXTERNAL RESOURCES USED FOR IMPLEMENTATION'S SMOOTHNESS - BUILT-IN ALGORITHMS:
 *  ==> https://cplusplus.com/reference/algorithm/find/ ==> Finding an element inside a vector ==> find() algorithm.
 *  ==> https://www.geeksforgeeks.org/sorting-a-vector-in-c/ ==> Sorting a vector ==> sort() algorithm.
 *
 * @author Osama M. Ghaliah
 */

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

namespace ariel {
    class MagicalContainer {
    private:
        // All elements storage.
        vector <int> elements;
        // All elements storage - in ascending order.
        vector <int> ascendedElements;
        // All prime elements ONLY storage.
        vector <int*> primeElements;

    public:
        // Constructor and a destructor.
        MagicalContainer();
        ~MagicalContainer();

        // Essential methods - adding/removing elements, retrieving the container's size and prime-validation.
        void addElement(int element);
        void removeElement(int element);
        unsigned int size() const;
        bool isPrime(int number);
        // Maintaining the prime numbers addresses after adding or removing an element from primeElements vector.
        void maintainAddresses();

        /*
         * This class represents an iterator which traverses on our MagicalContainer elements in ascending order.
         */
        class AscendingIterator {
        private:
            unsigned int position;
            MagicalContainer *container;

        public:
            // Constructors and a destructor.
            AscendingIterator();
            AscendingIterator(MagicalContainer& container);
            AscendingIterator(MagicalContainer& container, unsigned int position);
            ~AscendingIterator();

            // Overloaded operators.
            int& operator * () const;
            AscendingIterator& operator ++ ();
            AscendingIterator& operator = (const AscendingIterator& ascendingIterator);
            bool operator == (const AscendingIterator& ascendingIterator) const;
            bool operator != (const AscendingIterator& ascendingIterator) const;
            bool operator < (const AscendingIterator& rightItr) const;
            bool operator > (const AscendingIterator& rightItr) const;

            // Beginning and ending iterators retrieval.
            AscendingIterator begin();
            AscendingIterator end();
        };


        /*
         * This class represents an iterator which traverses on our MagicalContainer elements in a side-cross order.
         * SIDE-CROSS ==> Means that the iterator traverses in a "one from the start and one from the end" manner.
         *  E.g, {2, 1, 8, 6, -3, 4} ---> {2, 4, 1, -3, 8, 6}
         *  Why {2, 4, 1, -3, 8, 6} ?
         *  The 2 is the first element from the start.
         *  The 4 is the first element from the end.
         *  The 1 is the second element from the start.
         *  The 8 is the second element from the end.
         *  And so on...
         */
        class SideCrossIterator {
        private:
            unsigned int position;
            MagicalContainer *container;

        public:
            // Constructors and a destructor.
            SideCrossIterator();
            SideCrossIterator(MagicalContainer& container);
            SideCrossIterator(MagicalContainer& container, unsigned int position);
            ~SideCrossIterator();

            // Overloaded operators.
            int& operator * () const;
            SideCrossIterator& operator ++ ();
            SideCrossIterator& operator = (const SideCrossIterator& sideCrossIterator);
            bool operator == (const SideCrossIterator& sideCrossIterator) const;
            bool operator != (const SideCrossIterator& sideCrossIterator) const;
            bool operator < (const SideCrossIterator& rightItr) const;
            bool operator > (const SideCrossIterator& rightItr) const;

            // Beginning and ending iterators retrieval.
            SideCrossIterator begin();
            SideCrossIterator end();
        };


        /*
         * This inner class represents an iterator which travers on our MagicalContainer elements in a prime-ary order.
         * PRIME-ARY ==> Means that the iterator traverses ONLY over prime numbers. E.g, 2, 3, 5, 7... etc.
         */
        class PrimeIterator {
        private:
            unsigned int position;
            MagicalContainer *container;

        public:
            // Constructors and a destructor.
            PrimeIterator();
            PrimeIterator(MagicalContainer& container);
            PrimeIterator(MagicalContainer& container, unsigned int position);
            ~PrimeIterator();

            // Overloaded operators.
            int& operator * () const;
            PrimeIterator& operator ++ ();
            PrimeIterator& operator = (const PrimeIterator& primeIterator);
            bool operator == (const PrimeIterator& primeIterator) const;
            bool operator != (const PrimeIterator& primeIterator) const;
            bool operator < (const PrimeIterator& rightItr) const;
            bool operator > (const PrimeIterator& rightItr) const;

            // Beginning and ending iterators retrieval.
            PrimeIterator begin();
            PrimeIterator end();
        };
    };
}