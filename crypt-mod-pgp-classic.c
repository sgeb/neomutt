/* 
 * Copyright (C) 2004 g10 Code GmbH
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

/* 
    This is a crytpo module wrapping the classic pgp code.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include "crypt-mod.h"
#include "pgp.h"

/**
 * crypt_mod_pgp_void_passphrase - XXX
 *
 * DESCRIPTION
 */
static void crypt_mod_pgp_void_passphrase (void)
{
  pgp_void_passphrase ();
}

/**
 * crypt_mod_pgp_valid_passphrase - XXX
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_pgp_valid_passphrase (void)
{
  return pgp_valid_passphrase ();
}

/**
 * crypt_mod_pgp_decrypt_mime - XXX
 * @a: YYY
 * @b: YYY
 * @c: YYY
 * @d: YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_pgp_decrypt_mime (FILE *a, FILE **b, BODY *c, BODY **d)
{
  return pgp_decrypt_mime (a, b, c, d);
}

/**
 * crypt_mod_pgp_application_handler - XXX
 * @m: YYY
 * @s: YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_pgp_application_handler (BODY *m, STATE *s)
{
  return pgp_application_pgp_handler (m, s);
}

/**
 * crypt_mod_pgp_findkeys - XXX
 * @adrlist:     YYY
 * @oppenc_mode: YYY
 *
 * DESCRIPTION
 *
 * Returns: char*
 */
static char *crypt_mod_pgp_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  return pgp_findKeys (adrlist, oppenc_mode);
}

/**
 * crypt_mod_pgp_sign_message - XXX
 * @a: YYY
 *
 * DESCRIPTION
 *
 * Returns: BODY*
 */
static BODY *crypt_mod_pgp_sign_message (BODY *a)
{
  return pgp_sign_message (a);
}

/**
 * crypt_mod_pgp_verify_one - XXX
 * @sigbdy: YYY
 * @s:      YYY
 * @tempf:  YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_pgp_verify_one (BODY *sigbdy, STATE *s, const char *tempf)
{
  return pgp_verify_one (sigbdy, s, tempf);
}

/**
 * crypt_mod_pgp_send_menu - XXX
 * @msg:    YYY
 * @redraw: YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_pgp_send_menu (HEADER *msg, int *redraw)
{
  return pgp_send_menu (msg, redraw);
}

/**
 * crypt_mod_pgp_encrypt_message - XXX
 * @a:       YYY
 * @keylist: YYY
 * @sign:    YYY
 *
 * DESCRIPTION
 *
 * Returns: BODY*
 */
static BODY *crypt_mod_pgp_encrypt_message (BODY *a, char *keylist, int sign)
{
  return pgp_encrypt_message (a, keylist, sign);
}

/**
 * crypt_mod_pgp_make_key_attachment - XXX
 * @tempf: YYY
 *
 * DESCRIPTION
 *
 * Returns: BODY*
 */
static BODY *crypt_mod_pgp_make_key_attachment (char *tempf)
{
  return pgp_make_key_attachment (tempf);
}

/**
 * crypt_mod_pgp_check_traditional - XXX
 * @fp:          YYY
 * @b:           YYY
 * @tagged_only: YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_pgp_check_traditional (FILE *fp, BODY *b, int tagged_only)
{
  return pgp_check_traditional (fp, b, tagged_only);
}

/**
 * crypt_mod_pgp_traditional_encryptsign - XXX
 * @a:       YYY
 * @flags:   YYY
 * @keylist: YYY
 *
 * DESCRIPTION
 *
 * Returns: BODY*
 */
static BODY *crypt_mod_pgp_traditional_encryptsign (BODY *a, int flags, char *keylist)
{
  return pgp_traditional_encryptsign (a, flags, keylist);
}

/**
 * crypt_mod_pgp_encrypted_handler - XXX
 * @m: YYY
 * @s: YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_pgp_encrypted_handler (BODY *m, STATE *s)
{
  return pgp_encrypted_handler (m, s);
}

/**
 * crypt_mod_pgp_invoke_getkeys - XXX
 * @addr: YYY
 *
 * DESCRIPTION
 */
static void crypt_mod_pgp_invoke_getkeys (ADDRESS *addr)
{
  pgp_invoke_getkeys (addr);
}

/**
 * crypt_mod_pgp_invoke_import - XXX
 * @fname: YYY
 *
 * DESCRIPTION
 */
static void crypt_mod_pgp_invoke_import (const char *fname)
{
  pgp_invoke_import (fname);
}

/**
 * crypt_mod_pgp_extract_keys_from_attachment_list - XXX
 * @fp:  YYY
 * @tag: YYY
 * @top: YYY
 *
 * DESCRIPTION
 */
static void crypt_mod_pgp_extract_keys_from_attachment_list (FILE *fp, int tag, BODY *top)
{
  pgp_extract_keys_from_attachment_list (fp, tag, top);
}

struct crypt_module_specs crypt_mod_pgp_classic =
  { APPLICATION_PGP,
    {
      NULL,			/* init */
      crypt_mod_pgp_void_passphrase,
      crypt_mod_pgp_valid_passphrase,
      crypt_mod_pgp_decrypt_mime,
      crypt_mod_pgp_application_handler,
      crypt_mod_pgp_encrypted_handler,
      crypt_mod_pgp_findkeys,
      crypt_mod_pgp_sign_message,
      crypt_mod_pgp_verify_one,
      crypt_mod_pgp_send_menu,
      NULL,

      crypt_mod_pgp_encrypt_message,
      crypt_mod_pgp_make_key_attachment,
      crypt_mod_pgp_check_traditional,
      crypt_mod_pgp_traditional_encryptsign,
      crypt_mod_pgp_invoke_getkeys,
      crypt_mod_pgp_invoke_import,
      crypt_mod_pgp_extract_keys_from_attachment_list,

      NULL,			/* smime_getkeys */
      NULL,			/* smime_verify_sender */
      NULL,			/* smime_build_smime_entity */
      NULL,			/* smime_invoke_import */
    }
  };
