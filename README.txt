Project by: Owen Wexler and Huzaif Mansuri

Here is the command line we used to run

To compile: enter the directory of the project, then type "make" into the command prompt.
To execute: type "./mymalloc" into the command prompt after compiling.


Our Test Plan: memgrind.c:

Our program runs through five major tests (3 of which have already been given to us), then performs a few mini-tests once each that are designed to show how the program can determine incorrect usage and produce error messages.

Here are the five tests:

1. Allocate and then immediately free the same chunk 120 times, then repeat x50.
2. Allocate 120 times, then free all 120 chunks in a row, then repeat x50.
3. Allocate or free randomly with equal chance until we've allocated 120 times total, then free all chunks and repeat x50.
4. Allocate 120 chunks of alternating sizes, then free them in a row, then repeat x50.
5. Allocate 120 chunks of 1 byte memory, then free only half of them, and reallocate 60 more 2-byte chunks. Then free everything. x50


Here are the Mini-Tests. They are performed only once and were constructed based on a lecture that Menendez gave on February 23rd.
1. Allocate all memory, then try to allocate more.
2. Allocate more memory than exists in total.
3. Attempt to free an address that is outside the range of MEMSIZE.
4. Attempt to free an address that isn't the start of a chunk.
5. Attempt allocate memory when gaps exist, but which are not large enough to fit the memory allocated.


Miscellaneous Notes:
It was unclear if any additional tests had to be repeated 50 times each.