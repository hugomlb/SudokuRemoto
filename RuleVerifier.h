#ifndef _RULEVERIFIER_H_
#define  _RULEVERIFIER_H_

typedef struct {
  int numbers[10];
  int legalNumbers, totalNumbers;
} ruleVerifier_t;

void ruleVerifier_init(ruleVerifier_t *self);

void ruleVerifier_addNumber(ruleVerifier_t *self, int num);

void ruleVerifier_reset(ruleVerifier_t *self);

int ruleVerifier_verify(ruleVerifier_t *self);

void ruleVerifier_release(ruleVerifier_t *self);

#endif
