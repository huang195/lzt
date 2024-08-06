all: client server


client: client.c
	podman build -t docker.io/haih/client:latest -f Dockerfile.client .
	podman push docker.io/haih/client:latest 

server: server.c
	podman build -t docker.io/haih/server:latest -f Dockerfile.server .
	podman push docker.io/haih/server:latest 
