/*
  Copyright (c) 2015 Pontus Sköldström, Bertrand Pechenot

  This file is part of libdd, the DoubleDecker hierarchical
  messaging system DoubleDecker is free software; you can
  redistribute it and/or modify it under the terms of the GNU Lesser
  General Public License (LGPL) version 2.1 as published by the Free
  Software Foundation.

  As a special exception, the Authors give you permission to link this
  library with independent modules to produce an executable,
  regardless of the license terms of these independent modules, and to
  copy and distribute the resulting executable under terms of your
  choice, provided that you also meet, for each linked independent
  module, the terms and conditions of the license of that module. An
  independent module is a module which is not derived from or based on
  this library.  If you modify this library, you must extend this
  exception to your version of the library.  DoubleDecker is
  distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
  License for more details.  You should have received a copy of the
  GNU Lesser General Public License along with this program.  If not,
  see <http://www.gnu.org/licenses/>.
*/

#ifndef _DDKEYS_H_
#define _DDKEYS_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <sodium.h>
#include <string.h>
#include <sodium.h>
#include <czmq.h>

typedef struct ddkeystate {
  unsigned char *publicpubkey;
  unsigned char *ddpubkey;
  unsigned char *privkey;
  unsigned char *pubkey;
  unsigned char *ddboxk;
  unsigned char *custboxk;
  unsigned char *pubboxk;
  char *hash;
  zhash_t *clientkeys;
} ddkeystate_t;

ddkeystate_t *read_ddkeys(char *filename, char *customer);
#endif
