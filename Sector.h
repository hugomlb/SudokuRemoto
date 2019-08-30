#ifndef _SECTOR_H_
#define  _SECTOR_H_

#include "Sector.h"
#include "Board.h"

typedef struct {
  cell_t *sectorStart;
} sector_t;

void sector_init(sector_t *self, board_t *pBoard, int rowNum, int columnNum);

int sector_checkRules(sector_t *self);

#endif
