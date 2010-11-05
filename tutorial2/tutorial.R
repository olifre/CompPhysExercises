f <- function(p, x, t, err) {
  s <- sum((x-(p[1]+p[2]*t))/err)
  return(s)
}

chisqr <- function(p, x, t, err) {
  cs <- sum((((p[1]*t+p[2])-x)**2)/((err)**2))
  return(cs)
}

corchisqr <- function(p, x, t, err, A) {
  C <- solve(A)
  ccs <- (x-(p[1]*t+p[2])) %*% C %*% (x-(p[1]*t+p[2]))
  return(ccs)
}

fit.boot <- function(data, ivector, err, t, par, A) {
  x <- rep(0, times=length(data[1,]))
  if(!missing(ivector)) {
    for(i in 1:length(data[1,])){
      x[i] <- mean(data[ivector, i])
    }
  }
  else {
    for(i in 1:length(data[1,])) {
      x[i] <- mean(data[,i])
    }
  }
  res <- optim(par=par, fn=corchisqr, x=x, err=err, t=t, method=c("BFGS"), A=A)
  return(c(res$par, res$value))
}
