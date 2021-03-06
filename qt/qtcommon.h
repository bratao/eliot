/*****************************************************************************
 * Eliot
 * Copyright (C) 2010-2012 Olivier Teuli�re
 * Authors: Olivier Teuli�re <ipkiss @@ gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *****************************************************************************/

#ifndef QT_COMMON_H_
#define QT_COMMON_H_

#include "config.h"
#include <string>
#include <QString>
#include "encoding.h"

#if ENABLE_NLS
#   include <libintl.h>
#   define _(String) gettext(String)
// Apparently needed on Windows, where libintl.h defines sprintf
// as libintl_sprintf...
#   undef sprintf
#else
#   define _(String) String
#endif

// Convert to/from std::wstring
std::wstring wfq(const QString &q);
QString qfw(const wstring &wstr);
// Convert to/from local encoding
#define qfl(s) qfw(convertToWc(s))
#define lfq(s) convertToMb(wfq(s))
// Convert to/from utf-8 char*
#define qfu(s) QString::fromUtf8(string(s).c_str())
#define ufq(s) (s).toUtf8().data()
// Translation macro to use gettext
#ifdef __APPLE__
// On MacOSX, we force the encoding to UTF-8, because we have trouble
// detecting the current encoding properly (see call to
// bind_textdomain_codeset() in main.cpp)
#    define _q(s) qfu(_(s))
#else
#    define _q(s) QString::fromLocal8Bit(_(s))
#endif


class QObject;
class QWidget;

class QtCommon
{
public:
    /// Unit test for the macros above
    static void CheckConversions();

    /**
     * Kill the given widget, i.e. hide it, cut its signals, and mark it for deletion.
     * If a iSource object is given, signals from the source will be disconnected
     * from the widget to destroy as well.
     */
    static void DestroyObject(QWidget *ioWidgetToDestroy,
                              QObject *iSource = NULL);

    /**
     * Ask for a confirmation.
     * Return true if the user confirms, false otherwise.
     * By default, the question is "Do you want to continue?".
     * If a parent is provided, the window is centered on it.
     */
    static bool requestConfirmation(QString confoKey,
                                    QString iMsg,
                                    QString iQuestion = "",
                                    QWidget *iParent = 0);

};

#endif
