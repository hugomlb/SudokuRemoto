#ifndef _PROTOCOLC_H_
#define  _PROTOCOLC_H_
#include "SocketC.h"
typedef struct {
  socketC_t socket;
  char answer[723];
} protocolC_t;

int protocolC_init(protocolC_t *self, const char *host, const char *serv);

int protocolC_receive(protocolC_t *self, char *buf, int lenght);

int protocolC_send(protocolC_t *self, char *buf, int lenght);

int protocolC_getAnswer(protocolC_t *self);

int protocolC_sendCmmd(protocolC_t *self, char *buf, int getAnsw, int lenght);

void protocolC_release(protocolC_t *self);

#endif
