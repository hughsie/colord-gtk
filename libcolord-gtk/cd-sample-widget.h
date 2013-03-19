/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2012 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

#if !defined (__COLORD_GTK_H_INSIDE__) && !defined (CD_COMPILATION)
#error "Only <colord-gtk.h> can be included directly."
#endif

#ifndef __CD_SAMPLE_WIDGET_H__
#define __CD_SAMPLE_WIDGET_H__

#include <gtk/gtk.h>
#include <colord.h>

G_BEGIN_DECLS

#define CD_TYPE_SAMPLE_WIDGET		(cd_sample_widget_get_type ())
#define CD_SAMPLE_WIDGET(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), CD_TYPE_SAMPLE_WIDGET, CdSampleWidget))
#define CD_SAMPLE_WIDGET_CLASS(obj)	(G_TYPE_CHECK_CLASS_CAST ((obj), CD_SAMPLE_WIDGET, CdSampleWidgetClass))
#define CD_IS_SAMPLE_WIDGET(obj)	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CD_TYPE_SAMPLE_WIDGET))
#define CD_IS_SAMPLE_WIDGET_CLASS(obj)	(G_TYPE_CHECK_CLASS_TYPE ((obj), EFF_TYPE_SAMPLE_WIDGET))
#define CD_SAMPLE_WIDGET_GET_CLASS	(G_TYPE_INSTANCE_GET_CLASS ((obj), CD_TYPE_SAMPLE_WIDGET, CdSampleWidgetClass))

typedef struct CdSampleWidget		CdSampleWidget;
typedef struct CdSampleWidgetClass	CdSampleWidgetClass;
typedef struct CdSampleWidgetPrivate	CdSampleWidgetPrivate;

struct CdSampleWidget
{
	GtkDrawingArea		 parent;
	CdSampleWidgetPrivate	*priv;
};

struct CdSampleWidgetClass
{
	GtkDrawingAreaClass	 parent_class;
};

GType		 cd_sample_widget_get_type	(void);
GtkWidget	*cd_sample_widget_new		(void);
void		 cd_sample_widget_set_color	(CdSampleWidget		*sample,
						 const CdColorRGB	*color);

G_END_DECLS

#endif
