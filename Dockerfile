FROM debian:stable-slim
RUN apt update && apt install -y make libreadline-dev gcc

ENV HOSTNAME=debian
ENV USER=root

WORKDIR /root
COPY . .
RUN make && make clean
CMD	./minishell
