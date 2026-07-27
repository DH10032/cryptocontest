# cryptocontest

## pwndbg

[pwndbg](https://github.com/pwndbg/pwndbg) (a GDB plugin for exploit
development and reverse engineering) can be installed in this environment.

```bash
./scripts/install-pwndbg.sh
```

The container is ephemeral, so re-run the script after starting a fresh
session. After it finishes, pwndbg loads automatically on every `gdb` launch.

Verify:

```bash
gdb -q -batch -ex version -ex quit | grep -i pwndbg
# Pwndbg:   2026.07.27 build: ... (Linux)
```

### Environment notes

Confirmed working on the web session container (Ubuntu 24.04, x86_64,
GDB 15.1 with embedded CPython 3.12):

- The venv is built with `/usr/bin/python3.12` — the same Python GDB embeds.
- `git clone` over https works; PyPI is reachable, so `uv` pulls the
  dependencies fine.
- GitHub *HTML* pages are blocked by the egress policy, but the git protocol
  is not — `pip install pwndbg` does **not** work (no distributions are
  published on PyPI), so the script installs from the git checkout instead.
