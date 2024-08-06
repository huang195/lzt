#!/bin/sh

kubectl delete pod client --force
kubectl delete pod server --force
kubectl delete -f server.yaml
