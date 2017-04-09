# libv8
This project is used to store the prebuilt static and dynamic libraries of the V8 JavaScript engine

## Build

First make sure you have installed the latest version of [node.js](http://nodejs.org/)
(You may need to restart your computer after this step).

Then install the depsync tool:

```
npm install -g depsync
```
Run the depsync tool in the project's root directory:

```
depsync
```
Wait for a while until it finishes, and all the dependencies of this project will be automatically downloaded. Then just run the camke command to build or open the project with CLion.