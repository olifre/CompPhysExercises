fit.boot <- function(data, ivector, err, t, par) {
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
  res <- optim(par=par, fn=chisqr, x=x, err=err, t=t, method=c("BFGS"))
  return(c(res$par, res$value))
}
