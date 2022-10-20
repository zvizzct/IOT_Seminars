# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Uni/2022-2023/iot/espp/esp-idf-v4.4.2/components/bootloader/subproject"
  "C:/Users/victo/eclipse-workspace/Seminar_3_4/build/bootloader"
  "C:/Users/victo/eclipse-workspace/Seminar_3_4/build/bootloader-prefix"
  "C:/Users/victo/eclipse-workspace/Seminar_3_4/build/bootloader-prefix/tmp"
  "C:/Users/victo/eclipse-workspace/Seminar_3_4/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/victo/eclipse-workspace/Seminar_3_4/build/bootloader-prefix/src"
  "C:/Users/victo/eclipse-workspace/Seminar_3_4/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/victo/eclipse-workspace/Seminar_3_4/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
