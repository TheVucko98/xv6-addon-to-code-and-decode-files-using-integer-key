# OS2025 - Homework 2: xv6 File System Enhancement

This project extends the MIT xv6 operating system by adding advanced file system features, encryption capabilities, and new system calls and user-space utilities.

---

## 🧩 Overview

The goal of this assignment is to enhance the xv6 file system with the following functionalities:

- Support for **large files** using a **double indirect pointer** in the inode structure.
- **Encryption and decryption** of file contents using a **Caesar cipher** with a global key.
- A set of **new system calls** and **user programs** that manage encryption, console echo behavior, and large file creation.

All modifications are integrated seamlessly into the xv6 kernel without breaking existing functionality or performance.

---

## ⚙️ Implemented Features

### 🔸 File System Enhancements
- Modified `inode` and `dinode` structures to include a **double indirect block pointer**.
- Supports files up to `11 + 128 + 128*128` blocks.
- Fully integrated into existing xv6 read/write logic (no mkfs modification required).

### 🔸 File Encryption & Decryption
- Uses a **Caesar cipher** for file content encryption.
- Supports encryption/decryption of any regular file on disk.
- Tracks encryption status using the `major` field in the inode (0 = unencrypted, 1 = encrypted).
- Read/write syscalls automatically encrypt/decrypt data transparently using the global key.

---

## 🧠 System Calls

| System Call | Description | Return Values |
|--------------|--------------|----------------|
| `int setkey(int key)` | Sets global Caesar cipher key | `0` on success, `-1` on error |
| `int setecho(int echo)` | Enables/disables console echo (1 = normal, 0 = masked as '*') | `0` on success, `-1` on error |
| `int encr(int fd)` | Encrypts the open file | `0` success, `-1` key not set, `-2` T_DEV file, `-3` already encrypted |
| `int decr(int fd)` | Decrypts the open file | `0` success, `-1` key not set, `-2` T_DEV file, `-3` not encrypted |

---

## 💻 User Programs

### 🔹 `setkey`
Sets the global encryption key via `setkey()` syscall.  
Options:
- `--help` or `-h` — show help
- `--secret` or `-s` — read key from `STDIN` with echo disabled via `setecho(0)`

### 🔹 `encr`
Encrypts one or more files using the current key.  
Options:
- `--help` or `-h` — show help
- `--encrypt-all` or `-a` — encrypts all unencrypted files in the current directory

### 🔹 `decr`
Decrypts one or more files using the current key.  
Options:
- `--help` or `-h` — show help
- `--decrypt-all` or `-a` — decrypts all encrypted files in the current directory

### 🔹 `blockwriter`
Creates a file of a specified size in blocks and fills it with predictable text data.  
Options:
- `--help` or `-h` — show help
- `--output-file` or `-o <FILENAME>` — output file name (default: `long.txt`)
- `--blocks` or `-b <BLOCKS>` — number of blocks (default: `150`)

---

## 🧩 Integration Notes

- Existing xv6 functionalities (read/write, open/close, fork/exec, etc.) remain unaffected.
- Encryption works transparently within the file system layer.
- Device files (`T_DEV`) cannot be encrypted or decrypted.
- Code adheres to xv6 coding style and passes all provided test scripts.

---

## 🚀 How to Build & Run

```bash
# Clone your assigned repository
git clone <your-github-classroom-repo>

cd xv6-public
make qemu
