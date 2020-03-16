FROM pennsive/r-env:base
WORKDIR /src
RUN Rscript -e "install.packages('Rcpp')"
COPY . .
RUN Rscript /src/R/RcppExports.R