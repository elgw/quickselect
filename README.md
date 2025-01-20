# Quickselect

Just another quicksort implementation.

- The library can be built for 32-bit or 64-bit floating point arrays.

- Clean under valgrind and `-fanalyzer`, although all corner cases not
  tested.

- Tested with gcc and clang under linux.

- Median of five was tested but the average performance was too poor
   to be included.

- Performance: > 10X faster than quicksort in some cases. For an array
  of 8M elements, quickselect took in average 0.07 s. In comparison,
  it took 1.0 s for a full qsort.

## Usage

Just add `quickselect.c` and `quickselect.h` to your program.
