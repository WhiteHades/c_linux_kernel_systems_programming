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
        binutils \
        bochs \
        bochs-sdl \
        build-essential \
        ca-certificates \
        curl \
        genisoimage \
        gcc-multilib \
        grub-pc-bin \
        make \
        nasm \
        qemu-system-x86 \
        qemu-system-gui \
        xorriso \
    && rm -rf /var/lib/apt/lists/*

COPY study.sh /usr/local/bin/book-study
RUN chmod 0555 /usr/local/bin/book-study
RUN curl --fail --location --silent --show-error \
      https://raw.githubusercontent.com/littleosbook/littleosbook/e90faeb24c5c9fed8cde9a35974893706e81cbbf/files/stage2_eltorito \
      --output /opt/stage2_eltorito \
    && echo '6ef07c7fc2552b63d3ceffa38a713e9ba9c88a54267fce2c93448966eaeeaff1  /opt/stage2_eltorito' \
      | sha256sum --check --strict \
    && chmod 0444 /opt/stage2_eltorito
COPY probe /opt/probe

WORKDIR /workspace
CMD ["bash"]
