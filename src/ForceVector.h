//
// Created by Denis on 2018-03-30.
//

#ifndef PROJECT2_FORCEVECTOR_H
#define PROJECT2_FORCEVECTOR_H

class ForceVector {
 public:
  ForceVector(double x, double y) : x(x), y(y) {}

  double getX() const {
    return x;
  }

  double getY() const {
    return y;
  }

  ForceVector &operator+=(const ForceVector &rhs) // compound assignment (does not need to be a member,
  {                           // but often is, to modify the private members)
    /* addition of rhs to *this takes place here */
    this->x += rhs.getX();
    this->y += rhs.getY();

    return *this; // return the result by reference
  }

  // friends defined inside class body are inline and are hidden from non-ADL lookup
  friend ForceVector operator+(ForceVector lhs,        // passing lhs by value helps optimize chained a+b+c
                               const ForceVector &rhs) // otherwise, both parameters may be const references
  {
    lhs += rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

 private:
  double x = 0;
  double y = 0;
};

#endif //PROJECT2_FORCEVECTOR_H
