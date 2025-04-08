#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

void r_list_poke(SEXP x, R_xlen_t i, SEXP value) {
    PROTECT(x);
    SET_VECTOR_ELT(x, i, value);
    UNPROTECT(1);
}

SEXP ffi_make_list(void) {
    SEXP out = PROTECT(Rf_allocVector(VECSXP, 1));

    SEXP elt = Rf_allocVector(INTSXP, 2);
    r_list_poke(out, 0, elt);

    SET_INTEGER_ELT(elt, 0, 1);
    SET_INTEGER_ELT(elt, 1, 2);

    SEXP names = Rf_allocVector(STRSXP, 2);
    Rf_setAttrib(elt, R_NamesSymbol, names);

    SET_STRING_ELT(names, 0, Rf_mkCharCE("x", CE_UTF8));
    SET_STRING_ELT(names, 1, Rf_mkCharCE("y", CE_UTF8));

    UNPROTECT(1);
    return out;
}

static const R_CallMethodDef CallEntries[] = {
  {"ffi_make_list",         (DL_FUNC) &ffi_make_list, 0},
  {NULL, NULL, 0}
};

void R_init_testrchk(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
