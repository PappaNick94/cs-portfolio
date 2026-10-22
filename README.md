# Corner Grocer Item Tracker

CS 210: Programming Languages — Project Three

## Project Summary

A Corner Grocer wanted to know how often each item was purchased so they could
rearrange their produce section. They provided a daily purchase log: a text file
where every line is a single item name, repeated once per purchase. This C++
program reads that log, counts how often each item appears, and presents the
results through a console menu. The user can look up a single item's frequency,
print every item with its count, or print a histogram showing one asterisk per
purchase. At startup the program also writes a backup file, `frequency.dat`,
containing every item and its count, without the user having to ask for it.

## What I Did Well

I kept the design separated by responsibility. The `GroceryTracker` class owns
the data and every operation on it — loading, backup, lookup, and printing —
while `main.cpp` does nothing but run the menu loop. That split means the menu
code never touches the data structure directly, so I could change how counts are
stored without editing `main.cpp` at all.

I also handled the case-sensitivity problem rather than ignoring it. A private
`Normalize` helper capitalizes the first letter and lowercases the rest, applied
both when loading the file and when looking an item up, so a user typing
`potatoes` gets the same answer as `Potatoes`. Menu input is validated too: if
`std::cin` fails on non-numeric input, `ReadMenuChoice` clears the error state
and discards the rest of the line, which prevents the infinite loop that
otherwise happens when you type a letter at a numeric prompt. Both file
operations return a `bool` so the caller decides what to do, rather than the
class printing errors on its own.

## Where I Could Enhance the Code

The input and backup filenames are hardcoded as constants at the top of
`main.cpp`. Accepting them as command-line arguments would let the grocer point
the program at a different day's log without recompiling.

Error reporting on load is coarse. `LoadFromFile` returns false only when the
file won't open, so a malformed or empty file is indistinguishable from a valid
one. Reporting how many records were read, and warning on zero, would catch a
bad input file immediately instead of showing an empty menu result.

`PrintHistogram` builds the asterisk run with `std::string(count, '*')`, which is
fine for the sample data but would wrap badly if an item appeared several hundred
times. Scaling the bar to a maximum width would keep the output readable at any
data size.

Finally, I'd add unit tests for `GroceryTracker` covering normalization, an item
that was never purchased, and an empty file. Right now I verified behavior by
running the program and reading the output, which works but doesn't protect
against regressions if I change the class later.

## Most Challenging Parts

Input validation was the piece that took the longest. I came into this from
Python, where bad input raises an exception you can catch. In C++, `std::cin`
fails silently, sets an error flag, and leaves the offending characters sitting
in the buffer, so the next read fails the same way and the menu loops forever.
I worked it out by deliberately feeding the program letters and watching where
it went wrong, then reading up on `cin.clear()` and `cin.ignore()` until I
understood that one resets the stream state and the other discards the leftover
input — and that you need both, in that order.

The other adjustment was the header and implementation split. Deciding what
belongs in `GroceryTracker.h` versus `GroceryTracker.cpp`, and marking the
read-only methods `const`, was unfamiliar at first but made the class easier to
reason about once it clicked.

Resources I'm keeping in my support network: cppreference.com for standard
library behavior, the zyBooks course material, compiler warnings as a first pass
of feedback, and my instructor's office hours for anything a reference page
doesn't resolve.

## Transferable Skills

File I/O, parsing structured text, selecting an appropriate data structure, and
validating untrusted input apply to essentially every program I'll write. The
`std::map` choice in particular was a deliberate trade-off — ordered iteration
for alphabetized output, at O(log n) lookup instead of the average O(1) an
unordered map would give — and reasoning about that kind of trade-off carries
into any language. These same patterns show up directly in the Python ETL and
API integration work I do outside of class, where the problems are identical even
though the syntax isn't.

## Maintainability, Readability, and Adaptability

Each function does one thing and is short enough to read without scrolling.
Names say what they do (`LoadFromFile`, `WriteBackupFile`, `GetFrequency`), so
the code reads without needing comments to explain mechanics; the comments that
are there explain intent and non-obvious decisions instead, like why
`itemCounts_` is cleared before loading or what `std::string(count, '*')` does.

The data structure is private and reachable only through the class's public
methods, so swapping `std::map` for something else would touch one file. Filenames
live in named constants rather than scattered string literals. Adding a menu
option means adding a case to the switch and a method to the class — no changes
anywhere else.
