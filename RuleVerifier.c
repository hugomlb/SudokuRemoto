#include "RuleVerifier.h"

#define YES 0;
#define NO 1;

void ruleVerifier_init(ruleVerifier_t *self) {
  for (int i = 0; i < 10; i ++) {
    self -> numbers [i] = 0;
  }
  self -> legalNumbers = 0;
  self -> totalNumbers = 0;
}

void ruleVerifier_addNumber(ruleVerifier_t *self, int num) {
  self -> totalNumbers ++;
  if (self -> numbers [num] == 0) {
    self -> numbers [num] = num;
    self -> legalNumbers ++;
  }
}

int ruleVerifier_verify(ruleVerifier_t *self) {
  int onRule;
  if (self -> legalNumbers == self -> totalNumbers) {
    onRule = YES;
  } else {
    onRule = NO;
  }
  return onRule;
}
