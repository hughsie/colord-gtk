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

#include "config.h"

#include <gtk/gtk.h>
#include <math.h>
#include <colord.h>

#include "cd-sample-widget.h"

G_DEFINE_TYPE (CdSampleWidget, cd_sample_widget, GTK_TYPE_DRAWING_AREA);
#define CD_SAMPLE_WIDGET_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CD_TYPE_SAMPLE_WIDGET, CdSampleWidgetPrivate))

struct CdSampleWidgetPrivate
{
	cairo_t			*cr;
	CdColorRGB		 color;
};

enum
{
	PROP_0,
	PROP_COLOR,
};

/**
 * up_sample_get_property:
 **/
static void
up_sample_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	CdSampleWidget *sample = CD_SAMPLE_WIDGET (object);
	switch (prop_id) {
	case PROP_COLOR:
		g_value_set_boxed (value, &sample->priv->color);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

/**
 * up_sample_set_property:
 **/
static void
up_sample_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	CdColorRGB *tmp;
	CdSampleWidget *sample = CD_SAMPLE_WIDGET (object);

	switch (prop_id) {
	case PROP_COLOR:
		tmp = g_value_get_boxed (value);
		cd_color_rgb_copy (tmp, &sample->priv->color);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}

	/* refresh widget */
	gtk_widget_hide (GTK_WIDGET (sample));
	gtk_widget_show (GTK_WIDGET (sample));
}

/**
 * cd_sample_widget_draw_rounded_rectangle:
 **/
static void
cd_sample_widget_draw_rounded_rectangle (cairo_t *cr,
					 gdouble x,
					 gdouble y,
					 gdouble width,
					 gdouble height,
					 gdouble corner_radius)
{
	gdouble aspect = width / height;
	gdouble radius = corner_radius / aspect;
	gdouble degrees = M_PI / 180.0;

	cairo_new_sub_path (cr);
	cairo_arc (cr, x + width - radius, y + radius,
		   radius, -90 * degrees, 0 * degrees);
	cairo_arc (cr, x + width - radius, y + height - radius,
		   radius, 0 * degrees, 90 * degrees);
	cairo_arc (cr, x + radius, y + height - radius,
		   radius, 90 * degrees, 180 * degrees);
	cairo_arc (cr, x + radius, y + radius,
		   radius, 180 * degrees, 270 * degrees);
	cairo_close_path (cr);
}

/**
 * cd_sample_widget_draw:
 **/
static gboolean
cd_sample_widget_draw (GtkWidget *widget, cairo_t *cr)
{
	CdColorRGB *color;
	CdSampleWidget *sample = CD_SAMPLE_WIDGET (widget);
	GtkAllocation allocation;

	g_return_val_if_fail (CD_IS_SAMPLE_WIDGET (sample), FALSE);

	color = &sample->priv->color;
	gtk_widget_get_allocation (widget, &allocation);
	cairo_save (cr);
	cairo_set_source_rgb (cr, color->R, color->G, color->B);
	cd_sample_widget_draw_rounded_rectangle (cr, 0, 0,
						 allocation.width,
						 allocation.height,
						 10.5);
	cairo_fill_preserve (cr);
	cairo_set_source_rgba (cr, 0.5, 0.5, 0.5, 1.0);
	cairo_set_line_width (cr, 1.0);
	cairo_stroke (cr);
	cairo_restore (cr);
	return FALSE;
}

/**
 * cd_sample_window_enter_notify_event_cb:
 **/
static gboolean
cd_sample_window_enter_notify_event_cb (GtkWidget *widget,
					GdkEvent *event,
					gpointer user_data)
{
	GdkCursor *cursor;
	GdkWindow *window;

	cursor = gdk_cursor_new (GDK_BLANK_CURSOR);
	window = gtk_widget_get_window (widget);
	gdk_window_set_cursor (window, cursor);
	g_object_unref (cursor);
	return TRUE;
}

/**
 * cd_sample_window_leave_notify_event_cb:
 **/
static gboolean
cd_sample_window_leave_notify_event_cb (GtkWidget *widget,
					GdkEvent *event,
					gpointer user_data)
{
	GdkCursor *cursor;
	GdkWindow *window;

	cursor = gdk_cursor_new (GDK_ARROW);
	window = gtk_widget_get_window (widget);
	gdk_window_set_cursor (window, cursor);
	g_object_unref (cursor);
	return TRUE;
}

/**
 * cd_sample_widget_class_init:
 **/
static void
cd_sample_widget_class_init (CdSampleWidgetClass *class)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (class);
	GObjectClass *object_class = G_OBJECT_CLASS (class);

	widget_class->draw = cd_sample_widget_draw;
	object_class->get_property = up_sample_get_property;
	object_class->set_property = up_sample_set_property;

	g_type_class_add_private (class, sizeof (CdSampleWidgetPrivate));

	/* properties */
	g_object_class_install_property (object_class,
					 PROP_COLOR,
					 g_param_spec_boxed ("color", NULL, NULL,
							     CD_TYPE_COLOR_RGB,
							     G_PARAM_READWRITE));
}

/**
 * cd_example_window_realize_cb:
 **/
static void
cd_example_window_realize_cb (GtkWidget *widget, gpointer user_data)
{
	GdkWindow *window;

	/* hide the mouse pointer when over the calibration widget */
	window = gtk_widget_get_window (widget);
	g_assert (window != NULL);
	gdk_window_set_events (window, GDK_EXPOSURE_MASK |
				       GDK_ENTER_NOTIFY_MASK |
				       GDK_LEAVE_NOTIFY_MASK);
}

/**
 * cd_sample_widget_init:
 **/
static void
cd_sample_widget_init (CdSampleWidget *sample)
{
	sample->priv = CD_SAMPLE_WIDGET_GET_PRIVATE (sample);
	cd_color_rgb_set (&sample->priv->color, 1.0, 1.0, 1.0);

	g_signal_connect (sample, "realize",
			  G_CALLBACK (cd_example_window_realize_cb), NULL);
	g_signal_connect (sample, "enter-notify-event",
			  G_CALLBACK (cd_sample_window_enter_notify_event_cb), NULL);
	g_signal_connect (sample, "leave-notify-event",
			  G_CALLBACK (cd_sample_window_leave_notify_event_cb), NULL);
}

/**
 * cd_sample_widget_set_color:
 * @sample: This class instance
 * @color: A color
 *
 * Sets the color for the sample widget
 *
 * Since: 0.1.24
 **/
void
cd_sample_widget_set_color (CdSampleWidget *sample, const CdColorRGB *color)
{
	g_return_if_fail (color != NULL);
	g_return_if_fail (CD_IS_SAMPLE_WIDGET (sample));

	/* set new color and refresh */
	cd_color_rgb_copy (color, &sample->priv->color);
	gtk_widget_queue_draw (GTK_WIDGET (sample));
}

/**
 * cd_sample_widget_new:
 *
 * Return value: A new #CdSampleWidget object.
 *
 * Since: 0.1.24
 **/
GtkWidget *
cd_sample_widget_new (void)
{
	return g_object_new (CD_TYPE_SAMPLE_WIDGET, NULL);
}
