# Architecture - 多项目架构

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

Infrastructure 是一个多项目架构，包含多个独立的工具库和组件。

## 📁 项目结构

```
architecture/
├── CMakeLists.txt          # 顶层 CMake 配置
├── stk/                    # STK - Simple Tool Kit
│   ├── include/            # 公共头文件
│   ├── src/                # 源代码
│   └── tests/              # 单元测试
├── [other projects]/       # 其他项目
└── ...
```

## 📦 子项目

### STK - Simple Tool Kit

STK 是一个轻量级的 C/C++ 工具库，提供泛型容器和字符串处理功能。

#### ✨ 特性

- **双语言支持**：同时提供 C 和 C++ 接口
- **泛型容器**：支持 int、float、double、pointer、string 等类型
- **红黑树**：完整实现 RBTree，支持插入、删除、查找、遍历
- **数学运算**：向量支持加减乘、点积、范数、归一化等运算
- **跨平台**：支持 Windows、Linux、macOS
- **可选择库类型**：支持静态库和动态库（-fPIC）
- **模块化**：可按需选择编译模块（Vector、RBTree、String）

#### 📦 STK 模块

| 模块 | 描述 | C 接口 | C++ 接口 |
|------|------|--------|----------|
| Vector | 动态数组/数学向量 | `stk_vector_int.h`, ... | `stk::vector<T>` |
| RBTree | 红黑树 | `stk_rbtree_int.h`, ... | `stk::rbtree<T>` |
| String | 字符串 | `stk_string.h` | `stk::string` |

#### 🚀 STK 编译安装

```bash
cd architecture
mkdir build && cd build

# 只编译 STK
cmake .. -DBUILD_STK=ON
cmake --build . --config Release

# 编译 STK 静态库
cmake .. -DBUILD_STK=ON -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTS=ON
cmake --build . --config Release

# 编译 STK 动态库
cmake .. -DBUILD_STK=ON -DBUILD_SHARED_LIBS=ON
cmake --build . --config Release
```

#### STK CMake 选项

| 选项 | 默认值 | 描述 |
|------|--------|------|
| `BUILD_STK` | ON | 构建 STK 库 |
| `BUILD_SHARED_LIBS` | ON | 构建共享库（OFF=静态库） |
| `BUILD_CLIB` | ON | 构建 C 版本库 |
| `BUILD_VECTOR` | ON | 构建 Vector 模块 |
| `BUILD_RBTREE` | ON | 构建 RBTree 模块 |
| `BUILD_STRING` | ON | 构建 String 模块 |
| `BUILD_TESTS` | OFF | 构建单元测试 |

```bash
# 示例：只构建 Vector 模块的静态库
cmake .. -DBUILD_STK=ON -DBUILD_SHARED_LIBS=OFF -DBUILD_RBTREE=OFF -DBUILD_STRING=OFF
```

#### STK 运行测试

```bash
cd build
cmake .. -DBUILD_STK=ON -DBUILD_TESTS=ON
make
ctest -V --output-on-failure
```

## 🏗️ 环境要求

- CMake 3.12+
- C99 / C++17 编译器
- Windows: Visual Studio 2017+
- Linux: GCC 7+
- macOS: Clang 10+

## 📄 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件