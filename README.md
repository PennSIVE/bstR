# bstR

Binary search tree implementation with only basic operations. Rcpp exposes this data structure with the S4 class system.

BSTs are ideal when you need to search through your data many times, e.g. searching for the min takes logarithmic (instead of linear) time.

Example usage:
```R
root <- NULL
test <- c(2,5,3,9,8,11,6)
for (val in test) {
    node <- new("BSTnode")
    node@setValue(val)
    if (is.atomic(root)) {
        root <- node
    } else {
        root@addNode(node)
    }
}
root@inorder() # print what we took in
root@min() # this operation is very efficient
root@max() # ^same
```