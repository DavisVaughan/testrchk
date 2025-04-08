#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

void r_fancy_list_setter(SEXP x, R_xlen_t i, SEXP value) {
    // Imagine other stuff happens in here besides just `SET_VECTOR_ELT()`
    SET_VECTOR_ELT(x, i, value);
}

SEXP ffi_make_list_false_positive(void) {
    SEXP out = PROTECT(Rf_allocVector(VECSXP, 1));

    // NOTE: rchk does not seem to think `elt` is protected here.
    SEXP elt = Rf_allocVector(INTSXP, 2);
    r_fancy_list_setter(out, 0, elt);

    // NOTE: The allocation here is when rchk complains about `elt` being unprotected
    SEXP names = Rf_allocVector(STRSXP, 2);
    Rf_setAttrib(elt, R_NamesSymbol, names);

    UNPROTECT(1);
    return out;
}

SEXP ffi_make_list_ok(void) {
    SEXP out = PROTECT(Rf_allocVector(VECSXP, 1));

    SEXP elt = Rf_allocVector(INTSXP, 2);
    SET_VECTOR_ELT(out, 0, elt);

    SEXP names = Rf_allocVector(STRSXP, 2);
    Rf_setAttrib(elt, R_NamesSymbol, names);

    UNPROTECT(1);
    return out;
}

static const R_CallMethodDef CallEntries[] = {
  {"ffi_make_list_false_positive",         (DL_FUNC) &ffi_make_list_false_positive, 0},
  {"ffi_make_list_ok",         (DL_FUNC) &ffi_make_list_ok, 0},
  {NULL, NULL, 0}
};

void R_init_testrchk(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
