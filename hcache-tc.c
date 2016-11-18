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

#ifdef HAVE_TC

#include "hcache-backend.h"
#include "mutt.h"
#include <tcbdb.h>

static void *
hcache_tc_open(const char *path)
{
  TCBDB *db = tcbdbnew();
  if (!db)
      return NULL;
  if (option(OPTHCACHECOMPRESS))
    tcbdbtune(db, 0, 0, 0, -1, -1, BDBTDEFLATE);
  if (tcbdbopen(db, path, BDBOWRITER | BDBOCREAT))
    return db;
  else
  {
#ifdef DEBUG
    int ecode = tcbdbecode (db);
    dprint (2, (debugfile, "tcbdbopen failed for %s: %s (ecode %d)\n", path, tcbdberrmsg (ecode), ecode));
#endif
    tcbdbdel(db);
    return NULL;
  }
}

static void *
hcache_tc_fetch(void *ctx, const char *key, size_t keylen)
{
  int sp;

  if (!ctx)
    return NULL;

  TCBDB *db = ctx;
  return tcbdbget(db, key, keylen, &sp);
}

static int
hcache_tc_store(void *ctx, const char *key, size_t keylen, void *data, size_t dlen)
{
  if (!ctx)
    return -1;

  TCBDB *db = ctx;
  return tcbdbput(db, key, keylen, data, dlen);
}

static int
hcache_tc_delete(void *ctx, const char *key, size_t keylen)
{
  if (!ctx)
    return -1;

  TCBDB *db = ctx;
  return tcbdbout(db, key, keylen);
}

static void
hcache_tc_close(void **ctx)
{
  if (!ctx || !*ctx)
    return;

  TCBDB *db = *ctx;
  if (!tcbdbclose(db))
  {
#ifdef DEBUG
    int ecode = tcbdbecode (db);
    dprint (2, (debugfile, "tcbdbclose failed: %s (ecode %d)\n", tcbdberrmsg (ecode), ecode));
#endif
  }
  tcbdbdel(db);
}

static const char *
hcache_tc_backend(void)
{
  return "tokyocabinet " _TC_VERSION;
}

HCACHE_BACKEND_OPS(tc)

#endif /* HAVE_TC */
