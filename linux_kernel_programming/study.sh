#!/usr/bin/env bash
set -euo pipefail

command_name="${1:-shell}"
shift || true

kernel_dir() {
  find -L /lib/modules -mindepth 2 -maxdepth 2 -type d -name build -print -quit
}

vm_state=/workspace/.state

guest_boot() {
  guest_command="${1:-}"
  mkdir -p "$vm_state"
  : > "$vm_state/guest-exit"
  if [[ -n "$guest_command" ]]; then
    printf '%s\n' "$guest_command" >"$vm_state/guest-command"
  else
    : > "$vm_state/guest-command"
  fi

  qemu_args=(
    -machine pc
    -m 2G
    -smp 2
    -cpu max
    -nographic
    -serial mon:stdio
    -nic none
    -no-reboot
    -kernel /opt/vm/vmlinuz
    -initrd /opt/vm/initramfs.img
    -append "console=ttyS0 rdinit=/init"
    -virtfs "local,path=/opt/vm/guest-root,mount_tag=root,security_model=none,readonly=on"
    -virtfs "local,path=/usr,mount_tag=usr,security_model=none,readonly=on"
    -virtfs "local,path=/etc,mount_tag=etc,security_model=none,readonly=on"
    -virtfs "local,path=/workspace/code,mount_tag=code,security_model=none"
    -virtfs "local,path=/workspace/exercises,mount_tag=exercises,security_model=none"
    -virtfs "local,path=/workspace/.state,mount_tag=state,security_model=none"
  )
  if [[ "${BOOK_KVM:-0}" == 1 || -e /dev/kvm ]]; then
    qemu_args+=( -enable-kvm )
  fi
  if [[ -z "$guest_command" ]]; then
    if qemu-system-x86_64 "${qemu_args[@]}"; then
      qemu_status=0
    else
      qemu_status=$?
    fi
  else
    if timeout "${BOOK_VM_TIMEOUT:-60}s" qemu-system-x86_64 "${qemu_args[@]}"; then
      qemu_status=0
    else
      qemu_status=$?
    fi
  fi
  if (( qemu_status != 0 )); then
    return "$qemu_status"
  fi
  if [[ -s "$vm_state/guest-exit" ]]; then
    guest_status="$(tr -d '[:space:]' <"$vm_state/guest-exit")"
    [[ "$guest_status" =~ ^[0-9]+$ ]] && return "$guest_status"
  fi
  return "$qemu_status"
}

case "$command_name" in
  verify)
    for tool in gcc make bc bison flex clang sparse qemu-system-x86_64; do
      command -v "$tool" >/dev/null
    done
    kdir="$(kernel_dir)"
    test -n "$kdir"
    test -f /workspace/code/ch04/helloworld_lkm/Makefile
    make -C /workspace/code/ch04/helloworld_lkm KDIR="$kdir" clean >/dev/null 2>&1 || true
    make -C /workspace/code/ch04/helloworld_lkm KDIR="$kdir"
    guest_boot 'set -eu; uname -a; test -f /workspace/code/ch04/helloworld_lkm/helloworld_lkm.ko; insmod /workspace/code/ch04/helloworld_lkm/helloworld_lkm.ko; rmmod helloworld_lkm'
    echo "kernel programming toolchain ready"
    ;;
  build)
    target="${1:-/workspace/code/ch04/helloworld_lkm}"
    shift || true
    kdir="${KDIR:-$(kernel_dir)}"
    test -n "$kdir"
    make -C "$target" KDIR="$kdir" "$@"
    ;;
  run)
    script="${1:-}"
    shift || true
    if [[ -n "$script" ]]; then
      case "$script" in
        /workspace/code/*|/workspace/exercises/*) guest_script="$script" ;;
        code/*|exercises/*) guest_script="/workspace/$script" ;;
        *) echo "run accepts a script under code/ or exercises/" >&2; exit 2 ;;
      esac
      guest_command=sh
      printf -v quoted '%q' "$guest_script"
      guest_command+=" $quoted"
      for argument in "$@"; do
        printf -v quoted '%q' "$argument"
        guest_command+=" $quoted"
      done
      guest_boot "$guest_command"
    else
      guest_boot 'uname -a; cat /proc/version; echo "guest ready: /workspace/code"'
    fi
    ;;
  shell)
    guest_boot
    ;;
  *)
    echo "usage: study.sh verify|build [dir] [make args...]|run [code|exercises/script.sh] [args...]|shell" >&2
    exit 2
    ;;
esac
