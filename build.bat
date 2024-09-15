@echo off

chcp 65001


set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja


set BUILD_FOLDER=build_%BUILD_SUFFIX%

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..
cmake --build .

cmd /k
