# lzt

# instructions

## create seccomp profile

```
podman exec [podman vm id] mkdir -p /var/lib/kubelet/seccomp
podman cp profiles/notify.json [podman vm id]:/var/lib/kubelet/seccomp/notify.json
```
