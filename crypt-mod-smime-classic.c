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
    This is a crytpo module wrapping the classic smime code.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include "crypt-mod.h"
#include "smime.h"

/**
 * crypt_mod_smime_void_passphrase - XXX
 *
 * DESCRIPTION
 */
static void crypt_mod_smime_void_passphrase (void)
{
  smime_void_passphrase ();
}

/**
 * crypt_mod_smime_valid_passphrase - XXX
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_smime_valid_passphrase (void)
{
  return smime_valid_passphrase ();
}

/**
 * crypt_mod_smime_decrypt_mime - XXX
 * @a: YYY
 * @b: YYY
 * @c: YYY
 * @d: YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_smime_decrypt_mime (FILE *a, FILE **b, BODY *c, BODY **d)
{
  return smime_decrypt_mime (a, b, c, d);
}
static int crypt_mod_smime_application_handler (BODY *m, STATE *s)
{
  return smime_application_smime_handler (m, s);
}

/**
 * crypt_mod_smime_findkeys - XXX
 * @adrlist:     YYY
 * @oppenc_mode: YYY
 *
 * DESCRIPTION
 *
 * Returns: char*
 */
static char *crypt_mod_smime_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  return smime_findKeys (adrlist, oppenc_mode);
}

/**
 * crypt_mod_smime_sign_message - XXX
 * @a: YYY
 *
 * DESCRIPTION
 *
 * Returns: BODY*
 */
static BODY *crypt_mod_smime_sign_message (BODY *a)
{
  return smime_sign_message (a);
}

/**
 * crypt_mod_smime_verify_one - XXX
 * @sigbdy: YYY
 * @s:      YYY
 * @tempf:  YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_smime_verify_one (BODY *sigbdy, STATE *s, const char *tempf)
{
  return smime_verify_one (sigbdy, s, tempf);
}

/**
 * crypt_mod_smime_send_menu - XXX
 * @msg:    YYY
 * @redraw: YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_smime_send_menu (HEADER *msg, int *redraw)
{
  return smime_send_menu (msg, redraw);
}

/**
 * crypt_mod_smime_getkeys - XXX
 * @env: YYY
 *
 * DESCRIPTION
 */
static void crypt_mod_smime_getkeys (ENVELOPE *env)
{
  smime_getkeys (env);
}

/**
 * crypt_mod_smime_verify_sender - XXX
 * @h: YYY
 *
 * DESCRIPTION
 *
 * Returns: int
 */
static int crypt_mod_smime_verify_sender (HEADER *h)
{
  return smime_verify_sender (h);
}

static BODY *crypt_mod_smime_build_smime_entity (BODY *a, char *certlist)
{
  return smime_build_smime_entity (a, certlist);
}

/**
 * crypt_mod_smime_invoke_import - XXX
 * @infile:  YYY
 * @mailbox: YYY
 *
 * DESCRIPTION
 */
static void crypt_mod_smime_invoke_import (char *infile, char *mailbox)
{
  smime_invoke_import (infile, mailbox);
}


struct crypt_module_specs crypt_mod_smime_classic =
  { APPLICATION_SMIME,
    {
      NULL,			/* init */
      crypt_mod_smime_void_passphrase,
      crypt_mod_smime_valid_passphrase,
      crypt_mod_smime_decrypt_mime,
      crypt_mod_smime_application_handler,
      NULL,			/* encrypted_handler */
      crypt_mod_smime_findkeys,
      crypt_mod_smime_sign_message,
      crypt_mod_smime_verify_one,
      crypt_mod_smime_send_menu,
      NULL,

      NULL,			/* pgp_encrypt_message */
      NULL,			/* pgp_make_key_attachment */
      NULL,			/* pgp_check_traditional */
      NULL,			/* pgp_traditional_encryptsign */
      NULL,			/* pgp_invoke_getkeys */
      NULL,			/* pgp_invoke_import */
      NULL,			/* pgp_extract_keys_from_attachment_list */
      
      crypt_mod_smime_getkeys,
      crypt_mod_smime_verify_sender,
      crypt_mod_smime_build_smime_entity,
      crypt_mod_smime_invoke_import,
    }
  };
