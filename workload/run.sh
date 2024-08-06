#!/bin/sh

kubectl run server --image=haih/server
kubectl apply -f server.yaml
sleep 5
kubectl run client --image=haih/client
