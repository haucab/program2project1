## This branch is for what the professor named "New requirements", which never materialized. Code is ugly, unfinished and untested

This was a university project that was canceled midway through by the professor. Codebase is uncommented, unfinished
extremely buggy and does not follow ANY sort of good programming practices as it was hacked together in a few
days (in my defence I saw MUCH WORSE codebases from other teams).

### No part of this codebase should ever make it onto another project. It is better to start from scratch than to use this.

Rough sketch of requirements:
- Database that holds a list of branches of the company, a list of employees, and a list of sent/received packages
- Said lists must be structured with a binary search tree, a doubly-liked circular list, and an AVL respectively
- All tree-like structures must have an option to display by level.
- Must preserve state by saving to file
- File can be an arbitrary format defined by the program
- File must preserve EXACT position of the items in the binary search tree / AVL
- I don't remember what info must be saved about each branch/person/package

Implementation details that I remember:
- There is no option to set a blank date. To set that a package has not arrived at its destination yet, an estimated
date must be set in the future. This date can later be changed to a more accurate estimate whenever needed.

Bugs that I remember:
- Binary tree code doesn't work, needs extensive rethinking.
- Package list isn't converted to AVL yet.
- File save doesn't work with all requirements yet, may not even work at all, don't remember.
- Deleting a person crashes the program. I knew the fix but the project was cancelled. It's something about a `strcpy_s`
being called with the wrong number. I remember it being something extremely trivial. Anyone who sees this in the future
can probably figure it out pretty quickly.

### If you are enough of a masochist to use this codebase, please send me a DM/Jabber so I can see what the hell you're doing with this monstrocity

Any instances of this code being found in the wild by others will result in the perpetrator being reported to the
authorities for being a violent sociopath and potentially becoming a future threat to society.
