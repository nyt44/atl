#!/bin/bash

if [[ $1 = "clean" ]]
then
  rm -rf out &&\
  rm -rf ftests/bin &&\
  echo Clean successfull.
else
  mkdir -p out &&\
  cd out &&\
  cmake .. &&\
  make &&\
  cd .. &&\
  mkdir -p ftests/bin &&\
  cp out/ftests/libpy_atl.so ftests/bin/py_atl.so &&\
  echo Build successfull.
fi

echo build.sh finished.
