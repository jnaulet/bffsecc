# The bffsecc project
## What is bffsecc ?
Bffsecc stands for "Basic Framework For Safer Embedded C Code".

It's a collection of macros & as its name implies, it is supposed to help
embedded developpers to create a safer code.

## Why bffsecc ?

After many years in the embedded software business i tried all the techniques in the book
and basically, two of them give the most solid results: asserts & unit tests.

These are the most powerful tools an embedded C developer can use, but they are not without drawbacks :

  - asserts usually consume a lot of RAM & need to output results to a console
  - after a successful build & run, unit tests are often overlooked & not maintained properly

bffsecc is an attempt at solving these two issues by providing an really small but yet powerful API
that doesn't consume much RAM, doesn't require a console port & tries to force the developer to
maintain its unit tests.

## Is bffsecc enough to fly to the moon ?

Nope. This tool is only part of your arsenal... You need to master static analysis & coding rules, too.

As a static analyzer, i suggest splint, cause it is really harsh and punitive :)

## Basic API

### Asserts
In e_assert.h :
```
bool e_assert(bool predicate);
```
This is your main option when it comes to asserts & a powerful one, indeed.

In debug mode, when using a debugger or a probe, this function sets a breakpoint at the current pc
if the predicate is false. Then you can look at memory and/or stack before any crash happens (hopefully).

In release mode (-DNDEBUG), it just checks the predicate value, which allows you to return an error 
or solve the abnormal condition if needed.

```
void e_assert_fail(void);
```
In debug mode, this macro forces a breakpoint at the current pc. This is useful for code coverage.

In release mode, this is simply ignored.

```
void e_assert_void(bool predicate);
```
Use it in void returning functions, same as POSIX 'assert' function.

### Unit tests
In u_test.h :
```
INIT_U_TESTS : Declares the required global variables to run the tests properly
U_TEST(func) : Declares a void (void) function as a unit test, mostly for cosmetic reasons
U_TESTS : Substitutes to main to run the unit tests declared by U_TEST
RUN_U_TEST : Calls the current unit test function (with log)
END_U_TESTS : Returns the status of the tests, mainly for automation purposes

Example of structure :

INIT_U_TESTS;

U_TEST(test1)
{
  /* ... */
}

U_TESTS {
  RUN_U_TEST(test1);
  RUN_U_TEST(test2);
  /* ... */
  END_U_TESTS;
}
```

#### Unit tests assertions
```
void u_assert(bool predicate);
void u_assert_eq(var a, var b);
void u_assert_str_eq(char *a, char *b);
```
These functions are used inside unit tests to check values & show if a test
succeeded or failed & why.

## Any examples ?

Yes, just check the examples directory.
