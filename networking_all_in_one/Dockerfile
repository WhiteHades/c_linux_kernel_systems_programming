FROM fedora:44@sha256:43b29f65a41eb9c35e1cd5323e3bdf3b655c2357a9f4f1ff2f9c2798e5045d80
RUN dnf -y --setopt=timeout=20 --setopt=minrate=20k --setopt=retries=2 \
    --setopt=max_parallel_downloads=10 \
    '--setopt=fedora.metalink=' \
    '--setopt=fedora.baseurl=https://dl.fedoraproject.org/pub/fedora/linux/releases/$releasever/Everything/$basearch/os/' \
    '--setopt=updates.metalink=' \
    '--setopt=updates.baseurl=https://dl.fedoraproject.org/pub/fedora/linux/updates/$releasever/Everything/$basearch/' \
    install iproute iputils bind-utils traceroute tcpdump nmap-ncat curl python3 dnsmasq util-linux \
    && command -v setpriv \
    && dnf clean all
COPY --chmod=0555 entrypoint.sh /usr/local/bin/network-entrypoint
ENTRYPOINT ["/usr/local/bin/network-entrypoint"]
WORKDIR /workspace/exercises
