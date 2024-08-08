# lzt

# instructions

## create kind cluster

## create seccomp profile

```
podman exec [podman vm id] mkdir -p /var/lib/kubelet/seccomp/profiles
podman cp profiles/notify.json [podman vm id]:/var/lib/kubelet/seccomp/profiles/notify.json
```

## build and run seccomp agent

There are some issues with DockerHub rate limiting anonymous image pulls when
connected to the IBM network. A workaround is to load and use local images in a
kind cluster.

In the seccompagent repo:

```
make container-build
podman save -o image.tar docker.io/haih/spireseccompagent:latest-WIP
kind load image-archive image.tar 
rm -rf image.tar
```

We can now run the seccomp agent in the lzt repo:

```
kubectl apply -f deploy/seccompagent.yaml
```
