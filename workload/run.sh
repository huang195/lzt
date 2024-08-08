#!/bin/sh

kubectl apply -f server.yaml
sleep 10
kubectl apply -f client.yaml
