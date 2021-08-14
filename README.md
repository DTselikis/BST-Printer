<div align="center">
<h1>BST-Printer</h1>
A Binary Search Tree with printing utility. 
<br>
<img src="https://i.imgur.com/cDoxVGw.png" width="200">
</div>

## Usage
A program that has the basic functionality of a Binary Search Tree and also the utility to print the tree vertically maintaining the BST format.
## Supported operations
- Node insertion
- Node deletion
- Find minimum key
- Find maximum Key
- Find keys in ginen range
- Print tree
## Node deletion
The deletion of a node performs a slitly different from the standard behavior. When the node to be deleted has none or at most one child, the deletion is as expected. But in the case of two childrens the the node to be deleted is **marked** as deleted but in remaines in the tree but will not be travered. The real deletion will hapen when the tree (or a subtree) needs to be reconstructed, which will happen under two conditions:
- The nodes marked as deleted is greater than 50% of the total nodes of the subtree and
- height of the subtree is at least 3.
- In case of node insertion the total nodes of one of the subtrees must be at most equal with the total nodes of the other subtree.
If **both** first and second conditions are met, the the tree will be constructed. Reconstruction can also be occured during node insartion if third condition is met.
#### Note
The detelion of a node can cause a tree reconstruction based on the third condition.
## Tree reconstruction
During reconstruction all nodes marked as deleted are removed from the tree. Then all keys are stored in a sorted matrix which then will be transformed in a balanced Binary Search Tree.

## Dependencies
- C++11

## Compilation
#### Windows
Compiled using MSVC 19.28.29912 .
#### Linux
Compiled using g++ 9.3.0. 
```makefile
make
```
