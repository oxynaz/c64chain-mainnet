# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/user/github-export-mainnet/translations"
  "/home/user/github-export-mainnet/build/translations"
  "/home/user/github-export-mainnet/build/generate_translations_header-prefix"
  "/home/user/github-export-mainnet/build/generate_translations_header-prefix/tmp"
  "/home/user/github-export-mainnet/build/generate_translations_header-prefix/src/generate_translations_header-stamp"
  "/home/user/github-export-mainnet/build/generate_translations_header-prefix/src"
  "/home/user/github-export-mainnet/build/generate_translations_header-prefix/src/generate_translations_header-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/user/github-export-mainnet/build/generate_translations_header-prefix/src/generate_translations_header-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/user/github-export-mainnet/build/generate_translations_header-prefix/src/generate_translations_header-stamp${cfgdir}") # cfgdir has leading slash
endif()
