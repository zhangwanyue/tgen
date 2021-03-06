/*
 * The Shadow Simulator
 * See LICENSE for licensing information
 */

#ifndef TGEN_IO_H_
#define TGEN_IO_H_

#include "tgen.h"

typedef enum _TGenEvent {
    TGEN_EVENT_NONE = 0,
    TGEN_EVENT_READ = 1 << 0,
    TGEN_EVENT_WRITE = 1 << 1,
    TGEN_EVENT_DONE = 1 << 2,
} TGenEvent;

typedef TGenEvent (*TGenIO_notifyEventFunc)(gpointer data, gint descriptor, TGenEvent events);
typedef gboolean (*TGenIO_notifyCheckTimeoutFunc)(gpointer data, gint descriptor);

typedef struct _TGenIO TGenIO;

TGenIO* tgenio_new();
void tgenio_ref(TGenIO* io);
void tgenio_unref(TGenIO* io);

gboolean tgenio_register(TGenIO* io, gint descriptor, TGenIO_notifyEventFunc notify,
        TGenIO_notifyCheckTimeoutFunc checkTimeout, gpointer data, GDestroyNotify destructData);
void tgenio_deregister(TGenIO* io, gint descriptor);

gint tgenio_loopOnce(TGenIO* io, gint maxEvents);
void tgenio_checkTimeouts(TGenIO* io);
void tgenio_setEvents(TGenIO *io, gint descriptor, TGenEvent events);
gint tgenio_getEpollDescriptor(TGenIO* io);

#endif /* TGEN_IO_H_ */
