# Challenges
1. Pick and open source implementation of a language you like. Download the source code and pokek around in it. Try to find the code that implements the scanner and parser. Are they handwritten, or generated using tools like Lex and Yacc? (.l or .y files usually imply the latter.)
  - https://github.com/python/cpython/tree/main/Parser
  - Looks mostly handwritten, but I do see they use Zephyr ASDL and generate C from it?
2. Just-in-time compilation tends to be the fastest way to implement dynamically typed languages, but not all of them use it. What reasons are there to _not_ JIT?
  - Simplicity / ease of understanding. Easier to design.
  - Code complexity / size / generated binary size?
  - Other reasons?
3. Most Lisp implementations that compile to C also contain an interpreter that lets them execute Lisp code on the fly as well. Why?
  - Easier to quickly try new ideas with a REPL.
  - Potentially easier to debug.
