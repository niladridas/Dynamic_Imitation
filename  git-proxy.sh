#!/bin/sh

exec corkscrew <name of proxy server> <port> $*

# <name_of_proxy_server> and <port> are the ip address and port of the server
# e.g. exec corkscrew 192.168.0.1 808 $*
