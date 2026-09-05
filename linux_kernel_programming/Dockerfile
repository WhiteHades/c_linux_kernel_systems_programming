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
        bc \
        bison \
        bash \
        build-essential \
        ca-certificates \
        clang \
        coccinelle \
        cppcheck \
        flex \
        gawk \
        gdb \
        git \
        libelf-dev \
        libncurses-dev \
        libnuma-dev \
        libssl-dev \
        pahole \
        perl \
        python3 \
        procps \
        qemu-system-x86 \
        sparse \
        sudo \
        stress-ng \
        strace \
        tree \
        xz-utils \
        zstd \
        linux-image-virtual \
        linux-headers-virtual \
        busybox-static \
        cpio \
        kmod \
    && rm -rf /var/lib/apt/lists/*

COPY vm/init /opt/vm-init
COPY vm/guest-init /usr/local/bin/book-guest-init
RUN set -eux; \
    chmod 0555 /opt/vm-init; \
    chmod 0555 /usr/local/bin/book-guest-init; \
    kernel_version="$(find -L /lib/modules -mindepth 1 -maxdepth 1 -type d -printf '%f\n' | sort -V | tail -n1)"; \
    test -n "$kernel_version"; \
    test -f "/boot/vmlinuz-$kernel_version"; \
    test -d "/lib/modules/$kernel_version"; \
    test -e "/lib/modules/$kernel_version/build"; \
    mkdir -p /opt/vm/guest-root/usr /opt/vm/guest-root/etc \
        /opt/vm/guest-root/dev /opt/vm/guest-root/proc \
        /opt/vm/guest-root/sys/fs/cgroup /opt/vm/guest-root/run \
        /opt/vm/guest-root/tmp /opt/vm/guest-root/var \
        /opt/vm/guest-root/workspace/code \
        /opt/vm/guest-root/workspace/exercises \
        /opt/vm/guest-root/workspace/.state; \
    ln -s usr/bin /opt/vm/guest-root/bin; \
    ln -s usr/sbin /opt/vm/guest-root/sbin; \
    ln -s usr/lib /opt/vm/guest-root/lib; \
    ln -s usr/lib64 /opt/vm/guest-root/lib64; \
    mkdir -p /opt/vm/rootfs/bin /opt/vm/rootfs/sbin /opt/vm/rootfs/etc \
        /opt/vm/rootfs/dev /opt/vm/rootfs/proc /opt/vm/rootfs/sys \
        /opt/vm/rootfs/mnt/code /opt/vm/rootfs/mnt/exercises \
        /opt/vm/rootfs/mnt/state /opt/vm/rootfs/lib/modules; \
    cp -L /bin/busybox /opt/vm/rootfs/bin/busybox; \
    for applet in cat chroot dmesg mount mkdir modprobe poweroff sh sync uname; do \
        ln -s busybox "/opt/vm/rootfs/bin/$applet"; \
    done; \
    ln -s ../bin/busybox /opt/vm/rootfs/sbin/insmod; \
    ln -s ../bin/busybox /opt/vm/rootfs/sbin/rmmod; \
    module_dir="/lib/modules/$kernel_version"; \
    minimal_module_dir="/opt/vm/rootfs/lib/modules/$kernel_version"; \
    mkdir -p "$minimal_module_dir"; \
    cp -a "$module_dir"/modules.* "$minimal_module_dir/"; \
    awk -F': *' '\
      { deps[$1] = $2; if ($1 ~ /(^|\/)(9p|9pnet|9pnet_virtio)\.ko(\.|$)/) roots[++n] = $1 } \
      function visit(module, i, count, parts) { \
        if (seen[module]++) return; \
        print module; \
        count = split(deps[module], parts, " "); \
        for (i = 1; i <= count; i++) if (parts[i] != "") visit(parts[i]); \
      } \
      END { for (i = 1; i <= n; i++) visit(roots[i]) } \
    ' "$module_dir/modules.dep" > /tmp/vm-modules; \
    while IFS= read -r module; do \
      test -n "$module"; \
      module_path="$minimal_module_dir/$module"; \
      mkdir -p "$(dirname "$module_path")"; \
      cp -a "$module_dir/$module" "$module_path"; \
      case "$module_path" in \
        *.ko.zst) zstd -q -d -f "$module_path" -o "${module_path%.zst}"; rm -f "$module_path" ;; \
        *.ko.xz) xz -d -f "$module_path" ;; \
        *.ko.gz) gzip -d -f "$module_path" ;; \
      esac; \
    done < /tmp/vm-modules; \
    test -s /tmp/vm-modules; \
    depmod -b /opt/vm/rootfs "$kernel_version"; \
    rm -f /tmp/vm-modules; \
    cp /opt/vm-init /opt/vm/rootfs/init; \
    chmod 0555 /opt/vm/rootfs/init; \
    printf '%s\n' "$kernel_version" > /opt/vm/kernel-version; \
    cp "/boot/vmlinuz-$kernel_version" /opt/vm/vmlinuz; \
    chmod 0444 /opt/vm/vmlinuz; \
    (cd /opt/vm/rootfs && find . -print0 | cpio --null -o -H newc 2>/dev/null | gzip -9) > /opt/vm/initramfs.img; \
    rm -rf /opt/vm/rootfs /opt/vm-init

WORKDIR /workspace
CMD ["bash"]
