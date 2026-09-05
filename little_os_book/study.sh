#!/usr/bin/env bash
set -euo pipefail

export LANG=C.UTF-8
export LC_ALL=C.UTF-8

command_name="${1:-shell}"
shift || true

boot_probe() (
  stage2=/workspace/code/author/files/stage2_eltorito
  [[ -f "$stage2" ]] || stage2=/opt/stage2_eltorito
  test -f "$stage2"
  temp_dir="$(mktemp -d)"
  trap 'rm -rf "$temp_dir"' EXIT
  nasm -f elf32 /opt/probe/loader.s -o "$temp_dir/loader.o"
  ld -m elf_i386 -T /opt/probe/link.ld "$temp_dir/loader.o" -o "$temp_dir/kernel.elf"
  mkdir -p "$temp_dir/iso/boot/grub"
  cp "$stage2" "$temp_dir/iso/boot/grub/stage2_eltorito"
  # genisoimage writes the boot-info table into the boot image.
  chmod u+w "$temp_dir/iso/boot/grub/stage2_eltorito"
  cp "$temp_dir/kernel.elf" "$temp_dir/iso/boot/"
  cp /opt/probe/menu.lst "$temp_dir/iso/boot/grub/"
  genisoimage -quiet -R -b boot/grub/stage2_eltorito \
    -no-emul-boot -boot-load-size 4 -boot-info-table \
    -o "$temp_dir/probe.iso" "$temp_dir/iso"
  if timeout "${BOOK_VM_TIMEOUT:-20}s" qemu-system-i386 \
    -cdrom "$temp_dir/probe.iso" -display none -monitor none -serial none -nic none \
    -no-reboot -device isa-debug-exit,iobase=0xf4,iosize=0x04; then
    qemu_status=0
  else
    qemu_status=$?
  fi
  [[ "$qemu_status" == 33 ]] || {
    echo "OS boot probe failed (QEMU status $qemu_status)." >&2
    return 1
  }
  echo "GRUB and IA-32 boot probe passed"
)

case "$command_name" in
  verify)
    for tool in gcc ld nasm make genisoimage qemu-system-i386 bochs; do
      command -v "$tool" >/dev/null
    done
    test -f /opt/stage2_eltorito || test -f /workspace/code/author/files/stage2_eltorito
    temp_dir="$(mktemp -d)"
    trap 'rm -rf "$temp_dir"' EXIT
    printf 'int main(void) { return 0; }\n' >"$temp_dir/check.c"
    gcc -m32 -ffreestanding -c "$temp_dir/check.c" -o "$temp_dir/check.o"
    nasm -f elf32 /dev/stdin -o "$temp_dir/check-asm.o" <<'EOF'
global check_asm
check_asm:
    ret
EOF
    boot_probe
    echo "OS toolchain ready"
    ;;
  build)
    target="${1:-/workspace/exercises}"
    shift || true
    if [[ -f "$target/Makefile" || -f "$target/makefile" ]]; then
      if [[ ! -f "$target/stage2_eltorito" && -f /opt/stage2_eltorito ]]; then
        cp /opt/stage2_eltorito "$target/stage2_eltorito"
      fi
      [[ ! -f "$target/stage2_eltorito" ]] || chmod u+w "$target/stage2_eltorito"
      make -C "$target" "$@"
    else
      boot_probe
      echo "No Makefile yet. Add the files from the book, then run mise run build."
    fi
    ;;
  run)
    target="${1:-/workspace/exercises}"
    shift || true
    if [[ -f "$target/os.iso" ]]; then
      exec qemu-system-i386 -cdrom "$target/os.iso" -display curses -monitor vc -serial none -nic none -no-reboot -no-shutdown "$@"
    fi
    if [[ -f "$target/Makefile" || -f "$target/makefile" ]]; then
      if [[ ! -f "$target/stage2_eltorito" && -f /opt/stage2_eltorito ]]; then
        cp /opt/stage2_eltorito "$target/stage2_eltorito"
      fi
      [[ ! -f "$target/stage2_eltorito" ]] || chmod u+w "$target/stage2_eltorito"
      if make -C "$target" os.iso; then
        exec qemu-system-i386 -cdrom "$target/os.iso" -display curses -monitor vc -serial none -nic none -no-reboot -no-shutdown "$@"
      fi
      exec make -C "$target" run "$@"
    fi
    boot_probe
    echo "No OS project yet. Add the files from the book, then run mise run run."
    ;;
  shell)
    exec bash "$@"
    ;;
  *)
    echo "usage: study.sh verify|build [dir] [make args...]|run [dir] [qemu args...]|shell" >&2
    exit 2
    ;;
esac
