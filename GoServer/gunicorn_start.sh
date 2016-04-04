#!/bin/bash

cd /home/pavelgolubev345/CocosWorkspace/GoGame/GoServer
exec gunicorn -c gunicorn_conf.py GoGame:application

