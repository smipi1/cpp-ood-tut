# OOP language features

## Features shared with non-OOP languages

* [Variables](https://en.wikipedia.org/wiki/Variable_(computer_science)): To store state / information
* [Procedures (AKA functions, methods, routines, or subroutines)](https://en.wikipedia.org/wiki/Procedure_(computer_science)): Take input, generate output and manipulate data
* [Structured programming constructs](https://en.wikipedia.org/wiki/Structured_programming): Loops and conditionals
* [Modular programming](https://en.wikipedia.org/wiki/Modular_programming): Group procedures into files / modules

---

## Objects and classes

* [Classes](https://en.wikipedia.org/wiki/Class_(computer_programming)) define the data format (which maintains *state*) and available *methods*:
  - Colloquially: **classes** contain the **data members** and **member functions / methods**
  - A **Class** is an extensible program-code-template for creating an [object](https://en.wikipedia.org/wiki/Object_(object-oriented_programming))
* [Objects](https://en.wikipedia.org/wiki/Object_(object-oriented_programming)) are instances of classes:
  - The *state* is usually hidden and kept private.
  - Interactions are mediated by the *methods*.
  
### Class terminology:

* Member variables - all variables defined by a particular class, of which there are:
  - Class variables - only one copy of each per class;  they are shared across derived objects
  - Instance variables / attributes - belong to individual objects; every object has its own copy of each one
* Methods - of which there are:
  - Class methods - belong to the class as a whole and have access to only class variables and inputs from the procedure call
  - Instance methods - belong to individual objects, and have access to instance variables for the specific object they are called on, inputs, and class variables

---

## Class-based vs prototype based


## Dynamic dispatch / message parsing


## Data abstraction


## Encapsulation


## Composition, inheritance and delegation


## Polymorphism


## Open recursion


---

[Previous](./context.md) | [Top](../README.md) | [Next](./C-examples.md)