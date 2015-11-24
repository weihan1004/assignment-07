/* ----------------------------------------------------------------------------
 * Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * A class representing a point in n-dimensional space.
 *
 *
 * Notes:
 *
 * - [Why can’t I separate the definition of my templates class from its
 *   declaration and put it inside a .cpp file?]
 *   (https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl)
 *
 * - Since this is a header, we should be careful not to use any `using ...`
 *   statements (except when those statements are importing symbols into a
 *   namespace other than the global one).
 */

#ifndef POINT_H
#define POINT_H
// ----------------------------------------------------------------------------

#include <cmath>
#include <exception>
#include <iostream>

// ----------------------------------------------------------------------------

template <typename T, const unsigned int SIZE>
class Point {
    private:
        T components_[SIZE];

    public:
        class Error : public std::exception {
            private:
                const char * description;
            public:
                Error(const char * s) : description(s) {}
                const char * what() const noexcept {
                    return description;
                }
        };
        class EmptyStreamError : public Error { public:
            EmptyStreamError(const char * s = "empty stream") : Error(s) {}
        };
        class InvalidSymbolError : public Error { public:
            InvalidSymbolError(const char * s = "invalid symbol") : Error(s) {}
        };

        Point();

        double distance(const Point & p) const;

        bool operator>(const Point & p) const;

        std::istream & fromStream(std::istream & is);
        std::ostream & toStream(std::ostream & os) const;
};

// ............................................................................

template <typename T, const unsigned int SIZE>
std::istream & operator>>(std::istream & is, Point<T,SIZE> & p);

template <typename T, const unsigned int SIZE>
std::ostream & operator<<(std::ostream & os, const Point<T,SIZE> & p);

// ----------------------------------------------------------------------------

template <typename T, const unsigned int SIZE>
Point<T,SIZE>::Point() : components_{} {}

template <typename T, const unsigned int SIZE>
double Point<T,SIZE>::distance(const Point & p) const {
    T sum_of_squares = 0;
    for (unsigned int i = 0; i < SIZE; i++)
        sum_of_squares += std::pow( components_[i] - p.components_[i], 2 );
    return std::sqrt(sum_of_squares);
}

template <typename T, const unsigned int SIZE>
bool Point<T,SIZE>::operator>(const Point & p) const {
    return distance( Point{} ) > p.distance( Point{} );
}

template <typename T, const unsigned int SIZE>
std::istream & Point<T,SIZE>::fromStream(std::istream & is) {
    char parenthesis;
    T temp;

    is >> parenthesis;
    if (!is.good()) {
        is.clear();
        throw EmptyStreamError();
    }
    if (parenthesis != '(')
        throw InvalidSymbolError();

    for (unsigned int i = 0; i < SIZE; i++) {
        is >> temp;
        if (!is.good()) {
            is.clear();
            throw InvalidSymbolError("unable to read value");
        }
        components_[i] = temp;
    }

    is >> parenthesis;
    if (!is.good()) {
        is.clear();
        throw EmptyStreamError();
    }
    if (parenthesis != ')')
        throw InvalidSymbolError();

    return is;
}

template <typename T, const unsigned int SIZE>
std::ostream & Point<T,SIZE>::toStream(std::ostream & os) const {
    os << "( ";
    for (unsigned int i = 0; i < SIZE; i++)
        os << components_[i] << " ";
    os << ")";

    return os;
}

// ............................................................................

template <typename T, const unsigned int SIZE>
std::istream & operator>>(std::istream & is, Point<T,SIZE> & p) {
    return p.fromStream(is);
}

template <typename T, const unsigned int SIZE>
std::ostream & operator<<(std::ostream & os, const Point<T,SIZE> & p) {
    return p.toStream(os);
}

// ----------------------------------------------------------------------------
#endif  // POINT_H

