/*
 * XVGA.h
 *
 *  Created on: Nov 20, 2014
 *      Author: Kurt Metzger
 */

#ifndef XVGA_H_
#define XVGA_H_

#define BLUE 2

void XVGAinit(Uint16);
void GoTo(Uint16 x, Uint16 y);
void Draw(Uint16 color, Uint16 x, Uint16 y);
void InitSpi(void);
void InitSystem(void);
void ConfigPort(void);

#endif /* XVGA_H_ */
