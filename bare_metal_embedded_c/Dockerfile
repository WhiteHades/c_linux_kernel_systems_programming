FROM gcc:16@sha256:213a0e383dc1429862a8f12624dfe8fb43339bc808a79f4e578529e4903b3054 AS certs

FROM ubuntu:26.04@sha256:2260313b31c8c011cd2eebe728008efac1b3982be73eb71348ea2648d2c0e09b

COPY --from=certs /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt

ENV DEBIAN_FRONTEND=noninteractive

RUN for source in /etc/apt/sources.list /etc/apt/sources.list.d/ubuntu.sources; do \
      if [ -f "$source" ]; then \
        sed -i \
          -e 's|http://archive.ubuntu.com/ubuntu|https://archive.ubuntu.com/ubuntu|g' \
          -e 's|http://security.ubuntu.com/ubuntu|https://security.ubuntu.com/ubuntu|g' \
          "$source"; \
      fi; \
    done

RUN apt-get -o Acquire::https::CaInfo=/etc/ssl/certs/ca-certificates.crt update \
    && apt-get -o Acquire::https::CaInfo=/etc/ssl/certs/ca-certificates.crt \
        install --no-install-recommends -y \
        bash \
        binutils-arm-none-eabi \
        ca-certificates \
        gcc-arm-none-eabi \
        gdb-multiarch \
        libnewlib-arm-none-eabi \
        make \
        openocd \
    && rm -rf /var/lib/apt/lists/*

COPY study.sh /usr/local/bin/book-study
RUN chmod 0555 /usr/local/bin/book-study

WORKDIR /workspace
CMD ["bash"]
