/*
 * Copyright (C) 2021 Georges Basile Stavracas Neto <georges.stavracas@gmail.com>
 *               2009-2012 Richard Hughes <richard@hughsie.com>
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

#include "config.h"

#include <glib-object.h>

#include <colord.h>

#include "cd-sample-widget.h"
#include "cd-sample-window.h"

static void     cd_sample_window_finalize	(GObject     *object);

#define CD_SAMPLE_WINDOW_PULSE_DELAY		80	/* ms */

/**
 * CdSampleWindowPrivate:
 *
 * Private #CdSampleWindow data
 **/
struct _CdSampleWindowPrivate
{
	GtkWidget			*sample_widget;
	GtkWidget			*progress_bar;
	guint				 pulse_id;
};

G_DEFINE_TYPE_WITH_CODE (CdSampleWindow, cd_sample_window, GTK_TYPE_WINDOW,
			 G_ADD_PRIVATE (CdSampleWindow))

/**
 * cd_sample_window_pulse_cb:
 **/
static gboolean
cd_sample_window_pulse_cb (CdSampleWindow *sample_window)
{
	CdSampleWindowPrivate *priv = cd_sample_window_get_instance_private (sample_window);
	gtk_progress_bar_pulse (GTK_PROGRESS_BAR (priv->progress_bar));
	return TRUE;
}

/**
 * cd_sample_window_set_fraction:
 * @sample_window: a valid #CdSampleWindow instance
 * @fraction: the fraction value to show, or -1 for pulsing.
 *
 * Sets the percentage value on the window.
 *
 * Since: 0.1.22
 **/
void
cd_sample_window_set_fraction (CdSampleWindow *sample_window,
			       gdouble fraction)
{
	CdSampleWindowPrivate *priv = cd_sample_window_get_instance_private (sample_window);

	/* make pulse */
	if (fraction == -1) {
		if (priv->pulse_id == 0) {
			priv->pulse_id = g_timeout_add (CD_SAMPLE_WINDOW_PULSE_DELAY,
							(GSourceFunc) cd_sample_window_pulse_cb,
							sample_window);
		}
		return;
	}

	/* no more pulsing */
	if (priv->pulse_id != 0) {
		g_source_remove (priv->pulse_id);
		priv->pulse_id = 0;
	}

	/* set static value */
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (priv->progress_bar), fraction);
}

/**
 * cd_sample_window_set_color:
 * @sample_window: a valid #CdSampleWindow instance
 * @color: the color
 *
 * Sets the window to a specific color.
 *
 * Since: 0.1.22
 **/
void
cd_sample_window_set_color (CdSampleWindow *sample_window,
			    const CdColorRGB *color)
{
	CdSampleWindowPrivate *priv = cd_sample_window_get_instance_private (sample_window);

	g_debug ("setting RGB: %f, %f, %f", color->R, color->G, color->B);
	cd_sample_widget_set_color (CD_SAMPLE_WIDGET (priv->sample_widget), color);

	/* force redraw */
	gtk_widget_set_visible (priv->sample_widget, FALSE);
	gtk_widget_set_visible (priv->sample_widget, TRUE);
}

/**
 * cd_sample_window_class_init:
 **/
static void
cd_sample_window_class_init (CdSampleWindowClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = cd_sample_window_finalize;
}

/**
 * cd_sample_window_init:
 **/
static void
cd_sample_window_init (CdSampleWindow *sample_window)
{
	CdSampleWindowPrivate *priv = cd_sample_window_get_instance_private (sample_window);
	GtkWindow *window = GTK_WINDOW (sample_window);
	GtkWidget *vbox;
	priv->sample_widget = cd_sample_widget_new ();
	priv->progress_bar = gtk_progress_bar_new ();

	/* pack in two widgets into the window */
	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_window_set_child (window, vbox);
	gtk_box_append (GTK_BOX (vbox), priv->sample_widget);
	gtk_box_append (GTK_BOX (vbox), priv->progress_bar);
	gtk_widget_set_size_request (priv->sample_widget, 400, 400);

	gtk_widget_set_cursor (GTK_WIDGET (window), gdk_cursor_new_from_name ("blank", NULL));
}

/**
 * cd_sample_window_finalize:
 **/
static void
cd_sample_window_finalize (GObject *object)
{
	CdSampleWindow *sample_window = CD_SAMPLE_WINDOW (object);
	CdSampleWindowPrivate *priv = cd_sample_window_get_instance_private (sample_window);

	if (priv->pulse_id != 0)
		g_source_remove (priv->pulse_id);

	G_OBJECT_CLASS (cd_sample_window_parent_class)->finalize (object);
}

/**
 * cd_sample_window_new:
 *
 * Return value: a new #CdSampleWindow object.
 *
 * Since: 0.1.22
 **/
GtkWindow *
cd_sample_window_new (void)
{
	CdSampleWindow *sample_window;
	sample_window = g_object_new (CD_TYPE_SAMPLE_WINDOW,
				      "decorated", FALSE,
				      "default-height", 400,
				      "default-width", 400,
				      "deletable", FALSE,
				      "destroy-with-parent", TRUE,
				      "icon-name", "icc-profile",
				      "resizable", FALSE,
				      "title", "calibration square",
				      NULL);
	return GTK_WINDOW (sample_window);
}
