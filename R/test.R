## usethis namespace: start
#' @useDynLib testrchk, .registration = TRUE
## usethis namespace: end
NULL

make_list_false_positive <- function() {
  .Call(ffi_make_list_false_positive)
}

make_list_ok <- function() {
  .Call(ffi_make_list_ok)
}
