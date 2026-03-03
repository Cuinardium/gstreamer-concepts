#include "gst/gstbus.h"
#include "gst/gstelement.h"
#include "gst/gstmessage.h"
#include "gst/gstparse.h"
#include <gst/gst.h>

int main(int argc, char *argv[])
{

  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Create the elements */
  /* el parse launch es una forma mas facil de crear un pipeline */
  /* el pipeline es un elemento que contiene todos los elementos de la aplicacion */
  /* el pipeline tambien es un bin por lo que utiliza las mismas funciones que el bin */
  pipeline = gst_parse_launch("playbin uri=https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm", NULL);


  /* Start playing */
  /* todos los pipelines tienen un estado que se puede cambiar con el set_state */
  /* en este caso estamos cambiando el estado a playing */
  gst_element_set_state(pipeline, GST_STATE_PLAYING);

  /* Wait until error or EOS */
  /* este llamdo es bloqueante y espera hasta que se reciba un mensaje de error o EOS */
  /* el laburo lo hace gstreamer en otro thread */
  bus = gst_element_get_bus(pipeline);
  msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

  if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
    g_printerr("An error occured!\n");
  }

  /* Free resources */
  gst_object_unref(msg);
  gst_object_unref(bus);
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);
  return EXIT_SUCCESS;
}

