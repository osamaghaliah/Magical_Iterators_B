#include "MagicalContainer.hpp"

using namespace ariel;
// Abbreviations - for reading convenience.
using MC_AI = MagicalContainer::AscendingIterator;
using MC_SCI = MagicalContainer::SideCrossIterator;
using MC_PI = MagicalContainer::PrimeIterator;


            // ################     MagicalContainer Implementation     ################ \\

MagicalContainer::MagicalContainer() : elements(), ascendedElements(), primeElements() {}

MagicalContainer::~MagicalContainer() {}

void MagicalContainer::addElement(int element) {
    this->elements.push_back(element);
    this->ascendedElements.push_back(element);
    // Sorting ascendedElements vector in order to maintain the ascending order.
    sort(this->ascendedElements.begin(), this->ascendedElements.end());

    // primeElements vector must contain prime numbers ONLY.
    if (isPrime(element)) {
        this->primeElements.push_back(&(this->ascendedElements.back()));
    }

    // Maintain addresses for the primeElements pointers.
    this->maintainAddresses();
}

void MagicalContainer::removeElement(int element) {
    // Handling a possible extreme case - the element may not exist.
    if (find(this->elements.begin(), this->elements.end(), element) == this->elements.end()) {
        throw runtime_error("Element " + to_string(element) + " is NOT found inside the container.");
    }

    // Attempting to find the given element.
    auto itr1 = find(this->elements.begin(), this->elements.end(), element);
    auto itr2 = find(this->ascendedElements.begin(), this->ascendedElements.end(), element);

    // The element was found inside elements vector - removing it must be done.
    if (itr1 != this->elements.end()) {
        this->elements.erase(itr1);
    }

    // The element was found inside ascendedElements vector - removing it must be done.
    if (itr2 != this->ascendedElements.end()) {
        this->ascendedElements.erase(itr2);
    }

    // If it is prime, then it is surely inside the primeElements vector - removing it must be done.
    if (isPrime(element)) {
        this->primeElements.pop_back();
    }

    // Maintain addresses for the primeElements pointers.
    this->maintainAddresses();
}

unsigned int MagicalContainer::size() const {
    return this->elements.size();
}

bool MagicalContainer::isPrime(int number) {
    // Handling a possible extreme case - any numbers smaller than 1 (inclusive) are NOT prime.
    if (number <= 1) {
        return false;
    } else if (number == 2) { // 2 is the only even prime number.
        return true;
    }

    // Attempting to detect a third divisor. If so, it is NOT prime.
    for (int i = 2; i < number; i++) {
        int temp = number % i;

        if (temp == 0) {
            return false;
        }
    }

    // The given number is definitely a prime number - no third divisor was found.
    return true;
}

void MagicalContainer::maintainAddresses() {
    unsigned int primeElementsTracker = 0, ascendedElementsTracker = 0;

    // Updating each address accordingly.
    for (int value : this->ascendedElements) {
        if (this->isPrime(value)) {
            this->primeElements[primeElementsTracker] = &(this->ascendedElements[ascendedElementsTracker]);
            primeElementsTracker++;
        }

        ascendedElementsTracker++;
    }
}


            // ################     AscendingIterator Implementation     ################ \\

MC_AI::AscendingIterator() : container(nullptr), position(0) {}

MC_AI::AscendingIterator(MagicalContainer& container) : container(&container), position(0) {}

MC_AI::AscendingIterator(MagicalContainer& container, unsigned int position) : container(&container), position(position) {}

MC_AI::~AscendingIterator() {}

int& MC_AI::operator * () const {
    return this->container->ascendedElements[this->position];
}

MC_AI& MC_AI::operator++() {
    // Handling a possible extreme case - the current position may be "out of bounds".
    if (this->position >= this->end().position) {
        throw runtime_error("The iterator's position has exceeded its limit.");
    } else {
        ++this->position;
        return *this;
    }
}

MC_AI& MC_AI::operator = (const MC_AI& ascendingIterator) {
    // Handling a possible extreme case - iterators' elements vectors are not the same.
    if (this->container->elements != ascendingIterator.container->elements) {
        throw runtime_error("Assigning a different container for an iterator is NOT allowed.");
    } else {
        this->position = ascendingIterator.position;
        return *this;
    }
}

bool MC_AI::operator == (const MC_AI& ascendingIterator) const {
    return this->position == ascendingIterator.position;
}

bool MC_AI::operator != (const MC_AI& ascendingIterator) const {
    return this->position != ascendingIterator.position;
}

bool MC_AI::operator < (const MC_AI& rightItr) const {
    return this->position < rightItr.position;
}

bool MC_AI::operator > (const MC_AI& rightItr) const {
    return this->position > rightItr.position;
}

MC_AI MC_AI::begin() {
    // Iterator pointing at the first position.
    return AscendingIterator(*this->container);
}

MC_AI MC_AI::end() {
    // Iterator pointing at the last position.
    return AscendingIterator(*this->container, this->container->ascendedElements.size());
}


            // ################     SideCrossIterator Implementation     ################ \\

MC_SCI::SideCrossIterator() : container(nullptr), position(0) {}

MC_SCI::SideCrossIterator(MagicalContainer& container) : container(&container), position(0) {}

MC_SCI::SideCrossIterator(MagicalContainer& container, unsigned int position) : container(&container), position(position) {}

MC_SCI::~SideCrossIterator() {}

int& MC_SCI::operator * () const {
    return this->container->ascendedElements[this->position];
}

MC_SCI& MC_SCI::operator ++ () {
    // Handling a possible extreme case - the current position may be "out of bounds".
    if (this->position == this->end().position) {
        throw runtime_error("The iterator's position has exceeded its limit.");
    } else {
        unsigned int barrier = this->container->ascendedElements.size();

        // Determining the position according to the middle index - providing the side-cross positioning respectively.
        if (this->position < (barrier / 2)) {
            this->position = barrier - 1 - this->position;
        } else if (this->position == (barrier / 2)) {
            this->position = barrier;
        } else {
            this->position = barrier - this->position;
        }
    }

    return *this;
}

MC_SCI& MC_SCI::operator = (const MC_SCI& sideCrossIterator) {
    // Handling a possible extreme case.
    if (this->container->elements != sideCrossIterator.container->elements) {
        throw runtime_error("Assigning a different container for an iterator is NOT allowed.");
    } else {
        this->position = sideCrossIterator.position;
        return *this;
    }
}

bool MC_SCI::operator == (const MC_SCI & sideCrossIterator) const {
    return this->position == sideCrossIterator.position;
}

bool MC_SCI::operator != (const MC_SCI & sideCrossIterator) const {
    return this->position != sideCrossIterator.position;
}

bool MC_SCI::operator < (const MC_SCI& rightItr) const {
    return this->position < rightItr.position;
}

bool MC_SCI::operator > (const MC_SCI& rightItr) const {
    return this->position > rightItr.position;
}

MC_SCI MC_SCI::begin() {
    // Iterator pointing at the first position.
    return SideCrossIterator(*(this->container));
}

MC_SCI MC_SCI::end() {
    // Iterator pointing at the last position.
    return SideCrossIterator(*(this->container), this->container->ascendedElements.size());
}


            // ################     PrimeIterator Implementation     ################ \\

MC_PI::PrimeIterator() : container(nullptr), position(0) {}

MC_PI::PrimeIterator(MagicalContainer& container) : container(&container), position(0) {}

MC_PI::PrimeIterator(MagicalContainer& container, unsigned int position) : container(&container), position(position) {}

MC_PI::~PrimeIterator() {}

int& MC_PI::operator * () const {
    return *this->container->primeElements[this->position];
}

MC_PI& MC_PI::operator ++ () {
    // Handling a possible extreme case.
    if (this->position >= this->end().position) {
        throw runtime_error("The iterator's position has exceeded its limit.");
    } else {
        ++this->position;
        return *this;
    }
}

MC_PI& MC_PI::operator = (const MC_PI& primeIterator) {
    // Handling a possible extreme case.
    if (this->container->elements != primeIterator.container->elements) {
        throw runtime_error("Assigning a different container for an iterator is NOT allowed.");
    } else {
        this->position = primeIterator.position;
        return *this;
    }
}

bool MC_PI::operator == (const MC_PI& primeIterator) const {
    return this->position == primeIterator.position;
}

bool MC_PI::operator != (const MC_PI& primeIterator) const {
    return this->position != primeIterator.position;
}

bool MC_PI::operator < (const MC_PI& rightItr) const {
    return this->position < rightItr.position;
}

bool MC_PI::operator > (const MC_PI& rightItr) const {
    return this->position > rightItr.position;
}

MC_PI MC_PI::begin() {
    // Iterator pointing at the first position.
    return PrimeIterator(*(this->container));
}

MC_PI MC_PI::end() {
    // Iterator pointing at the last position.
    return PrimeIterator(*(this->container), this->container->primeElements.size());
}