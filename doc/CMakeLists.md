# ============================================================================
#  ProjectName - 根 CMake 配置文件
#  基于大型项目最佳实践（参考 OpenCV 架构）
# ============================================================================

# ----------------------------------------------------------------------------
#  1. 禁止源码内构建
# ----------------------------------------------------------------------------
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
       Example:
         mkdir build && cd build && cmake ..
")
endif()

# ----------------------------------------------------------------------------
#  2. 包含最低版本配置
# ----------------------------------------------------------------------------
include(cmake/ProjectMinDepVersions.cmake OPTIONAL RESULT_VARIABLE HAS_MIN_VERSION)
if(NOT HAS_MIN_VERSION)
  set(MIN_VER_CMAKE "3.12")
  set(MIN_VER_CXX "17")
  set(MIN_VER_C "11")
endif()

# ----------------------------------------------------------------------------
#  3. CMake 最低版本要求
# ----------------------------------------------------------------------------
if(CMAKE_SYSTEM_NAME MATCHES "WindowsPhone|WindowsStore")
  cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
  cmake_policy(VERSION 2.8)
else()
  cmake_minimum_required(VERSION "${MIN_VER_CMAKE}" FATAL_ERROR)
endif()

# ----------------------------------------------------------------------------
#  4. CMake 策略设置（最佳实践）
# ----------------------------------------------------------------------------
if(POLICY CMP0026)
  cmake_policy(SET CMP0026 NEW)      # 目标名称使用
endif()
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)      # macOS @rpath
endif()
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)      # if() 参数解析
endif()
if(POLICY CMP0057)
  cmake_policy(SET CMP0057 NEW)      # IN_LIST 支持
endif()
if(POLICY CMP0066)
  cmake_policy(SET CMP0066 NEW)      # try_compile 标志
endif()
if(POLICY CMP0067)
  cmake_policy(SET CMP0067 NEW)      # 语言标准标志
endif()
if(POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)      # option() 变量
endif()
if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)      # MSVC 运行时库
endif()
if(POLICY CMP0146)
  cmake_policy(SET CMP0146 OLD)      # 旧版 FindCUDA
endif()

# ----------------------------------------------------------------------------
#  5. 项目声明
# ----------------------------------------------------------------------------
project(ProjectName VERSION 1.0.0 LANGUAGES C CXX)

# ----------------------------------------------------------------------------
#  6. 编译标准设置
# ----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD ${MIN_VER_CXX})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD ${MIN_VER_C})
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ----------------------------------------------------------------------------
#  7. 构建类型配置
# ----------------------------------------------------------------------------
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT PROJECT_SKIP_DEFAULT_BUILD_TYPE)
  message(STATUS "'Release' build type is used by default. Use CMAKE_BUILD_TYPE to specify build type")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build")
endif()

if(DEFINED CMAKE_BUILD_TYPE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)

# ----------------------------------------------------------------------------
#  8. 输出目录统一
# ----------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(3P_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/3rdparty/lib)

# ----------------------------------------------------------------------------
#  9. 位置无关代码（共享库必需）
# ----------------------------------------------------------------------------
option(ENABLE_PIC "Generate position independent code" ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ${ENABLE_PIC})

# ----------------------------------------------------------------------------
#  10. 安装前缀智能默认值
# ----------------------------------------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  if(NOT CMAKE_CROSSCOMPILING)
    if(WIN32)
      set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory" FORCE)
    else()
      set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Installation Directory" FORCE)
    endif()
  else()
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory" FORCE)
  endif()
endif()

# ----------------------------------------------------------------------------
#  11. Visual Studio 相对路径（避免路径过长）
# ----------------------------------------------------------------------------
if(MSVC)
  set(CMAKE_USE_RELATIVE_PATHS ON CACHE INTERNAL "" FORCE)
endif()

# ----------------------------------------------------------------------------
#  12. 启用测试
# ----------------------------------------------------------------------------
enable_testing()

# ----------------------------------------------------------------------------
#  13. Git 版本检测
# ----------------------------------------------------------------------------
find_package(Git QUIET)

if(NOT DEFINED PROJECT_VCSVERSION AND GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --always --dirty
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_VCSVERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
endif()

if(NOT PROJECT_VCSVERSION)
  set(PROJECT_VCSVERSION "unknown")
endif()

# ----------------------------------------------------------------------------
#  14. 版本号拆分为组件
# ----------------------------------------------------------------------------
string(REPLACE "." ";" PROJECT_VERSION_LIST ${PROJECT_VERSION})
list(GET PROJECT_VERSION_LIST 0 PROJECT_VERSION_MAJOR)
list(GET PROJECT_VERSION_LIST 1 PROJECT_VERSION_MINOR)
list(GET PROJECT_VERSION_LIST 2 PROJECT_VERSION_PATCH)

# ----------------------------------------------------------------------------
#  15. 编译选项
# ----------------------------------------------------------------------------
option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(ENABLE_LTO "Enable Link Time Optimization" OFF)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

# ----------------------------------------------------------------------------
#  16. 第三方库选项
# ----------------------------------------------------------------------------
option(WITH_PROTOBUF "Enable Protocol Buffer support" ON)
option(WITH_EIGEN "Enable Eigen support" ON)
option(WITH_OPENMP "Enable OpenMP support" OFF)
option(WITH_TBB "Enable TBB support" OFF)
option(WITH_CUDA "Enable CUDA support" OFF)

# ----------------------------------------------------------------------------
#  17. 模块构建选项
# ----------------------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_CORE "Build core module" ON)
option(BUILD_UTILS "Build utils module" ON)
option(BUILD_IO "Build IO module" ON)
option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_BENCHMARKS "Build performance benchmarks" OFF)

# ----------------------------------------------------------------------------
#  18. 安装选项
# ----------------------------------------------------------------------------
option(INSTALL_EXAMPLES "Install example programs" OFF)
option(INSTALL_TESTS "Install test binaries" OFF)
option(INSTALL_PKGCONFIG "Generate pkg-config file" ON)

# ----------------------------------------------------------------------------
#  19. 平台特定设置
# ----------------------------------------------------------------------------
if(WIN32)
  set(PLATFORM_NAME "Windows")
elseif(APPLE)
  set(PLATFORM_NAME "macOS")
elseif(UNIX)
  set(PLATFORM_NAME "Linux")
endif()

# ----------------------------------------------------------------------------
#  20. 检查系统库
# ----------------------------------------------------------------------------
if(UNIX AND NOT APPLE)
  find_package(Threads REQUIRED)
  set(PLATFORM_LINK_LIBS ${CMAKE_THREAD_LIBS_INIT} dl m rt)
endif()

# ----------------------------------------------------------------------------
#  21. 包含工具模块
# ----------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(ProjectUtils OPTIONAL)
include(ProjectCompilerOptions OPTIONAL)
include(ProjectModuleUtils OPTIONAL)

# ----------------------------------------------------------------------------
#  22. 检测编译器特性
# ----------------------------------------------------------------------------
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckCXXCompilerFlag)

# 检查 C++17 特性
check_cxx_compiler_flag("-std=c++17" HAVE_CXX17)

if(NOT HAVE_CXX17)
  message(WARNING "C++17 is not fully supported by this compiler")
endif()

# ----------------------------------------------------------------------------
#  23. 检测第三方库
# ----------------------------------------------------------------------------
if(WITH_EIGEN)
  find_package(Eigen3 QUIET)
  if(Eigen3_FOUND)
    set(HAVE_EIGEN TRUE)
    message(STATUS "Eigen found: ${EIGEN3_VERSION}")
  else()
    message(STATUS "Eigen not found, using built-in")
  endif()
endif()

if(WITH_PROTOBUF)
  find_package(Protobuf QUIET)
  if(Protobuf_FOUND)
    set(HAVE_PROTOBUF TRUE)
    message(STATUS "Protobuf found: ${Protobuf_VERSION}")
  endif()
endif()

if(WITH_OPENMP)
  find_package(OpenMP QUIET)
  if(OpenMP_CXX_FOUND)
    set(HAVE_OPENMP TRUE)
  endif()
endif()

# ----------------------------------------------------------------------------
#  24. 配置头文件生成
# ----------------------------------------------------------------------------
set(CONFIG_HEADER_DIR ${CMAKE_BINARY_DIR}/include/project)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/config.h.in
  ${CONFIG_HEADER_DIR}/config.h
  @ONLY
)

# ----------------------------------------------------------------------------
#  25. 包含子目录
# ----------------------------------------------------------------------------
include_directories(${CONFIG_HEADER_DIR})

# 第三方库子目录（如果存在）
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/CMakeLists.txt)
  add_subdirectory(3rdparty)
endif()

# 主库模块
if(BUILD_CORE AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/modules/core/CMakeLists.txt)
  add_subdirectory(modules/core)
endif()

if(BUILD_UTILS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/modules/utils/CMakeLists.txt)
  add_subdirectory(modules/utils)
endif()

if(BUILD_IO AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/modules/io/CMakeLists.txt)
  add_subdirectory(modules/io)
endif()

# 应用程序（如果存在）
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/apps/CMakeLists.txt)
  add_subdirectory(apps)
endif()

# 示例程序
if(BUILD_EXAMPLES AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/samples/CMakeLists.txt)
  add_subdirectory(samples)
endif()

# 测试
if(BUILD_TESTS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
  enable_testing()
  add_subdirectory(tests)
endif()

# 文档
if(BUILD_DOCS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/doc/CMakeLists.txt)
  add_subdirectory(doc)
endif()

# ----------------------------------------------------------------------------
#  26. 安装规则
# ----------------------------------------------------------------------------
# 公共头文件安装
install(DIRECTORY include/project/
  DESTINATION include/project
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".git*" EXCLUDE
)

# 库导出
install(EXPORT ProjectTargets
  FILE ProjectTargets.cmake
  NAMESPACE project::
  DESTINATION lib/cmake/project
)

# 版本配置
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_BINARY_DIR}/ProjectConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  ${CMAKE_BINARY_DIR}/ProjectConfigVersion.cmake
  DESTINATION lib/cmake/project
)

# pkg-config 文件
if(INSTALL_PKGCONFIG)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/project.pc.in
    ${CMAKE_BINARY_DIR}/project.pc
    @ONLY
  )
  install(FILES ${CMAKE_BINARY_DIR}/project.pc DESTINATION lib/pkgconfig)
endif()

# ----------------------------------------------------------------------------
#  27. CPack 打包配置
# ----------------------------------------------------------------------------
include(CPack)

set(CPACK_PACKAGE_NAME "ProjectName")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ProjectName - A high-performance library")
set(CPACK_PACKAGE_VENDOR "Project Vendor")
set(CPACK_PACKAGE_CONTACT "user@example.com")

if(WIN32)
  set(CPACK_GENERATOR "NSIS;ZIP")
  set(CPACK_NSIS_DISPLAY_NAME "ProjectName")
elseif(APPLE)
  set(CPACK_GENERATOR "DragNDrop;Bundle")
else()
  set(CPACK_GENERATOR "DEB;RPM;TGZ")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "user@example.com")
  set(CPACK_RPM_PACKAGE_LICENSE "MIT")
endif()

# ----------------------------------------------------------------------------
#  28. 配置信息输出（OpenCV 风格）
# ----------------------------------------------------------------------------
macro(STATUS msg)
  message(STATUS "${msg}")
endmacro()

macro(PRINT_FEATURE name condition)
  if(${condition})
    status("    ${name}:" "YES")
  else()
    status("    ${name}:" "NO")
  endif()
endmacro()

status("")
status("==================== ProjectName Configuration ====================")
status("  General:")
status("    Version:           ${PROJECT_VERSION}")
if(PROJECT_VCSVERSION)
  status("    VCS version:       ${PROJECT_VCSVERSION}")
endif()
status("    Platform:          ${PLATFORM_NAME}")
status("    Architecture:      ${CMAKE_SYSTEM_PROCESSOR}")
status("    Build type:        ${CMAKE_BUILD_TYPE}")
status("    Install prefix:    ${CMAKE_INSTALL_PREFIX}")
status("")
status("  Compiler:")
status("    C++ compiler:      ${CMAKE_CXX_COMPILER}")
status("    C++ standard:      ${CMAKE_CXX_STANDARD}")
status("    C compiler:        ${CMAKE_C_COMPILER}")
status("    C standard:        ${CMAKE_C_STANDARD}")
status("")
status("  Build options:")
status("    Shared libraries:  ${BUILD_SHARED_LIBS}")
status("    PIC enabled:       ${ENABLE_PIC}")
status("    Warnings as errors: ${ENABLE_WARNINGS_AS_ERRORS}")
status("    LTO enabled:       ${ENABLE_LTO}")
status("")
status("  Modules:")
status("    Core:              ${BUILD_CORE}")
status("    Utils:             ${BUILD_UTILS}")
status("    IO:                ${BUILD_IO}")
status("")
status("  Features:")
PRINT_FEATURE("Eigen" HAVE_EIGEN)
PRINT_FEATURE("Protobuf" HAVE_PROTOBUF)
PRINT_FEATURE("OpenMP" HAVE_OPENMP)
status("")
status("  Components:")
status("    Tests:             ${BUILD_TESTS}")
status("    Examples:          ${BUILD_EXAMPLES}")
status("    Documentation:     ${BUILD_DOCS}")
status("")
status("  Directories:")
status("    Source dir:        ${CMAKE_SOURCE_DIR}")
status("    Binary dir:        ${CMAKE_BINARY_DIR}")
status("    Install prefix:    ${CMAKE_INSTALL_PREFIX}")
status("===============================================================")
status("")

# ----------------------------------------------------------------------------
#  29. 可选：生成 setup_vars 脚本
# ---------------------------------------------------------------------------
if(UNIX AND NOT CMAKE_CROSSCOMPILING)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/setup_vars.sh.in
    ${CMAKE_BINARY_DIR}/setup_vars.sh
    @ONLY
  )
  message(STATUS "Environment setup script: ${CMAKE_BINARY_DIR}/setup_vars.sh")
endif()

# ----------------------------------------------------------------------------
#  30. 最后的钩子（用于调试）
# ----------------------------------------------------------------------------
if(CMAKE_VERBOSE_MAKEFILE)
  file(WRITE ${CMAKE_BINARY_DIR}/cmake_vars.txt
    "PROJECT_VERSION: ${PROJECT_VERSION}\n"
    "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}\n"
    "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}\n"
    "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n"
  )
endif()

message(STATUS "Configuration complete. Ready to build.")