#ifndef _SOCKET_H_
#define _SOCKET_H_

typedef struct {

} socket_t;

int socket_send(socket_t *self, const void *buffer, size_t lenght);

//***************VER PARAMETROS DE ESTA FUNCION****************
int socket_receive();

void socket_init(socket_t *self);

//**************VER PARAMETROS DE ESTA FUNCION*****************
void socket_release();

int socket_connect(socket_t *self, const char *host, const char *service);



#endif
