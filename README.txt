Project by: Owen Wexler and Huzaif Mansuri

Here is the command line we used to run

To compile:gcc -Wall -Werror -fsanitize=address memgrind.c -o memgrind
To execute:./memgrind.c


Our Test Plan:




How our test programs work, including memgrind.c:


memgrind.c:

Here are the five tests:

1. Allocate and then immediately free the same chunk 120 times, then repeat x50.
2. Allocate 120 times, then free all 120 chunks in a row, then repeat x50.
3. Allocate or free randomly with equal chance until we've allocated 120 times total, then free all chunks and repeat x50.
4.
5.


other programs:

We did not write any other test programs. (yet?)





Miscellaneous Notes:
