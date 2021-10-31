# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)

project(haloceded-patches
    VERSION 1.0.0
    LANGUAGES CXX
)

add_executable(haloceded-patcher main.cpp)

set_target_properties(haloceded-patcher PROPERTIES LINK_FLAGS "-static -static-libgcc")
