FROM ubuntu:latest
RUN apt-get update &&\
    apt-get -y install g++ && \
    apt-get -y install libboost-all-dev &&\
    apt-get -y install cmake
WORKDIR /app
COPY . .
RUN mkdir build && cd build && cmake .. && make

CMD ["./build/Translator", "--f" , "program.txt"]
ENTRYPOINT ["./build/Translator"]


