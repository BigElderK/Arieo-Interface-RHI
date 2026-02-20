cmake_minimum_required (VERSION 3.31)

include($ENV{ARIEO_BUILD_ENV_PACKAGES_OUTPUT_DIR}/cmake/build_environment.cmake)
project(ArieoEngine)

arieo_engine_project(
    arieo_rhi_interface
    PROJECT_TYPE interface

    DEPENDENCIES
        ARIEO_PACKAGES
            Arieo-Core
            Arieo-Interface-Window
        INTERFACES
            Arieo-Interface-Window::arieo_window_interface
            Arieo-Core::arieo_core

    SOURCES
        INTERFACE_INCLUDE_FOLDERS
            ${CMAKE_CURRENT_LIST_DIR}/public/include

    INTERFACE_CODE_GENERATION
        ROOT_NAMESPACE Arieo::Interface::RHI
        SCRIPT_PACKAGE_NAME arieo:rhi

        AST_GENERATE_FOLDER
            ${CMAKE_CURRENT_LIST_DIR}/_generated/ast
        NATIVE_CODE_GENERATE_FOLDER
            ${CMAKE_CURRENT_LIST_DIR}/_generated/native
        WASM_WIT_GENERATE_FOLDER
            ${CMAKE_CURRENT_LIST_DIR}/_generated/wasm/wit
        WASM_CXX_SCRIPT_GENERATE_FOLDER
            ${CMAKE_CURRENT_LIST_DIR}/_generated/wasm/cxx
        WASM_CSHARP_SCRIPT_GENERATE_FOLDER
            ${CMAKE_CURRENT_LIST_DIR}/_generated/wasm/csharp
        WASM_RUST_SCRIPT_GENERATE_FOLDER
            ${CMAKE_CURRENT_LIST_DIR}/_generated/wasm/rust
)
