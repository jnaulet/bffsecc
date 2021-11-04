# The Seven Deadly Sins of the Embedded C Developer

## 1: Not using a static analyzer
Rationale: The static analyzer serves two purposes. First it checks for avoidable errors
before any execution or even compilation of the code.

Second, it ensures you keep your code clean & organized during the whole life of
the project.

## 2: Using nested switches & too much nesting in general
Rationale: This kind of construction almost garantees you won't be able
to get a decent code coverage in your unit tests.

As a general rule of thumb, a switch deserves its own function and two levels of
nesting per function (three, exceptionally) is the maximum.

## 3: Keyword & types redefinition
Rationale: any competent developer must be able to understand your code just by looking
at it. Any custom stuff is forbidden, especially if it's already available in ANSI C
or POSIX.

stddef.h, stdint.h & stdbool.h are your only choices regarding base types.

'const', 'volatile' & 'register' are keywords telling the compiler how it should behave,
not properties of a type. Don't hide them in typedefs or defines.

structs as objects should not be 'typedef'-ed, to remind the developer it doesn't fit
inside a register.

## 4: Mixing C & C++
Rationale: this will make any decent static analyzer complain or go crazy. C might be
included in C++ but the opposite is not true.

More, the linker might not be able to link object files compiled by gcc & g++ without
an indecent number of extern "C" wraps all over the headers. Awful.

## 5: Using global variables
Rationale: This will make any refactoring of your code a pain. You will find out the hard
way what file uses this variable you just moved around or removed.

All your globals should de static , including your main program context and you should
only manipulate them with accessors (a.k.a object oriented programming).

## 6: Not checking parameters
Rationale: Any function parameter must have boundaries & has to be checked
(or better, asserted with bffsecc e_assert() function).

You must confirm your parameters are correct first, so then you can safely execute your
algorithm with no need for exceptions management.

Your program must be like a conveyor belt in a biscuit factory. Any non-conform
parameter must be kicked out, the program cannot stop or crash.

Some of these checks could be perfomed by your static analyzer but beware, some
don't !

## 7: Not being coherent
Rationale: You must be able to spot any anomaly instantaneously.

Files names, functions names, coding guidelines, indentation, etc. Pick a standard and
apply it religiously so any inconsistency is obvious and can be remedied quickly.

Use an automatic indentation system so your code doesn't slowly drift to inconsistency
every time someone fixes or adds something. This is especially useful for bug tracking,
you want your patches to be free of any kind of "noise".

By making the exception the norm, you will make your life miserable.

### 8 (bonus): Trying to be smart
Rationale: You might be tempted to use a hack to make quick work of what appears to be
an otherwise long and fastidious job, but it's usually a mistake.

I especially think about the temptation of generalisation, when you think you could
replace a bunch of accessors with a table full of properties.

The risk is you discover more and more properties along the way and you table grows
and grows until it makes too many things for its own good.

Be selfish and think about yourself in a few months, in which state do you want your
code to be when it will come back to you with a bug hidden somewhere ?
