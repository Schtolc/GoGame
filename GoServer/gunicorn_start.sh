#!/bin/bash

cd /home/pavelgolubev345/CocosWorkspace/GoGameLogic/GoServer
exec gunicorn -c gunicorn_conf.py GoGameLogic:application

