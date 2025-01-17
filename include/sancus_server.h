/*
 * This file is part of sancus-core <http://github.com/amery/sancus-core>
 *
 * Copyright (c) 2011, Alejandro Mery <amery@geeks.cl>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the author nor the names of its contributors may
 *     be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _SANCUS_SERVER_H
#define _SANCUS_SERVER_H

/*
 * tcp server
 */
enum sancus_tcp_server_error {
	SANCUS_TCP_SERVER_WATCHER_ERROR,
	SANCUS_TCP_SERVER_ACCEPT_ERROR,
};
struct sancus_tcp_server {
	struct sancus_list ports;
	struct sancus_list connections;
};

void sancus_tcp_server_init(struct sancus_tcp_server *server);

/*
 * tcp listening ports
 */
struct sancus_tcp_port {
	struct sancus_list ports;

	ev_io connection_watcher;
};

int sancus_tcp_ipv4_port(struct sancus_tcp_port *self, struct sancus_tcp_server *server,
			 const char *addr, unsigned port,
			 bool cloexec, void (*sockopts) (int));
int sancus_tcp_ipv6_port(struct sancus_tcp_port *self, struct sancus_tcp_server *server,
			 const char *addr, unsigned port,
			 bool cloexec, void (*sockopts) (int));
int sancus_tcp_local_port(struct sancus_tcp_port *self, struct sancus_tcp_server *server,
			  const char *path,
			  bool cloexec, void (*sockopts) (int));

int sancus_tcp_port_listen(struct sancus_tcp_port *self, unsigned backlog);
void sancus_tcp_port_start(struct sancus_tcp_port *self, struct ev_loop *loop);
void sancus_tcp_port_stop(struct sancus_tcp_port *self, struct ev_loop *loop);

#endif /* !_SANCUS_SERVER_H */
