/* tishot - capture d'écran d'une TI-Nspire via USB
 * Copyright (C) 2026 Foxof7207
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. This program is distributed WITHOUT ANY WARRANTY; see LICENSE.
 */
#include <stdio.h>
#include <stdint.h>
#include <ticonv.h>
#include <ticables.h>
#include <tifiles.h>
#include <ticalcs.h>
int main(void){
  ticables_library_init(); tifiles_library_init(); ticalcs_library_init();
  CableHandle*c=ticables_handle_new(CABLE_USB,PORT_1);
  if(!c){fprintf(stderr,"cable\n");return 1;}
  ticables_options_set_timeout(c,100);
  CalcHandle*h=ticalcs_handle_new(CALC_NSPIRE);
  if(!h){fprintf(stderr,"calc\n");return 1;}
  int e=ticalcs_cable_attach(h,c); fprintf(stderr,"attach=%d\n",e); if(e)return 2; e=ticalcs_calc_isready(h); fprintf(stderr,"ready=%d\n",e);
  CalcScreenCoord sc; uint8_t*bm=NULL;
  e=ticalcs_calc_recv_screen_rgb888(h,&sc,&bm);
  if(e||!bm){fprintf(stderr,"recv %d\n",e);return 3;}
  fprintf(stderr,"%ux%u\n",sc.width,sc.height);
  FILE*f=fopen("screen.ppm","wb"); fprintf(f,"P6\n%u %u\n255\n",sc.width,sc.height);
  fwrite(bm,3,sc.width*sc.height,f); fclose(f);
  ticalcs_free_screen(bm); ticalcs_cable_detach(h); ticalcs_handle_del(h); ticables_handle_del(c);
  return 0;}
