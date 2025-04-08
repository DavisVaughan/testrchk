## usethis namespace: start
#' @useDynLib testrchk, .registration = TRUE
## usethis namespace: end
NULL

make_list <- function() {
  .Call(ffi_make_list)
}
