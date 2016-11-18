/*
 * Copyright (C) 2004 Thomas Glanzmann <sithglan@stud.uni-erlangen.de>
 * Copyright (C) 2004 Tobias Werth <sitowert@stud.uni-erlangen.de>
 * Copyright (C) 2004 Brian Fundakowski Feldman <green@FreeBSD.org>
 * Copyright (C) 2016 Pietro Cerutti <gahr@gahr.ch>
 *
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program; if not, write to the Free Software
 *     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "config.h"

#ifdef HAVE_QDBM

#include "hcache-backend.h"
#include "mutt.h"
#include <depot.h>
#include <cabin.h>
#include <villa.h>

static void *
hcache_qdbm_open(const char *path)
{
  int flags = VL_OWRITER | VL_OCREAT;

  if (option(OPTHCACHECOMPRESS))
    flags |= VL_OZCOMP;

  return vlopen (path, flags, VL_CMPLEX);
}

static void *
hcache_qdbm_fetch(void *ctx, const char *key, size_t keylen)
{
  if (!ctx)
    return NULL;

  VILLA *db = ctx;
  return vlget(db, key, keylen, NULL);
}

static int
hcache_qdbm_store(void *ctx, const char *key, size_t keylen, void *data, size_t dlen)
{
  if (!ctx)
    return -1;

  VILLA *db = ctx;
  return vlput(db, key, keylen, data, dlen, VL_DOVER);
}

static int
hcache_qdbm_delete(void *ctx, const char *key, size_t keylen)
{
  if (!ctx)
    return -1;

  VILLA *db = ctx;
  return vlout(db, key, keylen);
}

static void
hcache_qdbm_close(void **ctx)
{
  if (!ctx || !*ctx)
    return;

  VILLA *db = *ctx;
  vlclose(db);
}

static const char *
hcache_qdbm_backend(void)
{
  return "qdbm " _QDBM_VERSION;
}

HCACHE_BACKEND_OPS(qdbm)

#endif /* HAVE_LMDB */
