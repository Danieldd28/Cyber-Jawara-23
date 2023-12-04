FROM ubuntu:22.04

RUN apt-get -y update && apt-get -y install socat python2 --fix-missing && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/chall
#RUN groupadd ctf && useradd --no-create-home -g ctf ctf

COPY wordless.py wordless.py
COPY flag.txt /flag.txt

RUN chmod 644 /flag.txt

EXPOSE 5000
ENTRYPOINT socat -dd TCP4-LISTEN:5000,fork,reuseaddr EXEC:"./wordless.py",su=nobody
