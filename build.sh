#!/usr/bin/env bash
if [ "$1" = prod ]; then
    docker-compose -f docker-compose.yaml -f docker-compose.tx2.yaml build .
else
    docker-compose build .
fi 

if [ "$2" = run ] || [ "$1" = run ]; then
  docker-compose up -d
fi
