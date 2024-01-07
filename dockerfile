FROM gcc:latest

RUN apt-get update && apt-get install -y libmicrohttpd-dev

WORKDIR /usr/src/myapp

COPY myapp.c .

RUN gcc -o myapp myapp.c -lmicrohttpd

EXPOSE 80

CMD ["./myapp"]