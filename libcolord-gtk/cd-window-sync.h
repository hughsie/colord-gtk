/*
 * Copyright (C) 2012 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#if !defined (__COLORD_GTK_H_INSIDE__) && !defined (CD_COMPILATION)
#error "Only <colord-gtk.h> can be included directly."
#endif

#ifndef __CD_WINDOW_SYNC_H
#define __CD_WINDOW_SYNC_H

#include <glib-object.h>
#include <gio/gio.h>

G_BEGIN_DECLS

CdProfile	*cd_window_get_profile_sync		(CdWindow	*window,
							 GtkWidget	*widget,
							 GCancellable	*cancellable,
							 GError		**error);

G_END_DECLS

#endif /* __CD_WINDOW_SYNC_H */

