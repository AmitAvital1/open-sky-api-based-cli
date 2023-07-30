#!/bin/bash

mkdir /tmp/flights_pipes

sudo docker pull omerefron/db_service

sudo docker pull omerefron/flights_service

sudo docker run --name db_service -d -v /tmp/flights_pipes:/flights_pipes db_service

sudo docker run --name flights_service -it -v /tmp/flights_pipes:/flights_pipes flights_service





