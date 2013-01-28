/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2009-2012 Richard Hughes <richard@hughsie.com>
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

#define CD_SAMPLE_WINDOW_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CD_TYPE_SAMPLE_WINDOW, CdSampleWindowPrivate))
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

G_DEFINE_TYPE (CdSampleWindow, cd_sample_window, GTK_TYPE_WINDOW)

/**
 * cd_sample_window_pulse_cb:
 **/
static gboolean
cd_sample_window_pulse_cb (CdSampleWindow *sample_window)
{
	gtk_progress_bar_pulse (GTK_PROGRESS_BAR (sample_window->priv->progress_bar));
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
	CdSampleWindowPrivate *priv = sample_window->priv;

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
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (sample_window->priv->progress_bar), fraction);
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
	g_debug ("setting RGB: %f, %f, %f", color->R, color->G, color->B);
	cd_sample_widget_set_color (CD_SAMPLE_WIDGET (sample_window->priv->sample_widget), color);

	/* force redraw */
	gtk_widget_set_visible (sample_window->priv->sample_widget, FALSE);
	gtk_widget_set_visible (sample_window->priv->sample_widget, TRUE);
}

/**
 * cd_sample_window_class_init:
 **/
static void
cd_sample_window_class_init (CdSampleWindowClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = cd_sample_window_finalize;
	g_type_class_add_private (klass, sizeof (CdSampleWindowPrivate));
}

/**
 * cd_sample_window_enter_notify_cb:
 **/
static gboolean
cd_sample_window_enter_notify_cb (GtkWidget *widget, GdkEventCrossing *event, CdSampleWindow *sample_window)
{
	GdkCursor *cursor;

	/* hide cursor */
	cursor = gdk_cursor_new_for_display (gdk_display_get_default (), GDK_BLANK_CURSOR);
	gdk_window_set_cursor (gtk_widget_get_window (widget), cursor);
	g_object_unref (cursor);

	return FALSE;
}

/**
 * cd_sample_window_leave_notify_cb:
 **/
static gboolean
cd_sample_window_leave_notify_cb (GtkWidget *widget, GdkEventCrossing *event,
				   CdSampleWindow *sample_window)
{
	/* restore cursor */
	gdk_window_set_cursor (gtk_widget_get_window (widget), NULL);
	return FALSE;
}

static gboolean
cd_sample_window_visibility_notify_cb (GtkWidget *widget, GdkEventVisibility *event,
					CdSampleWindow *sample_window)
{
	/* reshow it */
	gtk_window_present (GTK_WINDOW (widget));
	return TRUE;
}

/**
 * cd_sample_window_init:
 **/
static void
cd_sample_window_init (CdSampleWindow *sample_window)
{
	GtkWindow *window = GTK_WINDOW (sample_window);
	GtkWidget *vbox;
	sample_window->priv = CD_SAMPLE_WINDOW_GET_PRIVATE (sample_window);
	sample_window->priv->sample_widget = cd_sample_widget_new ();
	sample_window->priv->progress_bar = gtk_progress_bar_new ();

	/* pack in two widgets into the window */
	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add (GTK_CONTAINER (sample_window), vbox);
	gtk_box_pack_start (GTK_BOX (vbox), sample_window->priv->sample_widget, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), sample_window->priv->progress_bar, FALSE, FALSE, 0);
	gtk_widget_set_size_request (sample_window->priv->sample_widget, 400, 400);
	gtk_widget_show_all (vbox);

	/* be clever and allow the colorimeter to do it's job */
	g_signal_connect (window, "enter-notify-event",
			  G_CALLBACK(cd_sample_window_enter_notify_cb),
			  sample_window);
	g_signal_connect (window, "leave-notify-event",
			  G_CALLBACK(cd_sample_window_leave_notify_cb),
			  sample_window);
	g_signal_connect (window, "visibility-notify-event",
			  G_CALLBACK(cd_sample_window_visibility_notify_cb),
			  sample_window);

	/* show on all virtual desktops */
	gtk_window_stick (window);
}

/**
 * cd_sample_window_finalize:
 **/
static void
cd_sample_window_finalize (GObject *object)
{
	CdSampleWindow *sample_window = CD_SAMPLE_WINDOW (object);
	CdSampleWindowPrivate *priv = sample_window->priv;

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
				      "accept-focus", FALSE,
				      "decorated", FALSE,
				      "default-height", 400,
				      "default-width", 400,
				      "deletable", FALSE,
				      "destroy-with-parent", TRUE,
				      "icon-name", "icc-profile",
				      "resizable", FALSE,
				      "skip-pager-hint", TRUE,
				      "skip-taskbar-hint", TRUE,
				      "title", "calibration square",
				      "type-hint", GDK_WINDOW_TYPE_HINT_SPLASHSCREEN,
				      "urgency-hint", TRUE,
				      NULL);
	return GTK_WINDOW (sample_window);
}
