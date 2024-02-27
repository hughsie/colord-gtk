/*
 * Copyright (C) 2010-2012 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#if !defined (__COLORD_GTK_H_INSIDE__) && !defined (CD_COMPILATION)
#error "Only <colord-gtk.h> can be included directly."
#endif

#ifndef __CD_SAMPLE_WINDOW_H
#define __CD_SAMPLE_WINDOW_H

#include <glib-object.h>
#include <gtk/gtk.h>
#include <colord.h>

G_BEGIN_DECLS

#define CD_TYPE_SAMPLE_WINDOW		(cd_sample_window_get_type ())
#define CD_SAMPLE_WINDOW(o)		(G_TYPE_CHECK_INSTANCE_CAST ((o), CD_TYPE_SAMPLE_WINDOW, CdSampleWindow))
#define CD_IS_SAMPLE_WINDOW(o)		(G_TYPE_CHECK_INSTANCE_TYPE ((o), CD_TYPE_SAMPLE_WINDOW))

typedef struct _CdSampleWindowPrivate	CdSampleWindowPrivate;
typedef struct _CdSampleWindow		CdSampleWindow;
typedef struct _CdSampleWindowClass	CdSampleWindowClass;

struct _CdSampleWindow
{
	 GtkWindow			 parent;
	 CdSampleWindowPrivate		*priv;
};

struct _CdSampleWindowClass
{
	GtkWindowClass			 parent_class;
};

GType		 cd_sample_window_get_type		(void);
GtkWindow	*cd_sample_window_new			(void);
void		 cd_sample_window_set_color		(CdSampleWindow		*sample_window,
							 const CdColorRGB	*color);
void		 cd_sample_window_set_fraction		(CdSampleWindow		*sample_window,
							 gdouble		 fraction);

G_END_DECLS

#endif /* __CD_SAMPLE_WINDOW_H */

