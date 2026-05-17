# Documentation for String Exception Definitions
Function usage: Defines two dedicated exception types for string operations to handle out-of-bounds and negative index errors.


# Documentation of Exception `OutOfStringRange`
Function usage: Thrown when accessing a string with an index or length that exceeds valid bounds.
Implementation:
```cpp
class OutOfStringRange : public std::out_of_range {
public:
    OutOfStringRange(const std::string msg, const int idx=0)
     : std::out_of_range("Out of range: index out of \"" + (std::string)msg + "\"") {}
};
```
**Base class**: `std::out_of_range`
**Error message**: `Out of range: index out of "[string]"`
**Scenarios**:
- `left` / `right` / `mid` with length larger than string size
- Start index beyond string boundary


# Documentation of Exception `IndexUnderflow`
Function usage: Thrown when an index or length is negative (less than 0).
Implementation:
```cpp
class IndexUnderflow : public std::out_of_range {
public:
    IndexUnderflow(const int idx)
     : std::out_of_range("Index underflow: index " + std::to_string(idx) + " less than 0") {}
};
```
**Base class**: `std::out_of_range`
**Error message**: `Index underflow: index [value] less than 0`
**Scenarios**:
- Negative length in substring functions
- Negative repeat count
- Negative start index in string operations