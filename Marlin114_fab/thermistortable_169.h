/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

  
//R@25C = 100k, Beta = 4750 K FABtotum
const short temptable_169[][2] PROGMEM = {
{	13*OVERSAMPLENR 	,	300	},	
{	14*OVERSAMPLENR 	,	295	},	
{	16*OVERSAMPLENR 	,	290	},	
{	17*OVERSAMPLENR 	,	285	},	
{	18*OVERSAMPLENR 	,	280	},	
{	19*OVERSAMPLENR 	,	275	},	
{	21*OVERSAMPLENR 	,	270	},	
{	22*OVERSAMPLENR 	,	265	},	
{	24*OVERSAMPLENR 	,	260	},	
{	26*OVERSAMPLENR 	,	255	},	
{	28*OVERSAMPLENR 	,	250	},	
{	31*OVERSAMPLENR	  ,	245	},	
{	33*OVERSAMPLENR	  ,	240	},	
{	36*OVERSAMPLENR	  ,	235	},	
{	40*OVERSAMPLENR	  ,	230	},	
{	43*OVERSAMPLENR	  ,	225	},	
{	47*OVERSAMPLENR	  ,	220	},	
{	52*OVERSAMPLENR	  ,	215	},	
{	57*OVERSAMPLENR	  ,	210	},	
{	62*OVERSAMPLENR	  ,	205	},	
{	68*OVERSAMPLENR	  ,	200	},	
{	75*OVERSAMPLENR	  ,	195	},	
{	83*OVERSAMPLENR	  ,	190	},	
{	91*OVERSAMPLENR	  ,	185	},	
{	101*OVERSAMPLENR	,	180	},	
{	112*OVERSAMPLENR	,	175	},	
{	123*OVERSAMPLENR	,	170	},	
{	137*OVERSAMPLENR	,	165	},	
{	152*OVERSAMPLENR	,	160	},	
{	168*OVERSAMPLENR	,	155	},	
{	187*OVERSAMPLENR	,	150	},	
{	207*OVERSAMPLENR	,	145	},	
{	230*OVERSAMPLENR	,	140	},	
{	254*OVERSAMPLENR	,	135	},	
{	282*OVERSAMPLENR	,	130	},	
{	312*OVERSAMPLENR	,	125	},	
{	344*OVERSAMPLENR	,	120	},	
{	379*OVERSAMPLENR	,	115	},	
{	416*OVERSAMPLENR	,	110	},	
{	455*OVERSAMPLENR	,	105	},	
{	496*OVERSAMPLENR	,	100	},	
{	539*OVERSAMPLENR	,	95	},	
{	582*OVERSAMPLENR	,	90	},	
{	625*OVERSAMPLENR	,	85	},	
{	668*OVERSAMPLENR	,	80	},	
{	710*OVERSAMPLENR	,	75	},	
{	750*OVERSAMPLENR	,	70	},	
{	787*OVERSAMPLENR	,	65	},	
{	822*OVERSAMPLENR	,	60	},	
{	854*OVERSAMPLENR	,	55	},	
{	882*OVERSAMPLENR	,	50	},	
{	907*OVERSAMPLENR	,	45	},	
{	929*OVERSAMPLENR	,	40	},	
{	947*OVERSAMPLENR	,	35	},	
{	963*OVERSAMPLENR	,	30	},	
{	976*OVERSAMPLENR	,	25	},	
{	986*OVERSAMPLENR	,	20	},	
{	995*OVERSAMPLENR	,	15	},	
{	1002*OVERSAMPLENR	,	10	},	
{	1007*OVERSAMPLENR	,	5	},	
{	1012*OVERSAMPLENR	,	0	}	//safety
};
