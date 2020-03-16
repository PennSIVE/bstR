Rcpp::sourceCpp("/src/cpp/main.cpp")

setClass(
    "BSTnode",
    slots = c(
        ptr = "externalptr",
        setValue = "function",
        getValue = "function",
        min = "function",
        max = "function",
        addNode = "function",
        inorder = "function"
    )
)

setMethod(
    "initialize",
    "BSTnode",
    function(.Object) {
        .Object@ptr <- MakeBSTnode()
        .Object@setValue <- function(x) {
            UpdateBSTnode(.Object@ptr, x)
        }
        .Object@getValue <- function() {
            GetBSTnodeValue(.Object@ptr)
        }
        .Object@min <- function() {
            getMin(.Object@ptr)
        }
        .Object@max <- function() {
            getMax(.Object@ptr)
        }
        .Object@addNode <- function(x) {
            addNode(.Object@ptr, x)
        }
        .Object@inorder <- function() {
            inorderTraversal(.Object@ptr)
        }
        .Object
    }
) 


root <- NULL
test <- c(2,5,3,9,8,11,6)
for (val in test) {
    ptr <- new("BSTnode")
    ptr@setValue(val)
    if (is.atomic(root)) {
        root <- ptr
    } else {
        root@addNode(ptr)
    }
}
root@inorder()
root@min()
root@max()