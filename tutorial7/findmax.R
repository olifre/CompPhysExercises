findmax <- function() {
	f <- function(x) if((x>=-1) && (x<=1)) return(-exp(-x^2) * cos(50*x)) else return(NA);
	res <- optimize(f, interval=c(-1, 1));
	print(res);
}
