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
    This is a crytpo module wrapping the gpgme based pgp code.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef CRYPT_BACKEND_GPGME

#include "crypt-mod.h"
#include "crypt-gpgme.h"

/**
 * crypt_mod_pgp_init - XXX
 *
 * DESCRIPTION
 */
static void crypt_mod_pgp_init (void)
{
  pgp_gpgme_init ();
}

/**
 * crypt_mod_pgp_void_passphrase - XXX
 *
 * DESCRIPTION
 */
static void crypt_mod_pgp_void_passphrase (void)
{
  /* Handled by gpg-agent.  */
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
  /* Handled by gpg-agent.  */
  return 1;
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
  return pgp_gpgme_decrypt_mime (a, b, c, d);
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
  return pgp_gpgme_application_handler (m, s);
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
  return pgp_gpgme_encrypted_handler (m, s);
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
  return pgp_gpgme_check_traditional (fp, b, tagged_only);
}

/**
 * crypt_mod_pgp_invoke_import - XXX
 * @fname: YYY
 *
 * DESCRIPTION
 */
static void crypt_mod_pgp_invoke_import (const char *fname)
{
  pgp_gpgme_invoke_import (fname);
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
  return pgp_gpgme_findkeys (adrlist, oppenc_mode);
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
  return pgp_gpgme_sign_message (a);
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
  return pgp_gpgme_verify_one (sigbdy, s, tempf);
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
  return pgp_gpgme_send_menu (msg, redraw);
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
  return pgp_gpgme_encrypt_message (a, keylist, sign);
}

#ifdef HAVE_GPGME_OP_EXPORT_KEYS
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
  return pgp_gpgme_make_key_attachment (tempf);
}
#endif

/**
 * crypt_mod_pgp_set_sender - XXX
 * @sender: YYY
 *
 * DESCRIPTION
 */
static void crypt_mod_pgp_set_sender (const char *sender)
{
  gpgme_set_sender (sender);
}

struct crypt_module_specs crypt_mod_pgp_gpgme =
  { APPLICATION_PGP,
    {
      /* Common.  */
      crypt_mod_pgp_init,
      crypt_mod_pgp_void_passphrase,
      crypt_mod_pgp_valid_passphrase,
      crypt_mod_pgp_decrypt_mime,
      crypt_mod_pgp_application_handler,
      crypt_mod_pgp_encrypted_handler,
      crypt_mod_pgp_findkeys,
      crypt_mod_pgp_sign_message,
      crypt_mod_pgp_verify_one,
      crypt_mod_pgp_send_menu,
      crypt_mod_pgp_set_sender,

      /* PGP specific.  */
      crypt_mod_pgp_encrypt_message,
#ifdef HAVE_GPGME_OP_EXPORT_KEYS
      crypt_mod_pgp_make_key_attachment,
#else
      NULL,
#endif
      crypt_mod_pgp_check_traditional,
      NULL, 			/* pgp_traditional_encryptsign  */
      NULL, /* pgp_invoke_getkeys  */
      crypt_mod_pgp_invoke_import,
      NULL, /* pgp_extract_keys_from_attachment_list  */

      NULL,			/* smime_getkeys */
      NULL,			/* smime_verify_sender */
      NULL,			/* smime_build_smime_entity */
      NULL,			/* smime_invoke_import */
    }
  };

#endif
