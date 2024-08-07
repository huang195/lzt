#!/bin/sh

kubectl delete -f server.yaml --force
kubectl delete -f client.yaml --force
