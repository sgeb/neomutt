/*
 * Copyright (C) 1999-2001,2005,2009 Brendan Cully <brendan@kublai.com>
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

/* SASL PLAIN support */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include "mutt.h"
#include "imap_private.h"
#include "auth.h"

/* imap_auth_plain: SASL PLAIN support */
imap_auth_res_t imap_auth_plain (IMAP_DATA* idata, const char* method)
{
  char auth[STRING];
  char buf[STRING];
  size_t authlen;
  size_t buflen;

  if (mutt_account_getuser (&idata->conn->account))
    return IMAP_AUTH_FAILURE;
  if (mutt_account_getpass (&idata->conn->account))
    return IMAP_AUTH_FAILURE;

  mutt_message _("Logging in...");

  authlen = snprintf (auth, sizeof (auth), "%s%c%s%c%s",
      idata->conn->account.user, '\0', idata->conn->account.user, '\0',
      idata->conn->account.pass);

  buflen = snprintf (buf, sizeof (buf), "AUTHENTICATE PLAIN ");
  mutt_to_base64 ((unsigned char *)buf+buflen, (unsigned char *)auth,
      authlen, STRING-buflen);

  if (!imap_exec (idata, buf, IMAP_CMD_FAIL_OK | IMAP_CMD_PASS))
  {
    mutt_clear_error(); /* clear "Logging in...".  fixes #3524 */
    return IMAP_AUTH_SUCCESS;
  }

  mutt_error _("Login failed.");
  mutt_sleep (2);
  return IMAP_AUTH_FAILURE;
}
