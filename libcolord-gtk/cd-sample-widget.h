/*
 * Copyright (C) 2012 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
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
