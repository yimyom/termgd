#' Open a terminal graphics device
#'
#' Creates a graphics device for terminal rendering
#' @param width Device width in inches
#' @param height Device height in inches
#' @param pointsize Default font size
#' @export
termgd <- function(width = 640, height = 480, pointsize = 12)
{
  invisible(.Call(termgd_create, width, height, pointsize))
}
