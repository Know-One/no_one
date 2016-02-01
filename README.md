# No_One

Random reusable "libs" that are intended to be compiled into your projects.

Currently only my random numbers library is up. Others will be added later.

 **no_random.c no_random.h**
  This random numbers library used a faster way to gather entropy than polling key presses, mouse clicks etc..
  It gathers entropy by measuring the difference between calling the same "get time" function twice in a row.
  In *thoery* the output should should always be the same.

  However in reality this not so. There is always variance. This is due to how modern computers handle multiple 
  tasks at once, and are receiving many kinds of inputs (data,peripherals,etc..) and even enviromental 
  differences such as temperature all have an affect.

  Naturally the output is not all entropy. I only keep one bit from the difference. And then I whiten the bits 
  to ensure the output is actually entropy. While it is random, this entropy is highly biased from what ever 
  it's source may be. So I use hashing to scramble the entropy into a less biased form.

  Check the header for for usage details.


 **no_test_random.c**
  Just link with no_random.c and no_random.h for a simple test of the library.
  This file requires at least c99 support. The library itself does not.

