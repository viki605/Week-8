# Week-8
This program is a Souvenir Tracker written in C++ that allows users to log souvenirs they collect, view summaries, save data to a file, and get a recommendation on their collecting level.

This project is a continuation of my Week 07 assignment, and for Week 08 I expanded the program by organizing the logic into a C++ class.

**Features:**

- Friendly introduction banner

- Menu-driven program using switch

- Input validation for strings, integers, and doubles

- Console color formatting (Windows)

- Enum to represent souvenir types

- Struct to group souvenir data

- Array of structs to store multiple souvenirs

- File output to save souvenir reports

- Summary calculations (total, average, highest, lowest)

- Recommendation system using compound conditions

- Uses for, while, and do-while loops


**The SouvenirTracker class manages:**

- An array of Souvenir structs

- A counter to track how many souvenirs are stored

- Member functions for collecting input, displaying data, saving to a file, processing summaries, and recommending a collecting level


**Loops Used**

- for loop – adding a fixed number of souvenirs

- while loop – processing the array for totals and averages

- do-while loop – repeating the menu until the user quits


**File Output**

- Souvenir data is saved to report.txt

- The file can be viewed from the program using a menu option

- Output is formatted using setw, alignment, and precision
