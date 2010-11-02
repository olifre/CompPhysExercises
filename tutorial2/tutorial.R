f <- function(p, x, t, err) {
  s <- sum((x-(p[1]+p[2]*t))/err)
  return(s)
}
