#!/usr/bin/env bash

set -euo pipefail

cd -- "$(dirname -- "${BASH_SOURCE[0]}")"

IMAGE="build/mellow.iso"
OVMF_CODE="/usr/share/edk2/x64/OVMF_CODE.4m.fd"

echo "=> Building Mellow"
make

echo "=> Booting Mellow"
exec qemu-system-x86_64 \
	-drive if=pflash,format=raw,readonly=on,file="$OVMF_CODE" \
	-cdrom "$IMAGE"
