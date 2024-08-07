#!/bin/sh

kubectl apply -f server.yaml
sleep 5
kubectl apply -f client.yaml
