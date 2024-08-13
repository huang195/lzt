#!/bin/sh

kubectl apply -f server.yaml
sleep 3
kubectl apply -f client.yaml
