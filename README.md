# CS 210 Portfolio – Corner Grocer Item Tracker

**Brian Robinson** · SNHU CS 210: Programming Languages

This repo holds my Project Three for CS 210, the Corner Grocer item tracker, written in C++.

## Project files

| File | What it does |
|------|--------------|
| [`CornerGrocer/CornerGrocer/main.cpp`](CornerGrocer/CornerGrocer/main.cpp) | Menu loop, input checking, and the flow of the program |
| [`CornerGrocer/CornerGrocer/GroceryTracker.h`](CornerGrocer/CornerGrocer/GroceryTracker.h) | The `GroceryTracker` class declaration |
| [`CornerGrocer/CornerGrocer/GroceryTracker.cpp`](CornerGrocer/CornerGrocer/GroceryTracker.cpp) | The class code: reading the file, counting, printing, backup |
| [`CornerGrocer/CornerGrocer/CS210_Project_Three_Input_File.txt`](CornerGrocer/CornerGrocer/CS210_Project_Three_Input_File.txt) | The day's purchase log (one item per line) |
| [`CornerGrocer/CornerGrocer.sln`](CornerGrocer/CornerGrocer.sln) | Visual Studio 2022 solution |

To run it, open `CornerGrocer.sln` in Visual Studio 2022 and press Ctrl+F5. The input file has to be in the same folder the program runs from, and that's already set up in the project folder.

## Reflection

### Summarize the project and what problem it was solving.

The Corner Grocer wanted to rearrange their produce section based on what people actually buy. They had a text file that logs every item bought during the day, one item per line, and they needed a program to make sense of it. My program reads that file and counts how many times each item shows up. Then it gives a menu where you can look up one item, print every item with its count, or print a text histogram with stars. It also saves a backup of all the counts to `frequency.dat` as soon as it starts, so the data's saved even if nobody picks anything from the menu.

### What did you do particularly well?

I think the input checking is the best part. If you type letters, a number that isn't on the menu, or something like `2abc`, the program doesn't crash or loop forever. It just tells you what went wrong and asks again. Item lookups also ignore case and extra spaces, so `apples`, `APPLES`, and ` Apples ` all find the same thing. I also kept the code split up well. All the counting and printing lives in the `GroceryTracker` class, and `main.cpp` only handles the menu.

### Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

- **Faster lookups.** Right now `GetItemFrequency` loops over every item to do the case-insensitive match. That's fine for 20 items, but a real store has thousands. I could store a lowercase version of each name as the map key so lookups use the map's O(log n) search instead of checking every item.
- **No hard-coded file names.** The input and backup file names are constants in `main.cpp`. Letting the user pass them in on the command line would make the program work for any day's file without recompiling.
- **Tests.** I tested by running the menu by hand. Unit tests for `Trim`, `ToLower`, and the counting would catch mistakes sooner if someone changes the code later.
- **Huge counts.** If an item was bought 500 times, the histogram line would run way off the screen. Scaling the bars to a max width would fix that.

### Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

Two things gave me trouble. The first was the menu input. When you type a letter where `cin` wants a number, `cin` goes into a fail state and the program loops forever. I fixed it by calling `cin.clear()` and `cin.ignore()` to reset the stream and throw away the bad input. The second one was sneakier. My item lookups kept saying 0 for items I knew were in the file. I used the Visual Studio debugger to look at the strings and saw that each line ended with a hidden `\r` from the Windows line endings. The `Trim` helper strips that out now.

For my support network, I'm adding [cppreference.com](https://en.cppreference.com/) for looking up how the standard library works, the Visual Studio debugger (watching variables solved the `\r` bug way faster than print statements), the zyBooks chapters for the course, and Stack Overflow for when I'm stuck on a weird error.

### What skills from this project will be particularly transferable to other projects or course work?

- Reading and writing files with `ifstream` and `ofstream`, and checking that the file actually opened
- Using a `std::map` to count things. Counting how often stuff shows up comes up all the time.
- Checking user input so a program can't be broken by a typo
- Splitting a program into a header, a class file, and a main file
- Using the debugger instead of guessing

These work in pretty much any language. Python has dictionaries and Java has HashMaps, and the idea's the same.

### How did you make this program maintainable, readable, and adaptable?

- Every file starts with a comment block saying what it's for, and each function has a short comment saying what it does.
- Names explain themselves: `LoadItems`, `WriteBackupFile`, `GetItemFrequency`, `m_itemCounts`.
- The menu numbers are named constants (`MENU_SEARCH_ITEM`, `MENU_EXIT`, etc.) instead of bare numbers in the `switch`, so changing the menu means changing one spot.
- The file names are constants at the top of `main.cpp`, so pointing it at a different file is a one-line change.
- The histogram symbol is a parameter with a default (`'*'`), so it can be changed without touching the function.
- The class doesn't know anything about the menu. That means the same class could be used with a GUI or a different program later.
