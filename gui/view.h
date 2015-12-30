/*****************************************************************************
**
** Copyright (C) 2015 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 28/12/2015.
**
** This file is part of Q-UML (UML tool for Qt).
**
** Q-UML is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Q-UML is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.

** You should have received a copy of the GNU Lesser General Public License
** along with Q-UML.  If not, see <http://www.gnu.org/licenses/>.
**
*****************************************************************************/
#pragma once

#include <QGraphicsView>

#include <project/project_types.hpp>

namespace gui {

    /// The class View
    class View : public QGraphicsView
    {
        Q_OBJECT

    public:
        View(QWidget *parent = 0);

        void dropEvent(QDropEvent *de);
        void dragEnterEvent(QDragEnterEvent *de);
        void dragMoveEvent(QDragMoveEvent *de);
        void dragLeaveEvent(QDragLeaveEvent *de);

    public slots:
        void onCurrentProjectChanged(const project::SharedProject &p);

    private:
        project::SharedProject project() const;

        project::WeakProject m_Project;
    };

} // namespace gui
