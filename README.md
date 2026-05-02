# STK - Simple Tool Kit

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

STK 是一个轻量级的 C/C++ 工具库，提供泛型容器（Vector、RBTree）和字符串处理功能。

## ✨ 特性

- **双语言支持**：同时提供 C 和 C++ 接口
- **泛型容器**：支持 int、float、double、pointer、string 等类型
- **红黑树**：完整实现 RBTree，支持插入、删除、查找、遍历
- **字符串**：功能丰富的字符串操作
- **跨平台**：支持 Windows、Linux、macOS
- **可选择库类型**：支持静态库和动态库
- **模块化**：可按需选择编译模块

## 📦 模块

| 模块 | 描述 | C 接口 | C++ 接口 |
|------|------|--------|----------|
| Vector | 动态数组 | `VecInt`, `VecFloat`, ... | `stk::vector<T>` |
| RBTree | 红黑树 | `RBTreeInt`, `RBTreeFloat`, ... | `stk::rbtree<T>` |
| String | 字符串 | `String` | `stk::string` |

## 🚀 快速开始

### 环境要求

- CMake 3.12+
- C99/C++17 编译器
- Windows: Visual Studio 2017+
- Linux: GCC 7+
- macOS: Clang 10+

### 编译安装

```bash
git clone https://github.com/yourname/stk.git
cd stk
mkdir build && cd build

# 编译静态库（默认）
cmake .. -DBUILD_SHARED_LIBS=OFF
cmake --build . --config Release
sudo cmake --install .

# 编译动态库
cmake .. -DBUILD_SHARED_LIBS=ON
cmake --build . --config Release