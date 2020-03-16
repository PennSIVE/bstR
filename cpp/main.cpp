#include <Rcpp.h>
#include <stdlib.h>

struct BSTnode
{
    double value;
    struct BSTnode *left;
    struct BSTnode *right;
};

BSTnode *init_BSTnode()
{
    return (BSTnode *)::malloc(sizeof(BSTnode));
}

void free_BSTnode(BSTnode *ptr)
{
    ::free(ptr);
    ::printf("free_BSTnode called.\n"); 
}

typedef Rcpp::XPtr<BSTnode, Rcpp::PreserveStorage, free_BSTnode> xptr_t;

// [[Rcpp::export]]
xptr_t MakeBSTnode()
{
    BSTnode *ptr = init_BSTnode();
    ptr->value = 0;
    ptr->left = NULL;
    ptr->right = NULL;

    return xptr_t(ptr, true);
}

// [[Rcpp::export]]
void UpdateBSTnode(xptr_t ptr, SEXP x)
{
    if (TYPEOF(x) == REALSXP)
    {
        R_xlen_t i = 0, sz = XLENGTH(x);
        for (; i < sz; i++)
        {
            if (!ISNA(REAL(x)[i]))
            {
                ptr->value = REAL(x)[i];
            }
        }
        return;
    }

    if (TYPEOF(x) == INTSXP)
    {
        R_xlen_t i = 0, sz = XLENGTH(x);
        for (; i < sz; i++)
        {
            if (!ISNA(INTEGER(x)[i]))
            {
                ptr->value = INTEGER(x)[i];
            }
        }
        return;
    }

    Rf_warning("Invalid SEXPTYPE.\n");
}

// [[Rcpp::export]]
double GetBSTnodeValue(xptr_t ptr)
{
    return ptr->value;
}

// [[Rcpp::export]]
double getMin(xptr_t ptr)
{
    BSTnode *cur = (BSTnode *)R_ExternalPtrAddr(ptr);
    while (cur->right != NULL)
    {
        cur = cur->right;
    }
    return cur->value;
}

// [[Rcpp::export]]
double getMax(xptr_t ptr)
{
    BSTnode *cur = (BSTnode *)R_ExternalPtrAddr(ptr);
    while (cur->left != NULL)
    {
        cur = cur->left;
    }
    return cur->value;
}

// [[Rcpp::export]]
void addNode(xptr_t ptr, SEXP exp)
{
    // TYPEOF(exp) == S4SXP
    std::string rtypename("BSTnode");
    Rcpp::S4 s4obj(exp);
    if (!s4obj.is(rtypename.c_str()))
    {
        Rf_error((std::string("object is not of the type ") + rtypename).c_str());
    }

    SEXP extptrsxp = s4obj.slot("ptr");
    // TYPEOF(extptrsxp) == EXTPTRSXP
    BSTnode *real = (BSTnode *)R_ExternalPtrAddr(extptrsxp);

    double v = real->value;
    if (ptr->value < v)
    {
        if (ptr->left != NULL)
        {
            addNode(xptr_t(ptr->left, true), exp);
        }
        else
        {
            ptr->left = real;
        }
    }
    else
    {
        if (ptr->right != NULL)
        {
            addNode(xptr_t(ptr->right, true), exp);
        }
        else
        {
            ptr->right = real;
        }
    }
}

// [[Rcpp::export]]
void inorderTraversal(xptr_t x)
{
    BSTnode *ptr = (BSTnode *)R_ExternalPtrAddr(x);
    if (ptr == NULL)
    {
        return;
    }
    inorderTraversal(xptr_t(ptr->left, true));
    ::printf("%f\n", ptr->value);
    inorderTraversal(xptr_t(ptr->right, true));
}