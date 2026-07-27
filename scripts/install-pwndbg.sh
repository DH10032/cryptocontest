#!/usr/bin/env bash
#
# Install pwndbg (GDB plugin for exploit dev / reversing) into this environment.
#
# Verified to work on the Claude Code web session container:
#   - Ubuntu 24.04, x86_64
#   - GDB 15.1 with embedded CPython 3.12  (venv is built with /usr/bin/python3.12)
#   - git clone over https works; PyPI (pypi.org / files.pythonhosted.org) is reachable
#   - GitHub HTML browsing is blocked, but the git protocol is not, so `git clone` is fine
#
# The container is ephemeral, so re-run this after starting a fresh session.
# Usage: ./scripts/install-pwndbg.sh
set -euo pipefail

# Where to keep the pwndbg checkout. Override with PWNDBG_DIR=... if desired.
PWNDBG_DIR="${PWNDBG_DIR:-$HOME/pwndbg}"
PWNDBG_REPO="https://github.com/pwndbg/pwndbg.git"

# Skip pwndbg's own on-launch dependency auto-update (needs network every start).
export PWNDBG_NO_AUTOUPDATE=1

echo "[*] Installing pwndbg into: ${PWNDBG_DIR}"

if [ -d "${PWNDBG_DIR}/.git" ]; then
    echo "[*] Existing checkout found, updating..."
    git -C "${PWNDBG_DIR}" pull --ff-only || echo "[!] pull failed, continuing with existing checkout"
else
    echo "[*] Cloning pwndbg (shallow)..."
    git clone --depth 1 "${PWNDBG_REPO}" "${PWNDBG_DIR}"
fi

echo "[*] Running pwndbg setup.sh (builds a venv with gdb's python, installs deps via uv)..."
( cd "${PWNDBG_DIR}" && ./setup.sh )

echo
echo "[+] Done. pwndbg was appended to ~/.gdbinit and loads on every 'gdb' launch."
echo "[+] Quick check:"
echo "      gdb -q -batch -ex 'version' -ex quit | grep -i pwndbg"
