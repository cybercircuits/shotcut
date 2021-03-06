/*
 * Copyright (c) 2015 Meltytech, LLC
 * Author: Harald Hvaal <harald.hvaal@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UNDOHELPER_H
#define UNDOHELPER_H

#include "models/multitrackmodel.h"
#include <MltPlaylist.h>
#include <QString>
#include <QMap>
#include <QList>

class UndoHelper
{
public:
    UndoHelper(MultitrackModel & model);

    void recordBeforeState();
    void recordAfterState();
    void undoChanges();

private:
    void debugPrintState();

    enum ChangeFlags {
        NoChange = 0x0,
        ClipInfoModified = 0x1,
        XMLModified = 0x2,
        Moved = 0x4,
        Removed = 0x8
    };

    struct Info {
        int oldTrackIndex;
        int oldClipIndex;
        int newTrackIndex;
        int newClipIndex;
        bool isBlank;
        QString xml;
        int frame_in;
        int frame_out;

        int changes;
        Info()
            : oldTrackIndex(-1)
            , oldClipIndex(-1)
            , newTrackIndex(-1)
            , newClipIndex(-1)
            , isBlank(false)
            , frame_in(-1)
            , frame_out(-1)
            , changes(NoChange)
        {}
    };
    QMap<int,Info> m_state;
    QList<QPair<int,int> > m_clipsAdded;
    MultitrackModel & m_model;
};

#endif // UNDOHELPER_H
