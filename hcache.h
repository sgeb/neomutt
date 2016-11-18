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

#ifndef _HCACHE_H_
#define _HCACHE_H_ 1

#include "mutt.h"

struct header_cache;
typedef struct header_cache header_cache_t;

typedef int (*hcache_namer_t)(const char* path, char* dest, size_t dlen);

/**
 * mutt_hcache_open - open the connection to the header cache.
 *
 * @param path Location of the header cache (often as specified by the user).
 * @param folder Name of the folder containing the messages.
 * @param namer Optional (might be NULL) client-specific function to form the
 * final name of the hcache database file.
 * @return Pointer to a header_cache_t struct on success, NULL otherwise.
 */
header_cache_t *
mutt_hcache_open(const char *path, const char *folder, hcache_namer_t namer);

/**
 * mutt_hcache_close - close the connection to the header cache.
 *
 * @param h Pointer to the header_cache_t structure got by mutt_hcache_open.
 */
void
mutt_hcache_close(header_cache_t *h);

/**
 * mutt_hcache_fetch - fetch and validate a  message's header from the cache.
 *
 * @param h Pointer to the header_cache_t structure got by mutt_hcache_open.
 * @param key Message identification string.
 * @param keylen Length of the string pointed to by key.
 * @return Pointer to the data if found and valid, NULL otherwise.
 * @note This function performs a check on the validity of the data found by
 * comparing it with the crc value of the header_cache_t structure.
 */
void *
mutt_hcache_fetch(header_cache_t *h, const char *key, size_t keylen);

/**
 * mutt_hcache_fetch_raw - fetch a message's header from the cache.
 *
 * @param h Pointer to the header_cache_t structure got by mutt_hcache_open.
 * @param key Message identification string.
 * @param keylen Length of the string pointed to by key.
 * @return Pointer to the data if found, NULL otherwise.
 * @note This function does not perform any check on the validity of the data
 * found.
 */
void *
mutt_hcache_fetch_raw(header_cache_t *h, const char *key, size_t keylen);

/**
 * mutt_hcache_restore - restore a HEADER from data retrieved from the cache.
 *
 * @param d Data retrieved using mutt_hcache_fetch or mutt_hcache_fetch_raw.
 * @return Pointer to the restored header (cannot be NULL).
 * @note The returned HEADER must be free'd by caller code with
 * mutt_free_header.
 */
HEADER *
mutt_hcache_restore(const unsigned char *d);

/**
 * mutt_hcache_store - store a HEADER along with a validity datum.
 *
 * @param h Pointer to the header_cache_t structure got by mutt_hcache_open.
 * @param key Message identification string.
 * @param keylen Length of the string pointed to by key.
 * @param header Message header to store.
 * @param uidvalidity IMAP-specific UIDVALIDITY value, or 0 to use the current
 * time.
 * @return 0 on success, -1 otherwise.
 */
int
mutt_hcache_store(header_cache_t *h, const char *key, size_t keylen,
                  HEADER *header, unsigned int uidvalidity);

/**
 * mutt_hcache_store_raw - store a key / data pair.
 *
 * @param h Pointer to the header_cache_t structure got by mutt_hcache_open.
 * @param key Message identification string.
 * @param keylen Length of the string pointed to by key.
 * @param data Payload to associate with key.
 * @param dlen Length of the buffer pointed to by the @data parameter.
 * @return 0 on success, -1 otherwise.
 */
int
mutt_hcache_store_raw(header_cache_t *h, const char* key, size_t keylen, 
                      void* data, size_t dlen);

/**
 * mutt_hcache_delete - delete a key / data pair.
 *
 * @param h Pointer to the header_cache_t structure got by mutt_hcache_open.
 * @param key Message identification string.
 * @param keylen Length of the string pointed to by key.
 * @return 0 on success, -1 otherwise.
 */
int
mutt_hcache_delete(header_cache_t *h, const char *key, size_t keylen);

/**
 * mutt_hcache_backend - get a backend-specific identification string.
 *
 * @return String describing the currently used hcache backend.
 */
const char *
mutt_hcache_backend(void);

/**
 * mutt_hcache_is_valid_backend
 *
 * @param s String identifying a backend.
 * @return 1 if s is recognized as a valid backend, 0 otherwise.
 */
int
mutt_hcache_is_valid_backend(const char *s);


#endif /* _HCACHE_H_ */
