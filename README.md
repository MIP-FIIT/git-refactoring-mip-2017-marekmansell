# MIP - Git Refactoring
This repository contains a refactored version of *Project 1* for *Procedural Programming*.

# Documentation
There is an online documentation hosted on http://marekmansell.sk/mip/

# Refactoring comments
While refactoring this code, I have made the source code much more readable and maintainable. Most of the work has been done on creating proper comments, which have not been properly written in the earlier verion. Secondly, I have renamed variables to apropriate names. Another important change was made in the *if* statements, where double brackets with an exclemaing mark were replaced with a comparison to *0*. Each function was tailored so that it contains only the code appropiate for the given task. Most of the so called magic numbers have been transformed in to defined constants. Unfortunately I was not able to create unit tests, however, in the git repo I have added a LICENCE, README and CONTRIB file, as well as documentation written in ReStructuRed and generated with Spinx and the ReadTheDocs theme. This documentation is hosted [online](http://marekmansell.sk/mip/) thanks to _gitpages_ - [this is the repo](https://github.com/marekmansell/mip). A branch was created for the docs and merged in to the master branch. An apripriate .gitignore file has been added, part of which has been downloaded form an online source (default [gitignore files](https://github.com/github/gitignore)) and part has been added by the author. Two issues were made, however, only one was closed - the [Create Docs](https://github.com/MIP-FIIT/git-refactoring-mip-2017-marekmansell/issues/1) was succefully closed, but not the [Create tests](https://github.com/MIP-FIIT/git-refactoring-mip-2017-marekmansell/issues/4). In the end, a version tah _1.0_ should be added.

# Author
Marek Mansell - Student of FIIT, Slovak University of Technology

Personal website: www.marekmansell.sk

# LICENCE
This repository is licenced under the MIT licence. More detailed information can be found in the *LICENCE* file.

# To Do List
*  ~~Rename variables to appropriate names~~
*  ~~Replace parameter numbers with constants (#define)~~
*  Create unit tests
*  ~~Add comments and format them properly~~
*  ~~Correct pointer handling~~
*  ~~Add LICENCE, README, gitignore~~
*  ~~Sphinx Documentation (docs file)~~
*  ~~Translate everything into English (except strings)~~
*  ~~Create functions for specific tasks in order to improve readibility~~
*  ~~Write guide for developers (maybe CONTRIB file?)~~ 
