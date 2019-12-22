#!/bin/bash

if [[ $1 = "clean" ]]
then
  rm -rf out &&\
  rm  ftests/py_atl.so &&\
  echo Clean successfull.
else
  mkdir -p out &&\
  cd out &&\
  cmake .. &&\
  make &&\
  cd .. &&\
  cp out/ftests/cpp/libpy_atl.so ftests/py_atl.so &&\
  echo Build successfull.
fi

echo build.sh finished.
