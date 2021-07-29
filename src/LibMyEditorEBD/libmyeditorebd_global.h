#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LIBMYEDITOREBD_LIB)
#  define LIBMYEDITOREBD_EXPORT Q_DECL_EXPORT
# else
#  define LIBMYEDITOREBD_EXPORT Q_DECL_IMPORT
# endif
#else
# define LIBMYEDITOREBD_EXPORT
#endif
