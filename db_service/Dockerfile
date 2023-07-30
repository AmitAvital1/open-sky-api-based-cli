FROM ubuntu:latest

WORKDIR .

COPY build/main .
COPY build/lib/libutility.so.1 .
COPY ./flightScanner.sh .

RUN apt-get update && apt-get install -y \ 
    libzip-dev \
    curl

RUN mkdir flightDB

ENV LD_LIBRARY_PATH .


CMD ./main

