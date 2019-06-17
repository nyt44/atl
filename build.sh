#!/bin/bash

if [[ $1 = "clean" ]]
then
  rm -rf out &&\
  echo Clean successfull.
else
  mkdir -p out &&\
  cd out &&\
  cmake .. &&\
  make &&\
  cd .. &&\
  echo Build successfull.
fi

echo build.sh finished.
