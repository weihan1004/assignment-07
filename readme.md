## Templates and Exceptions

### Overview

There are several input files containing points, formatted as described below.
We want to go through these points and find the point in each file furthest
from zero.

This is somewhat of a challenge: in some of the input files the points have
integer components, and in others they have floating point components.  Also,
the number of components that each point has varies between input files.
Finally, some of the input files have points that are not properly formatted,
and need to be ignored.

To do this, we want to write a `Point` class template capable of representing
these points, and overload the stream insertion and extraction operators to
help with reading in and writing out `Point` objects in the given format.  We
will need a `distance` method to tell us how far away one point is from another
(so that we can determine how far away each point is from zero).  In addition,
it might be helpful to overload at least one of the comparison operators, with
the convention that one point is "larger" than another if and only if it is
further away from zero (which is to say, if and only if the line from zero to
that that point is longer than the line from zero to the other point).

To handle the improperly formatted points contained in some of the files, we
will use exceptions.  The stream extraction operator for the `Point` class
template should not be responsible for knowing the exact input format of the
list of points: it should only be concerned with the input format for a single
point.  Because of this, it does not have enough information to properly take
care of an error.  When an invalid point is detected, the overloaded stream
extraction operator should throw an exception indicating the type of error.
The controlling program should catch this exception and handle the error.


### Specifics

#### Format of a Point

A point will consist of an open parenthesis, followed by the appropriate number
of components (formatted according to their type, which must be numeric)
separated by whitespace, followed by a closing parenthesis.  Whitespace should
be ignored, except as a separator for components within a point (this is the
normal behavior the stream extraction operators for the relevant fundamental
types).  For examples of valid points, please see the given input files.

The format of a point is the business of the stream extraction operator for the
`Point` class template.  Also, the stream insertion operator for the `Point`
class template is responsible for generating valid points (so, it has to know a
little about the format, but not as much as the stream extraction operator
does).  No other part of the program should know anything about the format of a
point.

#### Input File Format

Each valid line of an input file should contain a single, properly formatted
point.

In most cases, we need not care about whether each point is on its own line, or
whether the points are on the same line, but specifying them to be on separate
lines has the advantage that when an error occurs, we can read and discard to
the end of the line, and then try again.

The format of the input files is the business of `main`, or whatever function
it may delegate this to.  No part of the `Point` class template, or its
associated overloaded operators, should know anything about it.

#### Input File Naming Scheme

The input files are named with the type and number of the components in each
valid point.  Thus `input-int-2.txt` has points with 2 integer components.  The
input files with some invalid data have `bad` appended.  The file with
`very-bad` appended has no valid data.

#### Exceptions

There should be two types of exceptions: one for when the stream is empty
(which will occur if the file has nothing in it, or if we have reached the end
of the file), and one for when an "invalid symbol" is encountered (i.e. when we
try to read in some part of a point, but fail even though the stream is not
empty).

Because it seems like a good practice, all exceptions should be derived (either
directly or indirectly) from the `std::exception` class provided by the
`<exception>` header.

#### Formula for the Distance Between Two Points

You may be familiar with the formula for the distance between two points in the
two dimensional Euclidean plane:

```c++
std::sqrt( std::pow( x-x_1, 2 ) + std::pow( y-y_1, 2 ) );
```

In general, the distance between two points, no matter how many dimensions they
have, is the square root of the sum of the squares of the differences between
the corresponding components of each point.  Thus, for a point of three
dimensions, we have:

```c++
std::sqrt( std::pow( x-x_1, 2 ) + std::pow( y-y_1, 2 ) + std::pow( z-z_1, 2 ) );
```

and so on.

#### Expected Output

```
the point furthest from ( 0 ) in ../input-int-1.txt is ( -127 )

the point furthest from ( 0 0 ) in ../input-int-2.txt is ( 124 92 )

the point furthest from ( 0 0 0 0 0 ) in ../input-int-5.txt is ( -128 -65 -116 -42 -119 )

the point furthest from ( 0 0 ) in ../input-double-2.txt is ( -6.92889e+37 8.66612e+27 )

the point furthest from ( 0 0 0 ) in ../input-double-3.txt is ( 1.57831e+22 1.25715e-33 2.84409e+38 )

ERROR: ignoring invalid element (unable to read value)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 154
ERROR: ignoring invalid element (unable to read value)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 187
ERROR: ignoring invalid element (unable to read value)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 340
ERROR: ignoring invalid element (unable to read value)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 379
ERROR: ignoring invalid element (unable to read value)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 462
ERROR: ignoring invalid element (unable to read value)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 473
ERROR: ignoring invalid element (invalid symbol)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 490
ERROR: ignoring invalid element (unable to read value)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 637
ERROR: ignoring invalid element (invalid symbol)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 673
ERROR: ignoring invalid element (unable to read value)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 714
ERROR: ignoring invalid element (invalid symbol)
  source code line: 55
  reading from: ../input-int-3-bad.txt
  at position: 730
the point furthest from ( 0 0 0 ) in ../input-int-3-bad.txt is ( 80 102 -116 )

ERROR: unable to read first element (unable to read value)
  source code line: 41
  reading from: ../input-int-4-very-bad.txt
  at position: 12
```

##### Notes:

- The error messages are partly from the messages contained in the exceptions
  (obtained via the `what` method, and placed in parenthesis above) and partly
  generated within the function called by `main` (in my implementation).

- The "source code line" numbers are obtained by using the `__LINE__` macro.

- The input file stream positions are obtained by calling the `tellg` method on
  the input stream (i.e. `infile.gellg()`).

- Because it seems like a good practice, the error messages are output to
  `cerr` rather than `cout`.  If you can, it would be good to do this in your
  program as well; but unless you know something about stream redirection (you
  can look up "redirecting stderr in bash" or something similar if you're
  curious), the distinction probably isn't significant.

- If you can't get your output to look exactly like this, that's okay.  The
  important thing is that the point furthest from zero in each input file is
  listed, and that errors are shown when they occur (in some reasonable
  format).


### Requirements

If the above is enough information for you, feel free to work based just on
that.  Please make sure to use this assignment to explore class templates,
function templates, exceptions, and operator overloading.

If you'd like a bit more guidance, read on.

- Write a `Point` class template with two template parameters: a `typename T`,
  representing the type of the components of the point (`int`, `double`, etc.),
  and a `const unsigned int SIZE`, representing the number of components.

- The `Point` class template should contain the following private members:
    - An array named `components_`  of type `T` with `SIZE` elements

- The `Point` class template should contain the following public members:
    - A constructor that takes no arguments and initializes every element of
      the array to zero
    - A `const` `distance` method that takes a `const` reference to another
      `Point` and returns the distance between the two `Point`s as a `double`
    - An overloaded `const` `operator>` method that takes a `const` reference
      to another `Point`, returns `true` if the current `Point` is further from
      the zero `Point` than the `Point` that was passed, and `false` otherwise
    - A `const` `toStream` method to help with overloading the stream insertion
      operator, that takes a reference to a `std::ostream`, inserts the current
      `Point`, and returns the reference to the `std::ostream` that it received
    - A `fromStream` method to help with overloading the stream extraction
      operator, that takes a reference to a `std::istream`, extracts a single
      `Point` and sets the current object equal to it (or throws the
      appropriate exception if it cannot), and returns the reference to the
      `std::istream` that it received.  More explicitly, this method should do
      the following:
        - Try to read a single open parenthesis, using the stream extraction
          operator, into a variable of type `char`
        - Test the input stream to make sure no errors occurred
            - If an error occurred because the stream was empty, clear the
              error, and throw an `EmptyStreamError`
        - Test the character to make sure it is an open parenthesis
            - If it is not, throw an `InvalidSymbolError`
        - For however many elements there ought to be (as defined by the `SIZE`
          template parameter), do the following:
            - Try to read a single component of the point into the appropariate
              position of the `components_` array
            - Test the input stream to make sure no errors occurred
                - If an error did occur, clear the error, and throw an invalid
                  symbol error with the message "unable to read value".
        - Try to read a single close parenthesis, using the stream extraction
          operator, into a variable of type `char`
        - Test the input stream to make sure no errors occurred
            - If an error occurred because the stream was empty, clear the
              error, and throw an `EmptyStreamError`
        - Test the character to make sure it is a close parenthesis
            - If it is not, throw an `InvalidSymbolError`
        - Return the reference to the `std::istream` that was passed as an
          argument

- The `Point` class template should contain the following classes defined with
  `public` access:
    - `class Error : public std::exception`: this class should have
        - A `private` `const char * description`
        - A `public` constructor that takes a `const char *` and sets
          `description` equal to it
        - A `public` method named `what`, overriding the one inherited from
          `std::exception`, that takes no arguments, and returns `description`
    - `class EmptyStreamError : public Error`: this class should have
        - A `public` constructor that optionally takes a `const char *`, and
          passes the value to the parent constructor (to be stored in
          `description`)
    - `class InvalidSymbolError : public Error`: this class should have
        - A `public` constructor that optionally takes a `const char *`, and
          passes the value to the parent constructor

- Overload the stream insertion operator for the `Point` class template, using
  the `toStream` method described above.  Because it is being used for a class
  template, this will have to be a function template with the same template
  parameters.

- Overload the stream extraction operator for the `Point` class template, using
  the `fromStream` method described above.  Because it is being used for a
  class template, this will have to be a function template with the same
  template parameters.
  
- Because the above are class templates and function templates, the entire
  definition will need to be visible at the point of instantiation (which in
  our case will be the point at which the class or the method is first used).
  Thus, the definitions for the methods of the `Point` class template, as well
  as the definitions for the stream insertion and extraction operators, etc.,
  will have to be in the header file `point.h`.

- In `main.cpp`, write a `void` function template (with the same template
  parameters as your `Point` class template) called `print_max` that takes as
  an argument the name of a file as a `const string &` (or a `const char *`)
  and does the following:
    - Opens the file
    - Tries to read in a single point
        - If this fails, output the appropriate error and return (exiting the
          function)
    - Considers this point to be the maximum point found so far
    - Enters an infinite loop that does the following:
        - Tries to read in a single point
            - If this fails
                - If the exception is an `EmptyStreamError`, assume we're done
                  reading, and `break` out of the loop
                - If the exception is an `InvalidSymbolError`, output an
                  appropriate error message, and ignore everything until the
                  next newline
                - If the exception is anything else that can be caught as a
                  `std::exception`, output an appropriate error message and
                  return (exiting the function)
        - Compares this point with the current maximum
            - If the point is larger than the current maximum, replace the
              current maximum with this point
    - Outputs the largest properly formatted point found, along with an
      appropriate message

- In the `main` function, use `print_max` to output the largest properly
  formatted point found, along with an appropriate message, for every given
  input file.


### Style

- Place your solution in a `solution--YOURNAME` subdirectory, or in the base
  directory.

- Document and format your code well and consistently.
- Wrap lines at 79 or 80 columns whenever possible.
- End your file with a blank line.
- Do *not* use `using namespace std;`.  You may get around typing `std::` in
  front of things or with, e.g., `using std::cout;`.

- `main()` must have its own `.cpp` file.  I suggest calling it `main.cpp`.

- Declare member functions and function arguments as `const` when appropriate
  (pretty much whenever possible).

- Include your copyright and license information at the top of every file,
  followed by a brief description of the file's contents, e.g.

  ```c++
  /* ----------------------------------------------------------------------------
   * Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>
   * Released under the [MIT License] (http://opensource.org/licenses/MIT)
   * ------------------------------------------------------------------------- */

  /**
   * A short program to print "Hello World!" to standard output.
   */
  ```

- Use "include guards" in all `.h` files.  Be sure to give the preprocessor
  variable a (unique) name corresponding to the file name.  For example, in
  `point.h`:

  ```c++
  #ifndef POINT_H
  #define POINT_H
  // ----------------------------------------------------------------------------

  // ... everything besides the copyright information and file description

  // ----------------------------------------------------------------------------
  #endif  // POINT_H
  ```


-------------------------------------------------------------------------------
[![Creative Commons License](https://i.creativecommons.org/l/by/4.0/88x31.png)]
(http://creativecommons.org/licenses/by/4.0/)  
Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>  
This work is licensed under a [Creative Commons Attribution 4.0 International
License] (http://creativecommons.org/licenses/by/4.0/)  
Project located at <https://github.com/2015-fall-csuf-benblazak-cpsc-121>

